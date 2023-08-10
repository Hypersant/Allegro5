#include "cAI.h"

cAI::~cAI() {
    //dtor
}

std::vector<std::pair<int, int>> cAI::calc() {
    std::vector<std::pair<int, int>> inst { };

    //while (self.rect.hasCollided(other.rect) != true) {
    // subtract X, subtract Y as needed
    // add to instruction set
    // COLLISION IS ***GUARANTEED***
    //}

    //std::vector<std::pair<int, int>>::iterator it = inst.begin();
    /*
        std::string toPrint { "START: [ " + std::to_string(start.first) + ", " + std::to_string(start.second) + " ]" };
        std::string toPrint2 { "END:   [ " + std::to_string(stop.first) + ", " + std::to_string(stop.second) + " ]" };

        al_draw_text(G_FONT, al_map_rgba(0, 255, 0, 0), 600, 25, 0, toPrint.c_str());
        al_draw_text(G_FONT, al_map_rgba(255, 0, 0, 0), 600, 35, 0, toPrint2.c_str());

        //std::cerr << "** START **\n";

        // First pass must be 1:1 pixel-alignment (could be optimized by a range-bound-check)
        // Second pass can reduce per segment movements by Nth amounts
        // Desired moves to be made (must be connected +/- by N units of length)
        while (start != stop) {
            //std::cerr << "[SIZE] " << inst.size() << " | " << start.first << ", " << start.second << " | " << stop.first << ", " << stop.second << "\n";
            int x = 0;
            int y = 0;

            if (start.first > stop.first) {
                x = std::get<0>(start) -= 1;
                //start.first -= 1;

                al_draw_line(start.first, start.second, stop.first, stop.second, al_map_rgb(255, 0, 0), -1);
            } else if (start.first < stop.first) {
                x = std::get<0>(start) += 1;
                //start.first += 1;

                al_draw_line(start.first, start.second, stop.first, stop.second, al_map_rgb(0, 255, 0), -1);
            }

            if (start.second > stop.second) {
                y = std::get<1>(start) -= 1;
                //start.second -= 1;

                al_draw_line(start.first, start.second, stop.first, stop.second, al_map_rgb(0, 0, 255), -1);

            } else if (start.second < stop.second) {
                y = std::get<1>(start) += 1;
                //start.second += 1;

                al_draw_line(start.first, start.second, stop.first, stop.second, al_map_rgb(127, 0, 127), -1);
            }

            // Add next move (pixel-by-pixel)
            inst.emplace_back(std::make_pair(x, y));
        }

        //std::cerr << "** END **\n";
    */
    return inst;
}

void cAI::init(sRect* start, sRect* end) {
    sRect tmp { *start };

    std::cout << "m_self's data (Gill's rectangular box)\n" << m_self.m_X << " <-> " << m_self.m_width << "\n" << m_self.m_Y << " <-> " << m_self.m_height << "\n-- -- -- -- --\n\n"
              << "m_objective's data (target rectangular box)\n" << m_objective.m_X << " <-> " << m_objective.m_width << "\n" << m_objective.m_Y << " <-> " << m_objective.m_height << "\n-- -- -- -- --\n\n";

    bool bRun = false;

    while (!bRun) {
        if (m_self.m_X > m_objective.m_X) {
            m_self.m_X--;
        } else if (m_self.m_X < m_objective.m_X) {
            m_self.m_X++;
        }

        if (m_self.m_Y > m_objective.m_Y) {
            m_self.m_Y--;
        } else if (m_self.m_Y < m_objective.m_Y) {
            m_self.m_Y++;
        }

        if (m_self.m_X == m_objective.m_X && m_self.m_Y == m_objective.m_Y) {
            bRun = true;
        }
        m_instructions.emplace_back(sPoint{ m_self.m_X, m_self.m_Y });
    }

    for (const auto& f : m_instructions) {
        //std::cout << "{ " << f.x << ", " << f.y << " }\n";
    }

    m_pathCalculated = true;
}
