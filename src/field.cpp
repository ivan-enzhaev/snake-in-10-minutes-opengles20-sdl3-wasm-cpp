#include "field.h"
#include "painter.h"
#include <cstdlib>
#include <ctime>

Field::Field()
{
    for (int y = 0; y < Field::HEIGHT; ++y)
    {
        for (int x = 0; x < Field::WIDTH; ++x)
        {
            m_m[y][x] = Field::EMPTY;
        }
    }

    this->newFruit();
}

void Field::setBlock(Field::Type type, int x, int y)
{
    m_m[y][x] = type;
}

Field::Type Field::block(int x, int y) const
{
    return m_m[y][x];
}

void Field::draw(Painter *p) const
{
    for (int y = 0; y < Field::HEIGHT; ++y)
    {
        for (int x = 0; x < Field::WIDTH; ++x)
        {
            switch (m_m[y][x])
            {
                case Field::EMPTY:
                {
                    break;
                }
                case Field::SNAKE_BLOCK:
                {
                    p->rectangle(x * (float) Field::BLOCK_WIDTH,
                        y * (float) Field::BLOCK_HEIGHT,
                        (float) Field::BLOCK_WIDTH,
                        (float) Field::BLOCK_HEIGHT, glm::vec3(0.058f, 0.615f, 0.345f));
                    break;
                }
                case Field::FRUIT:
                {
                    p->circle(x * (float) Field::BLOCK_WIDTH + (float) Field::BLOCK_WIDTH / 2.f,
                        y * (float) Field::BLOCK_HEIGHT + (float) Field::BLOCK_HEIGHT / 2.f,
                        (float) Field::BLOCK_WIDTH / 2.f - 1.f, glm::vec3(0.8f, 0.1f, 0.3f));
                    break;
                }
            }
        }
    }
}

void Field::newFruit()
{
    int x, y;
    std::srand(std::time(NULL));
    do
    {
        x = std::rand() % Field::WIDTH;
        y = std::rand() % Field::HEIGHT;
    } while (this->block(x, y) != Field::EMPTY);
    this->setBlock(Field::FRUIT, x, y);
}
