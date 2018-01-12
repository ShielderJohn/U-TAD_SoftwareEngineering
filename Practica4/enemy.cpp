#include "stdafx.h"
#include "enemy.h"


Enemy::Enemy(int initialLife, int worldWidth) {
	m_isAlive			= false;
	m_initialLife		= initialLife;
	m_life				= initialLife;
	m_position			= -1;
	m_isHalfLife		= false;
	m_worldWidth		= worldWidth;
}

Enemy::~Enemy() {

}

void Enemy::Spawn() {
	if	((rand() & 1) == 0)	{ m_position = 0; m_direction = 1; }
	else					{ m_position = m_worldWidth - 1; m_direction = -1; }

	m_isAlive = true;
}

void Enemy::Move() {
	m_position += m_direction;
}

void Enemy::ReceiveDamage(int damage) {
	m_life -= damage;

	if (m_life <= m_initialLife / 2)
		m_isHalfLife = true;

	if (m_life <= 0) Reset();
}

void Enemy::Reset() {
	m_isAlive		= false;
	m_life			= m_initialLife;
	m_position		= -1;
	m_isHalfLife	= false;
}

bool Enemy::IsAlive() {
	return m_isAlive;
}

int Enemy::GetPosition() {
	return m_position;
}

int Enemy::GetDirection() {
	return m_direction;
}

bool Enemy::IsHalfLife() {
	return m_isHalfLife;
}