#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

class Enemy {
public:
	Enemy(int initialLife, int worldWidth);
	~Enemy();

	void	Spawn();
	void	Move();
	void	ReceiveDamage(int damage);
	void	Reset();

	bool	IsAlive();
	int		GetPosition();
	int		GetDirection();
	bool	IsHalfLife();

private:
	bool	m_isAlive;
	int		m_initialLife;
	int		m_life;
	int		m_position;
	int		m_direction;
	bool	m_isHalfLife;
	int		m_worldWidth;
};

#endif