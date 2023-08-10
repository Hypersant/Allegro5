#ifndef SRECT_H
#define SRECT_H


class sRect {
public:
    sRect() = default;
    sRect(int x = 0, int y = 0, int width = 0, int height = 0);

    int m_X { 0 };
    int m_Y { 0 };
    int m_width { 0 };
    int m_height { 0 };

protected:

private:
};

#endif // SRECT_H
