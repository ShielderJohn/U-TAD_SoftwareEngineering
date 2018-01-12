#include "stdafx.h"
#include "globals.h"
#include "game.h"


int main() {

	Game* game = new Game();

	while (true) {
		game->DetectInput();
		game->RunLogic();
		game->Paint();

		Sleep(MILLISECONDS);
	}

	delete game;
	delete atmosphere;
	Player::ResetInstance();

	return 0;
}
