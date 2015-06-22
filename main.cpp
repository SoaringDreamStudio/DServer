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
    std::cout << "Start connecting to DataBase MySQL" << std::endl;
    int timert3 = SDL_GetTicks();
    int timert2 = SDL_GetTicks();
    while(timert3 + 3000 > SDL_GetTicks())
    {
        if(timert2 + 299 < SDL_GetTicks())
        {
            std::cout << ".";
            timert2 = SDL_GetTicks();
        }
    }
    std::cout<< (unsigned char)(251) << std::endl << "Connection complete!" << std::endl;

	if ( !(*socket).Open( ServerPort ) )
	{
		std::cout << "failed to create socket!\n" << std::endl;
	}

    LoadConfigs();
    LoadStage();

    spawn.x = 0;
    spawn.y = 0;

}


CMain::~CMain(void)
{

    ShutdownSockets();

}

void CMain::LoadStage()
{

    /*mobs.push_back(new Mobs(&spawn,
                            1,
                            100,
                            100));*/

    //создается поток файловый для чтения
    std::ifstream LoadedFile("data/stages/stage.dat");

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

            //добаляет в поток строку из string
            std::istringstream iss(line);

            int ID;
            int X;
            int Y;

            //переменные "предыдущее слово в строке" и "первое слово в строке"
            std::string PreviousWord;

            //пока не строка не закончилась
            while (iss)
            {

                //текущее слово
                std::string word;


                //текущее слово вставляется из потока
                iss >> word;

                //если предыдущее слово name, то записываем слово во временную переменную
                if(PreviousWord == "ID:")
                    ID = atoi(word.c_str());

                if(PreviousWord == "x:")
                    X = atoi(word.c_str());

                if(PreviousWord == "y:")
                    Y = atoi(word.c_str());



                //предыдущее слово приравнять к текущему
                PreviousWord = word;
            }
            ground.push_back(new Ground(&spawn,
                                        ID,
                                        X,
                                        Y));


        }
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "File could not be open " << std::endl;
    }

