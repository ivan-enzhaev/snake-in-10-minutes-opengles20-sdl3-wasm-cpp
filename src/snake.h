#ifndef SNAKE_H
#define SNAKE_H

#include <cstddef>
#include <list>
#include <utility>

class Field;

class Snake
{
public:
    enum Status
    {
        INCREASED,
        LIVE,
        WIN,
        DEAD
    };
    enum Direction
    {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };
    Snake();
    void tick(Field &);
    void keyEvent(Direction);
    size_t size() const;
    size_t maxSize() const;
    Snake::Status status() const;

private:
    typedef std::list<std::pair<int, int>> Blocks;
    Blocks m_blocks;
    Direction m_direction;
    Snake::Status m_status;
    size_t m_maxSize;
};

#endif // SNAKE_H
