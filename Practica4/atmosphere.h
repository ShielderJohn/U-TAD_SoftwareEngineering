#pragma once
#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

#include <vector>


class Atmosphere {
public:
	Atmosphere(int width);
	~Atmosphere();

	void	UpdateAtmosphere();
	int		GetRainValue(int position);

private:
	int m_width;
	int m_randomValue;
	int m_maxValue;
	int m_minValue;
	int m_midValue;

	std::vector<int> m_rain;
};

#endif