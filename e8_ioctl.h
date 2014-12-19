#ifndef E8_IOCTL_H
#define E8_IOCTL_H

class e8_ioctl
{
public:
	static int fb;
	
public:
	e8_ioctl();
	~e8_ioctl();
	
	void ioctl_a1(bool b);
	void ioctl_b1(bool b);
	void ioctl_c1(bool b);
	void ioctl_a2(bool b);
	void ioctl_b2(bool b);
	void ioctl_en_pmt(bool b);
	void ioctl_a0(bool b);
	void ioctl_b0(bool b);
	void ioctl_c0(bool b);
	void ioctl_en1(bool b);
	void ioctl_en2(bool b);
	void ioctl_en3(bool b);
	void ioctl_en4(bool b);
}
