#pragma once
#include "graphics.h"
#include "Menu.h"
#include "GameLVL.h"
#include "MainCharacter.h"
#include <windows.h>
#include <math.h>
class CMain
{
public:
	CMain(int passed_ScreenWidth, int passed_ScreenHeight, net::Socket* passed_gsocket);
	~CMain(void);
	int GameLoop();
	void GameMenu();
	bool GOMenu();
	void Loading();
	void DrawLoadingProcess(float, LoadingProcess*); //��������� ������� ��� ���������� ��������� �������� �� �������� ������� � ����������� �� ������

private:
    float CameraX;
    float CameraY;

    net::Socket* gsocket;

    MainCharacter* MainHero;
    GameLVL* gameLVL;
    bool objectsHead;
    bool normalHead;

	int ScreenWidth;
	int ScreenHeight;
	bool quit;
	bool Mquit;

    //CInterpretator* interpretator;
	CSDL_Setup* csdl_setup;

	int timeCheck;
	int updateTimer; //������ ��� ������� �����
	int MouseX;
	int MouseY;
    bool ignoreGameOver;

    int ServerTimeOut;

    int timerSend;
};

