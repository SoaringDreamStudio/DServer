#pragma once
#include "libraries.h"
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

	std::vector<Characters*> characters;
	std::vector<Mobs*> mobs;
	std::vector<Normal*> normal;
	std::vector<Wtrig*> wtrig;
	std::vector<Trigger*> trigger;
	std::vector<Ground*> ground;
};

