#include "game.h"
#include "resource_manager.h"
#include <sprite_renderer.h>
#include <game_object.h>
#include <ball_object.h>

using namespace std;

SpriteRenderer *Renderer;
GameObject *Player;
BallObject *Ball;

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Ball;
}

void Game::Init()
{
   // load shaders
   ResourceManager::LoadShader("src/sprite.vs", "src/sprite.fs", nullptr, "sprite");

   // configure shaders
   glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
                            static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load texture
    ResourceManager::LoadTexture("resources/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("resources/background.jpg", false, "background");
    ResourceManager::LoadTexture("resources/block.png", false, "block");
    ResourceManager::LoadTexture("resources/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("resources/paddle.png", true, "paddle");
    
    // load levels
    GameLevel one; one.Load("resources/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("resources/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("resources/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("resources/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    // game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}

void Game::Update(float dt)
{
    Ball->Move(dt, this->Width);
    // check collisions
    this->DoCollisions();
    if (Ball->Position.y >= this->Height){
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f){
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x){
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
            if (this->Keys[GLFW_KEY_SPACE])
                Ball->Stuck = false;
        }
    }
}

void Game::Render()
{
    // background
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
    // draw level
    this->Levels[this->Level].Draw(*Renderer);
    // draw player
    Player->Draw(*Renderer);
    // draw ball
    Ball->Draw(*Renderer);
}

void Game::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("resources/one.lvl", this->Width, this->Height / 2);
    else if (this->Level == 1)
        this->Levels[1].Load("resources/two.lvl", this->Width, this->Height / 2);
    else if (this->Level == 2)
        this->Levels[2].Load("resources/three.lvl", this->Width, this->Height / 2);
    else if (this->Level == 3)
        this->Levels[3].Load("resources/four.lvl", this->Width, this->Height / 2);
}


void Game::ResetPlayer()
{
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f), INITIAL_BALL_VELOCITY);
}

bool CheckCollision(GameObject &one, GameObject &two); // AABB - AABB collision
Collision CheckCollision(BallObject &one, GameObject &two); // AABB - Circle collision
Direction VectorDirection(glm::vec2 target); 

void Game::DoCollisions()
{
    for (GameObject &box: this->Levels[this->Level].Bricks){
        if (!box.Destroyed){
            Collision Collision = CheckCollision(*Ball, box);
            if (get<0>(Collision)){ 
                // destroy block if not solid
                if (!box.IsSolid)
                    box.Destroyed = true;
                // collision resolution
                Direction dir = get<1>(Collision);
                glm::vec2 diff_vector = get<2>(Collision);
                if (dir == LEFT || dir == RIGHT){
                    Ball->Velocity.x = -Ball->Velocity.x;
                    // relocate
                    float penetration = Ball->Radius - abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration; 
                    else
                        Ball->Position.x -= penetration; 
                } else {
                Ball->Velocity.y = -Ball->Velocity.y;
                float penetration = Ball->Radius - abs(diff_vector.y);
                if (dir == UP)
                    Ball->Position.y -= penetration; 
                else
                    Ball->Position.y += penetration;
                }
            }
        }
    }

    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && get<0>(result)){
        float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
        float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        float percentage = distance / (Player->Size.x / 2.0f);

        float strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
        Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
    }
}


bool CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
                      two.Position.x + two.Size.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
                      two.Position.y + two.Size.y >= one.Position.y;
    return collisionX && collisionY;
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // centre point
    glm::vec2 center(one.Position + one.Radius);
    // AABB - center, half extends
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    // get D = C-B
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;

    if (glm::length(difference) < one.Radius)
        return make_tuple(true, VectorDirection(difference), difference);
    else
        return make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
    
}

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, -1.0f),
        glm::vec2(-1.0f, 0.0f)
    };

    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++){
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max){
            max = dot_product;
            best_match = i; 
        }
    }
    return (Direction)best_match;
}
    