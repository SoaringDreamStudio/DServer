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
#include <ctime>

namespace net
{
	// platform independent wait for n seconds

#if PLATFORM == PLATFORM_WINDOWS

	void wait( float seconds );

#else

	#include <unistd.h>
	void wait( float seconds ) { usleep( (int) ( seconds * 1000000.0f ) ); }

#endif

	// internet address

	class Address
	{
	public:

		Address();

		Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port );

		Address( unsigned int address, unsigned short port );

		unsigned int GetAddress() const;

		unsigned char GetA() const;

		unsigned char GetB() const;

		unsigned char GetC() const;

		unsigned char GetD() const;

		unsigned short GetPort() const;

		bool operator == ( const Address & other ) const;

		bool operator != ( const Address & other ) const;

	private:

		unsigned int address;
		unsigned short port;
	};

	// sockets


    class Connection
	{
    public:

        enum Mode
		{
			None,
			Client,
			Server
		};

        Connection(unsigned int passed_address, unsigned int protocolId, float timeout, int passed_port);

		~Connection();

		bool Start();

		void Stop();

		void Listen();

		void Connect( );

		bool IsConnecting() const;

		bool ConnectFailed() const;

		bool IsConnected() const;

		bool IsListening() const;

		Mode GetMode() const;

		void Update(  );

		unsigned char* CreatePacket( const unsigned char data[], int size );

		unsigned char* ReceivePacket( unsigned char data[], int size );

		bool GetFirstTime() {return firstTime;}

		void ConnectionUsed() {firstTime = false;}

		Address getAddress() {return addressPort;}

		void ConnectOnce() {lastConnect = time (NULL);}

	protected:

		void ClearData();

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

		bool firstTime;

		bool running;
		Mode mode;
		State state;
		float timeoutAccumulator;
		Address addressPort;
		time_t lastConnect;
	};



	class Socket
	{
	public:

		Socket( unsigned int passed_protocolId, float passed_timeout, int passed_destinationPort);

		~Socket();

		bool Open( unsigned short port );

		void Close();

		bool IsOpen() const;

		bool Send( const Address & destination, const void * data, int size );

		void SendToClients( const Address & destination, unsigned char * data, int size );

        void Update();

		int Receive( Address & sender, unsigned char * data, int size );

		std::map<unsigned int, Connection*> getConnections() {return connectedClients;}

	private:

		int socket;
		unsigned int protocolId;
		float timeout;
		int destinationPort;
		std::map<unsigned int, Connection*> connectedClients;
	};


}

#endif
