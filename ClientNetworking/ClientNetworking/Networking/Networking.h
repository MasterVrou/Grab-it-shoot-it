#pragma once
#include "preHeads.h"

//#define SERVERIP "127.0.0.1"
#define SERVERPORT 5555
#define TEXT "connected to the server"




class Networking
{
private:
	sf::TcpSocket thisClient;
	std::vector<sf::TcpSocket*> clientSockets;
	std::vector<sf::Vector3f> playerServerPositions;
	//sf::Vector3f playerServerPositions;

	std::size_t received;

	sf::Vector3f playerInfo;//first two values the input and last value which player he is

	char buffer[2000];
	std::string firstMessage;
	bool readyToStart;
	bool firstTime;
	bool predictionRequired;
	sf::Packet lastPacket;
	sf::Packet newPacket;

	void initNet();

public:
	Networking();

	std::vector<sf::Vector3f> tcpReceiveUpdate();
	//sf::Vector3f tcpReceiveUpdate();
	void tcpSendInput(sf::Vector2f input);

	int getMyId();
	bool getReadyToStart();
	bool getPredictionRequired();
	
};



