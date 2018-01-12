#include "stdafx.h"
#include "bullet.h"


Bullet::Bullet() {
	m_isShot	= false;
	m_position	= -1;
	m_direction = 0;
}

Bullet::~Bullet() {

}

void Bullet::Shoot(int position, char direction) {
	m_isShot	= true;
	m_position	= position;

	if		(direction == LEFT)		m_direction = -1;
	else if (direction == RIGHT)	m_direction = 1;
}

void Bullet::Move() {
	m_position += m_direction;
}

void Bullet::Reset() {
	m_isShot	= false;
	m_position	= -1;
	m_direction = 0;
}

int Bullet::GetPosition() {
	return m_position;
}

int Bullet::GetDirection() {
	return m_direction;
}

bool Bullet::IsShot() {
	return m_isShot;
}