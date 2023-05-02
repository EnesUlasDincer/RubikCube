#include "../include/renderFunctions.hpp"
#include "../include/MouseProperties.hpp"
#include "../include/KeyProperties.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth)
{
    glViewport(0, 0, width, heigth);
}

void framebuffer_editor(GLFWwindow* window)
{
    int current_scr_width = 0;
    int current_scr_height = 0;
    glfwGetWindowSize(window, &current_scr_width, &current_scr_height);
    glViewport(0, 0, current_scr_width, current_scr_height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    
}

void info(){
    printf (" Welcome to the Bouncing Ball game!!!! \n"
            "---------------------------------------\n"
            "Here are the game controllers:\n"
            "r -- Restarts the cube\n"
            "v -- Randomly shuffles the cube\n"
            "h -- help about controllers\n"
            "q -- quit (exit) the program\n"
            );
}


void infoHelp(){
    printf (
            "---------------------------------------\n"
            "Here are the informations about game controllers:\n"
            "r -- Restarts the cube\n"
            "v -- Randomly shuffles the cube\n"

            "Button 2 rotates the cube back to front\n"
            "Button 8 rotates the cube front to back\n"
            "Button 4 rotates the cube right to left\n"
            "Button 6 rotates the cube left to right\n"
            "Button 3 rotates the cube counter clockwise\n"
            "Button 7 rotates the cube clockwise\n"

            "h -- help about controllers\n"
            "q -- quit (exit) the program\n"
            
            "---------------------------------------\n"
    );
}


void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

void GLCheckError()
{
    while(GLenum error =  glGetError()){
        COUT << "[OpenGL Error] (" << error << ")" << ENDL; 
    }
}

bool GLLogCall(const char* function, const char* file, int line)
{
    if(GLenum error =  glGetError()){
        COUT << "[OpenGL Error] (" << error << ")" << 
        function << " " << file << ":" << line << ENDL; 
        return false;
    }
    return true;
}

void colorChanger(float * ColorChannel, float increment)
{
    static float color_increment = increment;
    if (*ColorChannel > 1.0f)
            color_increment = -increment;
    else if(*ColorChannel < 0.0f)
            color_increment = +increment;
    
    *ColorChannel += color_increment;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // MOUSE_RIGHT_CLICK = false;
    if ( action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
        
        // MOUSE_RIGHT_CLICK implies there is a mouse click occured.
        mouseProperties_extern.MOUSE_RIGHT_CLICK = true;
        
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        // Convert mouse coordinates to normalized device coordinates
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        mouseProperties_extern.ndcMouseX = mouseX;
        mouseProperties_extern.ndcMouseY = windowHeight - mouseY;


    }else if(action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_RIGHT){
        mouseProperties_extern.MOUSE_RIGHT_CLICK = false;
    }
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyProperties_extern.KEY_2_PRESSED = false;
    keyProperties_extern.KEY_3_PRESSED = false;
    keyProperties_extern.KEY_4_PRESSED = false;
    keyProperties_extern.KEY_6_PRESSED = false;
    keyProperties_extern.KEY_7_PRESSED = false;
    keyProperties_extern.KEY_8_PRESSED = false;
    keyProperties_extern.KEY_RESTART_PRESSED = false;
    keyProperties_extern.KEY_SHUFFLE_PRESSED = false;
    if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_2_PRESSED = true;
    }
    if (key == GLFW_KEY_KP_3 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_3_PRESSED = true;
    }
    if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_4_PRESSED = true;
    }
    if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_6_PRESSED = true;
    }
    if (key == GLFW_KEY_KP_7 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_7_PRESSED = true;
    }
    if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_8_PRESSED = true;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        keyProperties_extern.KEY_RESTART_PRESSED = true;
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        keyProperties_extern.KEY_SHUFFLE_PRESSED = true;
    }

    // Information about cube
    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        infoHelp();
    }
}

