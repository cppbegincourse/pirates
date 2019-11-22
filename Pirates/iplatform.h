#ifndef IPLATFORM_H
#define IPLATFORM_H
#include "stdafx.h"
#include "Input.h"

#include <chrono>

class IPlatform {
public:
	virtual void Init() { timer = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch()); };
	virtual Input Update() {
		std::chrono::milliseconds newTime = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
		elapsedTime = newTime - timer;
		timer = newTime;
		return Input::NONE;
	};
	virtual void EndDraw() = 0;
	virtual void ClearScreen() = 0;
	virtual void DrawSprite(char sprite, int row, int col) = 0;
    virtual void DrawRow(const char* string, int row, int col) = 0;
    virtual const GameScreen& GetWinScreen() = 0;
    virtual const GameScreen& GetLoseScreen() = 0;
	virtual int GetElapsedTime() { return elapsedTime.count(); };
    virtual ~IPlatform();

private:
	std::chrono::milliseconds elapsedTime;
	std::chrono::milliseconds timer;
};

#endif // IPLATFORM_H
