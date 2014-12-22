/******************************************************
 * adc_thread.cpp
 *
 *  Created on: 2014-12-22
 *      Author: luoxiaofeng
 * 功能简要：
 *  	采集AD线程；
 *
 ******************************************************/

#include "ADC_thread.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include<QFile>
#include<stdio.h>
#define CMD_PORT_SELECTED 0x0C
#define CMD_BIT_SELECTED 0x0D
int fd;  //ID
int fd1;
ADC_thread *pADC_thread;

ADC_thread::ADC_thread()
{

    QFile f("/dev/spidev0.0");
    if (f.exists())
    {
        fd = open("/dev/spidev0.0", O_RDWR);
        if (fd < 0)
        {
            printf("error !open ADC device !\n !");
        }
    }

    ADC_Run_Status=ADC_Run_Status;  //初始化
}

ADC_thread::~ADC_thread()
{

}
void ADC_thread::run()
{
    while(1)
    {
        switch(ADC_Run_Status)
        {
            case ADC_START:
                start_ADC();
                sleep(1);
                break;
            case ADC_PAUSE:
                sleep(1);
                break;
            default:
                break;
        }
    }
}
void ADC_thread::start_ADC()
{
    int len;
    double dValue;
    double dValue_Volt;
    int ibuffer;
    ioctl(fd, CMD_PORT_SELECTED, 0);//设置通道
    ioctl(fd, CMD_BIT_SELECTED, 12);//设置12位数据
    len = read(fd, &ibuffer, sizeof(ibuffer));//读ad转换后的数据

   if(len>0) // 读出数据有效
   {
       dValue=(float)ibuffer;
       dValue_Volt=(3.3/4095)*dValue;
       printf("Current AD=%f\n",dValue);
       printf("Current AD_Volt=%f\n",dValue_Volt);
   }
   else
   {
       printf("error !open ADC device !\n");
   }

}
