#ifndef FRUIT_H
#define FRUIT_H

class Field;

class Fruit
{
public:
    Fruit(int x = 0, int y = 0);
    bool draw(Field &) const;

private:
    const int m_x;
    const int m_y;
};

#endif // FRUIT_H
