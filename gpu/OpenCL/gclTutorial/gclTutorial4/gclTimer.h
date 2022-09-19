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
	void Start(void);//������ʱ��
	void Stop(void); //ֹͣ��ʱ��
	void Reset(void);//��λ��ʱ��
	double GetElapsedTime(void);//�������ŵ�ʱ��
};
