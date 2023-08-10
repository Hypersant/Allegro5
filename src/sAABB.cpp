#include "sAABB.h"

bool sAABB::collided(sRect* other) {
    bool retVal { true };

    if (m_area.m_X > other->m_X && m_area.m_X > other->m_width) {
        retVal = false;
    }

    if (m_area.m_X < other->m_X && m_area.m_X < other->m_width) {
        retVal = false;
    }

    if (m_area.m_Y > other->m_Y && m_area.m_Y > other->m_height) {
        retVal = false;
    }

    if (m_area.m_Y < other->m_Y && m_area.m_Y < other->m_height) {
        retVal = false;
    }

    return retVal;
};

bool sAABB::hasCollision() {
    return false;
}
