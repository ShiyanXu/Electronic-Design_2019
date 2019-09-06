#include "mpu9250.h"
#include "myiic.h"
#include "delay.h"
#include "usart.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "math.h"

static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};
#define q30  1073741824.0f
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
float Pitch,Roll,Yaw;
float temp;
unsigned long sensor_timestamp;//mask of sensors read from fifo
short gyro[3],accel[3],sensors;
unsigned char more;						 //remaining packets in fifo														 
long quat[4];
//误差纠正
#define  Pitch_error  1.0
#define  Roll_error   -2.0
#define  Yaw_error    0.0
																					 
																					 
//带DMP的9250初始化
u8 MPU_DMP_Init(void){
	printf("\r\nstrating DMP init...\r\n");
	printf("init via inv_mpu.c...\r\n");
		if(!mpu_init())
		printf("inv_mpu.c ready.\r\n");
	else
		printf("inv_mpu.c failed.\r\n");
	mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
	mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
	mpu_set_sample_rate(100);//采样频率
	dmp_load_motion_driver_firmware();
	dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
	dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
            DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
            DMP_FEATURE_GYRO_CAL);
	dmp_set_fifo_rate(100);
	if(!mpu_set_dmp_state(1))
		printf("MPU_DMP_Init() finshed.\r\n");
	else
		printf("MPU_DMP_Init() failed.\r\n");
	printf("Running self test.\r\n");
	run_self_test();
	printf("\r\nMPU with DMP init succeed.\r\n");
	
	

}

void MPU_Data_Push_by_DMP(void){
	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);	 
  if (sensors & INV_WXYZ_QUAT )
	{
			q0 = quat[0] / q30;
			q1 = quat[1] / q30;
			q2 = quat[2] / q30;
			q3 = quat[3] / q30;
			
			Pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3 + Pitch_error; // pitch
			Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3 + Roll_error; // roll
			Yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3 + Yaw_error;//Yaw


			
	}
	
	
	
	
	
}

static void run_self_test(void)
{
    int result;

    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) 
    {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
		printf("setting bias succesfully.....\r\n");
    }
	else
	{
		printf("bias has not been modified....\r\n");
	}
    
}

static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static  unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;
    return scalar;
}




//不带9250的初始化MPU9250
//返回值:0,成功
//    其他,错误代码
u8 MPU9250_Init(void)
{
	u8 res=0;
	IIC_Init();     //初始化IIC总线

	printf("Reset..............\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU9250

	delay_ms(100);  //延时100ms
	printf("Wakeup.............\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU9250
	MPU_Set_Gyro_Fsr(3);					        	//陀螺仪传感器,±2000dps
	MPU_Set_Accel_Fsr(0);					       	 	//加速度传感器,±2g
	MPU_Set_Rate(50);						       	 	//设置采样率50Hz
	printf("Disable INT........\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
	printf("Disable SlaveMode..\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
	printf("Disable FIFO.......\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	printf("INT low............\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INT引脚低电平有效，开启bypass模式，可以直接读取磁力计
	
	printf("Reading ID.........\r\n");
	res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  //读取MPU6500的ID#
	switch(res){
		case 0x73: printf("MPU9250 Modle ID:0x%2x\r\n",res); break;
		case 0x71: printf("MPU9250 on Chip ID:0x%2x\r\n",res);break;
		case 0x69: printf("MPU6050 Modle ID:0x%2x\r\n",res);break;
		default: printf("unknown ID:0x%2x\r\n",res);return 1; 
	}
	
	res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			//读取AK8963 ID  
	if(res==AK8963_ID)
	{
			MPU_Write_Byte(AK8963_ADDR,MAG_CNTL2,0X01);		//复位AK8963
	delay_ms(50);
			MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11);		//设置AK8963为单次测量
	}else{
		printf("\r\nAK8963 init failed.\r\n");
		return 1;
	}
	printf("\r\n");
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//设置CLKSEL,PLL X轴为参考
	MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//加速度与陀螺仪都工作
	MPU_Set_Rate(50);						       	//设置采样率为50Hz   

	

	return 0;
}

void MPU_Data_Push_Without_DMP(void){
	//原始数据
		short aacx,aacy, aacz, gyrox, gyroy, gyroz, megx, megy, megz, roll, pitch, yaw;
	  short mpu9250_temp,Mag[3],Gyro[3],Acc[3];	
		mpu9250_temp = MPU_Get_Temperature();//mpu9250获取温度
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
		MPU_Get_Magnetometer(&megx,&megy,&megz);

		printf("Gyro:%6d, %6d, %6d\r\n",gyrox,gyroy,gyroz);
		printf("Acc :%6d, %6d, %6d\r\n",aacx,aacy,aacz);
		printf("Mag :%6d, %6d, %6d\r\n",megx,megy,megz);
		printf("temp:%6d          \r\n",mpu9250_temp);
	
}

//设置MPU9250陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
	
	// fsr =0  量程范围 250dps
	// fsr =1  量程范围 500dps
	// fsr =2  量程范围 1000dps
	// fsr =3  量程范围 2000dps
}
//设置MPU9250加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}

//设置MPU9250的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);//设置数字低通滤波器  
}

//设置MPU9250的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return temp*100;;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res; 
	res=MPU_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

//得到磁力计值(原始值)
//mx,my,mz:磁力计x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Magnetometer(short *mx,short *my,short *mz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(AK8963_ADDR,MAG_XOUT_L,6,buf);
	if(res==0)
	{
		*mx=((u16)buf[1]<<8)|buf[0];  
		*my=((u16)buf[3]<<8)|buf[2];  
		*mz=((u16)buf[5]<<8)|buf[4];
	} 	
    MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); //AK8963每次读完以后都需要重新设置为单次测量模式
    return res;;
}

//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    u8 i;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte(buf[i]);  //发送数据
        if(IIC_Wait_Ack())      //等待ACK
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
} 

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答
	  IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); //发送器件地址+读命令
    IIC_Wait_Ack();             //等待应答
    while(len)
    {
        if(len==1)*buf=IIC_Read_Byte(0);//读数据,发送nACK 
				else *buf=IIC_Read_Byte(1);		//读数据,发送ACK  
				len--;
				buf++;  
    }
    IIC_Stop();                 //产生一个停止条件
    return 0;       
}

//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data)
{
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答
    IIC_Send_Byte(data);        //发送数据
    if(IIC_Wait_Ack())          //等待ACK
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}

//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 MPU_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    IIC_Wait_Ack();             //等待应答
    IIC_Send_Byte(reg);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答
	  IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); //发送器件地址+读命令
    IIC_Wait_Ack();             //等待应答
    res=IIC_Read_Byte(0);		    //读数据,发送nACK  
    IIC_Stop();                 //产生一个停止条件
    return res;  
}
