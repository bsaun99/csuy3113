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

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Entity.h"
#define PLATFORM_COUNT 20

#define ENEMY_COUNT 3

struct GameState {
    Entity *player;
    Entity *platforms;
    Entity *enemies;
    Entity *font;
};

GameState state;
GLuint fontTextureID;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix, laserMatrix;


GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
    
    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_image_free(image);
    return textureID;
}

//GLint laserTextureID = LoadTexture("laser.png");

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("RISE OF THE AI!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Initialize Font
    fontTextureID = LoadTexture("font1.png");
    
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(-3.5,0,0);
    state.player->movement = glm::vec3(0);
    state.player->velocity = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0); // use this to change the speed he falls
    state.player->speed = 1.5f;
    state.player->textureID = LoadTexture("betty.png");
    
    state.player->animRight = new int[4] {3, 7, 11, 15};
    state.player->animLeft = new int[4] {1, 5, 9, 13};
    state.player->animUp = new int[4] {2, 6, 10, 14};
    state.player->animDown = new int[4] {0, 4, 8, 12};
    
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    state.player->jumpPower = 7.0f;
    
    state.platforms = new Entity[PLATFORM_COUNT];
    GLuint platformTextureID = LoadTexture("obsidian.png");
    
    /*
    for (int i=0; i < 11; i++) {
        state.platforms->entityType = PLATFORM;
        state.platforms[i].textureID = platformTextureID;
        state.platforms[i].position = glm::vec3(-5 + i, -3.25f, 0);
    }
     */
    
    state.platforms->entityType = PLATFORM;
    state.platforms[0].textureID = platformTextureID;
    state.platforms[0].position = glm::vec3(-4.5, -3.25f, 0);
    
    state.platforms[1].textureID = platformTextureID;
    state.platforms[1].position = glm::vec3(-3.5, -3.25f, 0);
    
    state.platforms[2].textureID = platformTextureID;
    state.platforms[2].position = glm::vec3(-2.5, -3.25f, 0);
    
    state.platforms[3].textureID = platformTextureID;
    state.platforms[3].position = glm::vec3(-1.5, -3.25f, 0);
    
    state.platforms[4].textureID = platformTextureID;
    state.platforms[4].position = glm::vec3(-0.5, -3.25f, 0);
    
    state.platforms[5].textureID = platformTextureID;
    state.platforms[5].position = glm::vec3(0.5, -3.25f, 0);
    
    state.platforms[6].textureID = platformTextureID;
    state.platforms[6].position = glm::vec3(1.5, -3.25f, 0);
    
    state.platforms[7].textureID = platformTextureID;
    state.platforms[7].position = glm::vec3(2.5, -3.25f, 0);
    
    state.platforms[8].textureID = platformTextureID;
    state.platforms[8].position = glm::vec3(3.5, -3.25f, 0);
    
    state.platforms[9].textureID = platformTextureID;
    state.platforms[9].position = glm::vec3(4.5, -3.25f, 0);
    
    state.platforms[10].textureID = platformTextureID;
    state.platforms[10].position = glm::vec3(-1.2, -1.25f, 0);
    
    state.platforms[11].textureID = platformTextureID;
    state.platforms[11].position = glm::vec3(-2.2, -1.25f, 0);
    
    state.platforms[12].textureID = platformTextureID;
    state.platforms[12].position = glm::vec3(-3.2, -1.25f, 0);
    
    state.platforms[13].textureID = platformTextureID;
    state.platforms[13].position = glm::vec3(1, 0.3, 0);
    
    state.platforms[14].textureID = platformTextureID;
    state.platforms[14].position = glm::vec3(2, 0.3, 0);
    
    state.platforms[15].textureID = platformTextureID;
    state.platforms[15].position = glm::vec3(3, 0.3, 0);
    
    state.platforms[16].textureID = platformTextureID;
    state.platforms[16].position = glm::vec3(5, 1.3, 0);
    
    state.platforms[17].textureID = platformTextureID;
    state.platforms[17].position = glm::vec3(-5, 1.3, 0);
    
    state.platforms[18].textureID = platformTextureID;
    state.platforms[18].position = glm::vec3(5, 2.3, 0);
    
    state.platforms[19].textureID = platformTextureID;
    state.platforms[19].position = glm::vec3(-5, 2.3, 0);

    for (int i=0; i< PLATFORM_COUNT; i++) {
        state.platforms[i].Update(0, NULL, NULL, NULL, 0, 0);
    }
    
    state.enemies = new Entity[ENEMY_COUNT];
    state.enemies[0].entityType = ENEMY;
    
    // First Enemy
    GLint enemyTextureID = LoadTexture("32x32-bat-sprite.png");
    
    state.enemies[0].animRight = new int[4] {12, 13, 14, 15};
    state.enemies[0].animLeft = new int[4] {4, 5, 6, 7};
    state.enemies[0].animUp = new int[4] {0, 1, 2, 3};
    state.enemies[0].animDown = new int[4] {0, 1, 2, 3};
    
    state.enemies[0].animIndices = state.enemies->animRight;
    state.enemies[0].animFrames = 4;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;
    state.enemies[0].animCols = 4;
    state.enemies[0].animRows = 4;
    
    state.enemies[0].height = 0.7f;
    state.enemies[0].width = 0.7f;
    
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(-3, 1.35, 0);
    state.enemies->speed = 1;
    state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = WALKING;
    
    // Second enemy
    state.enemies[1].entityType = ENEMY;
    GLint enemy2TextureID = LoadTexture("chewbacca.png");
    state.enemies[1].textureID = enemy2TextureID;
    
    state.enemies[1].position = glm::vec3(4, -2.35, 0);
    state.enemies->speed = 1;
    state.enemies[1].aiType = FLYER;
    state.enemies[1].aiState = IDLE;
    
    state.enemies[1].height = 0.8f;
    state.enemies[1].width = 0.8f;
    
    
    // Third enemy
    state.enemies[2].entityType = ENEMY;
    GLint enemy3TextureID = LoadTexture("monster.png");
    state.enemies[2].textureID = enemy3TextureID;
    
    state.enemies[2].animRight = new int[3] {3, 4, 5};
    state.enemies[2].animLeft = new int[3] {9, 10, 11};
    state.enemies[2].animUp = new int[3] {0, 1, 2}; 
    state.enemies[2].animDown = new int[3] {6, 7, 8};
    
    state.enemies[2].animIndices = state.enemies->animRight;
    state.enemies[2].animFrames = 3;
    state.enemies[2].animIndex = 0;
    state.enemies[2].animTime = 0;
    state.enemies[2].animCols = 3;
    state.enemies[2].animRows = 4;
    
    state.enemies[2].position = glm::vec3(3, 1.3, 0);
    state.enemies->speed = 1;
    state.enemies[2].aiType = WAITANDGO;
    state.enemies[2].aiState = WALKING;
    
    state.enemies[2].height = 0.8f;
    state.enemies[2].width = 0.8f;
     

    
}


