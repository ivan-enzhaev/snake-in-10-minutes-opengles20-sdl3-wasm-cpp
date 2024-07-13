#include "snake.h"
#include "field.h"
#include <cstdlib>
#include <ctime>

Snake::Snake()
{
    m_status = Snake::LIVE;
    m_maxSize = 20;
    std::srand(std::time(NULL));
    std::rand();
    m_direction = static_cast<Snake::Direction>(std::rand() % 4);
    m_blocks.push_back(std::pair<int, int>(Field::WIDTH / 2,
        Field::HEIGHT / 2));
}

Snake::Status Snake::status() const
{
    return m_status;
}

void Snake::tick(Field &field)
{
    std::pair<int, int> p = m_blocks.front();
    switch (m_direction)
    {
        case Snake::LEFT:
            --(p.first);
            break;
        case Snake::UP:
            --(p.second);
            break;
        case Snake::RIGHT:
            ++(p.first);
            break;
        case Snake::DOWN:
            ++(p.second);
            break;
    }

    if ((p.first < 0) || (p.first >= Field::WIDTH) ||
        (p.second < 0) || (p.second >= Field::HEIGHT))
    {
        m_status = Snake::DEAD;
        return;
    }

    if (field.block(p.first, p.second) == Field::SNAKE_BLOCK)
    {
        m_status = Snake::DEAD;
        return;
    }

    m_blocks.push_front(p);

    if (field.block(p.first, p.second) != Field::FRUIT)
    {
        field.setBlock(Field::SNAKE_BLOCK, p.first, p.second);
        std::pair<int, int> p = m_blocks.back();
        field.setBlock(Field::EMPTY, p.first, p.second);
        m_blocks.pop_back();
        m_status = Snake::LIVE;
    }
    else
    {
        field.setBlock(Field::SNAKE_BLOCK, p.first, p.second);
        field.newFruit();
        m_status = Snake::INCREASED;
    }

    if (m_blocks.size() == m_maxSize)
    {
        m_status = Snake::WIN;
        return;
    }
}

void Snake::keyEvent(Snake::Direction d)
{
    if (d == m_direction)
    {
        return;
    }

    switch (d)
    {
        case Snake::LEFT:
            if (m_direction == Snake::RIGHT)
            {
                return;
            }
            break;
        case Snake::UP:
            if (m_direction == Snake::DOWN)
            {
                return;
            }
            break;
        case Snake::RIGHT:
            if (m_direction == Snake::LEFT)
            {
                return;
            }
            break;
        case Snake::DOWN:
            if (m_direction == Snake::UP)
            {
                return;
            }
            break;
    }

    m_direction = d;
}

size_t Snake::maxSize() const
{
    return m_maxSize;
}

size_t Snake::size() const
{
    return m_blocks.size();
}
