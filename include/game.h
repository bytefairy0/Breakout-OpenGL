#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game{
public:
    GameState               State;   // state
    bool                    Keys[1024];     // Input
    unsigned int            Width, Height;   // Dimensions
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state 
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};

#endif