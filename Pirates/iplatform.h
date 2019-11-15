#ifndef IPLATFORM_H
#define IPLATFORM_H
#include "Input.h"

class IPlatform {
public:
    virtual void Init() = 0;
    virtual Input Update() = 0;
	virtual void EndDraw() = 0;
	virtual void ClearScreen() = 0;
	virtual void DrawSprite(char sprite, int row, int col) = 0;
	virtual ~IPlatform() {};
};

#endif // IPLATFORM_H
