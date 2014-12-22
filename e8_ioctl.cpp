/***********************************************************************************
 * e8_ioctl.cpp
 * Created on: 2014-12-22
 *      Author: luoxiaofeng
 * 功能简要：
 *	该类实现的是将调用驱动的功能封装起来；
 *
 *************************************************************************************/
#include "e8_ioctl.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

e8_ioctl::e8_ioctl()
{
	fd = open(device, O_RDWR);
	if (fd < 0)
		printf("can't open device");
}

e8_ioctl::~e8_ioctl()
{

}

void e8_ioctl::ioctl_a1(b)
{
	int err;
	err=ioctl(fd,b,1);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_b1(b)
{
	int err;
	err=ioctl(fd,b,2);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_c1(b)
{
	int err;
	err=ioctl(fd,b,3);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_a2(b)
{
	int err;
	err=ioctl(fd,b,4);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_b2(b)
{
	int err;
	err=ioctl(fd,b,5);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_en_pmt(b)
{
	int err;
	err=ioctl(fd,b,6);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_a0(b)
{
	int err;
	err=ioctl(fd,b,7);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_b0(b)
{
	int err;
	err=ioctl(fd,b,8);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_c0(b)
{
	int err;
	err=ioctl(fd,b,9);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_en1(b)
{
	int err;
	err=ioctl(fd,b,10);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_en2(b)
{
	int err;
	err=ioctl(fd,b,11);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_en3(b)
{
	int err;
	err=ioctl(fd,b,12);
	if(err<0)
		printf("ioctl failed");
}

void e8_ioctl::ioctl_en4(b)
{
	int err;
	err=ioctl(fd,b,13);
	if(err<0)
		printf("ioctl failed");
}
