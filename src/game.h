#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include "field.h"
#include "snake.h"

class Painter;

class Game
{
public:
    Game();
    void newGame();
    void tick();
    void draw(Painter *) const;
    void keyEvent(Snake::Direction);
    Snake::Status status() const;
    size_t snakeSize() const;
    size_t snakeMaxSize() const;

private:
    Field m_field;
    Snake m_snake;
    size_t m_maxSize;
    Snake::Status m_status;
};

#endif // GAME_H
