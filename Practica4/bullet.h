#pragma once
#ifndef _BULLET_H
#define _BULLET_H

#define LEFT	'l'
#define RIGHT	'r'


class Bullet {
public:
	Bullet();
	~Bullet();

	void	Shoot(int position, char direction);
	void	Move();
	void	Reset();

	int		GetPosition();
	int		GetDirection();
	bool	IsShot();

private:
	bool	m_isShot;
	int		m_position;
	int		m_direction;
};

#endif