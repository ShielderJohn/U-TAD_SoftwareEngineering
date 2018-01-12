#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>

#define LEFT	'l'
#define RIGHT	'r'


class Player {
public:
	static const Player& Instance();
	static void ResetInstance();

	void	Move(char direction) const;
	int		GetPosition() const;
	void	SetPosition(int position) const;

private:
	Player();
	~Player();

	static Player*	m_player;
	mutable int		m_position;
};

#endif