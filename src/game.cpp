#include "game.h"
#include "painter.h"

Game::Game()
    : m_maxSize(m_snake.maxSize())
    , m_status(m_snake.status())
{
}

void Game::draw(Painter *p) const
{
    m_field.draw(p);
}

void Game::keyEvent(Snake::Direction d)
{
    m_snake.keyEvent(d);
}

size_t Game::snakeSize() const
{
    return m_snake.size();
}

size_t Game::snakeMaxSize() const
{
    return m_snake.maxSize();
}

void Game::newGame()
{
    m_snake = Snake();
    m_field = Field();
    m_maxSize = m_snake.maxSize();
    m_status = m_snake.status();
}

Snake::Status Game::status() const
{
    return m_status;
}

void Game::tick()
{
    m_snake.tick(m_field);
    Snake::Status status = m_snake.status();
    switch (status)
    {
        case Snake::INCREASED:
            m_status = Snake::INCREASED;
            break;
        case Snake::LIVE:
            m_status = Snake::LIVE;
            break;
        case Snake::WIN:
            m_status = Snake::WIN;
            break;
        case Snake::DEAD:
            m_status = Snake::DEAD;
            break;
    }
}
