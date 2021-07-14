#include "Entity.h"

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    speed = 0;
    
    modelMatrix = glm::mat4(1.0f);
}

bool Entity::CheckCollision(Entity *other) {
    if (other == this) return false;
    
    if (isActive == false || other->isActive == false) return false;
    
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    
    if (xdist < 0 && ydist < 0) return true;
    return false;
}

void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity *object = &objects[i];
        
        if (CheckCollision(object))
        {
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
            }
        }
    }
}

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity *object = &objects[i];
        
        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
            }
        }
    }
}

void Entity::GameOver(Entity* player, Entity* enemy) {
    switch(playerState){
        case ALIVE:
            if (enemy->isActive == false && player->isActive == true) {
                playerType = WINNER;
            }
            else if (enemy->isActive == true && player->isActive == true) {
                playerType = IN_PROGRESS;
            }
            break;
        
        case DEAD:
            if (player->isActive == false){
                playerType = LOSER;
            }
            break;
    }
}

void Entity::AI(Entity* player) {
    switch(aiType){
        case WALKER:
            AIWalker();
            break;
            
        case WAITANDGO:
            AIWaitAndGo(player);
            break;
            
        case PATROLLER:
            AIPatroller();
            break;
            
        case FLYER:
            AIFlyer();
            break;
            
        case SHOOTER:
            AIShooter();
            break;
    }
}


void Entity::AIWalker() {
    movement = glm::vec3(-1,0,0);
}

void Entity::AIPatroller() {
    movement = glm::vec3(-1,0,0);
    if (position.x >= 4.5f) {
        movement.x = -1.0 ;
    }
    else if (position.x <= -4.5f){
        movement.x = 1.0 ;
    }
}

void Entity::AIFlyer() {
    movement = glm::vec3(0,1,0);
    if (position.y >= 4.5f) {
        movement.y = -1.0 ;
    }
    else if (position.y <= 1.5f){
        movement.y = 1.0 ;
    }
}

void Entity::AIShooter() {
    if (laser > -5.3) {
        laser -= 6.0f;
    }
    else {
        laser += 11.8f ; // returns the laser back to Chewbaccas weapon to make it appear like he is constantly shooting
    }
    laserMatrix = glm::mat4(1.0f); //setting the model matrix to the identity matrix
    laserMatrix = glm::translate(laserMatrix, glm::vec3(laser, -0.4f, 0.0f));
}

void Entity::AIWaitAndGo(Entity* player) {
    switch(aiState) {
        case IDLE:
            if (glm::distance(position,player->position) < 3.0f){
                aiState = WALKING;
            }
            break;
        
        case WALKING:
            if (player->position.x < position.x){
                movement = glm::vec3(-1,0,0);
            }
            else {
                movement = glm::vec3(1,0,0);
            }
            break;
        
        case ATTACKING:
            if (CheckCollision(player) == true) {
                aiState = IDLE;
                player->isActive = false;
                player->playerState = DEAD;
            }
            break;
    }
}

void Entity::Update(float deltaTime, Entity* player, Entity* enemies, Entity *platforms, int platformCount, int enemyCount)
{
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    if (entityType == ENEMY){
        AI(player);
    }
    
    if (animIndices != NULL) {
        if (glm::length(movement) != 0) {
            animTime += deltaTime;

            if (animTime >= 0.25f)
            {
                animTime = 0.0f;
                animIndex++;
                if (animIndex >= animFrames)
                {
                    animIndex = 0;
                }
            }
        } else {
            animIndex = 0;
        }
    }
    
    if (jump) {
        jump = false;
        velocity.y += jumpPower;
    }
    
    velocity.x = movement.x * speed;
    velocity += acceleration * deltaTime;
    
    position.y += velocity.y * deltaTime; // Move on Y
    CheckCollisionsY(platforms, platformCount);// Fix if needed
    
    position.x += velocity.x * deltaTime; // Move on X
    CheckCollisionsX(platforms, platformCount);// Fix if needed
    
    CheckCollisionsX(enemies, enemyCount);
    CheckCollisionsY(enemies, enemyCount);
    
    sensorRight = glm::vec3(position.x + 0.6f, position.y - 0.6f, 0);
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;
    
    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
    if (isActive == false) return;
    
    program->SetModelMatrix(modelMatrix);
    
    if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
