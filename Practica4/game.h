#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <vector>

	
class Enemy;
class Bullet;

class Game {
public:
	Game();
	~Game();

	void DetectInput();
	void RunLogic();
	void Paint();
	void Reset();

private:
	void Shoot();
	void SpawnEnemies();
	void MoveEnemies();
	void MoveBullets();
	void CheckCollisions();

	void PaintStartGame();
	void PaintBackground();
	void PaintGame();
	void PaintGameOver();

	std::vector<Enemy>				m_enemies;
	std::vector<Bullet>				m_bullets;
	std::vector<Enemy>::iterator	m_enemyIterator;
	std::vector<Bullet>::iterator	m_bulletIterator;

	int		m_points;
	int		m_currentScreen;
	int		m_enemyPosition;
	int		m_enemyDirection;
	int		m_bulletPosition;
	int		m_bulletDirection;
	int		m_playerPosition;
	int		m_rainValue;
	char	m_shoot;
	bool	m_positionPainted;

	int m_randomValue;
	int m_maxValue;
	int m_minValue;
	int m_midValue;
};

#endif