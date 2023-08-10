#include "cUnit.h"

cUnit::cUnit(ALLEGRO_BITMAP* img) : m_image(img) {
    //ctor
}

cUnit::~cUnit() {
    //dtor
}

cUnit::cUnit(const cUnit& other) {
    //copy ctor
}

cUnit& cUnit::operator=(const cUnit& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
