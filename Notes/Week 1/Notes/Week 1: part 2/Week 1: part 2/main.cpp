//
//  main.cpp
//  Week 1: part 2
//
//  Created by Bethany Saunders on 6/1/21.
//  Copyright © 2021 Bethany Saunders. All rights reserved.
//

#include <iostream>

/*
 ================================================================
 Topic 1: Where is the Empire State Building
 ================================================================
 Topic 2: Vectors
 - vectors have a direction and magnitude (length)
 - can be though of as a displacement
 - we can add vectors together
 - we can also multiply a vector by a scalar
 - we can rotate a vector
 ================================================================
 Topic 3: Transformations (Translation, Rotation and Scale)
 - Translation: moving something
 - Rotation: translation and then turning
 - Scale: making it grow or shrink
 ================================================================
 Topic 4: Matrices
 - m-by-n Matrix: m rows by n columns
 - we can treat a 2D vector as a 2x1 matrix
 - Matrix Operations
     - Matrix Addition: add their corresponding entries.
        * must be the same size
     - Matrix Subtraction: subtract their corresponding entries
        * must be the same size
     - Scalar Multiplication: multiply each entry by S
 ================================================================
 Topic 5: Matrix Multiplication
 - the number of columns in the first matrix must match the number of rows in the second matrix
 - Example:
 | A B C | X | G H | = | A(G) + B(I) + C(K)    A(H) + B(J) + C(L) |
 | D E F |   | I J |   | D(G) + E(I) + F(K)    D(H) + E(J) + F(L) |
             | K L |
 ================================================================
 Topic 6: USING MATRIX MULITPLICATION TO TRANSFORM THINGS
 - Identity Matrix: a nxn matrix with a 1 on the diagonal and a 0 for the other values
    * multiplying by the identity matrix has no effect
    Example:
     |1|   |1 0|
           |0 1|
    - from our example code....
    modelMatrix = glm::mat4(1.0f);
 ================================================================
 Topic 7: Scaling
 - Example:
     |Sx  0| |X| = |Sx(X) + 0(Y)| = |Sx(X)|
     |0  Sy| |Y|   |0(X) + Sy(Y)|   |Sy(Y)|
 
     |2  0| |4| = |2(4) + 0(3)| = |2(4)|
     |0  2| |3|   |0(4) + 2(3)|   |2(3)|
 - Uniform and Non-uniform
 - we transform the matrix that will transform the vertices. This matrix is used by the vertex shader.
 
 Coding:
    - Start off with Identity:
        modelMatrx = glm::mat4(1.0f);
    - Scale what we have so far:
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 1.0f);
================================================================
Topic 8: Rotation
 | cos(theta) -sin(theta) | |X| = |cos(theta)*X + -sin(theta)*Y |
 | sin(theta)  cos(theta) | |Y|   |sin(theta)*X + cos(theta)*Y  |
 
 Coding:
 Start off with Identity:
 modelMatrix = glm::mat4(1.0f);
 Rotate what we have so far:
    modelMatrix = glm::rotate(modelMatrix, angle_in_radians, glm::vec3(0.0f, 0.0f, 1.0f));
 ================================================================
 Topic 9: Translation
 - Homogeneous Coordinates: first we need to represent our 2D vector as a 3D vector
 - Translation Matrix:
 | 1 0 Tx ||X|   |1(X) + 0(Y) + Tx(1)|      | X + Tx |
 | 0 1 Ty ||Y| = |0(X) + 1(Y) + Ty(1)|  ==> | Y + Ty |
 | 0 0 1  ||1|   |0(X) + 0(Y) + 1(1) |      | 1      |
 
 Coding:
- Start off with Identity:
    modelMatrix = glm::mat4(1.0f);
 - Translate what we ghave so far:
    modelMatrix = glm::translate(modelMatrix, angle_in_radians, glm::vec3(3.0f, 2.0f, 0.0f));
 ================================================================
 Topic 9: mat4
 - creates a 4x4 matrix.
 - this is due to everything being in 3D, therefore we need to use homogeneous coordinates to transform 3D vectors
    | X |      | X |
    | Y | -->  | Y |
    | Z |      | Z |
               | 1 |
  ================================================================
 */
