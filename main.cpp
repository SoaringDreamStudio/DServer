#include "Main.h"

CMain::CMain()
{
	quit = false;

    // initialize socket layer
    if ( !InitializeSockets() )
	{
		std::cout << "failed to initialize sockets\n" << std::endl;

	}
    socket = new net::Socket( ProtocolId, TimeOut, ServerPort);
	// create socket

	std::cout << "creating socket on port " <<  ServerPort  << std::endl;



	if ( !(*socket).Open( ServerPort ) )
	{
		std::cout << "failed to create socket!\n" << std::endl;
	}

}


CMain::~CMain(void)
{

    ShutdownSockets();

}

bool CMain::LoadConfigs()
{

}
void CMain::LoadPackets()
{
    (*socket).Update();
    net::Address sender;
    unsigned char buffer[256];
    int bytes_read = (*socket).Receive( sender, buffer, sizeof( buffer ) );
    if ( bytes_read )
    {
        printf( "received packet from %d.%d.%d.%d:%d (%d bytes)\n",
            sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(),
            sender.GetPort(), bytes_read );
    }
    //анализ пакета
    if(buffer[4] == 10)
    {
        std::string login;
        for(int n=5; n<=13;n++)
        {
            login += buffer[n];
        }
        std::cout << "login: " << login << std::endl;
        std::string pass;
        for(int n=14; n<=22;n++)
        {
            pass += buffer[n];
        }
        std::cout << "pass: " << pass << std::endl;
        int res = LoginClient(login, pass);
        if(res == 0)
        {
            std::cout << "pass not correct" << std::endl;
            char data[1];
            data[0] = 201;

            unsigned char packet[sizeof(data)+4];
            packet[0] = (unsigned char) ( ProtocolId >> 24 );
            packet[1] = (unsigned char) ( ( ProtocolId >> 16 ) & 0xFF );
            packet[2] = (unsigned char) ( ( ProtocolId >> 8 ) & 0xFF );
            packet[3] = (unsigned char) ( ( ProtocolId ) & 0xFF );
            memcpy( &packet[4], data, sizeof(data) );

            (*socket).Send(net::Address(sender.GetA(),
                                        sender.GetB(),
                                        sender.GetC(),
                                        sender.GetD(),
                                        sender.GetPort()),
                                        packet,
                                        sizeof(packet) );

            std::cout<< "Sent error packet" << std::endl;
        }

        else if(res == 1)
        {
            std::cout << "all good" << std::endl;
        }

        else if(res == 2)
        {
            std::cout << "reg. new login" << std::endl;
            characters.push_back(new Characters(0,
                                                500,
                                                500,
                                                login
                                                ));
        }

    }
    //если пакет при регистрации и не подходит по паролю, то отправить пакет с ошибкой и удалить connection
    for(int i = 0; i < 256; i++)
        buffer[i] = ' ';

}
void CMain::Calculation()
{

}
void CMain::SendPackets()
{

}
void CMain::SaveConfigs()
{

}

int CMain::LoginClient(std::string login, std::string pass)
{
    //создается поток файловый для чтения
    //char* filePath = "saves/" + login
    std::ifstream LoadedFile((std::string("saves/") + login).c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);
            if(line == pass)
                return 1;
            else
                return 0;
        }
    }
    else //в случае ошибки
    {
        std::cout << "File could not be open: saves/" << login << std::endl;
        std::cout << "creating new client" << std::endl;

        std::ofstream LoadedFile;
        CreateDirectory("saves", NULL);
        LoadedFile.open((std::string("saves/") + login).c_str());
        LoadedFile << pass << std::endl;

        LoadedFile.close();

        return 2;
    }
}

bool CMain::InitializeSockets()
{
    WSADATA WsaData;
    return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
}

void CMain::ShutdownSockets()
{
    WSACleanup();
}

