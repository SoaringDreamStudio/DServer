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
    bool InitializeSockets();
    void ShutdownSockets();

    int LoginClient(std::string,std::string);

	bool quit;

	int timeCheck;

	std::vector<Characters*> characters;
	std::vector<Mobs*> mobs;
	std::vector<Normal*> normal;
	std::vector<Wtrig*> wtrig;
	std::vector<Trigger*> trigger;
	std::vector<Ground*> ground;

	//переменные для сетевой игры
    const int ServerPort = 21995;
    const int ClientPort = 30001;
    const unsigned int ProtocolId = 0x99887766;
    const float DeltaTime = 0.25f;
    const float SendRate = 0.25f;
    const float TimeOut = 10.0f;

     net::Socket* socket;
};

