#include "cPlayer.h"

// cUnit from protected inherited class
cPlayer::cPlayer(ALLEGRO_BITMAP* bg) : cUnit(bg) {
};

void cPlayer::draw() {
    al_draw_tinted_bitmap(m_image, al_map_rgba_f(255, 255, 255, 0), m_Rect.m_X, m_Rect.m_Y, 0);
};

void cPlayer::epoch(int& x, int& y) {
    if (isValid && nextIns != std::end(instructions) && instructions.size() > 0) {
        nextIns = std::begin(instructions);
        m_Rect.m_X = nextIns->first;
        m_Rect.m_Y = nextIns->second;

        al_draw_line(nextIns->second, nextIns->second, nextIns->first, nextIns->first, al_map_rgb(255, 0, 255), -1);

        x = m_Rect.m_X;
        y = m_Rect.m_Y;
    }
}

void cPlayer::cleanup() {
    instructions.clear();
}
