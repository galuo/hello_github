/******************************************************
 * pwm_ctl.h
 *
 *  Created on: 2014-12-23
 *      Author: luoxiaofeng
 * 功能简要：
 *  	控制pwm产生方波；
 *
 ******************************************************/

#ifndef PWM_CTL_H_
#define PWM_CTL_H_

#define device_pwm "/dev/beep"
class CPWM_Ctl
{
public:
    static int fb;
public:
    CPWM_Ctl();
    virtual ~CPWM_Ctl();

    void open_pwm();
    void close_pwm();
};
#endif
