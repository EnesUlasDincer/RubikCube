#pragma once

#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include "shaderClass.hpp"

// Matrix operations
#include "../include/glm/glm/glm.hpp"
#include "../include/glm/glm/gtc/matrix_transform.hpp"
#include "../include/glm/glm/gtc/type_ptr.hpp"

#ifndef PRINT_MACROS
#define PRINT_MACROS

#define COUT std::cout
#define ENDL std::endl

#endif

#define deg2rad(x) x*M_PI/180


class BouncingBall
{
private:
    // Movement in axes
    float x_move;
    float y_move;
    float z_move;

    float Vx;
    float Vy;
    float Vz;

    float xo; // x coordinate
    float yo; // y coordinate
    float zo; // z coordinate

    // Energy
    float total_energy;

    // Time
    float time;

    // Time interval
    const float delta;

    // Constans
    const float gravity;
    const float alpha;
    const float initial_height;
    const float initial_Vx;
    const float initial_Vy;
    // const float initial_Vz;
    const float deprive_ratio;
    const float angle;
    const float ground_level;

    // State
    bool STOP_FLAG;


public:
    BouncingBall(float _Vx_init, float _Vy_init, float _initial_height, float _angle, float _deprive_ratio, float _ground_level);
    // Updating motion of the ball
    void loop();
    // Returns the motion on the x axes
    float GetMovement_x() const {return x_move;};
    // Returns the motion on the y axes
    float GetMovement_y() const {return y_move;};
    // Returns the motion on the z axes
    float GetMovement_z() const {return z_move;};
    // Restarts the variables
    void restart();
    // Update the movement
    void update(shaderClass& shader, int modelLoc);
};

