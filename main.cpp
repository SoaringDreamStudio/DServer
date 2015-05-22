#include "Main.h"

CMain::CMain()
{
	quit = false;

    // initialize socket layer
    if ( !InitializeSockets() )
	{
		std::cout << "failed to initialize sockets\n" << std::endl;

	}
    socket = new net::Socket( ProtocolId,  ServerPort);
	// create socket

	std::cout << "creating socket on port " <<  ServerPort  << std::endl;



	if ( !(*socket).Open( ServerPort ) )
	{
		std::cout << "failed to create socket!\n" << std::endl;
	}

    LoadConfigs();
    LoadStage();

    spawn.x = 300;
    spawn.y = 150;

}


CMain::~CMain(void)
{

    ShutdownSockets();

}

void CMain::LoadStage()
{
    characters.push_back(new Characters(&spawn,
                                        1,
                                        100,
                                        100,
                                        "LOL"));
    characters.push_back(new Characters(&spawn,
                                        1,
                                        400,
                                        300,
                                        "LOL2"));

    /*mobs.push_back(new Mobs(&spawn,
                            1,
                            100,
                            100));
    ground.push_back(new Ground(&spawn,
                            1,
                            100,
                            100));
    ground.push_back(new Ground(&spawn,
                            1,
                            300,
                            300));
    ground.push_back(new Ground(&spawn,
                            1,
                            400,
                            300));*/
    normal.push_back(new Normal(&spawn,
                            1,
                            100,
                            100));
    trigger.push_back(new Trigger(&spawn,
                            1,
                            100,
                            100,
                            false,
                            1));
    wtrig.push_back(new Wtrig(&spawn,
                            1,
                            100,
                            100,
                            false,
                            1));
}

void CMain::LoadConfigs()
{
    //создаетс€ поток файловый дл€ чтени€
    std::ifstream LoadedFile("ServerConfigs.conf");

    //инициализаци€ переменной-строки дл€ чтени€ конфигов
    std::string line;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполн€ть до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //добал€ет в поток строку из string
            std::istringstream iss(line);

            //переменные "предыдущее слово в строке" и "первое слово в строке"
            std::string PreviousWord;
            std::string FirstWord;

            //сбрасываем "первое слово в строке"
            FirstWord = "";

            //пока не строка не закончилась
            while (iss)
            {

                //текущее слово
                std::string word;

                //текущее слово вставл€етс€ из потока
                iss >> word;


                //если предыдущее слово Collision:, то считать местоположение картинки дл€ спрайта
                if (PreviousWord == "NameStage:")
                    nameStage = word;


                //если первое слово еще не заполнено, то записать его
                if(FirstWord.begin() == FirstWord.end())
                    FirstWord = word;


                //предыдущее слово приравн€ть к текущему
                PreviousWord = word;
            }


        }
        std::cout << "NameStage: " << nameStage << std::endl;
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "Can't find configs"<< std::endl;
        std::cout << "Creating configs"<< std::endl;

        std::ofstream LoadedFile;
        LoadedFile.open("ServerConfigs.conf");
        LoadedFile << "NameStage: stage" << std::endl;

        LoadedFile.close();
    }
}


