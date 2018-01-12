#include "stdafx.h"
#include "globals.h"
#include "enemy.h"
#include "bullet.h"
#include "game.h"


Game::Game() {
	m_currentScreen = -1;
	m_shoot			= 0;

	for (int i = 0; i < MAX_ENEMIES; i++)
		m_enemies.push_back(Enemy(INITIAL_ENEMY_LIFE, WORLD_WIDTH));

	for (int i = 0; i < MAX_BULLETS; i++)
		m_bullets.push_back(Bullet());
}

Game::~Game() {
	m_enemies.clear();
	m_bullets.clear();
}

void Game::DetectInput() {
	if (m_currentScreen == START_SCREEN || m_currentScreen == GAME_OVER_SCREEN) {
		input = _getch();

		// Start/Restart game
		if (input == INPUT_START) {
			Reset();
			m_currentScreen = GAME_SCREEN;
			PaintBackground();
		}
	}
	else if (_kbhit()) {
		input = _getch();

		// Move player
		if (input == INPUT_MOVE_LEFT && m_currentScreen == GAME_SCREEN)
			Player::Instance().Move(LEFT);
		else if (input == INPUT_MOVE_RIGHT && m_currentScreen == GAME_SCREEN)
			Player::Instance().Move(RIGHT);

		// Shoot
		if (input == INPUT_FIRE_LEFT && m_currentScreen == GAME_SCREEN)
			m_shoot = LEFT;
		else if (input == INPUT_FIRE_RIGHT && m_currentScreen == GAME_SCREEN)
			m_shoot = RIGHT;
	}
}

void Game::RunLogic() {
	if (m_currentScreen == -1)
		m_currentScreen = START_SCREEN;

	if (m_currentScreen == GAME_SCREEN) {
		m_playerPosition = Player::Instance().GetPosition();
		atmosphere->UpdateAtmosphere();

		Shoot();
		SpawnEnemies();
		MoveEnemies();
		MoveBullets();
		CheckCollisions();
	}
}

void Game::Paint() {
	if		(m_currentScreen == START_SCREEN)		PaintStartGame();
	else if (m_currentScreen == GAME_SCREEN)		PaintGame();
	else if (m_currentScreen == GAME_OVER_SCREEN)	PaintGameOver();
}

void Game::Reset() {
	// Reset player position
	Player::Instance().SetPosition(WORLD_WIDTH / 2);

	// Reset enemies
	for (m_enemyIterator = m_enemies.begin(); m_enemyIterator < m_enemies.end(); m_enemyIterator++)
		m_enemyIterator->Reset();

	// Reset bullets
	for (m_bulletIterator = m_bullets.begin(); m_bulletIterator < m_bullets.end(); m_bulletIterator++)
		m_bulletIterator->Reset();

	m_points = 0;

	system("cls");
}

void Game::Shoot() {
	if (m_shoot != 0) {
		int position;

		if (m_shoot == LEFT)
			position = Player::Instance().GetPosition() - 1;
		else if (m_shoot == RIGHT)
			position = Player::Instance().GetPosition() + 1;

		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator < m_bullets.end(); m_bulletIterator++) {
			if (!m_bulletIterator->IsShot()) {
				m_bulletIterator->Shoot(position, m_shoot);
				break;
			}
		}
	}

	m_shoot = 0;
}

void Game::SpawnEnemies() {
	m_maxValue = 100;
	m_minValue = 1;
	m_midValue = m_maxValue / 2;

	for (m_enemyIterator = m_enemies.begin(); m_enemyIterator < m_enemies.end(); m_enemyIterator++) {
		if (!m_enemyIterator->IsAlive()) {
			m_randomValue = rand() % (m_maxValue + 1 - m_minValue) + m_minValue;
			if (m_randomValue > m_midValue) m_enemyIterator->Spawn();
		}
	}
}

void Game::MoveEnemies() {
	for (m_enemyIterator = m_enemies.begin(); m_enemyIterator < m_enemies.end(); m_enemyIterator++)
		if (m_enemyIterator->IsAlive()) m_enemyIterator->Move();
}

void Game::MoveBullets() {
	for (m_bulletIterator = m_bullets.begin(); m_bulletIterator < m_bullets.end(); m_bulletIterator++)
		m_bulletIterator->Move();
}

