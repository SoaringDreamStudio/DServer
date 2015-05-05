/*
	Simple Network Library from "Networking for Game Programmers"
	http://www.gaffer.org/networking-for-game-programmers
	Author: Glenn Fiedler <gaffer@gaffer.org>
*/

#ifndef NET_H
#define NET_H

// platform detection

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS

	#include <winsock2.h>
	#pragma comment( lib, "wsock32.lib" )

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>

#else

	#error unknown platform!

#endif

#include <assert.h>
#include <map>

namespace net
{
	// platform independent wait for n seconds

#if PLATFORM == PLATFORM_WINDOWS

	void wait( float seconds )
	{
		Sleep( (int) ( seconds * 1000.0f ) );
	}

#else

	#include <unistd.h>
	void wait( float seconds ) { usleep( (int) ( seconds * 1000000.0f ) ); }

#endif

	// internet address

	class Address
	{
	public:

		Address()
		{
			address = 0;
			port = 0;
		}

		Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port )
		{
			this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
			this->port = port;
		}

		Address( unsigned int address, unsigned short port )
		{
			this->address = address;
			this->port = port;
		}

		unsigned int GetAddress() const
		{
			return address;
		}

		unsigned char GetA() const
		{
			return ( unsigned char ) ( address >> 24 );
		}

		unsigned char GetB() const
		{
			return ( unsigned char ) ( address >> 16 );
		}

		unsigned char GetC() const
		{
			return ( unsigned char ) ( address >> 8 );
		}

		unsigned char GetD() const
		{
			return ( unsigned char ) ( address );
		}

		unsigned short GetPort() const
		{
			return port;
		}

		bool operator == ( const Address & other ) const
		{
			return address == other.address && port == other.port;
		}

		bool operator != ( const Address & other ) const
		{
			return ! ( *this == other );
		}

	private:

		unsigned int address;
		unsigned short port;
	};

	// sockets

	inline bool InitializeSockets()
	{
		#if PLATFORM == PLATFORM_WINDOWS
	    WSADATA WsaData;
		return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
		#else
		return true;
		#endif
	}

	inline void ShutdownSockets()
	{
		#if PLATFORM == PLATFORM_WINDOWS
		WSACleanup();
		#endif
	}

    inline bool sequence_more_recent( unsigned int s1, unsigned int s2, unsigned int max_sequence )
	{
		return ( s1 > s2 ) && ( s1 - s2 <= max_sequence/2 ) || ( s2 > s1 ) && ( s2 - s1 > max_sequence/2 );
	}
