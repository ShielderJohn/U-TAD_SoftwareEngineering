#include "stdafx.h"
#include "player.h"


Player* Player::m_player = NULL;

Player::Player() {
	m_position = 0;
}

Player::~Player() {
	
}

const Player& Player::Instance() {
	if (m_player == NULL)
		m_player = new Player();

	return *m_player;
}

void Player::ResetInstance() {
	delete m_player;
	m_player = NULL;
}

void Player::Move(char direction) const {
	direction == LEFT ? m_position -= 1 : m_position += 1;
}

int Player::GetPosition() const {
	return m_position;
}

void Player::SetPosition(int position) const {
	m_position = position;
}