#include "preHeads.h"
#include "Networking.h"

void Networking::initNet()
{
	std::string serverIp;
	std::cout << "Give Server IP: " << std::endl;
	std::cin >> serverIp;

	thisClient.connect(serverIp, SERVERPORT);
	
	thisClient.receive(buffer, sizeof(buffer), received);
	std::cout << buffer << std::endl;

	thisClient.receive(buffer, sizeof(buffer), received);
	std::cout << buffer << std::endl;

	firstMessage = buffer;
	firstTime = true;
	predictionRequired = false;

	playerServerPositions.push_back(sf::Vector3f(0, 0, 0));
	playerServerPositions.push_back(sf::Vector3f(0, 0, 1));
}
	

Networking::Networking()
{
	initNet();
}



//sf::Vector3f Networking::tcpReceiveUpdate()
std::vector<sf::Vector3f> Networking::tcpReceiveUpdate()
{
	if (firstTime) {
		thisClient.receive(buffer, sizeof(buffer), received);
		std::cout << buffer << std::endl;

		std::string m = buffer;
		if (m == "ready to go")
		{
			readyToStart = true;
		}
		firstTime = false;
		thisClient.setBlocking(false);
	}
		

	if (readyToStart) 
	{
		lastPacket = newPacket;

		sf::Socket::Status status = thisClient.receive(newPacket);

		if (lastPacket.getData() == newPacket.getData())
		{
			predictionRequired = true;
		}
		else
		{
			predictionRequired = false;
		}

		//std::cout << predictionRequired << std::endl;
		newPacket >> playerServerPositions[0].x >> playerServerPositions[0].y >> playerServerPositions[0].z >> playerServerPositions[1].x >> playerServerPositions[1].y >> playerServerPositions[1].z;
		
		
		//std::cout << playerServerPositions[0].x << " " << playerServerPositions[0].y << " " << playerServerPositions[1].x << " " << playerServerPositions[1].y << std::endl;
	}
	return playerServerPositions;
}

void Networking::tcpSendInput(sf::Vector2f input)
{
	thisClient.send(&input, sizeof(input));
}



int Networking::getMyId()
{
	if (firstMessage == "waitting for second player")
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool Networking::getReadyToStart()
{
	return readyToStart;
}

bool Networking::getPredictionRequired()
{
	return predictionRequired;
}
