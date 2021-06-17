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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, player1Matrix,player2Matrix,starMatrix, projectionMatrix;

//        Player 1: Position, Movement, and Speed
glm::vec3 player1_position = glm::vec3(4.5, 0, 0); // position
glm::vec3 player1_movement = glm::vec3(0, 0, 0); // velocity
float player1_speed = 1.0f; // acceleration

//        Player 2: Position, Movement, and Speed
glm::vec3 player2_position = glm::vec3(-4.5, 0, 0); // position
glm::vec3 player2_movement = glm::vec3(0, 0, 0); // velocity
float player2_speed = 1.0f; // acceleration

//        Star: Position, Movement, and Speed
glm::vec3 star_position = glm::vec3(0, 0, 0); // position
glm::vec3 star_movement = glm::vec3(0, 0, 0); // velocity
float star_speed = 1.0f; // acceleration

GLuint pinkKirbyTextureID, blueKirbyTextureID, starTextureID;

int w=5, h=5, n=5;
GLuint LoadTexture(const char* filePath, int w, int h, int n) {
    
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

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Kirby Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    player1Matrix = glm::mat4(1.0f);
    player2Matrix = glm::mat4(1.0f);
    starMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background color
    
    glEnable(GL_BLEND);
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Loaded images
    pinkKirbyTextureID = LoadTexture("pink kirby.png", w, h, n);
    blueKirbyTextureID = LoadTexture("blue kirby.png", w, h, n);
    starTextureID = LoadTexture("star.png", w, h, n);
    
}

void ProcessInput() {
    
    player1_movement = glm::vec3(0);
    player2_movement = glm::vec3(0);
    star_movement = glm::vec3(0);
    
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
                    // pressing the spacebar will start the game
                    case SDLK_SPACE:
                        // Some sort of action
                        star_speed = 1.0f;
                        star_movement.x += 1.0f;
                        star_movement.y += 1.0f;
                        break;
                }
                break; // SDL_KEYDOWN
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                        if (gameIsRunning) {
                            star_speed = 1.0f;
                            star_movement.x += 1.0f;
                            star_movement.y += 1.0f;
                        }
                        else {
                            star_speed = 0.0f;
                            star_movement.x += 0.0f;
                            star_movement.y += 0.0f;
                        }
                        break;
                }
                break; // SDL_KEYUP
        }
        
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_UP]) {
        player1_movement.y = 3.0f;
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        player1_movement.y = -3.0f;
    }
    if (keys[SDL_SCANCODE_W]) {
        player2_movement.y = 3.0f;
    }
    else if (keys[SDL_SCANCODE_S]) {
        player2_movement.y = -3.0f;
    }
    
    // if holding down the buttons at the same time, they move at the same speed
    if (glm::length(player1_movement) > 3.0f) {
        player1_movement = glm::normalize(player1_movement);
    }
    else if (glm::length(player2_movement) > 3.0f) {
        player2_movement = glm::normalize(player2_movement);
    }
    
    // limits the movement of players to prevent paddles from going outside the window
    if (player1_position.y > 3.3) {
        player1_position.y = 3.3;
    }
    else if (player1_position.y < -3.3) {
        player1_position.y = -3.3;
    }
    if (player2_position.y > 3.3) {
        player2_position.y = 3.3;
    }
    else if (player2_position.y < -3.3) {
        player2_position.y = -3.3;
    }
    
    if (star_position.x > 640){
        star_position.x = 640;
        star_position.x -= 1;
        star_movement *= -1;
        
    }
    else if (star_position.x < 0 ){
        star_position.x = 0;
        star_movement *= 1;
    }
    // Collision with the top of the screen
    else if (star_position.y > 480 ){
        //star_position.y = 480;
        star_movement *= -1;
    }
    else if (star_position.y < 0 ){
        //star_position.y = 0;
        star_movement *= fabs(star_movement.x) ;
        star_movement *= fabs(star_movement.y) ;
        star_movement = glm::normalize(star_movement) ;
    }
    
    // Box-to-Box Collision
    // Player 1 Collision Variables
    float x1diff = fabs(star_position.x - player1_position.x);
    float y1diff = fabs(star_position.y - player1_position.y);
    
    float x1dist = x1diff - ((2*w)/ 2.0f);
    float y1dist = y1diff - ((2*h)/ 2.0f);
    
    // if they are colliding
    if (x1dist < 0 && y1dist < 0 ) {
        star_movement *= -1;
    }
    
    // Player 2 Collision Variables
    float x2diff = fabs(star_position.x - player2_position.x);
    float y2diff = fabs(star_position.y - player2_position.y);
    
    float x2dist = x2diff - ((2*w)/ 2.0f);
    float y2dist = y2diff - ((2*h)/ 2.0f);

    // if they are colliding
    if (x2dist < 0 && y2dist < 0 ) {
        star_movement *= -1;
    }
    
}

float lastTicks = 0.0f;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    star_position.x += star_movement.x * star_speed;
    star_position.y += star_movement.y * star_speed;
    //star_speed += 3.0f;
    
    // Add (direction * units per second * elapsed time)
    player1_position += player1_movement * player1_speed * deltaTime;
    player1Matrix = glm::mat4(1.0f);
    player1Matrix = glm::translate(player1Matrix, player1_position);
    
    player2_position += player2_movement * player2_speed * deltaTime;
    player2Matrix = glm::mat4(1.0f);
    player2Matrix = glm::translate(player2Matrix, player2_position);
    
    star_position += star_movement * star_speed * deltaTime;
    starMatrix = glm::mat4(1.0f);
    starMatrix = glm::translate(starMatrix, star_position);
}

void drawPlayer1() {
    program.SetModelMatrix(player1Matrix);
    glBindTexture(GL_TEXTURE_2D, pinkKirbyTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
void drawPlayer2() {
    program.SetModelMatrix(player2Matrix);
    glBindTexture(GL_TEXTURE_2D, blueKirbyTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
void drawStar() {
    program.SetModelMatrix(starMatrix);
    glBindTexture(GL_TEXTURE_2D, starTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Render() {
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    
    // draws 2d images
    drawPlayer1();
    drawPlayer2();
    drawStar();
    
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);
    
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

