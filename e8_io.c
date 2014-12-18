/***********************************************************************************
* e8_io.c
* 功能简要： 
*	该驱动注册一个字符设备“/dev/external_output”, 用于接口板的输出。
* 
* 提供的外部接口：
*       ioctol(struct inode *inode,struct file *file,unsigned int brightness);
*	用于控制输出电平高低。
* 调用实例：
*	提供控制台，命令式的测试程序。
*
*************************************************************************************/
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include <mach/map.h>
#include <mach/gpio.h>
//#include <mach/gpio-bank.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-core.h>
#include <plat/gpio-cfg.h>
#include <plat/gpio-cfg-helpers.h>

#define DEVICE_NAME "external_output"

/* 应用程序执行ioctl(fd, cmd, arg)时的第2个参数 */
#define IOCTL_GPIO_ON	1
#define IOCTL_GPIO_OFF	0

/* 用来指定接口板所用的GPIO引脚 */
static unsigned long gpio_table [] =
{
	S5PV210_GPH0(6),//A1
	S5PV210_GPH1(0),//B1
	S5PV210_GPH2(0),//C1
	S5PV210_GPH2(1),//A2
	S5PV210_GPH2(2),//B2
	S5PV210_GPH2(3),//EN_PMT
	S5PV210_GPH2(4),//A0
	S5PV210_GPH2(5),//B0
	S5PV210_GPH2(6),//C0
	S5PV210_GPH2(7),//EN1
	S5PV210_GPH3(0),//EN2
	S5PV210_GPH3(1),//EN3
	S5PV210_GPH3(2),//EN4
};
/* 用来指定GPIO引脚的功能：输出 */
static unsigned int gpio_cfg_table [] =
{
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
	S3C_GPIO_SFN(0),
};

/**
*函数功能：打开/dev/led设备，设备名是：/dev/led
**/
static int tq210_gpio_open(struct inode *inode, struct file *file)
{
	int i;
	int err;

	err = gpio_request(gpio_table[0], "GPH0_6");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH0_6 for A1 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[1], "GPH1_0");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH1_0 for B1 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[2], "GPH2_0");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_0 for C1 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[3], "GPH2_1");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_1 for A2 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[4], "GPH2_2");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_2 for B2 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[5], "GPH2_3");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_3 for EN_PMT pin\n");
        return err;
	}
	err = gpio_request(gpio_table[6], "GPH2_4");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_4 for A0 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[7], "GPH2_5");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_5 for B0 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[8], "GPH2_6");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_6 for C0 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[9], "GPH2_7");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH2_7 for EN1 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[10], "GPH3_0");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH3_0 for EN2 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[11], "GPH3_1");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH3_1 for EN3 pin\n");
        return err;
	}
	err = gpio_request(gpio_table[12], "GPH3_2");
	if(err)
	{
		printk(KERN_ERR "failed to request GPH3_2 for EN4 pin\n");
        return err;
	}
	printk(KERN_INFO " external_output opened\n");
	for (i = 0; i < sizeof(gpio_table)/sizeof(unsigned long); i++)
	{
		s3c_gpio_cfgpin(gpio_table[i], gpio_cfg_table[i]);
		gpio_direction_output(gpio_table[i], 0);
	}
	return 0;
}

/**
*函数功能：用于控制输出IO的电平高低
*控制字为cmd，arg为控制哪一个IO口的电平高低，取值范围为1-13：cmd为IOCTL_GPIO_ON时亮，cmd为IOCTL_GPIO_OFF为灭
**/
static long tq210_gpio_ioctl(
	struct file *file, 
	unsigned int cmd, 
	unsigned long arg)
{
	arg -= 1;
	if (arg > sizeof(gpio_table)/sizeof(unsigned long))
	{
		return -EINVAL;
	}

	switch(cmd)
	{
	case IOCTL_GPIO_ON:
		// 设置指定引脚的输出电平为1
		gpio_direction_output(gpio_table[arg], 1);
		return 0;

	case IOCTL_GPIO_OFF:
		// 设置指定引脚的输出电平为0
		gpio_direction_output(gpio_table[arg], 0);
		return 0;

	default:
		return -EINVAL;
	}
}

static int tq210_gpio_close(struct inode *inode, struct file *file)
{
	gpio_free(gpio_table[0]);
	gpio_free(gpio_table[1]);
	gpio_free(gpio_table[2]);
	gpio_free(gpio_table[3]);
	gpio_free(gpio_table[4]);
	gpio_free(gpio_table[5]);
	gpio_free(gpio_table[6]);
	gpio_free(gpio_table[7]);
	gpio_free(gpio_table[8]);
	gpio_free(gpio_table[9]);
	gpio_free(gpio_table[10]);
	gpio_free(gpio_table[11]);
	gpio_free(gpio_table[12]);
	printk(KERN_INFO "TQ210 LEDs driver successfully close\n");
	return 0;
}

/*驱动接口设置*/
static struct file_operations dev_fops = {
	.owner			=	THIS_MODULE,
	.unlocked_ioctl	=	tq210_gpio_ioctl,
	.open			= tq210_gpio_open,
	.release		= tq210_gpio_close,
};
/*设备结构的设置*/
static struct miscdevice misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DEVICE_NAME,
	.fops	= &dev_fops,
};
/*初始化设备，配置对应的IO，以及注册设备*/
static int __init dev_init(void)
{
	int ret;


	ret = misc_register(&misc);

	printk(KERN_INFO "TQ210 external_output driver successfully probed\n");

	return ret;
}
/*注销设备*/
static void __exit dev_exit(void)
{
	misc_deregister(&misc);
	gpio_free(gpio_table[0]);
	gpio_free(gpio_table[1]);
	gpio_free(gpio_table[2]);
	gpio_free(gpio_table[3]);
	gpio_free(gpio_table[4]);
	gpio_free(gpio_table[5]);
	gpio_free(gpio_table[6]);
	gpio_free(gpio_table[7]);
	gpio_free(gpio_table[8]);
	gpio_free(gpio_table[9]);
	gpio_free(gpio_table[10]);
	gpio_free(gpio_table[11]);
	gpio_free(gpio_table[12]);
	printk(KERN_INFO "TQ210 external_output driver successfully exit\n");
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("luoxiaofeng 527374998@qq.com");
MODULE_DESCRIPTION("接口输出IO驱动");
