//
//  main.cpp
//  Notes
//
//  Created by Bethany Saunders on 5/31/21.
//  Copyright © 2021 Bethany Saunders. All rights reserved.
//

#include <iostream>

/*
 ================================================================
 Topic 1: Matrix Multiplication Order
 - Matrix multiplication is not cummulative
 - Example:
        Translation(Rotation) != Rotation(Translation)
 ================================================================
 Topic 2: Spaces
 - Model Space
 - World Space
 - we are transforming from model space to world space
 - you may need to make a hierarchy if something is relative to another object
 ================================================================
 Topic 3: Transforming
 - keep track of position, rotation and scale in variables and setup the matrix as needed
 ================================================================
 Topic 4: Timing and FPS
 - things should happen in our games at the same speeds regardless of how fast or slow the user's hardware is.
 - faster hardware does more updates than slower update
 ================================================================
 Topic 5: DeltaTime
 - deltatime values on different computers:
    60 FPS: 16.66ms / 1000 = 0.0166
    30 FPS: 33.33ms / 1000 = 0.0333
 - used to control how fast something will move
 - we can use timing to handle rotation as well
 - ticks are the amount of time that have passed by
 ================================================================
 Topic 6: Orthographic
 - everything will appear to be the same size even if some of the objects are further away
 - the numbers represent how much of the world the user can see
    - For Example: projectionMatrix = glm::ortho(-5.0f, 5.0, -3.75f, 3.75f, -1.0f, 1.0f);
 program.SetProjectionMatrix(projectionMatrix)
 * if the numbers are smaller, everything will appear to be closer
 * if the numbers are larger, everything will appear to be further away
 ================================================================
 Topic 7: Colors and Textures
 - instead of values 0-255 or #00 - #ff, OpenGL colors have 3 or 4 channels ranging from 0.0 to 1.0 (floating point)
 - RGB or RGBA
    - RGBA affects the opacity of an object
 - glClearColor: sets the color to use when clearing the screen
 Example: glClearColor(float red
 - glClear: clears the screen using the color last set by glClearColor
 Example:
 ================================================================
 Topic 8: SetColor
 setting a solid color of an untextured polygon
 ShaderProgram::SetColor : sets the color to use when drawing a polygon
 Example: ShaderProgram::SetColor(float red, float green
 ================================================================
 Topic 9: Loading and Preparing Textures/ Images
 - do this during your setup, not every frame
 ================================================================
 Topic 10: STB_Image
 Loading an image with STB_image:
 - You must include STB_IMAGE_IMPLEMENTATION in one of the files you are including it from!
 #define STB_IMAGE_IMPLEMENTATION
 #include "stb_image.h"
 
 Use stbi_load to load the pixel data from an image file
 
 int w, h, n;
 unsigned char* image = stbi_load("Pacman.png", &w, &h, &n, STBI_rgb_alpha);
 
 After you are done loading the image data, you must free it.
 stbi_image_free(image);
 ================================================================
 Topic 11: Creating a Texture
 
 GLuint textureID;
 glGenTextures(1, &textureID);
 
 Binding a texture
 glBindTexture(GL_TEXTURE_2D, textureID);
 * GL_TEXTURE_2D is a "target"
 
 Setting the texture pixel data: this is what sends the image to the graphic card
 * images must be RGBA
 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
 ================================================================
 Topic 12: Loading a Texture
 
 Texture Filtering
 - original, minification, magnification
 - linear: good for high resolution textures and textures with anti-aliasing
 - nearest neighbor: good for pixel art (probably will use this one the most)
 * Use GL_LINEAR or GL_NEAREST
 * MIN = Minifying, MAG = Magnifying
 
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 
 Function:
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
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 
 stbi_image_free(image);
 return textureID;
 }
 ================================================================
 Topic 13: Texture Coordinates
 - coordinates that are referred to as UV coordinates
 - range from 0.0 to 1.0 and not by pixels
 - 2D sprites are made of 2 triangles
 - need to match the vertices to the UV coordinates
 Example:
 float vertices[] = {-0.5, -0.5
 float texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0
 
 Initialization:
 GLuint playerTextureID;
 void Initialize() {
 // Load the shader for handling textures!
 program.Load("Shaders
 */
