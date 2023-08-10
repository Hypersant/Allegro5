#ifndef CCONTROL_H
#define CCONTROL_H

#include <iostream>
#include <string_view>

#include "../include/sRect.h"
#include "../include/sAABB.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class cControl {
public:
    cControl() = default;
    virtual ~cControl();

    virtual void draw() = 0;

    sRect m_Rect { 0, 0, 0, 0 };
    ALLEGRO_COLOR m_color { al_map_rgb(0, 0, 0) };

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

    void updatePos(sRect rect) {
        m_Rect = rect;
    }

protected:
    cControl(sRect rect = sRect { 0, 0, 0, 0 }, ALLEGRO_COLOR color = al_map_rgb(0, 0, 0));
};

#endif // CCONTROL_H
