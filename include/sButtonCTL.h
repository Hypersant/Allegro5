#ifndef SBUTTONCTL_H
#define SBUTTONCTL_H

#include "../include/cControl.h"
#include "../include/sTextCTL.h"
#include "../include/sRect.h"

#include <iostream>
#include <experimental/random>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class sButtonCTL : public cControl {
public:
    sButtonCTL() = default;
    sButtonCTL(sRect rect, ALLEGRO_COLOR color);

    virtual ~sButtonCTL();

    sRect getArea() {
        return m_Rect;
    }

    void setArea(int field, int val) {
        sRect tmp = m_Rect; // Save the old data structure

        void* ptr = &m_Rect;

        for (auto n = 0; n < field; ++n) {
            ptr += sizeof(int);
        }

        ptr += sizeof(int);
        *(sRect*)ptr = 666;
        ptr += sizeof(int);
        *(sRect*)ptr = tmp.m_width;
        ptr += sizeof(int);
        *(sRect*)ptr = tmp.m_height;
    }

    ALLEGRO_COLOR getColor() {
        return m_color;
    }

    void setColor(ALLEGRO_COLOR val) {
        m_color = val;
    }

protected:

public:
    sTextCTL* m_text { nullptr };
    bool m_autoWidth { true };
    float m_thickness { -1.0f };

    void stapleText(sTextCTL* text = nullptr);

    void draw() override;
};

#endif // SBUTTONCTL_H
