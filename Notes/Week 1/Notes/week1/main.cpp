//
//  main.cpp
//  week1 - Notes
//
//  Created by Bethany Saunders on 5/22/21.
//  Copyright © 2021 Bethany Saunders. All rights reserved.
//

#include <iostream>
/*
================================================================
Topic 1: What is Game Programming?
================================================================
 Types of games we are making:
 - Low level programming
 - What are some common things video games have?
    * Graphics
    * Input
    * Game Logic
    * Audio
    * Physics, AI, UI
 
 The heart of Game Programming:
 Startup();
 while (gameIsRunning) {
    ProcessInput();
    Update();
    Render();
 }
 Shutdown();
 
================================================================
Topic 2: History of Gaming
================================================================
 
================================================================
Topic 3: OpenGL and DirectX
================================================================
 - OpenGL released in 1992
    * GL stands for graphic library
 - DirectX released in 1995
 
 Game Engines( will not be used in this class but being aware is key)
 
 In this course...
 - SDL
    * Layer on top of OpenGL
    * Window Management, Input, Events, Audio, Game Controllers and more
 
 ================================================================
 Topic 4: Git and Github
 ================================================================
 - For each project, you will submit a link to your github repository
 ================================================================
 Topic 5: Mac Setup
 ================================================================
 Topic 6: How did we get here
 - Hardware (Specialized) -> Software Rendering -> Hardware Rendering
 ================================================================
 Topic 7: Hardware Specialized
 - Mode 7 and the Super Nintendo
 - Super FX Chip
 ================================================================
 Topic 8: Software Rendering
 - Raycasting
 ================================================================
 Topic 9: Hardware Rendering
 ================================================================
 Topic 10: How does this all Work?
 - Triangles
 - Textures
    Hardware Rendering
    - load assets to graphics card RAM
    - run game logic
    - tell graphics card what to draw
    - display
 ================================================================
 Topic 11: 2D is Really 3D (in modern times)
 - we will use 2D sprites made of 2 Triangles this semester!
 - a triangle has 3 vertices (each point is a vertex)
 - triangles are 1 sided ( the side is determined by order of the vertices)
    - counter-clockwise (front facing)
    - clockwise (back facing)
 - texture coordinates
    - top-left corner coordinate is (0,0)
    - bottom-right corner coordinate is (1,1)
 - model coordinates (Cartesian Coordinate System)
    - top-left corner coordinate is (-1,1)
    - bottom-right corner coordinate is (1, -1)
 - Shaders: translates vertices to screen positions
 - Fragment Shader: for each pixel, determines what color to draw. Interpolated by distance from vertices. (might also grab a pixel/ color from a texture)
 ================================================================
 Topic 12: Coding a Triangle
 - Initialize
    - initializing a SDL
 
*/
