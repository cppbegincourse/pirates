#ifndef CLIPLATFORM_H
#define CLIPLATFORM_H
#include "iplatform.h"

#ifdef _WIN32
#define PDC_DLL_BUILD
#include "curses.h"
#else
#include <ncurses.h>
#endif

class CursesPlatfrom : public IPlatform {
public:
    void Init() override;
	void EndDraw() override { refresh(); };
	void DrawSprite(char sprite, int row, int col) override;
	void Update() override {} ;
	~CursesPlatfrom() = default;
};

#endif // CLIPLATFORM_H
