#ifndef CLIPLATFORM_H
#define CLIPLATFORM_H
#include "iplatform.h"

class CursesPlatfrom : public IPlatform {
    void Init() override;
    void Draw() override;
    void Update() override;
};

#endif // CLIPLATFORM_H
