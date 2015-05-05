/*
	Sending and Receiving Packets Example (Simple version!)
	From "Networking for Game Programmers" - http://www.gaffer.org/networking-for-game-programmers
	Author: Glenn Fiedler <gaffer@gaffer.org>
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Net.h"
#include "GameStructures.h"

using namespace std;
using namespace net;

const int ServerPort = 21995;
const int ClientPort = 30001;
const int ProtocolId = 0x99887766;
const float DeltaTime = 0.25f;
const float SendRate = 0.25f;
const float TimeOut = 10.0f;

int main( int argc, char * argv[] )
{
	// initialize socket layer

	if ( !InitializeSockets() )
	{
		printf( "failed to initialize sockets\n" );
		return 1;
	}

	// create socket


	printf( "creating socket on port %d\n", ServerPort );

	Socket socket(ProtocolId, TimeOut, ClientPort);

	if ( !socket.Open( ServerPort ) )
	{
		printf( "failed to create socket!\n" );
		return 1;
	}

	// send and receive packets to ourself until the user ctrl-breaks...
    // создание объектов на карте

	while ( true )
	{
		while ( true )
		{
            socket.Update();
			Address sender;
			unsigned char buffer[256];
			int bytes_read = socket.Receive( sender, buffer, sizeof( buffer ) );
			if ( !bytes_read )
            {
				break;
            }
			printf( "received packet from %d.%d.%d.%d:%d (%d bytes)\n",
				sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(),
				sender.GetPort(), bytes_read );
            const char data[] = "hello world!";

            unsigned char packet[sizeof(data)+4];
            packet[0] = (unsigned char) ( ProtocolId >> 24 );
            packet[1] = (unsigned char) ( ( ProtocolId >> 16 ) & 0xFF );
            packet[2] = (unsigned char) ( ( ProtocolId >> 8 ) & 0xFF );
            packet[3] = (unsigned char) ( ( ProtocolId ) & 0xFF );
            memcpy( &packet[4], data, sizeof(data) );

            socket.Send( net::Address(sender.GetA(),sender.GetB(),sender.GetC(),sender.GetD(),sender.GetPort()), packet, sizeof(packet) );

            std::cout<< "Sent" << std::endl;
		}
		wait( 0.25f );
	}
	// shutdown socket layer

	ShutdownSockets();

	return 0;
}
