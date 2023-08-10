#ifndef CAI_H
#define CAI_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "../include/sRect.h"
#include "../include/sAABB.h"

struct sPoint {
    sPoint() = default;
    sPoint(int X, int Y) : x(X), y(Y) { }

    int x { 0 };
    int y { 0 };
};

class cAI {
public:
    cAI() = default;

    virtual ~cAI();

public:
    std::vector<std::pair<int, int>> calc();
    void init(sRect* start = nullptr, sRect* end = nullptr);
    void clearShortTermMemory() {
        m_instructions.clear();
    }

    // Identify a path from m_start to m_end (any given two points within the rectangular range)
    sRect m_start { 0, 0, 0, 0 };
    sRect m_end { 0, 0, 0, 0 };

    sRect m_self { 0, 0, 0, 0 };
    sRect m_objective { 0, 0, 0, 0 };

    bool m_pathCalculated { false };
    bool m_actuate { false };
    std::vector<sPoint> m_instructions { };
    int m_attempts { 0 };
    bool m_initiated { false };

private:
    sAABB m_startPoint;
    sAABB m_endPoint;
};

#endif // CAI_H
