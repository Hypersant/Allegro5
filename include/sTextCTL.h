#ifndef STEXTCTL_H
#define STEXTCTL_H

#include <string>
#include <string_view>

#include "../include/cControl.h"
#include "../include/sRect.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

extern ALLEGRO_FONT* G_FONT;

class sTextCTL : public cControl {
public:
    sTextCTL() = default;
    sTextCTL(sRect, ALLEGRO_COLOR color);
    ~sTextCTL();

    ALLEGRO_COLOR Getcolor() {
        return m_color;
    }

    void Setcolor(ALLEGRO_COLOR val) {
        m_color = val;
    }

    ALLEGRO_FONT* Getfont() {
        return m_font;
    }

    void Setfont(ALLEGRO_FONT* val) {
        m_font = val;
    }

protected:

public:
    std::string_view m_text { "" };
    ALLEGRO_FONT* m_font { G_FONT };

    float strlenInPixels();
    void draw() override;
};

#endif // STEXTCTL_H
