#ifndef CPLAYER_H
#define CPLAYER_H

#include <vector>
#include <string>
#include <utility>

#include "../include/cUnit.h"
#include "../include/cAI.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

class cPlayer : public cUnit {
public:
    cPlayer() = default;
    cPlayer(ALLEGRO_BITMAP* bg = nullptr);

    cAI Getm_AI() {
        return m_AI;
    }
    void Setm_AI(cAI val) {
        m_AI = val;
    }
    bool GetisValid() {
        return isValid;
    }
    void SetisValid(bool val) {
        isValid = val;
    }
    bool GetisActive() {
        return isActive;
    }
    void SetisActive(bool val) {
        isActive = val;
    }
    std::vector<std::pair<int, int>> Getinstructions() {
        return instructions;
    }
    void Setinstructions(std::vector<std::pair<int, int>> val) {
        instructions = val;
    }
    std::vector<std::pair<int, int>>::iterator GetnextIns() {
        return nextIns;
    }
    void SetnextIns(std::vector<std::pair<int, int>>::iterator val) {
        nextIns = val;
    }

    void draw();
    void epoch(int& x, int& y);
    void cleanup();

protected:

public:
    cAI m_AI;

    bool isValid;
    bool isActive;
    std::vector<std::pair<int, int>> instructions;
    std::vector<std::pair<int, int>>::iterator nextIns;
};

#endif // CPLAYER_H
