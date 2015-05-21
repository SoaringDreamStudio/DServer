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
#include <iostream>
#include <SDL.h>

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
	class Socket;

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

        Connection(unsigned int passed_address,
                    unsigned int protocolId,
                    int passed_port,
                    std::string passed_login,
                    Socket * passed_socket);

		~Connection();

		void Update(  );

		unsigned char* CreatePacket( const unsigned char data[], int size );

		unsigned char* ReceivePacket( unsigned char data[], int size, unsigned int NumberOfPacket );

		bool GetFirstTime() {return firstTime;}

		void ConnectionUsed() {firstTime = false;}

		Address getAddress() {return addressPort;}

		void UpdatePacket() {lastConnect = time (NULL);}

		bool IsDisconencted() {return disconnected;}
		bool Send( const void * data, int size );

    private:
        unsigned int address;

		unsigned int protocolId;

		bool firstTime;

		bool running;
		Address addressPort;
		time_t lastConnect;
		int lastReceivedPacket;
		int lastShippedPacket;
		int timer;
		std::string login;
		Socket * socket;

		bool disconnected;
	};



	class Socket
	{
	public:

		Socket( unsigned int passed_protocolId, int passed_destinationPort);

		~Socket();

		bool Open( unsigned short port );

		void Close();

		bool IsOpen() const;

		int getSocket() {return socket;}

		bool Send( const Address & destination, const void * data, int size );

		void SendToClients( const Address & destination, unsigned char * data, int size );

        void Update();

		int Receive( Address & sender, unsigned char * data, int size, std::string* login );

		std::map<std::string, Connection*> getConnections() {return connectedClients;}

	private:

		int socket;
		unsigned int protocolId;
		int destinationPort;
		std::map<std::string, Connection*> connectedClients;
	};


}

#endif
