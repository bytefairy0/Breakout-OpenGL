#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game_level.h>

using namespace std;

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// collision typedef
typedef tuple<bool, Direction, glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

class Game{
public:
    GameState               State;   // state
    bool                    Keys[1024];     // Input
    unsigned int            Width, Height;   // Dimensions
    vector<GameLevel>       Levels;
    unsigned int            Level;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state 
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions();
    // reset 
    void ResetLevel();
    void ResetPlayer();
};


#endif