void CMain::LoadPackets()
{
    (*socket).Update();
    net::Address sender;
    unsigned char buffer[256];
    std::string login;
    int bytes_read = (*socket).Receive( sender, buffer, sizeof( buffer ), &login );
    if ( bytes_read )
    {
        /*printf( "received packet from %d.%d.%d.%d:%d (%d bytes)\n",
            sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(),
            sender.GetPort(), bytes_read );*/
            //анализ пакета
        if(buffer[16] == 10 || buffer[0] == 10)
        {
            for(int i = 0; i < 19; i++)
                std::cout << int(buffer[i]) << " ";
            std::cout << std::endl;
            std::string pass;
            for(int n=17; n<25;n++)
            {
                if(buffer[n] != 0)
                    pass += buffer[n];
            }
            std::cout << "login: " << login << std::endl;
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
                //отослать пакеты клиенту
                (*socket).getConnections()[login]->Send(packet,
                                                        sizeof(packet) );

                std::cout<< "Sent error packet" << std::endl;
            }

            else if(res == 1)
            {
                std::cout << "all good" << std::endl;
            }

            else if(res == 2)
            {
                std::cout << "reg. new login: " << login << std::endl;
                characters.push_back(new Characters(&spawn,
                                                    0,
                                                    500,
                                                    500,
                                                    login
                                                    ));
            }

        }
        else if(buffer[0] == 23)
        {
            unsigned int Size = (unsigned int)(buffer[1] << 24) + (unsigned int)(buffer[2]<< 16) + (unsigned int)(buffer[3] << 8) + buffer[4];
            //std::cout << Size << std::endl;
            bool fragments[Size];
            for(int i = 0; i < Size;i++)
            {

                fragments[i] = false;
            }
            while( !allTrue(fragments, Size))
            {
                socket->Update();
                unsigned char buffer[256];
                int bytes_read = socket->Receive( sender, buffer, sizeof( buffer ), &login );

                if(buffer[0] == 24)
                {
                    unsigned int Number = (unsigned int)(buffer[1] << 24) + (unsigned int)(buffer[2]<< 16) + (unsigned int)(buffer[3] << 8) + buffer[4];
                    //std::cout << Number << std::endl;
                    fragments[Number] = true;
                    unsigned int ID = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
                    //std::cout << ID << std::endl;
                    unsigned int X = (unsigned int)(buffer[9] << 24) + (unsigned int)(buffer[10]<< 16) + (unsigned int)(buffer[11] << 8) + buffer[12];
                    //std::cout << X << std::endl;
                    unsigned int Y = (unsigned int)(buffer[13] << 24) + (unsigned int)(buffer[14]<< 16) + (unsigned int)(buffer[15] << 8) + buffer[16];
                    //std::cout << Y << std::endl;
                    std::string Nickname;
                    for(int i = 17; i <=24; i++)
                    {
                        if(buffer[i] == 0)
                            break;
                        Nickname += buffer[i];
                    }/*
                    if(Nickname.size() > 8)
                    {
                        for(std::string::iterator i = Nickname.end(); i != Nickname.begin()+2; i--)
                        {
                            Nickname.erase(i);
                        }
                    }*/
                    std::cout << Nickname << std::endl;

                    bool existNickname;
                    int l=0;
                    for(std::vector<Characters*>::iterator it = characters.begin(); it != characters.end(); ++it,++l)
                    {
                        if((*it)->getNickName() == Nickname)
                        {
                            existNickname = true;
                            std::cout << (*it)->getNickName() << std::endl;
                            characters[l]->changeXY(X,Y);
                        }
                    }
                    if(!existNickname)
                    {
                        std::cout <<"lol " << Nickname << std::endl;
                        characters.push_back(new Characters(&spawn,
                                            1,
                                            spawn.x,
                                            spawn.y,
                                            Nickname));

                        std::cout << "Creating: " << Nickname << std::endl;
                    }
                }
            }
        //если пакет при регистрации и не подходит по паролю, то отправить пакет с ошибкой и удалить connection
        for(int i = 0; i < 256; i++)
            buffer[i] = ' ';
        }
        if(buffer[0] == 24)
        {
            unsigned int Number = (unsigned int)(buffer[1] << 24) + (unsigned int)(buffer[2]<< 16) + (unsigned int)(buffer[3] << 8) + buffer[4];

            unsigned int ID = (unsigned int)(buffer[5] << 24) + (unsigned int)(buffer[6]<< 16) + (unsigned int)(buffer[7] << 8) + buffer[8];
            //std::cout << ID << std::endl;
            unsigned int X = (unsigned int)(buffer[9] << 24) + (unsigned int)(buffer[10]<< 16) + (unsigned int)(buffer[11] << 8) + buffer[12];
            //std::cout << X << std::endl;
            unsigned int Y = (unsigned int)(buffer[13] << 24) + (unsigned int)(buffer[14]<< 16) + (unsigned int)(buffer[15] << 8) + buffer[16];
            //std::cout << Y << std::endl;
            std::string Nickname;
            for(int i = 17; i <=24; i++)
            {
                if(buffer[i] == 0)
                    break;
                Nickname += buffer[i];
            }
            //std::cout << Nickname << std::endl;

            bool existNickname;
            int l=0;
            for(std::vector<Characters*>::iterator it = characters.begin(); it != characters.end(); ++it,++l)
            {
                if((*it)->getNickName() == Nickname)
                {
                    existNickname = true;
                    characters[l]->changeXY(X,Y);
                }
            }
            if(!existNickname)
            {
                characters.push_back(new Characters(&spawn,
                                    1,
                                    spawn.x,
                                    spawn.y,
                                    Nickname));

                std::cout << "Creating: " << Nickname << std::endl;
            }
        }
        else if(buffer[0] == 254)
        {

        }
        else
        {

            std::cout << "bad packet" << int(buffer[16]) << " " << int(buffer[0]) << std::endl;
            for(int i = 0; i < 256; i++)
                buffer[i] = ' ';
        }
    }

}