void Game::CheckCollisions() {
	// Collision of player with world bounds
	if (m_playerPosition <= 0)
		Player::Instance().SetPosition(0);
	else if (m_playerPosition >= WORLD_WIDTH - 1)
		Player::Instance().SetPosition(WORLD_WIDTH - 1);

	// If enemy touches player, game is over
	for (m_enemyIterator = m_enemies.begin(); m_enemyIterator < m_enemies.end(); m_enemyIterator++) {
		m_enemyPosition = m_enemyIterator->GetPosition();
		m_enemyDirection = m_enemyIterator->GetDirection();

		if (m_enemyPosition == m_playerPosition
			|| m_enemyPosition - m_enemyDirection == m_playerPosition
			|| m_enemyPosition + m_enemyDirection == m_playerPosition)
			m_currentScreen = GAME_OVER_SCREEN;
	}

	// Bullet collisions
	for (m_bulletIterator = m_bullets.begin(); m_bulletIterator < m_bullets.end(); m_bulletIterator++) {
		if (m_bulletIterator->IsShot()) {
			m_bulletPosition = m_bulletIterator->GetPosition();
			m_bulletDirection = m_bulletIterator->GetDirection();

			// Collision with enemies
			for (m_enemyIterator = m_enemies.begin(); m_enemyIterator < m_enemies.end(); m_enemyIterator++) {
				if (m_enemyIterator->IsAlive()) {
					m_enemyPosition = m_enemyIterator->GetPosition();
					m_enemyDirection = m_enemyIterator->GetDirection();

					if (m_enemyPosition == m_bulletPosition ||
						m_enemyPosition - m_enemyDirection == m_bulletPosition) {
						m_enemyIterator->ReceiveDamage(BULLET_DAMAGE);
						m_bulletIterator->Reset();

						if (!m_enemyIterator->IsAlive()) m_points += 1;
					}
				}
			}
			
			// Collision with world bounds
			if (m_bulletPosition <= 0 && m_bulletDirection == -1 ||
				m_bulletPosition >= WORLD_WIDTH - 1 && m_bulletDirection == 1)
				m_bulletIterator->Reset();
		}
	}
}

void Game::PaintStartGame() {
	system("cls");
	SetConsoleTextAttribute(hConsole, PURPLE);

	std::cout << std::endl << std::endl;
	std::cout << "########   #######   #######  ##     ##       ##   ######## " << std::endl;
	std::cout << "##     ## ##     ## ##     ## ###   ###     ####   ##    ## " << std::endl;
	std::cout << "##     ## ##     ## ##     ## #### ####       ##       ##   " << std::endl;
	std::cout << "##     ## ##     ## ##     ## ## ### ##       ##      ##    " << std::endl;
	std::cout << "##     ## ##     ## ##     ## ##     ##       ##     ##     " << std::endl;
	std::cout << "##     ## ##     ## ##     ## ##     ##       ##     ##     " << std::endl;
	std::cout << "########   #######   #######  ##     ##     ######   ##     " << std::endl;
	std::cout << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << "Press T to start" << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, BLUE);
	std::cout << "MOVING: ";
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << INPUT_MOVE_LEFT << " / " << INPUT_MOVE_RIGHT << std::endl;

	SetConsoleTextAttribute(hConsole, BLUE);
	std::cout << "SHOOTING: ";
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << INPUT_FIRE_LEFT << " / " << INPUT_FIRE_RIGHT << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, BLUE);
	std::cout << "CURRENT SETTINGS: ";
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << MAX_ENEMIES << " enemies, ";
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << MAX_BULLETS << " bullets";
}