void ProcessInput() {
    
    state.player->movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // Move the player left
                        break;
                        
                    case SDLK_RIGHT:
                        // Move the player right
                        break;
                        
                    case SDLK_SPACE:
                        if (state.player->collidedBottom) {
                           state.player->jump = true;
                        }
                        break;
                }
                break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_LEFT]) {
        state.player->movement.x = -1.0f;
        state.player->animIndices = state.player->animLeft;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        state.player->movement.x = 1.0f;
        state.player->animIndices = state.player->animRight;
    }
    
    if (glm::length(state.player->movement) > 1.0f) {
        state.player->movement = glm::normalize(state.player->movement);
    }
    
    if (state.enemies[0].collidedLeft) {
        state.enemies[0].movement.x = -1;
    }
    else if (state.enemies[0].collidedRight) {
        state.enemies[0].movement.x = 1;
    }
    
    for (int i=0; i<ENEMY_COUNT; i++) {
        if (state.player->collidedBottom == true && state.enemies[i].collidedTop == true) {
            state.enemies[i].isActive = false;
            state.enemies[i].aiState = IDLE;
        }
    }
    
}

void DrawText(ShaderProgram *program, GLuint fontTextureID, std::string text, float size, float spacing, glm::vec3 position) {
    float width = 1.0f / 16.0f;
    float height = 1.0f / 16.0f;
    
    std::vector<float> vertices;
    std::vector<float> texCoords;
    
    for(int i = 0; i < text.size(); i++) {
        
        int index = (int)text[i];
        float offset = (size + spacing) * i;
        float u = (float)(index % 16) / 16.0f;
        float v = (float)(index / 16) / 16.0f;
        
        vertices.insert(vertices.end(), {
            offset + (-0.5f * size), 0.5f * size,
            offset + (-0.5f * size), -0.5f * size,
            offset + (0.5f * size), 0.5f * size,
            offset + (0.5f * size), -0.5f * size,
            offset + (0.5f * size), 0.5f * size,
            offset + (-0.5f * size), -0.5f * size,
        });
        texCoords.insert(texCoords.end(), {
            u, v,
            u, v + height,
            u + width, v,
            u + width, v + height,
            u + width, v,
            u, v + height,
        });
    }
    program->SetModelMatrix(modelMatrix);
    
    glUseProgram(program->programID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glBindTexture(GL_TEXTURE_2D, fontTextureID);
    glDrawArrays(GL_TRIANGLES, 0, (int)(text.size() * 6));
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;
void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }
    
    while (deltaTime >= FIXED_TIMESTEP) {
        // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
        state.player->Update(FIXED_TIMESTEP, state.player, state.enemies, state.platforms, PLATFORM_COUNT, ENEMY_COUNT);
        
        for (int i=0; i<ENEMY_COUNT; i++){
            state.enemies[i].Update(FIXED_TIMESTEP, state.player, state.enemies, state.platforms, PLATFORM_COUNT, ENEMY_COUNT);
        }
        
        deltaTime -= FIXED_TIMESTEP;
    }
    
    accumulator = deltaTime;
}
/*
void drawLaser() {
    program.SetModelMatrix(laserMatrix);
    glBindTexture(GL_TEXTURE_2D, laserTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
*/
void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int i =0; i<PLATFORM_COUNT; i++) {
        state.platforms[i].Render(&program);
    }
    
    for (int i=0; i<ENEMY_COUNT; i++){
        state.enemies[i].Render(&program);
    }
    
    glUseProgram(program.programID);
    state.player->Render(&program);
    
    if (state.player->playerType == LOSER) {
        DrawText(&program, fontTextureID, "YOU LOSE", 0.5f, -0.25f, glm::vec3(0.0f, 0.0f, 0));
    }
    else if (state.player->playerType == WINNER) {
        DrawText(&program, fontTextureID, "YOU WIN", 0.5f, -0.25f, glm::vec3(0.0f, 0.0f, 0));
    }
    

    //drawLaser();
    
    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}

