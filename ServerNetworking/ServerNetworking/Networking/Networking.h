#pragma once
#include "preHeads.h"

#define SERVERPORT 5555
#define TEXT "connected to the server"




class Networking
{
private:
	sf::IpAddress serverIp;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> clientSockets;
	std::vector<sf::Vector3f> currentInputs;
	std::size_t received;

	int numberOfClients = 0;
	sf::Vector3f playerInfo;//first two values the input and last value which player he is

	char buffer[2000];
	std::string text;
	int sendReadyCounter;

	void initNet();

public:
	Networking();

	std::vector<sf::Vector3f> tcpAcceptingAndReceiving();
	void tcpSendPlayerPositions(std::vector<sf::Vector3f> playerPositions);
	
};



