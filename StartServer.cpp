#include "Main.h"

using namespace std;

int main(int argc, char *argv[])
{

	CMain* cmain = new CMain();

    //cmain->LoadConfigs();
    for(;;)
    {
        cmain->LoadPackets();
        cmain->Calculation();
        cmain->SendPackets();
    }
	//cmain->Calculation();

	return 0;

}
