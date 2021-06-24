//
//  main.cpp
//  week4 notes
//
//  Created by Bethany Saunders on 6/21/21.
//  Copyright © 2021 Bethany Saunders. All rights reserved.
//

/*              SPRITE, TEXT, AND SPRITE ANIMATION
 ================================================================
 Topic 1: TEXTURE WRAP MODE
 ---------------------------------
 GL_REPEAT
 GL_MIRORED_REPEAT
 GL_CLAMP_TO_EDGE
 GL_CLAMP_TO_BORDER
 
 How we do this:
 glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
 - good to use when repeating tiles:
 
 ================================================================
 Topic 2: TEXTURE ATLAS
 - multiple sprites in a single texture
 ---------------------------------
 Sprite Sheet: a single image that has all the individual sprites that will be used for a game
 
 Tileset: a set of tiles, that are used to build our levels/map of our game
 - We can use texture coordinates to pull out a single tile in the tileset
 
 Fonts: an image of letters in a specific font
 - it contains all the letter and characters needed in a game
 ================================================================
 Topic 3: EVENLY SPACED
 ---------------------------------
 - we cannot create a uniform grid on top of a texture atlas that is not evenly spaced
 ================================================================
 Topic 4: DRAWING A SINGLE SPRITE
 ---------------------------------
 - we need the UV coordinates of the individual sprite
 
 How you do it:
 void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index) {
     float u = (float)(index % cols) / (float)cols;
     float v = (float)(index / cols) / (float)rows;
 
     float width = 1.0f / (float)cols;
     float height = 1.0f / (float)rows;
 
     float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
     u, v + height, u + width, v, u, v};
 
     float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
 
     glBindTexture(GL_TEXTURE_2D, textureID);
 
     glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
     glEnableVertexAttribArray(program->positionAttribute);
 
     glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
     glEnableVertexAttribArray(program->texCoordAttribute);
 
     glDrawArrays(GL_TRIANGLES, 0, 6);
 
     glDisableVertexAttribArray(program->positionAttribute);
     glDisableVertexAttribArray(program->texCoordAttribute);
 }
 ================================================================
 Topic 5: ANIMATION
 ---------------------------------
 How to do it:
 1. Define indices of animation
 2. have a timer
 3. go to next frame when timer hits value
 4. if last frame (go to first) - looping
 ================================================================
 Topic 6: MONOSPACED FONTS
 ---------------------------------
 - same space, same width font
 
 For each character in a string:
 - Draw 2 Triangles
 - Use UV coordinates for character
 
 Depending on the font texture, you may have to shift the character value
 ================================================================
 Topic 7: DRAW TEXT
 ---------------------------------
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
 
 ================================================================
 Topic 8: GAME OBJECT ENTITIES
 ---------------------------------
 ================================================================
 Topic 9: OBJECT POOL
 ---------------------------------
 - maximum number of objects
 - create/ allocate objects ahead of time
 - use bool for active or not
 - you can test with max amount of objects
 - less prone to memory leaks
 ================================================================
 Topic 10: GAME STATE
 ---------------------------------
 - entities, score, lives left, time left, etc.
 
 - you can pass a pointer to some of your other methods
 - maybe create a save game function
 - using some type of struct
 ================================================================
 Topic 11: GAME MODE
 ---------------------------------
 - Arcade games typically feature an "attract" mode. Also known as "demo" mode. sometimes seen in NES games.
 - Game plays itself, shows high scores, cut scenes, etc.
 - Modern Console/ PC Games typically do not have Attract/ Demo modes
 
 Example game modes can be: Main menu, chapter select, level select, cut scene, game level, win screen
 */
