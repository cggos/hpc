#pragma once

typedef __int64 i64;

class gclTimer
{
public:
	gclTimer(void);
	~gclTimer(void);

private:

    double _freq;
    double _clocks;
    double _start;
public:
	void Start(void);//启动计时器
	void Stop(void); //停止计时器
	void Reset(void);//复位计时器
	double GetElapsedTime(void);//计算流逝的时间
};
