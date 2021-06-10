//
//  main.cpp
//  week 3 Notes
//
//  Created by Bethany Saunders on 6/10/21.
//  Copyright © 2021 Bethany Saunders. All rights reserved.
//

/*
 ================================================================
 Topic 1: Input Introduction
 ================================================================
 Topic 2: Keyboard Input
 
 The Game Loop
 -working with the process input funciton
 -------------------------------------------------------------------
 ProcessInput();
     SDL_Event event;
     while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT
            || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
     }
 -------------------------------------------------------------------
 * you may want to use a switch/case for event types
 Updating ProcessInput(); to this instead
 Example:
 switch (event.type) {
    case SDL_QUIT:
    case SDL_WINDOWEVENT_CLOSE:
        gameIsRunning = false;
        break;
 }
 -------------------------------------------------------------------
 ProcessInput();
 * SDL_KEYDOWN is when a key is pressed.
 * SDL_KEYUP is when a key is released.
 
 // Check if a key was pressed
 case SDL_KEYDOWN:
    switch(event.key.keysym.sym) {
        // ..
    }
    break;
 -------------------------------------------------------------------
 
 // Check which key was pressed
 // https://wiki.libsdl.org/SDL_Scancode
 switch(event.key.keysym.sym) {
    case SDLK_RIGHT:
        player_x += 1;
        break;
    case SDLK_SPACE:
        PlayerJump();
        break;
 }
 -------------------------------------------------------------------
 SDL_KEYDOWN and SDL_KEYUP
 * great for knowing when a key was pressed or released
 * useful for actions such as jumping and shooting
 -------------------------------------------------------------------
 SDL_GetKeyboardState
 * Returns a pointer to an array of key states. A value of 1 means
    that the key is pressed and a value of 0 means that it is not.
    Indexes into this array are obtained by using SDL_Scancode
    values. The pointer returned is a pointer to an internal SDL
    array. It will be valid for the whole lifetime of the application
    and should not be freed by the caller.
 
 Code:
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT]) {
        PlayerLeft();
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        PlayerRight();
    }
 // Notice the above use SDL_SCANCODE_ and not SDLK_
 // https://wiki.libsdl.org/SDL_Scancode
 ================================================================
 Topic 3: Mouse Input / Mouse Coordinates
 ================================================================
 SDL_MOUSEMOTION
 * happens when the mouse is moved
 case SDL_MOUSEMOTION:
    // event.motion.x : x position in pixels
    // event.motion.y : y position in pixels
    // event.button.button : button that was clicked (1,2,3)
 break;
 
 Polling the Mouse
 -------------------------------------------------------------------
 // put this outside of “while (SDL_PollEvent(&event))”
 int x, y;
 SDL_GetMouseState(&x, &y);
 
 * Mouse Coordinates are in Pixels (not world coordinates)
 - Therefore we will need to translate from pixel coordinates to OpenGL units
 
 glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
 
 // Convert mouse x, y to world unit x, y
 // Assumes we are looking at 0,0 in our world.
 
 unit_x = ((x / width) * ortho_width) - (ortho_width / 2.0);
 unit_y = (((height - y) / height) * ortho_height) - (ortho_height / 2.0);
 ================================================================
 Topic 4: Controller Input
 
 Initialization
 -------------------------------------------------------------------
 SDL_Joystick *playerOneController;
 
 void Initialize() {
    // Initialize Video and the Joystick subsystem
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
 
    // Open the 1st controller found. Returns null on error.
    playerOneController = SDL_JoystickOpen(0);
 
    // Do the other stuff
 }
 -------------------------------------------------------------------
 Cleanup
 SDL_JoystickClose(playerOneController);
 -------------------------------------------------------------------
 Checking for Controllers
 You can SDL_NumJoysticks() to get the number of controllers.
 
 Axis and Button Events
     * SDL_JOYAXISMOTION
     * SDL_JOYBUTTONDOWN
     * SDL_JOYBUTTONUP
 
 SDL_JOYAXISMOTION and SDL_JOYBUTTONDOWN
 -------------------------------------------------------------------
 * Similar to keyboard events. Great for knowing when something
 happened, but does not handle sustained usage.
 -------------------------------------------------------------------
 Polling the Controller (used outside of that while loop)
 SDL_JoystickGetAxis(playerOneController, axisIndex);
 SDL_JoystickGetButton(playerOneController, buttonIndex);

 ================================================================
 Topic 5: Movement
 -------------------------------------------------------------------
                            The Game Loop
 ProcessInput()
 - Store the player’s intent to move/jump/etc.
 
 Update()
 - Test/Apply movement.
 - Player, enemies, moving platforms, etc.
 
 Render()
 - Draw the current state of the game.
 -------------------------------------------------------------------
We can store the player's position as a vctor as well as an intended movement
 // Start at 0,0,0
 glm::vec3 player_position = glm::vec3(0, 0, 0);
 
 // Don’t go anywhere (yet).
 glm::vec3 player_movement = glm::vec3(0, 0, 0);
 -------------------------------------------------------------------
 Set where we want to go in ProcessInput();
 
 player_movement = glm::vec3(0, 0, 0);
 
 const Uint8 *keys = SDL_GetKeyboardState(NULL);
 
 if (keys[SDL_SCANCODE_A]) {
    player_movement.x = -1.0f;
 }
 else if (keys[SDL_SCANCODE_D]) {
    player_movement.x = 1.0f;
 }
 -------------------------------------------------------------------
* all movement needs to consider timing
 float lastTicks = 0.0f;
 
 void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
 
    // Add (direction * units per second * elapsed time)
    player_position += player_movement * player_speed * deltaTime;
 
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, player_position);
 }
 -------------------------------------------------------------------
Look Out!
 Joysticks are in a circle, however the WASD keys would make a square...
 The pythagorean theorem: A^2 + B^2 = C^2
 Pressing D movement vector = [1, 0] : What is the magnitude? 1
 Pressing W movement vector = [0, 1] : What is the magnitude? 1
 Pressing W and D movement vector = [1, 1] : What is the magnitude? 1.414
 ================================================================
 Topic 5: Collision Detection
 -------------------------------------------------------------------
 Circle to Circle Detection
 * Distance is calculated via pythagorean theorem
 * if the distance between the center of the circle is less than the
    sum of the radii, they are colliding
 -------------------------------------------------------------------
 Point to Circle
 * Click UI, move the player, select a target
 * if the distance between the point and the circle's center is
    less than the radius, they are colliding
 -------------------------------------------------------------------
 Box to Box Collision Detection (probably will be used most)
 * Calculation:
    xdiff = fabs(x2 - x1)
    ydiff = fabs(y2 - y1)
    x_distance = xdiff - (width1 + width2) / 2
    y_distance = ydiff - (height1 + height2) /2
 
 function code:
 float xdist = fabs(x2 - x1) - ((w1 + w2) / 2.0f);
 float ydist = fabs(y2 - y1) - ((h1 + h2) / 2.0f);
 
 if (xdist < 0 && ydist < 0) // Colliding!
 * (both need to be <0 to be colliding)
 
 Point - Box Collision Detection
 -------------------------------------------------------------------
* Get the top left and bottom right corners.
* Check if the x,y of the point is inside.
 ================================================================
 Upcoming Project: Pong Game
 - work with box collisions instead of mxing it up
 - "w" and "s" keys as the player on the left moving up and down
 - "up" button and "down" button as the player on the right
 
 Requirements:
 Paddles/ Players(50%)
 * a paddle on each side that can move independently of eachother
 * the ball needs to bounce off of the paddles
 * the paddles should not be able to go off the top or the bottom of the screen
 * both players can use the keyboard
 * you can use images or untextered polygons
 
 Bounces off Walls (25%)
 * the ball needs to bounce off the top and the bottom of the screen
 
 Game Over (25%)
 * the game should stop when someone wins or loses (the ball hits a wall on the left or right)
 
 
 ================================================================
 */
