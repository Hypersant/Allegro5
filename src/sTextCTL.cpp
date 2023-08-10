#include "../include/sTextCTL.h"

sTextCTL::sTextCTL(sRect rect, ALLEGRO_COLOR color) : cControl(rect, color) {
}

sTextCTL::~sTextCTL() {
    //dtor
}

float sTextCTL::strlenInPixels() {
//    return m_text.length() * 5.8;
    return m_text.length() * 8;

}

void sTextCTL::draw() {
    al_draw_text(m_font, m_color, m_Rect.m_X + 8, m_Rect.m_Y + 6, ALLEGRO_ALIGN_LEFT, m_text.data());
};
