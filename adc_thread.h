/******************************************************
 * adc_thread.h
 *
 *  Created on: 2014-12-22
 *      Author: luoxiaofeng
 * 功能简要：
 *  	采集AD线程；
 *
 ******************************************************/

#ifndef ADC_THREAD_H_
#define ADC_THREAD_H_
#include <QThread>
#include <QObject>
#define ADC_START 0
#define ADC_PAUSE 1
class ADC_thread :public QThread
{

public:
    ADC_thread();
    virtual ~ADC_thread();
    void run();
    void start_ADC();
public:
    int ADC_Run_Status;
};
extern ADC_thread *pADC_thread;
#endif /* ADC_THREAD_H_ */
