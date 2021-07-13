#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

enum EntityType {PLAYER, PLATFORM, ENEMY};

enum PlayerState {ALIVE, DEAD};
enum PlayerType {WINNER, LOSER};

enum AIType {WALKER, WAITANDGO, PATROLLER, FLYER, SHOOTER};
enum AIState {IDLE, WALKING, ATTACKING};

class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState;
    PlayerState playerState;
    PlayerType playerType;
    
    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    glm::vec3 sensorRight;
    float speed;
    
    float width = 1;
    float height = 1;
    
    bool jump = false;
    float jumpPower = 0;
    GLuint textureID;
    GLuint fontTextureID;

    
    glm::mat4 modelMatrix;
    glm::mat4 laserMatrix;
    float laser;
    
    int *animRight = NULL;
    int *animLeft = NULL;
    int *animUp = NULL;
    int *animDown = NULL;

    int *animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;
    
    bool isActive = true;
    
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    
    Entity();
    
    bool CheckCollision(Entity *other);
    void CheckCollisionsY(Entity *objects, int objectCount);
    void CheckCollisionsX(Entity *objects, int objectCount);
    
    void Update(float deltaTime, Entity* player, Entity* enemies, Entity *platforms, int platformCount, int enemyCount);
    void Render(ShaderProgram *program);
    void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
    void DrawText(ShaderProgram *program, GLuint fontTextureID, std::string text, float size, float spacing, glm::vec3 position);
    
    void GameState(Entity* player);
    void GameOver(Entity* player, Entity* enemy);
    void AI(Entity* player);
    void AIWalker();
    void AIPatroller();
    void AIFlyer();
    void AIShooter();
    void AIWaitAndGo(Entity* player) ;
};
