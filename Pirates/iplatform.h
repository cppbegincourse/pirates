#ifndef IPLATFORM_H
#define IPLATFORM_H

class IPlatform {
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif // IPLATFORM_H
