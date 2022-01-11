#include "preHeads.h"
#include "Networking.h"

void Networking::initNet()
{
	serverIp = sf::IpAddress::getLocalAddress();
	listener.listen(SERVERPORT);
	selector.add(listener);
	
	text = "connected to the server";
	sendReadyCounter = 0;
}

Networking::Networking()
{
	initNet();
}

void Networking::tcpSendPlayerPositions(std::vector<sf::Vector3f> playerPositions)
{
	sf::Packet packet;
	packet << playerPositions[0].x << playerPositions[0].y << playerPositions[0].z << playerPositions[1].x << playerPositions[1].y << playerPositions[1].z;
	for (int i = 0; i < clientSockets.size(); i++)
	{
		clientSockets[i]->send(packet);
	}
}



std::vector<sf::Vector3f> Networking::tcpAcceptingAndReceiving()
{
	if (selector.wait())
	{
		
		if (selector.isReady(listener))
		{
		
			sf::TcpSocket* newClient = new sf::TcpSocket;
			listener.accept(*newClient);
			newClient->send(text.c_str(), text.length() + 1);
			numberOfClients++;
			if (numberOfClients == 1)
			{
				text = "waitting for second player";
				newClient->send(text.c_str(), text.length() + 1);
			}
			else if (numberOfClients == 2)
			{
				text = "another player has already joined.. Let's start";
				newClient->send(text.c_str(), text.length() + 1);
			}
			clientSockets.push_back(newClient);
			currentInputs.push_back(sf::Vector3f(0.f, 0.f, 0.f));
			selector.add(*newClient);

			std::cout << "new player in port: " << newClient->getRemotePort() << std::endl;
		}

		for (int i = 0; i < clientSockets.size(); i++)
		{
			if (clientSockets.size() == 2 && sendReadyCounter < 2)
			{
				text = "ready to go";
				clientSockets[i]->send(text.c_str(), text.length() + 1);
				sendReadyCounter++;
			}

			if (selector.isReady(*clientSockets[i]))
			{
				sf::Vector2f input;
				if (clientSockets[i]->receive(&input, sizeof(input), received) == sf::Socket::Done)
				{
					std::cout << "the input was: (" << input.x << ", " << input.y << ")" << std::endl;
					currentInputs[i] = sf::Vector3f(input.x, input.y, i);
				}
			}
		}
		return currentInputs;
	}
}