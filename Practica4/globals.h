#pragma once
#ifndef _GLOBALS_H_
#define _GLOBALS_H

#include "player.h"
#include "atmosphere.h"


#define START_SCREEN				0
#define GAME_SCREEN					1
#define GAME_OVER_SCREEN			2

#define WHITE						15
#define BLUE						3
#define GREEN						10
#define RED							12
#define GRAY						8
#define PURPLE						13

#define INPUT_MOVE_LEFT				'w'
#define INPUT_MOVE_RIGHT			'e'
#define INPUT_FIRE_LEFT				'u'
#define INPUT_FIRE_RIGHT			'i'
#define INPUT_START					't'

#define FLOOR_CHARACTER				'_'
#define PLAYER_CHARACTER			'@'
#define BULLET_CHARACTER			'o'
#define ENEMY_CHARACTER				'X'
#define ENEMY_HALF_LIFE_CHARACTER	'Z'
#define RAIN_FRAME_3_CHARACTER		'\''
#define RAIN_FRAME_2_CHARACTER		'/'
#define RAIN_FRAME_1_CHARACTER		'.'

#define WORLD_WIDTH					80
#define INITIAL_POSITION			WORLD_WIDTH / 2
#define FPS							20
#define MILLISECONDS				1000 / FPS

#define INITIAL_ENEMY_LIFE			2
#define MAX_ENEMIES					4
#define BULLET_DAMAGE				1
#define MAX_BULLETS					3


extern Atmosphere*	atmosphere;
extern HANDLE		hConsole;
extern char			input;

#endif