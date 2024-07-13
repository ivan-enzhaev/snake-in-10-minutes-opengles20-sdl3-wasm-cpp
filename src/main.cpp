#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengles2.h>

#include <iostream>
#include <map>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif // __EMSCRIPTEN__

#define GLM_FORCE_PURE
#include <glm/glm.hpp>

#include "game.h"
#include "painter.h"

Game *game;
Painter *painter;

std::map<std::string, bool> keys;

struct AppContext
{
    SDL_Window *window;
    SDL_GLContext glcontext;
    SDL_bool app_quit = SDL_FALSE;
};

int SDL_Fail()
{
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
    return -1;
}

int SDL_AppInit(void **appstate, int argc, char *argv[])
{
    // init the library, here we make a window so we only need the Video capabilities.
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        return SDL_Fail();
    }

    // create a window
    SDL_Window *window = SDL_CreateWindow("Snake in 10 minutes using OpenGL ES 2.0, SDL3, Emscripten, and C++", 480, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        return SDL_Fail();
    }

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // Enable MULTISAMPLE
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2); // can be 2, 4, 8 or 16

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    if (!glcontext)
    {
        return SDL_Fail();
    }

    glClearColor(0.188f, 0.22f, 0.255f, 1.f);

    game = new Game();
    game->newGame();
    painter = new Painter();

    SDL_ShowWindow(window);

    // set up the application data
    *appstate = new AppContext {
        window,
        glcontext,
    };

    return 0;
}

int SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    auto *app = (AppContext *)appstate;

    switch (event->type)
    {
        case SDL_EVENT_KEY_DOWN:
        {
            if (event->key.scancode == SDL_SCANCODE_W)
            {
                keys["up"] = true;
            }

            if (event->key.scancode == SDL_SCANCODE_S)
            {
                keys["down"] = true;
            }

            if (event->key.scancode == SDL_SCANCODE_A)
            {
                keys["left"] = true;
            }

            if (event->key.scancode == SDL_SCANCODE_D)
            {
                keys["right"] = true;
            }

            break;
        }
        case SDL_EVENT_KEY_UP:
        {
            if (event->key.scancode == SDL_SCANCODE_W)
            {
                keys["up"] = false;
            }

            if (event->key.scancode == SDL_SCANCODE_S)
            {
                keys["down"] = false;
            }

            if (event->key.scancode == SDL_SCANCODE_A)
            {
                keys["left"] = false;
            }

            if (event->key.scancode == SDL_SCANCODE_D)
            {
                keys["right"] = false;
            }

            break;
        }
        case SDL_EVENT_QUIT:
        {
            app->app_quit = SDL_TRUE;
            break;
        }
        default:
        {
            break;
        }
    }

    return 0;
}

void keyboardHandler()
{
    if (keys["up"])
    {
        game->keyEvent(Snake::UP);
    }

    if (keys["down"])
    {
        game->keyEvent(Snake::DOWN);
    }

    if (keys["left"])
    {
        game->keyEvent(Snake::LEFT);
    }

    if (keys["right"])
    {
        game->keyEvent(Snake::RIGHT);
    }
}

uint32_t lastTickTime = 0;
float timer = 0.f;

int SDL_AppIterate(void *appstate)
{
    auto *app = (AppContext *)appstate;

    uint32_t currentTickTime = SDL_GetTicks();
    float deltaTime = (currentTickTime - lastTickTime) / 1000.f;
    lastTickTime = currentTickTime;

    keyboardHandler();

    timer += deltaTime;
    if (timer > 0.3f)
    {
        Snake::Status status = game->status();

        switch( status ) {
            case Snake::LIVE:
                break;
            case Snake::INCREASED:
                break;
            case Snake::DEAD:
                game->newGame();
                break;
            case Snake::WIN:
                break;
        }

        game->tick();
        timer = 0.f;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    game->draw(painter);
    SDL_GL_SwapWindow(app->window);

    return app->app_quit;
}

void SDL_AppQuit(void *appstate)
{
    auto *app = (AppContext *)appstate;
    if (app)
    {
        SDL_GL_DeleteContext(app->glcontext);
        SDL_DestroyWindow(app->window);
        delete app;
    }

    delete game;
    delete painter;

    SDL_Quit();
}
