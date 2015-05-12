#include "Main.h"

using namespace std;

int main(int argc, char *argv[])
{

	CMain* cmain = new CMain();

    cmain->LoadConfigs();

	cmain->LoadPackets();
	cmain->Calculation();
    cmain->SendPackets();

	return 0;

}
