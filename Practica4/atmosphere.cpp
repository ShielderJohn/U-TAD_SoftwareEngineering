#include "stdafx.h"
#include "atmosphere.h"


Atmosphere::Atmosphere(int width) {
	m_width = width;
	m_rain = std::vector<int>(m_width);
}

Atmosphere::~Atmosphere() {
	m_rain.clear();
}

void Atmosphere::UpdateAtmosphere() {
	m_maxValue = 100;
	m_minValue = 1;
	m_midValue = m_maxValue / 2;

	for (int i = 0; i < m_width; i++) {
		// Not currently raining
		if (m_rain[i] == 0) {
			m_randomValue = rand() % (m_maxValue + 1 - m_minValue) + m_minValue;

			// Start raining
			if (m_randomValue > m_midValue) m_rain[i] = 3;
		}

		// Currently raining
		else m_rain[i] -= 1;
	}
}

int Atmosphere::GetRainValue(int position) {
	if (position >= 0 && position < m_width)
		return m_rain[position];
}