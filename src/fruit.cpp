#include "fruit.h"
#include "field.h"

Fruit::Fruit(int x, int y)
    : m_x(x)
    , m_y(y)
{
}

bool Fruit::draw(Field &f) const
{
    if (f.block(m_x, m_y) != Field::EMPTY)
    {
        return false;
    }

    f.setBlock(Field::FRUIT, m_x, m_y);

    return true;
}
