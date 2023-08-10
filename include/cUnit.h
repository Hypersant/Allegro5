#ifndef CUNIT_H
#define CUNIT_H

#include "../include/sRect.h"
#include "../include/sAABB.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class cUnit {
public:
    cUnit(const cUnit& other = nullptr);
    cUnit& operator=(const cUnit& other);
    virtual ~cUnit();

    ALLEGRO_BITMAP* Getm_image() {
        return m_image;
    }

    void Setm_image(ALLEGRO_BITMAP* val) {
        m_image = val;
    }

    bool collided(sRect* other) {
        bool retVal { false };

        if (m_Rect.m_X <= other->m_X &&
                m_Rect.m_width >= other->m_X &&
                m_Rect.m_Y <= other->m_Y &&
                m_Rect.m_height >= other->m_Y) {
            retVal = true;
        }

        return retVal;
    };

    sRect m_Rect { 0, 0, 0, 0 };

    void updatePos(sRect rect) {
        m_Rect = rect;
    }

protected:
    cUnit() = default;
    cUnit(ALLEGRO_BITMAP* img = nullptr);
    ALLEGRO_BITMAP* m_image;

private:
};

#endif // CUNIT_H
