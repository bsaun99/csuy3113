//
//  main.cpp
//  notes
//
//  Created by Bethany Saunders on 6/23/21.
//  Copyright © 2021 Bethany Saunders. All rights reserved.
//

/*              GAME PHYSICS, FIXED TIME STEP
 ================================================================
 Topic 1: Basic Game Physics
 ---------------------------------
 - Gravity, Jumping Movement
 - Fixed Timestep
 - Velocity
 - Acceleration through gravity
 
 * Currently, our timestep is as fast as our computer can go as well as variable
 * Variable Timestep - due to out variable timestep we skipped over
 ================================================================
 Topic 2: Fixed Timestep
 ---------------------------------

 ================================================================
 Topic 3: Gravity
 ---------------------------------
 Acceleration due to gravity is 9.81 m/s^2
 
 player.acceleration = glm::vec3(0, -9.81f, 0);
 
 Acceleration: the rate of change of velocity
    velocity.x += acceleration.x * elapsed;
    velocity.y += acceleration.y * elapsed;
 
 // You can also do this
 velocity += acceleration * elapsed
 
 Putting it all together:
player.acceleration = glm::vec3(0, -9.81f, 0);
 
 void Update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltatime;
 }
 
 Notice if acceleration never changes, velocity will keep accumulating
 ================================================================
 Topic 4: We got Stuck
 ---------------------------------

 
 ================================================================
 Topic 5: Check Collisions
 ---------------------------------
 - Normally we would apply the velcoity and apply it to our position
 - Let's use the Y velocity first
 - Check to see if we have collided with anything, then adjust based on penetration
 - next use x velocity
 - Check to see if we have collided with anything, then adjust based on penetration

 Update Code:
 - changing the y position first, then check the penetration and correct itself
 - changing the x position, then check the penetration and correct itself

 ================================================================
 Topic 6: Entity Type
 ---------------------------------
 
 ================================================================
 Topic 7: Is Active
 ---------------------------------
 a boolean value
 
 - Update: exit right away
 - CheckCollision: always false if either object is false!
 if (isActive == false || other.isActive == false) return false;
 - Render: no rendering. Exit right away
 
 ================================================================
 Topic 8: Collision Flags
 ---------------------------------
 - Player should only be able to jump when touching the ground
 - enemies change direction after hitting a wall
 ================================================================
 Topic 9: DrawText
 ---------------------------------
 
 ================================================================
 Project 3: Lunar Lander
 ---------------------------------
 Requirements:
 - Player Falls With gravity (25%)
    * Player should fall with gravity. Make the gravity really low so the player falls slowly
 
 - Moving with Acceleration (25%)
    * Moving left and right should change the acceleration (not the velocity)
    * in other words, when you go off the key, the ship should only drift for a bit
    * Do not use movement for this. Only update acceleration.
 
 - Mission Failed (25%)
    * If the player touches a wall/rock, show the text "Mission Failed"
 
 - Mission Successful (25%)
    * If the player touches the platform, show "Mission Successful"
*/
