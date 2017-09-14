#pragma once
#include "..\stdafx.h"

#include <chrono>

using timer = std::chrono::high_resolution_clock;

class FPSController
{
private:
	std::vector<std::function<void(int)>> listeners;

	void notifyListeners(int fps)
	{
		for (auto listenerFunc : listeners)
			listenerFunc(fps);
	}


	timer::time_point startTime;
	unsigned int frameCounter;
public:
	
	void startTimer()
	{
		startTime = timer::now();
		frameCounter = 0;
	}
		
	void update()
	{
		frameCounter++;
		auto now = timer::now();
		auto elapsed = now - startTime;
		double second = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() / 1000000;
		if (second > 0.5 && frameCounter > 10)
		{
			int fps = (double)frameCounter / second;
			notifyListeners(fps);
			startTime = now;
			frameCounter = 0;
		}
	}

	void addListener(const std::function<void(int)>& listenerFunc)
	{
		listeners.emplace_back(listenerFunc);
	}
};