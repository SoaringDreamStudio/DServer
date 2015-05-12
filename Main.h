#pragma once
#include <math.h>
class CMain
{
public:
	CMain();
	~CMain(void);
	bool LoadConfigs();
	void LoadPackets();
	void Calculation();
    void SendPackets();
    void SaveConfigs();

private:

	bool quit;

	int timeCheck;
};

