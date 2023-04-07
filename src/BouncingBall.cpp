#include "../include/BouncingBall.hpp"


BouncingBall::BouncingBall(float _Vx_init = 0.2f, float _Vy_init = 0.2f, float _initial_height = 1.0f, float _angle = 75, float _deprive_ratio = 0.55f, float _ground_level = 0.0f):
gravity(9.81/15), initial_Vx(_Vx_init), initial_Vy(_Vy_init),angle(deg2rad(_angle)), initial_height(_initial_height), deprive_ratio(_deprive_ratio), ground_level(_ground_level), delta(0.01f), alpha(1/tan(deg2rad(_angle)))
{
    x_move = 0.0f;
    y_move = 0.0f;
    z_move = 0.0f;

    Vx = initial_Vx;
    Vy = initial_Vy;
    Vz = 0.0f;

    xo = 0.0f;
    yo = 0.0f;
    zo = 0.0f;

    STOP_FLAG = false;

    total_energy = gravity * initial_height + initial_Vx*initial_Vx /2;
    time = 0.0f;
}

void BouncingBall::loop()
{
    if(!STOP_FLAG)
    {
        // Trajectory motion
        x_move = Vx*time + xo;
        y_move = -gravity*time*time/2 + Vy * time + yo;

        time += delta;
        if (initial_height + y_move <= ground_level) // Box hitted the ground
        {   
            total_energy *= deprive_ratio;
            Vy = sqrt(2*total_energy/(alpha*alpha +1));
            Vx = alpha * Vy;

            xo = x_move;
            yo = y_move;

            time = 0.0f;
            // Run until ball have a positive y coordinate
            while(initial_height + -gravity*time*time/2 + Vy * time + yo - ground_level < 0)
            {   
                time += delta;
                if (time > 20)
                {
                    COUT << "The box is stopped!!!!!" << ENDL;
                    STOP_FLAG = true;
                    break;
                }

            }
        }
    }
}

void BouncingBall::restart()
{
    // Movement in axes
    x_move = 0.0f;
    y_move = 0.0f;
    z_move = 0.0f;

    Vx = initial_Vx;
    Vy = initial_Vy;
    Vz = 0.0f;

    xo = 0.0f; // x coordinate
    yo = 0.0f; // y coordinate
    zo = 0.0f; // z coordinate

    STOP_FLAG = false;

    // Energy
    total_energy = gravity * initial_height + initial_Vx*initial_Vx /2;

    // Time
    time = 0.0f;
}

void BouncingBall::update(shaderClass& shader, int modelLoc)
{
    shader.Activate();
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(GetMovement_x(), GetMovement_y(), GetMovement_z()));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}