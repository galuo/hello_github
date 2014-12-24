	MODULE:=tq210_beep
	
ifneq ($(KERNELRELEASE),)
	obj-m:=$(MODULE).o
	module-objs:=$(MODULE).o
else
	KDIR:=/home/luo/Kernel_3.0.8_E8_for_Linux
	PWD:=$(shell pwd)

	CC:=arm-linux-gcc

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.mod.c *.o  *.symvers *.order  *.cmd .tmp_versions
endif


