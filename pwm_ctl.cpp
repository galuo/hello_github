/******************************************************
 * pwm_ctl.cpp
 *
 *  Created on: 2014-12-23
 *      Author: luoxiaofeng
 * 功能简要：
 *  	控制pwm产生方波；
 *
 ******************************************************/
#include "pwm_ctl.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
int CPWM_Ctl::fb=0;
CPWM_Ctl::CPWM_Ctl()
{
    fb = open(device_pwm, O_RDWR);
    if (fb < 0)
        printf("can't open device");
}
CPWM_Ctl::~CPWM_Ctl()
{

}

void CPWM_Ctl::open_pwm()
{
    ioctl(fb, 1, 1);
}

void CPWM_Ctl::close_pwm()
{
    ioctl(fb, 0, 1);
}
