#include "../include/sButtonCTL.h"

sButtonCTL::sButtonCTL(sRect rect, ALLEGRO_COLOR color) : cControl(rect, color) {
    if (m_text != nullptr) {
        m_text->m_Rect.m_X = m_Rect.m_X + 8;
        m_text->m_Rect.m_Y = m_Rect.m_Y + 0;

        // Auto-adjust the width
        m_Rect.m_width = 12 + (m_text->strlenInPixels() + m_text->m_Rect.m_X + 12);
    }
}

sButtonCTL::~sButtonCTL() {
    //dtor
}

void sButtonCTL::stapleText(sTextCTL* text) {
    m_text = text;

    // Updates the X/Y placement
    if (m_text != nullptr) {
        m_text->m_Rect.m_X = m_Rect.m_X + 8;
        m_text->m_Rect.m_Y = m_Rect.m_Y + 0;

        // Auto-adjust the width
        if (m_autoWidth == true) {
            m_Rect.m_width = 12 + (m_text->strlenInPixels() + m_text->m_Rect.m_X + 12);
        }
    }
}

void sButtonCTL::draw() {
    al_draw_rounded_rectangle(m_Rect.m_X, m_Rect.m_Y, m_Rect.m_width, m_Rect.m_height, 12, 6, m_color, m_thickness);

    if (m_text != nullptr) {
        m_text->m_Rect.m_X = m_Rect.m_X + 8;
        m_text->m_Rect.m_Y = m_Rect.m_Y + 0;

        // Auto-adjust the width
        if (m_autoWidth == true) {
            m_Rect.m_width = 12 + (m_text->strlenInPixels() + m_text->m_Rect.m_X + 12);
        }
    }

    // isVisible property (?)
    // I see no use in it... but maybe... :s
    if (m_text != nullptr) {
        // m_text->draw();
    } else {
        std::cout << "NULLPTR\n";
    }
}

