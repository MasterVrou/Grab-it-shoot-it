#include "preHeads.h"
#include "Game.h"
#include "Networking.h"

int main()
{
	//srand(static_cast<unsigned>(0)(time(0)));
	
	Game game;

	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}
	return 0;
}