/*
    //background

    ground.push_back(new Ground(&spawn,
                                    1,
                                    -200,
                                    0));

    //grass
    ground.push_back(new Ground(&spawn,
                            2,
                            200,
                            100));
    //ground
    ground.push_back(new Ground(&spawn,
                            3,
                            300,
                            100));
    //lava
    ground.push_back(new Ground(&spawn,
                            4,
                            400,
                            100));
    //sand1
    ground.push_back(new Ground(&spawn,
                            5,
                            500,
                            100));
    //sand2
    ground.push_back(new Ground(&spawn,
                            6,
                            600,
                            100));
    //water
    ground.push_back(new Ground(&spawn,
                            7,
                            700,
                            100));*/
    normal.push_back(new Normal(&spawn,
                            1,
                            100,
                            100));
    normal.push_back(new Normal(&spawn,
                            2,
                            300,
                            100));
    normal.push_back(new Normal(&spawn,
                            3,
                            500,
                            100));
    normal.push_back(new Normal(&spawn,
                            4,
                            700,
                            100));
    normal.push_back(new Normal(&spawn,
                            5,
                            100,
                            200));
    normal.push_back(new Normal(&spawn,
                            6,
                            300,
                            200));
    normal.push_back(new Normal(&spawn,
                            7,
                            500,
                            200));

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
    //создается поток файловый для чтения
    std::ifstream LoadedFile("ServerConfigs.conf");

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

            //добаляет в поток строку из string
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

                //текущее слово вставляется из потока
                iss >> word;


                //если предыдущее слово Collision:, то считать местоположение картинки для спрайта
                if (PreviousWord == "NameStage:")
                    nameStage = word;


                //если первое слово еще не заполнено, то записать его
                if(FirstWord.begin() == FirstWord.end())
                    FirstWord = word;


                //предыдущее слово приравнять к текущему
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
        if(/*buffer[16] == 10 ||*/ buffer[0] == 10)
        {
            /*for(int i = 0; i < 19; i++)
                std::cout << int(buffer[i]) << " ";
            std::cout << std::endl;*/
            std::string pass;
            for(int n=1; n<9;n++)
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
                characters.push_back(new Characters(&spawn,
                                                    1,
                                                    0,
                                                    0,
                                                    login
                                                    ));
                characters[characters.size()-1]->setActiveAnimation("stopu");

                //отправить всем пользователям пакеты о создании объекта

                std::map<std::string, net::Connection*> tmpcon;
                tmpcon = socket->getConnections();
                if(tmpcon.size() != 0) //костыль
                {
                    for (std::map<std::string, net::Connection*>::iterator it = tmpcon.begin(); it != tmpcon.end(); ++it)
                    {
                        if(it->first != login)
                        {
                            unsigned char data[33];
                            data[0] = 24;
                            //NumberOfPacket
                            data[1] = (unsigned char) ( 0 );
                            data[2] = (unsigned char) ( 0 );
                            data[3] = (unsigned char) ( 0 );
                            data[4] = (unsigned char) ( 0 );

                            //ID
                            data[5] = (unsigned char) ( characters[characters.size()-1]->getID() >> 24 );
                            data[6] = (unsigned char) ( characters[characters.size()-1]->getID() >> 16 );
                            data[7] = (unsigned char) ( characters[characters.size()-1]->getID() >> 8 );
                            data[8] = (unsigned char) ( characters[characters.size()-1]->getID() );

                            //X
                            data[9] = (unsigned char) ( characters[characters.size()-1]->getX() >> 24 );
                            data[10] = (unsigned char) ( characters[characters.size()-1]->getX() >> 16 );
                            data[11] = (unsigned char) ( characters[characters.size()-1]->getX() >> 8 );
                            data[12] = (unsigned char) ( characters[characters.size()-1]->getX() );

                            //Y
                            data[13] = (unsigned char) ( characters[characters.size()-1]->getY() >> 24 );
                            data[14] = (unsigned char) ( characters[characters.size()-1]->getY() >> 16 );
                            data[15] = (unsigned char) ( characters[characters.size()-1]->getY() >> 8 );
                            data[16] = (unsigned char) ( characters[characters.size()-1]->getY() );

                            //NickName
                            data[17] = (unsigned char) ( characters[characters.size()-1]->getNickName()[0]);
                            data[18] = (unsigned char) ( characters[characters.size()-1]->getNickName()[1]);
                            data[19] = (unsigned char) ( characters[characters.size()-1]->getNickName()[2]);
                            data[20] = (unsigned char) ( characters[characters.size()-1]->getNickName()[3]);
                            data[21] = (unsigned char) ( characters[characters.size()-1]->getNickName()[4]);
                            data[22] = (unsigned char) ( characters[characters.size()-1]->getNickName()[5]);
                            data[23] = (unsigned char) ( characters[characters.size()-1]->getNickName()[6]);
                            data[24] = (unsigned char) ( characters[characters.size()-1]->getNickName()[7]);

                            //ActiveAnimation
                            //std::cout << "ActiveAnimation " << characters[characters.size()-1]->getActiveAnimation() << std::endl;
                            if(0 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[25] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[0]);
                            else
                                data[25] = (unsigned char) ( 0 );
                            if(1 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[26] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[1]);
                            else
                                data[26] = (unsigned char) ( 0 );
                            if(2 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[27] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[2]);
                            else
                                data[27] = (unsigned char) ( 0 );
                            if(3 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[28] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[3]);
                            else
                                data[28] = (unsigned char) ( 0 );
                            if(4 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[29] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[4]);
                            else
                                data[29] = (unsigned char) ( 0 );
                            if(5 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[30] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[5]);
                            else
                                data[30] = (unsigned char) ( 0 );
                            if(6 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[31] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[6]);
                            else
                                data[31] = (unsigned char) ( 0 );
                            if(7 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[32] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[7]);
                            else
                                data[32] = (unsigned char) ( 0 );

                            it->second->Send(data, 33);
                            //std::cout << "sended" << std::endl;

                        }
                    }
                }
            }

            else if(res == 2)
            {
                std::cout << "reg. new login: " << login << std::endl;
                characters.push_back(new Characters(&spawn,
                                                    1,
                                                    0,
                                                    0,
                                                    login
                                                    ));
                characters[characters.size()-1]->setActiveAnimation("stopu");
                //отправить всем пользователям пакеты о создании объекта

                std::map<std::string, net::Connection*> tmpcon;
                tmpcon = socket->getConnections();
                if(tmpcon.size() != 0) //костыль
                {
                    for (std::map<std::string, net::Connection*>::iterator it = tmpcon.begin(); it != tmpcon.end(); ++it)
                    {
                        if(it->first != login)
                        {
                            unsigned char data[33];
                            data[0] = 24;
                            //NumberOfPacket
                            data[1] = (unsigned char) ( 0 );
                            data[2] = (unsigned char) ( 0 );
                            data[3] = (unsigned char) ( 0 );
                            data[4] = (unsigned char) ( 0 );

                            //ID
                            data[5] = (unsigned char) ( characters[characters.size()-1]->getID() >> 24 );
                            data[6] = (unsigned char) ( characters[characters.size()-1]->getID() >> 16 );
                            data[7] = (unsigned char) ( characters[characters.size()-1]->getID() >> 8 );
                            data[8] = (unsigned char) ( characters[characters.size()-1]->getID() );

                            //X
                            data[9] = (unsigned char) ( characters[characters.size()-1]->getX() >> 24 );
                            data[10] = (unsigned char) ( characters[characters.size()-1]->getX() >> 16 );
                            data[11] = (unsigned char) ( characters[characters.size()-1]->getX() >> 8 );
                            data[12] = (unsigned char) ( characters[characters.size()-1]->getX() );

                            //Y
                            data[13] = (unsigned char) ( characters[characters.size()-1]->getY() >> 24 );
                            data[14] = (unsigned char) ( characters[characters.size()-1]->getY() >> 16 );
                            data[15] = (unsigned char) ( characters[characters.size()-1]->getY() >> 8 );
                            data[16] = (unsigned char) ( characters[characters.size()-1]->getY() );

                            //NickName
                            data[17] = (unsigned char) ( characters[characters.size()-1]->getNickName()[0]);
                            data[18] = (unsigned char) ( characters[characters.size()-1]->getNickName()[1]);
                            data[19] = (unsigned char) ( characters[characters.size()-1]->getNickName()[2]);
                            data[20] = (unsigned char) ( characters[characters.size()-1]->getNickName()[3]);
                            data[21] = (unsigned char) ( characters[characters.size()-1]->getNickName()[4]);
                            data[22] = (unsigned char) ( characters[characters.size()-1]->getNickName()[5]);
                            data[23] = (unsigned char) ( characters[characters.size()-1]->getNickName()[6]);
                            data[24] = (unsigned char) ( characters[characters.size()-1]->getNickName()[7]);

                            //ActiveAnimation
                            //std::cout << "ActiveAnimation " << characters[characters.size()-1]->getActiveAnimation() << std::endl;
                            if(0 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[25] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[0]);
                            else
                                data[25] = (unsigned char) ( 0 );
                            if(1 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[26] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[1]);
                            else
                                data[26] = (unsigned char) ( 0 );
                            if(2 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[27] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[2]);
                            else
                                data[27] = (unsigned char) ( 0 );
                            if(3 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[28] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[3]);
                            else
                                data[28] = (unsigned char) ( 0 );
                            if(4 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[29] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[4]);
                            else
                                data[29] = (unsigned char) ( 0 );
                            if(5 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[30] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[5]);
                            else
                                data[30] = (unsigned char) ( 0 );
                            if(6 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[31] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[6]);
                            else
                                data[31] = (unsigned char) ( 0 );
                            if(7 < characters[characters.size()-1]->getActiveAnimation().size())
                                data[32] = (unsigned char) ( characters[characters.size()-1]->getActiveAnimation()[7]);
                            else
                                data[32] = (unsigned char) ( 0 );

                            it->second->Send(data, 33);
                            //std::cout << "sended" << std::endl;

                        }
                    }
                }
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
                    }
                    std::string activeAnimation;
                    for(int i = 25; i <=32; i++)
                    {
                        if(buffer[i] == 0)
                            break;
                        activeAnimation += buffer[i];
                    }
                    /*
                    if(Nickname.size() > 8)
                    {
                        for(std::string::iterator i = Nickname.end(); i != Nickname.begin()+2; i--)
                        {
                            Nickname.erase(i);
                        }
                    }*/
                    //std::cout << Nickname << std::endl;

                    bool existNickname;
                    int l=0;
                    for(std::vector<Characters*>::iterator it = characters.begin(); it != characters.end(); ++it,++l)
                    {
                        if((*it)->getNickName() == Nickname)
                        {
                            existNickname = true;
                            std::cout << (*it)->getNickName() << std::endl;
                            characters[l]->setActiveAnimation(activeAnimation);
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
                        characters[l]->setActiveAnimation(activeAnimation);

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
            std::string activeAnimation;
            for(int i = 25; i <=32; i++)
            {
                if(buffer[i] == 0)
                    break;
                activeAnimation += buffer[i];
            }
            //std::cout << Nickname << std::endl;

            bool existNickname;
            int l=0;
            for(std::vector<Characters*>::iterator it = characters.begin(); it != characters.end(); ++it,++l)
            {
                if((*it)->getNickName() == Nickname)
                {
                    existNickname = true;

                    characters[l]->setActiveAnimation(activeAnimation);
                    //if(characters[l]->getX() != X || characters[l]->getY() != Y)
                    //{
                        std::map<std::string, net::Connection*> tmpcon;
                        tmpcon = socket->getConnections();
                        if(tmpcon.size() != 0) //костыль
                        {
                            for (std::map<std::string, net::Connection*>::iterator it = tmpcon.begin(); it != tmpcon.end(); ++it)
                            {
                                if(it->first != Nickname)
                                {
                                    unsigned char data[33];
                                    data[0] = 24;
                                    //NumberOfPacket
                                    data[1] = (unsigned char) ( 0 );
                                    data[2] = (unsigned char) ( 0 );
                                    data[3] = (unsigned char) ( 0 );
                                    data[4] = (unsigned char) ( 0 );

                                    //ID
                                    data[5] = (unsigned char) ( characters[l]->getID() >> 24 );
                                    data[6] = (unsigned char) ( characters[l]->getID() >> 16 );
                                    data[7] = (unsigned char) ( characters[l]->getID() >> 8 );
                                    data[8] = (unsigned char) ( characters[l]->getID() );

                                    //X
                                    data[9] = (unsigned char) ( characters[l]->getX() >> 24 );
                                    data[10] = (unsigned char) ( characters[l]->getX() >> 16 );
                                    data[11] = (unsigned char) ( characters[l]->getX() >> 8 );
                                    data[12] = (unsigned char) ( characters[l]->getX() );

                                    //Y
                                    data[13] = (unsigned char) ( characters[l]->getY() >> 24 );
                                    data[14] = (unsigned char) ( characters[l]->getY() >> 16 );
                                    data[15] = (unsigned char) ( characters[l]->getY() >> 8 );
                                    data[16] = (unsigned char) ( characters[l]->getY() );

                                    //NickName
                                    data[17] = (unsigned char) ( characters[l]->getNickName()[0]);
                                    data[18] = (unsigned char) ( characters[l]->getNickName()[1]);
                                    data[19] = (unsigned char) ( characters[l]->getNickName()[2]);
                                    data[20] = (unsigned char) ( characters[l]->getNickName()[3]);
                                    data[21] = (unsigned char) ( characters[l]->getNickName()[4]);
                                    data[22] = (unsigned char) ( characters[l]->getNickName()[5]);
                                    data[23] = (unsigned char) ( characters[l]->getNickName()[6]);
                                    data[24] = (unsigned char) ( characters[l]->getNickName()[7]);

                                    //ActiveAnimation
                                    if(0 < characters[l]->getActiveAnimation().size())
                                        data[25] = (unsigned char) ( characters[l]->getActiveAnimation()[0]);
                                    else
                                        data[25] = (unsigned char) ( 0 );
                                    if(1 < characters[l]->getActiveAnimation().size())
                                        data[26] = (unsigned char) ( characters[l]->getActiveAnimation()[1]);
                                    else
                                        data[26] = (unsigned char) ( 0 );
                                    if(2 < characters[l]->getActiveAnimation().size())
                                        data[27] = (unsigned char) ( characters[l]->getActiveAnimation()[2]);
                                    else
                                        data[27] = (unsigned char) ( 0 );
                                    if(3 < characters[l]->getActiveAnimation().size())
                                        data[28] = (unsigned char) ( characters[l]->getActiveAnimation()[3]);
                                    else
                                        data[28] = (unsigned char) ( 0 );
                                    if(4 < characters[l]->getActiveAnimation().size())
                                        data[29] = (unsigned char) ( characters[l]->getActiveAnimation()[4]);
                                    else
                                        data[29] = (unsigned char) ( 0 );
                                    if(5 < characters[l]->getActiveAnimation().size())
                                        data[30] = (unsigned char) ( characters[l]->getActiveAnimation()[5]);
                                    else
                                        data[30] = (unsigned char) ( 0 );
                                    if(6 < characters[l]->getActiveAnimation().size())
                                        data[31] = (unsigned char) ( characters[l]->getActiveAnimation()[6]);
                                    else
                                        data[31] = (unsigned char) ( 0 );
                                    if(7 < characters[l]->getActiveAnimation().size())
                                        data[32] = (unsigned char) ( characters[l]->getActiveAnimation()[7]);
                                    else
                                        data[32] = (unsigned char) ( 0 );

                                    it->second->Send(data, 33);

                                }
                            }
                        }

                    //}
                    //отправить пакеты клиентам о смене координат


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

                characters[l]->setActiveAnimation(activeAnimation);

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
    std::vector<std::string> disconnected;
    disconnected = socket->getDisconected();
    for(int i = 0; i != disconnected.size(); i++)
    {
        for(std::vector<Characters*>::iterator it = characters.begin(); it != characters.end(); it++)
        {
            if((*it)->getNickName() == disconnected[i])
            {
                //std::cout << "(*it)->getNickName(): " << (*it)->getNickName() << std::endl;
                //std::cout << "disconnected[i]: " << disconnected[i] << std::endl;
                characters.erase(it);
                it = characters.begin();
                if(characters.begin() == characters.end())
                    break;
            }
        }
    }

    //прогон по всем отключившимся клиентам

    //if(!characters.empty())
    //    std::cout << characters[0]->getNickName() << " " << characters[0]->getActiveAnimation() << std::endl;

    /*//system("CLS");
    for(std::vector<Characters*>::iterator it = characters.begin(); it != characters.end(); ++it)
    {
        std::cout << (*it)->getNickName() << " " << (*it)->getActiveAnimation() << std::endl;

    }*/
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
            //std::cout << int(client.GetA())<< "." << int(client.GetB())<< "."  << int(client.GetC())<< "."  << int(client.GetD())<< "."  << client.GetPort() << std::endl;

            if (it->second->GetFirstTime() )
            {
                //отправить карту в пакетах

                std::cout << "FirstTimeUsed " << it->first << std::endl;

                socket->getConnections()[it->first]->ConnectionUsed();

                /*
                //Grounds
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
                }

                //normal
                std::cout << "normal.size() " << normal.size() << std::endl;
                data[0] = 25;
                data[1] = (unsigned char) ( normal.size() >> 24 );
                data[2] = (unsigned char) ( normal.size() >> 16 );
                data[3] = (unsigned char) ( normal.size() >> 8 );
                data[4] = (unsigned char) ( normal.size() );
                it->second->Send(data, 5);

                //std::cout<< "Sent map packet" << std::endl;*/

                for(int i = 0; i < normal.size(); i++)
                {
                    unsigned char data[17];
                    data[0] = 26;

                    //NumberOfPacket
                    data[1] = (unsigned char) ( i >> 24 );
                    data[2] = (unsigned char) ( i >> 16 );
                    data[3] = (unsigned char) ( i >> 8 );
                    data[4] = (unsigned char) ( i );

                    //ID
                    data[5] = (unsigned char) ( normal[i]->getID() >> 24 );
                    data[6] = (unsigned char) ( normal[i]->getID() >> 16 );
                    data[7] = (unsigned char) ( normal[i]->getID() >> 8 );
                    data[8] = (unsigned char) ( normal[i]->getID() );

                    //X
                    data[9] = (unsigned char) ( normal[i]->getX() >> 24 );
                    data[10] = (unsigned char) ( normal[i]->getX() >> 16 );
                    data[11] = (unsigned char) ( normal[i]->getX() >> 8 );
                    data[12] = (unsigned char) ( normal[i]->getX() );

                    //Y
                    data[13] = (unsigned char) ( normal[i]->getY() >> 24 );
                    data[14] = (unsigned char) ( normal[i]->getY() >> 16 );
                    data[15] = (unsigned char) ( normal[i]->getY() >> 8 );
                    data[16] = (unsigned char) ( normal[i]->getY() );


                    it->second->Send(data, 17);
                }

                unsigned char data[5];
                //unsigned char data[5];
                data[0] = 23;
                data[1] = (unsigned char) ( characters.size()-1 >> 24 );
                data[2] = (unsigned char) ( characters.size()-1 >> 16 );
                data[3] = (unsigned char) ( characters.size()-1 >> 8 );
                data[4] = (unsigned char) ( characters.size()-1 );


                it->second->Send(data, 5);

                bool mainSended = false;
                            //std::cout << "start " << std::endl;
                        //std::cout << " it->first " << it->first <<std::endl;

                std::cout << "characters.size() " << characters.size() << std::endl;
                for(int i = 0; i < characters.size(); i++)
                {
                    if(characters[i]->getNickName() == it->first)
                    {
                        //std::cout << "characters[i]->getNickName() " << characters[i]->getNickName() << " it->first " << it->first <<std::endl;
                        mainSended = true;
                    }
                    else
                    {
                        unsigned char data[33];
                        data[0] = 24;
                        if(!mainSended)
                        {
                            //std::cout << "i2: " << i << std::endl;
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

                            //ActiveAnimation
                            if(0 < characters[i]->getActiveAnimation().size())
                                data[25] = (unsigned char) ( characters[i]->getActiveAnimation()[0]);
                            else
                                data[25] = (unsigned char) ( 0 );
                            if(1 < characters[i]->getActiveAnimation().size())
                                data[26] = (unsigned char) ( characters[i]->getActiveAnimation()[1]);
                            else
                                data[26] = (unsigned char) ( 0 );
                            if(2 < characters[i]->getActiveAnimation().size())
                                data[27] = (unsigned char) ( characters[i]->getActiveAnimation()[2]);
                            else
                                data[27] = (unsigned char) ( 0 );
                            if(3 < characters[i]->getActiveAnimation().size())
                                data[28] = (unsigned char) ( characters[i]->getActiveAnimation()[3]);
                            else
                                data[28] = (unsigned char) ( 0 );
                            if(4 < characters[i]->getActiveAnimation().size())
                                data[29] = (unsigned char) ( characters[i]->getActiveAnimation()[4]);
                            else
                                data[29] = (unsigned char) ( 0 );
                            if(5 < characters[i]->getActiveAnimation().size())
                                data[30] = (unsigned char) ( characters[i]->getActiveAnimation()[5]);
                            else
                                data[30] = (unsigned char) ( 0 );
                            if(6 < characters[i]->getActiveAnimation().size())
                                data[31] = (unsigned char) ( characters[i]->getActiveAnimation()[6]);
                            else
                                data[31] = (unsigned char) ( 0 );
                            if(7 < characters[i]->getActiveAnimation().size())
                                data[32] = (unsigned char) ( characters[i]->getActiveAnimation()[7]);
                            else
                                data[32] = (unsigned char) ( 0 );

                            it->second->Send(data, 33);
                        }
                        else
                        {
                            //NumberOfPacket
                            //std::cout << "i: " << i << std::endl;
                            data[1] = (unsigned char) ( (i-1) >> 24 );
                            data[2] = (unsigned char) ( (i-1) >> 16 );
                            data[3] = (unsigned char) ( (i-1) >> 8 );
                            data[4] = (unsigned char) ( (i-1) );

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

                            //ActiveAnimation
                            if(0 < characters[i]->getActiveAnimation().size())
                                data[25] = (unsigned char) ( characters[i]->getActiveAnimation()[0]);
                            else
                                data[25] = (unsigned char) ( 0 );
                            if(1 < characters[i]->getActiveAnimation().size())
                                data[26] = (unsigned char) ( characters[i]->getActiveAnimation()[1]);
                            else
                                data[26] = (unsigned char) ( 0 );
                            if(2 < characters[i]->getActiveAnimation().size())
                                data[27] = (unsigned char) ( characters[i]->getActiveAnimation()[2]);
                            else
                                data[27] = (unsigned char) ( 0 );
                            if(3 < characters[i]->getActiveAnimation().size())
                                data[28] = (unsigned char) ( characters[i]->getActiveAnimation()[3]);
                            else
                                data[28] = (unsigned char) ( 0 );
                            if(4 < characters[i]->getActiveAnimation().size())
                                data[29] = (unsigned char) ( characters[i]->getActiveAnimation()[4]);
                            else
                                data[29] = (unsigned char) ( 0 );
                            if(5 < characters[i]->getActiveAnimation().size())
                                data[30] = (unsigned char) ( characters[i]->getActiveAnimation()[5]);
                            else
                                data[30] = (unsigned char) ( 0 );
                            if(6 < characters[i]->getActiveAnimation().size())
                                data[31] = (unsigned char) ( characters[i]->getActiveAnimation()[6]);
                            else
                                data[31] = (unsigned char) ( 0 );
                            if(7 < characters[i]->getActiveAnimation().size())
                                data[32] = (unsigned char) ( characters[i]->getActiveAnimation()[7]);
                            else
                                data[32] = (unsigned char) ( 0 );

                            it->second->Send(data, 33);
                        }

                    }
                }


                   // std::cout<< "Sent map fragment" << i << std::endl;




            }



        }
    }
}
void CMain::SaveConfigs()
{

}

int CMain::LoginClient(std::string login, std::string pass)
{
    //создается поток файловый для чтения
    //char* filePath = "saves/" + login
    std::string TmpPass = pass;
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

