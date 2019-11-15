#ifndef IPLATFORM_H
#define IPLATFORM_H
#include "Singleton.h"

class IPlatform {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
	virtual void EndDraw() = 0;
	virtual void DrawSprite(char sprite, int row, int col) = 0;
	virtual ~IPlatform() {};
};

#endif // IPLATFORM_H
