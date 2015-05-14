    #include "Net.h"
    using namespace net;
    using namespace std;
    #include <cstdio>
	#include <winsock2.h>
	#include <iostream>
	#pragma comment( lib, "wsock32.lib" )

	// platform independent wait for n seconds

	void wait( float seconds )
	{
		Sleep( (int) ( seconds * 1000.0f ) );
	}



    Address::Address()
    {
        address = 0;
        port = 0;
    }

    Address::Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port )
    {
        this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
        this->port = port;
    }

    Address::Address( unsigned int address, unsigned short port )
    {
        this->address = address;
        this->port = port;
    }

    unsigned int Address::GetAddress() const
    {
        return address;
    }

    unsigned char Address::GetA() const
    {
        return ( unsigned char ) ( address >> 24 );
    }

    unsigned char Address::GetB() const
    {
        return ( unsigned char ) ( address >> 16 );
    }

    unsigned char Address::GetC() const
    {
        return ( unsigned char ) ( address >> 8 );
    }

    unsigned char Address::GetD() const
    {
        return ( unsigned char ) ( address );
    }

    unsigned short Address::GetPort() const
    {
        return port;
    }

    bool Address::operator == ( const Address & other ) const
    {
        return address == other.address && port == other.port;
    }

    bool Address::operator != ( const Address & other ) const
    {
        return ! ( *this == other );
    }




    Connection::Connection(unsigned int passed_address, unsigned int protocolId, float timeout, int passed_port)
    {
        address = passed_address;
        this->protocolId = protocolId;
        this->timeout = timeout;
        mode = Server;
        running = true;
        printf("s1 ");
        addressPort = Address(address, passed_port);
        lastConnect = time (NULL);
        //ClearData();
    }

    Connection::~Connection()
    {
        if ( running )
            Stop();
    }

    bool Connection::Start()
    {
        assert( !running );
        printf( "start new connection\n" );
        running = true;
        return true;
    }

    void Connection::Stop()
    {
        assert( running );
        printf( "stop connection\n" );
        ClearData();
        running = false;
    }

    void Connection::Listen()
    {
        printf( "server listening for connection\n" );
        ClearData();
        mode = Server;
        state = Listening;
    }

    void Connection::Connect( )
    {
        printf( "client connecting to %d.%d.%d.%d:%d\n",
            addressPort.GetA(), addressPort.GetB(), addressPort.GetC(), addressPort.GetD(), addressPort.GetPort() );
        ClearData();
        mode = Client;
        state = Connecting;
    }

    bool Connection::IsConnecting() const
    {
        return state == Connecting;
    }

    bool Connection::ConnectFailed() const
    {
        return state == ConnectFail;
    }

    bool Connection::IsConnected() const
    {
        return state == Connected;
    }

    bool Connection::IsListening() const
    {
        return state == Listening;
    }

    Connection::Mode Connection::GetMode() const
    {
        return mode;
    }

    void Connection::Update( )
    {
        assert( running );
        if ( lastConnect + 1 < time (NULL) )
        {
            printf( "connection timed out\n" );
            ClearData();
            state = ConnectFail;

            lastConnect = time (NULL);
        }
    }

    unsigned char* Connection::CreatePacket( const unsigned char data[], int size )
    {
        assert( running );
        if ( addressPort.GetAddress() == 0 )
            return false;
        unsigned char packet[size+4];
        packet[0] = (unsigned char) ( protocolId >> 24 );
        packet[1] = (unsigned char) ( ( protocolId >> 16 ) & 0xFF );
        packet[2] = (unsigned char) ( ( protocolId >> 8 ) & 0xFF );
        packet[3] = (unsigned char) ( ( protocolId ) & 0xFF );
        memcpy( &packet[4], data, size );
        return packet;
    }

    unsigned char* Connection::ReceivePacket( unsigned char data[], int size )
    {
        assert( running );
        unsigned char packet[size-4];
        /*if ( sizeof(data) == 0 )
            return 0;
        if ( sizeof(data) <= 4 )
            return 0;
        if ( data[0] != (unsigned char) ( protocolId >> 24 ) ||
             data[1] != (unsigned char) ( ( protocolId >> 16 ) & 0xFF ) ||
             data[2] != (unsigned char) ( ( protocolId >> 8 ) & 0xFF ) ||
             data[3] != (unsigned char) ( protocolId & 0xFF ) )
            return 0;*/
        if ( mode == Server && !IsConnected() )
        {
            printf( "server accepts connection from client %d.%d.%d.%d:%d\n",
                addressPort.GetA(), addressPort.GetB(), addressPort.GetC(), addressPort.GetD(), addressPort.GetPort() );
            state = Connected;
            //addressPort = sender;
        }

        if ( mode == Client && state == Connecting )
        {
            printf( "client completes connection with server\n" );
            state = Connected;
        }
        timeoutAccumulator = 0.0f;

        memcpy( packet, &data[4], size - 4 );
        return packet;
        //return size - 4;

    }

    void Connection::ClearData()
    {
        state = Disconnected;
        timeoutAccumulator = 0.0f;
        //addressPort = Address();
    }

    Socket::Socket( unsigned int passed_protocolId, float passed_timeout, int passed_destinationPort)
    {
        protocolId = passed_protocolId;
        timeout = passed_timeout;
        socket = 0;
        destinationPort = passed_destinationPort;
    }

    Socket::~Socket()
    {
        Close();
    }

    bool Socket::Open( unsigned short port )
    {
        assert( !IsOpen() );

        // create socket

        socket = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

        if ( socket <= 0 )
        {
            printf( "failed to create socket\n" );
            socket = 0;
            return false;
        }

        // bind to port

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( (unsigned short) port );

        if ( bind( socket, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
        {
            printf( "failed to bind socket\n" );
            Close();
            return false;
        }

        // set non-blocking io

        #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

            int nonBlocking = 1;
            if ( fcntl( socket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
            {
                printf( "failed to set non-blocking socket\n" );
                Close();
                return false;
            }

        #elif PLATFORM == PLATFORM_WINDOWS

            DWORD nonBlocking = 1;
            if ( ioctlsocket( socket, FIONBIO, &nonBlocking ) != 0 )
            {
                printf( "failed to set non-blocking socket\n" );
                Close();
                return false;
            }

        #endif

        return true;
    }

    void Socket::Close()
    {
        if ( socket != 0 )
        {
            #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
            close( socket );
            #elif PLATFORM == PLATFORM_WINDOWS
            closesocket( socket );
            #endif
            socket = 0;
        }
    }

    bool Socket::IsOpen() const
    {
        return socket != 0;
    }

    bool Socket::Send( const Address & destination, const void * data, int size )
    {
        assert( data );
        assert( size > 0 );

        if ( socket == 0 )
            return false;

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl( destination.GetAddress() );
        address.sin_port = htons( (unsigned short) destination.GetPort() );

        int sent_bytes = sendto( socket, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in) );

        return sent_bytes == size;
    }

    void Socket::SendToClients( const Address & destination, unsigned char * data, int size )
    {
        for(std::map<unsigned int, Connection*>::iterator i = connectedClients.begin(); i != connectedClients.end(); ++i)
        {
            //таймер SDL по deltatime
            *data = *(i -> second->CreatePacket((const unsigned char*)data, size));
            size = sizeof(*data);

            assert( data );
            assert( size > 0 );

            //if ( socket == 0 )
            //    return false;

            sockaddr_in address;
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = htonl( destination.GetAddress() );
            address.sin_port = htons( (unsigned short) destination.GetPort() );

            int sent_bytes = sendto( socket, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in) );
        }

        //return sent_bytes == size;
    }

    void Socket::Update()
    {
        for(std::map<unsigned int, Connection*>::iterator i = connectedClients.begin(); i != connectedClients.end(); ++i)
        {
            i -> second->Update( );
            if(i->second->ConnectFailed())
            {
                connectedClients.erase(i);
                i = connectedClients.begin();
                break;
            }
        }
    }

    int Socket::Receive( Address & sender, unsigned char * data, int size )
    {
        Update();
        assert( data );
        assert( size > 0 );

        if ( socket == 0 )
            return false;

        #if PLATFORM == PLATFORM_WINDOWS
        typedef int socklen_t;
        #endif

        sockaddr_in from;
        socklen_t fromLength = sizeof( from );

        int received_bytes = recvfrom( socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength );

        if ( received_bytes <= 0 )
            return 0;

        unsigned int address = ntohl( from.sin_addr.s_addr );
        unsigned int port = ntohs( from.sin_port );

        if ( size != 0 &&
             size >= 4 &&
             data[0] == (unsigned char) ( protocolId >> 24 ) &&
             data[1] == (unsigned char) ( ( protocolId >> 16 ) & 0xFF ) &&
             data[2] == (unsigned char) ( ( protocolId >> 8 ) & 0xFF ) &&
             data[3] == (unsigned char) ( protocolId & 0xFF ) )
             {
                unsigned char packet[size - 4];
                memcpy( packet, &data[4], size - 4 );
                //создать обрезанный пакет


                std::map<unsigned int, Connection*>::iterator result = connectedClients.find(address);
                if (result != connectedClients.end())
                {
                    std::cout << "Element found: " << std::endl;
                    //отправить пакет на анализ
                    result->second->ReceivePacket(packet, size - 4);
                }
                else
                {
                    //проверка на корректность
                    if(packet[0] != 10)
                    {
                        std::cout << "Error! Too bad packet to registration" << std::endl;
                        //отправить пакет с ошибкой

                        sender = Address( address, port );
                        char data[1];
                        data[0] = 200;

                        unsigned char packet[sizeof(data)+4];
                        packet[0] = (unsigned char) ( protocolId >> 24 );
                        packet[1] = (unsigned char) ( ( protocolId >> 16 ) & 0xFF );
                        packet[2] = (unsigned char) ( ( protocolId >> 8 ) & 0xFF );
                        packet[3] = (unsigned char) ( ( protocolId ) & 0xFF );
                        memcpy( &packet[4], data, sizeof(data) );

                        this->Send(Address(sender.GetA(),
                                                    sender.GetB(),
                                                    sender.GetC(),
                                                    sender.GetD(),
                                                    sender.GetPort()),
                                                    packet,
                                                    sizeof(packet) );

                        std::cout<< "Sent error packet" << std::endl;
                    }
                    else
                    {
                        std::cout << "Creating new connection" << std::endl;
                        connectedClients[address] = new Connection(address, protocolId, timeout, destinationPort);
                    }
                    //отправить пакет на анализ

                    //result->second->ReceivePacket(packet, size - 4);
                }


                sender = Address( address, port );

                return received_bytes;
             }
             else
                return 0;


    }