void CMain::Calculation()
{

}
void CMain::SendPackets()
{
    std::map<std::string, net::Connection*> tmpcon;
    tmpcon = socket->getConnections();
    if(tmpcon.size() != 0) //костыль
    {
        for (std::map<std::string, net::Connection*>::iterator it = tmpcon.begin(); it != tmpcon.end(); ++it)
        {
            net::Address client = it->second->getAddress();
            std::cout << int(client.GetA())<< "." << int(client.GetB())<< "."  << int(client.GetC())<< "."  << int(client.GetD())<< "."  << client.GetPort() << std::endl;

            if (it->second->GetFirstTime() )
            {
                //отправить карту в пакетах

                //std::cout << "FirstTimeUsed" << std::endl;
                socket->getConnections()[it->first]->ConnectionUsed();

                unsigned char data[5];
                data[0] = 21;
                data[1] = (unsigned char) ( ground.size() >> 24 );
                data[2] = (unsigned char) ( ground.size() >> 16 );
                data[3] = (unsigned char) ( ground.size() >> 8 );
                data[4] = (unsigned char) ( ground.size() );
                it->second->Send(data, 5);

                //std::cout<< "Sent map packet" << std::endl;

                for(int i = 0; i < ground.size(); i++)
                {
                    unsigned char data[17];
                    data[0] = 22;

                    //NumberOfPacket
                    data[1] = (unsigned char) ( i >> 24 );
                    data[2] = (unsigned char) ( i >> 16 );
                    data[3] = (unsigned char) ( i >> 8 );
                    data[4] = (unsigned char) ( i );

                    //ID
                    data[5] = (unsigned char) ( ground[i]->getID() >> 24 );
                    data[6] = (unsigned char) ( ground[i]->getID() >> 16 );
                    data[7] = (unsigned char) ( ground[i]->getID() >> 8 );
                    data[8] = (unsigned char) ( ground[i]->getID() );

                    //X
                    data[9] = (unsigned char) ( ground[i]->getX() >> 24 );
                    data[10] = (unsigned char) ( ground[i]->getX() >> 16 );
                    data[11] = (unsigned char) ( ground[i]->getX() >> 8 );
                    data[12] = (unsigned char) ( ground[i]->getX() );

                    //Y
                    data[13] = (unsigned char) ( ground[i]->getY() >> 24 );
                    data[14] = (unsigned char) ( ground[i]->getY() >> 16 );
                    data[15] = (unsigned char) ( ground[i]->getY() >> 8 );
                    data[16] = (unsigned char) ( ground[i]->getY() );


                    it->second->Send(data, 17);

                    //std::cout<< "Sent map fragment" << i << std::endl;
                }
            }
            else
            {
                unsigned char data[5];
                data[0] = 23;
                data[1] = (unsigned char) ( characters.size() >> 24 );
                data[2] = (unsigned char) ( characters.size() >> 16 );
                data[3] = (unsigned char) ( characters.size() >> 8 );
                data[4] = (unsigned char) ( characters.size() );


                it->second->Send(data, 5);


                for(int i = 0; i < characters.size(); i++)
                {
                    unsigned char data[25];
                    data[0] = 24;

                    //NumberOfPacket
                    data[1] = (unsigned char) ( i >> 24 );
                    data[2] = (unsigned char) ( i >> 16 );
                    data[3] = (unsigned char) ( i >> 8 );
                    data[4] = (unsigned char) ( i );

                    //ID
                    data[5] = (unsigned char) ( characters[i]->getID() >> 24 );
                    data[6] = (unsigned char) ( characters[i]->getID() >> 16 );
                    data[7] = (unsigned char) ( characters[i]->getID() >> 8 );
                    data[8] = (unsigned char) ( characters[i]->getID() );

                    //X
                    data[9] = (unsigned char) ( characters[i]->getX() >> 24 );
                    data[10] = (unsigned char) ( characters[i]->getX() >> 16 );
                    data[11] = (unsigned char) ( characters[i]->getX() >> 8 );
                    data[12] = (unsigned char) ( characters[i]->getX() );

                    //Y
                    data[13] = (unsigned char) ( characters[i]->getY() >> 24 );
                    data[14] = (unsigned char) ( characters[i]->getY() >> 16 );
                    data[15] = (unsigned char) ( characters[i]->getY() >> 8 );
                    data[16] = (unsigned char) ( characters[i]->getY() );

                    //NickName
                    data[17] = (unsigned char) ( characters[i]->getNickName()[0]);
                    data[18] = (unsigned char) ( characters[i]->getNickName()[1]);
                    data[19] = (unsigned char) ( characters[i]->getNickName()[2]);
                    data[20] = (unsigned char) ( characters[i]->getNickName()[3]);
                    data[21] = (unsigned char) ( characters[i]->getNickName()[4]);
                    data[22] = (unsigned char) ( characters[i]->getNickName()[5]);
                    data[23] = (unsigned char) ( characters[i]->getNickName()[6]);
                    data[24] = (unsigned char) ( characters[i]->getNickName()[7]);


                    it->second->Send(data, 25);
                }
            }
        }
    }
}
void CMain::SaveConfigs()
{

}

int CMain::LoginClient(std::string login, std::string pass)
{
    //создаетс€ поток файловый дл€ чтени€
    //char* filePath = "saves/" + login
    std::string TmpPass = pass;
    std::ifstream LoadedFile((std::string("saves/") + login).c_str());

    //инициализаци€ переменной-строки дл€ чтени€ конфигов
    std::string line;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполн€ть до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);
            if(line[0] == TmpPass[0] &&
               line[1] == TmpPass[1] &&
               line[2] == TmpPass[2] &&
               line[3] == TmpPass[3] &&
               line[4] == TmpPass[4] &&
               line[5] == TmpPass[5] &&
               line[6] == TmpPass[6] &&
               line[7] == TmpPass[7]) // костыль
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

