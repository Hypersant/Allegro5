#ifndef SAABB_H
#define SAABB_H

#include "../include/sRect.h"

class sAABB {
public:
    sAABB() = default;

    sRect m_area { 0, 0, 0, 0 };

protected:

private:
    bool collided(sRect* other = nullptr);
    bool hasCollision();
};

#endif // SAABB_H