/*
	class PacketQueue : public std::list<PacketData>
	{
	public:

		bool exists( unsigned int sequence )
		{
			for ( iterator itor = begin(); itor != end(); ++itor )
				if ( itor->sequence == sequence )
					return true;
			return false;
		}

		void insert_sorted( const PacketData & p, unsigned int max_sequence )
		{
			if ( empty() )
			{
				push_back( p );
			}
			else
			{
				if ( !sequence_more_recent( p.sequence, front().sequence, max_sequence ) )
				{
					push_front( p );
				}
				else if ( sequence_more_recent( p.sequence, back().sequence, max_sequence ) )
				{
					push_back( p );
				}
				else
				{
					for ( PacketQueue::iterator itor = begin(); itor != end(); itor++ )
					{
						assert( itor->sequence != p.sequence );
						if ( sequence_more_recent( itor->sequence, p.sequence, max_sequence ) )
						{
							insert( itor, p );
							break;
						}
					}
				}
			}
		}

		void verify_sorted( unsigned int max_sequence )
		{
			PacketQueue::iterator prev = end();
			for ( PacketQueue::iterator itor = begin(); itor != end(); itor++ )
			{
				assert( itor->sequence <= max_sequence );
				if ( prev != end() )
				{
					assert( sequence_more_recent( itor->sequence, prev->sequence, max_sequence ) );
					prev = itor;
				}
			}
		}
	};

	// reliability system to support reliable connection
	//  + manages sent, received, pending ack and acked packet queues
	//  + separated out from reliable connection because it is quite complex and i want to unit test it!

    class ReliabilitySystem
	{
	public:

    private:

		unsigned int max_sequence;			// maximum sequence value before wrap around (used to test sequence wrap at low # values)
		unsigned int local_sequence;		// local sequence number for most recently sent packet
		unsigned int remote_sequence;		// remote sequence number for most recently received packet

		unsigned int sent_packets;			// total number of packets sent
		unsigned int recv_packets;			// total number of packets received
		unsigned int lost_packets;			// total number of packets lost
		unsigned int acked_packets;			// total number of packets acked

		float sent_bandwidth;				// approximate sent bandwidth over the last second
		float acked_bandwidth;				// approximate acked bandwidth over the last second
		float rtt;							// estimated round trip time
		float rtt_maximum;					// maximum expected round trip time (hard coded to one second for the moment)

		std::vector<unsigned int> acks;		// acked packets from last set of packet receives. cleared each update!

		PacketQueue sentQueue;				// sent packets used to calculate sent bandwidth (kept until rtt_maximum)
		PacketQueue pendingAckQueue;		// sent packets which have not been acked yet (kept until rtt_maximum * 2 )
		PacketQueue receivedQueue;			// received packets for determining acks to send (kept up to most recent recv sequence - 32)
		PacketQueue ackedQueue;				// acked packets (kept until rtt_maximum * 2)
	};
*/
    class Connection
	{
    public:

        enum Mode
		{
			None,
			Client,
			Server
		};

        Connection(unsigned int passed_address, unsigned int protocolId, float timeout, int passed_port)
        {
            address = passed_address;
            this->protocolId = protocolId;
			this->timeout = timeout;
			mode = Server;
			running = true;
			printf("s1 ");
			addressPort = Address(address, passed_port);
			//ClearData();
		}

		~Connection()
		{
			if ( running )
				Stop();
		}

		bool Start()
		{
			assert( !running );
			printf( "start new connection\n" );
			running = true;
			return true;
		}

		void Stop()
		{
			assert( running );
			printf( "stop connection\n" );
			ClearData();
			running = false;
		}

		void Listen()
		{
			printf( "server listening for connection\n" );
			ClearData();
			mode = Server;
			state = Listening;
		}

		void Connect( )
		{
			printf( "client connecting to %d.%d.%d.%d:%d\n",
				addressPort.GetA(), addressPort.GetB(), addressPort.GetC(), addressPort.GetD(), addressPort.GetPort() );
			ClearData();
			mode = Client;
			state = Connecting;
		}

		bool IsConnecting() const
		{
			return state == Connecting;
		}

		bool ConnectFailed() const
		{
			return state == ConnectFail;
		}

		bool IsConnected() const
		{
			return state == Connected;
		}

		bool IsListening() const
		{
			return state == Listening;
		}

		Mode GetMode() const
		{
			return mode;
		}

		void Update( float deltaTime )
		{
			assert( running );
			timeoutAccumulator += deltaTime;
			if ( timeoutAccumulator > timeout )
			{
				if ( state == Connecting )
				{
                    printf( "connect timed out\n" );
					ClearData();
					state = ConnectFail;
					//std::cout << "ConnectFailed " << ConnectFailed() <<std::endl;
				}
				else if ( state == Connected )
				{
					printf( "connection timed out\n" );
					ClearData();
					//if ( state == Connecting )
						state = ConnectFail;
					//std::cout << "ConnectFailed " << ConnectFailed() <<std::endl;
				}
			}
		}

		unsigned char* CreatePacket( const unsigned char data[], int size )
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

		unsigned char* ReceivePacket( unsigned char data[], int size )
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
	protected:

		void ClearData()
		{
			state = Disconnected;
			timeoutAccumulator = 0.0f;
			//addressPort = Address();
		}

    private:
        unsigned int address;

        enum State
		{
			Disconnected,
			Listening,
			Connecting,
			ConnectFail,
			Connected
		};

		unsigned int protocolId;
		float timeout;

		bool running;
		Mode mode;
		State state;
		float timeoutAccumulator;
		Address addressPort;
	};
/*
	class ReliableConnection : public Connection
	{
    public:

    private:
        void ClearData()
		{
			reliabilitySystem.Reset();
		}

		#ifdef NET_UNIT_TEST
		unsigned int packet_loss_mask;			// mask sequence number, if non-zero, drop packet - for unit test only
		#endif

		ReliabilitySystem reliabilitySystem;	// reliability system: manages sequence numbers and acks, tracks network stats etc.

	};
*/
	class Socket
	{
	public:

		Socket( unsigned int passed_protocolId, float passed_timeout, int passed_destinationPort)
		{
		    protocolId = passed_protocolId;
		    timeout = passed_timeout;
			socket = 0;
			destinationPort = passed_destinationPort;
		}

		~Socket()
		{
			Close();
		}

		bool Open( unsigned short port )
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

		void Close()
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

		bool IsOpen() const
		{
			return socket != 0;
		}

        bool Send( const Address & destination, const void * data, int size )
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

		void SendToClients( const Address & destination, unsigned char * data, int size )
		{
		    for(std::map<unsigned int, Connection*>::iterator i = connectedClients.begin(); i != connectedClients.end(); ++i)
		    {
		        //������ SDL �� deltatime
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

        void Update()
        {
            for(std::map<unsigned int, Connection*>::iterator i = connectedClients.begin(); i != connectedClients.end(); ++i)
		    {
		        i -> second->Update( 0.25f );
		        if(i->second->ConnectFailed())
                {
                    connectedClients.erase(i);
                    i = connectedClients.begin();
                    break;
                }
		    }
        }

		int Receive( Address & sender, unsigned char * data, int size )
		{
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
                    //������� ���������� �����


                    std::map<unsigned int, Connection*>::iterator result = connectedClients.find(address);
                    if (result != connectedClients.end())
                    {
                        std::cout << "Element found: " << std::endl;
                        //��������� ����� �� ������
                        result->second->ReceivePacket(packet, size - 4);
                    }
                    else
                    {
                        std::cout << "Creating new connection" << std::endl;
                        connectedClients[address] = new Connection(address, protocolId, timeout, destinationPort);

                        //��������� ����� �� ������

                        //result->second->ReceivePacket(packet, size - 4);
                    }


                    sender = Address( address, port );

                    return received_bytes;
				 }
				 else
                    return 0;


		}

	private:

		int socket;
		unsigned int protocolId;
		float timeout;
		int destinationPort;
		std::map<unsigned int, Connection*> connectedClients;
	};


}

#endif