void Game::PaintBackground() {
	SetConsoleTextAttribute(hConsole, PURPLE);
	std::cout << "                                                     ___ " << std::endl;
	std::cout << "                                                  ,o88888 " << std::endl;
	std::cout << "                                               ,o8888888' " << std::endl;
	std::cout << "                         ,:o:o:oooo.        ,8O88Pd8888\" " << std::endl;
	std::cout << "                     ,.::.::o:ooooOoOoO. ,oO8O8Pd888'\" " << std::endl;
	std::cout << "                   ,.:.::o:ooOoOoOO8O8OOo.8OOPd8O8O\" " << std::endl;
	std::cout << "                  , ..:.::o:ooOoOOOO8OOOOo.FdO8O8\" " << std::endl;
	std::cout << "                 , ..:.::o:ooOoOO8O888O8O,COCOO\" " << std::endl;
	std::cout << "                , . ..:.::o:ooOoOOOO8OOOOCOCO\" " << std::endl;
	std::cout << "                 . ..:.::o:ooOoOoOO8O8OCCCC\"o " << std::endl;
	std::cout << "                    . ..:.::o:ooooOoCoCCC\"o:o " << std::endl;
	std::cout << "                    . ..:.::o:o:,cooooCo\"oo:o: " << std::endl;
	std::cout << "                 `   . . ..:.:cocoooo\"'o:o:::' " << std::endl;
	std::cout << "                 .`   . ..::ccccoc\"'o:o:o:::' " << std::endl;
	std::cout << "                :.:.    ,c:cccc\"':.:.:.:.:.' " << std::endl;
	std::cout << "              ..:.:\"'`::::c:\"'..:. : . : . : . : .' " << std::endl;
	std::cout << "            ...:.'.:.::::\"'    . . . . .' " << std::endl;
	std::cout << "           .. . ....:.\"' `   .  . . '' " << std::endl;
	std::cout << "         . . . ....\"' " << std::endl;
	std::cout << "         .. . .\"'     -hrr- " << std::endl;
	std::cout << "        . " << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void Game::PaintGame() {

	std::cout << '\r';
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << "POINTS: " << m_points << "            ";
	m_positionPainted = false;

	for (int i = 0; i < WORLD_WIDTH; i++) {
		// Paint player
		if (i == m_playerPosition) {
			SetConsoleTextAttribute(hConsole, GREEN);
			std::cout << PLAYER_CHARACTER;
			m_positionPainted = true;
		}

		// Paint bullets
		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator < m_bullets.end(); m_bulletIterator++) {
			if (i == m_bulletIterator->GetPosition() && !m_positionPainted) {
				SetConsoleTextAttribute(hConsole, GREEN);
				std::cout << BULLET_CHARACTER;
				m_positionPainted = true;
			}
		}

		// Paint enemies
		for (m_enemyIterator = m_enemies.begin(); m_enemyIterator < m_enemies.end(); m_enemyIterator++) {
			if (i == m_enemyIterator->GetPosition() && !m_positionPainted) {
				SetConsoleTextAttribute(hConsole, RED);
				m_enemyIterator->IsHalfLife() ? std::cout << ENEMY_HALF_LIFE_CHARACTER : std::cout << ENEMY_CHARACTER;
				m_positionPainted = true;
			}
		}

		// Paint rain and floor
		if (!m_positionPainted) {
			m_rainValue = atmosphere->GetRainValue(i);

			SetConsoleTextAttribute(hConsole, BLUE);
			if		(m_rainValue == 3) { std::cout << RAIN_FRAME_3_CHARACTER; }
			else if (m_rainValue == 2) { std::cout << RAIN_FRAME_2_CHARACTER; }
			else if (m_rainValue == 1) { std::cout << RAIN_FRAME_1_CHARACTER; }
			else { SetConsoleTextAttribute(hConsole, GRAY); std::cout << FLOOR_CHARACTER; }
		}

		m_positionPainted = false;
	}
}

void Game::PaintGameOver() {
	system("cls");
	SetConsoleTextAttribute(hConsole, PURPLE);

	std::cout << std::endl << std::endl;
	std::cout << " ######      ###    ##     ## ########     #######  ##     ## ######## ########  " << std::endl;
	std::cout << "##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## " << std::endl;
	std::cout << "##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## " << std::endl;
	std::cout << "##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########  " << std::endl;
	std::cout << "##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##   " << std::endl;
	std::cout << "##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##  " << std::endl;
	std::cout << " ######   ##     ## ##     ## ########     #######     ###    ######## ##     ## " << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << '\r';
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << "TOTAL POINTS: " << m_points << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << "Press T to restart" << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, BLUE);
	std::cout << "MOVING: ";
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << INPUT_MOVE_LEFT << " / " << INPUT_MOVE_RIGHT << std::endl;

	SetConsoleTextAttribute(hConsole, BLUE);
	std::cout << "SHOOTING: ";
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << INPUT_FIRE_LEFT << " / " << INPUT_FIRE_RIGHT << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, BLUE);
	std::cout << "CURRENT SETTINGS: ";
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << MAX_ENEMIES << " enemies, ";
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << MAX_BULLETS << " bullets";
}