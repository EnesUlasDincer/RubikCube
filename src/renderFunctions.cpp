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
            "s -- starts the game\n"
            "p -- pause the game\n"
            "r -- restarts the game\n"
            "c -- switch between two colors\n"
            "h -- help about controllers\n"
            "q -- quit (exit) the program\n"
            );
}


void infoHelp(){
    printf (
            "---------------------------------------\n"
            "Here are the informations about game controllers:\n"
            "s -- starts the game\n"
            "p -- pause the game\n"
            "r -- restarts the game\n"
            "c -- switch between two colors (RED or GREEN)\n"
            "h -- help about controllers\n"
            "q -- quit (exit) the program\n"

            "whenever right button is pressed --> "
            "object type changes sphere to cube or viceversa.\n"

            "whenever left button is pressed --> "
            "object apperance changes lines to solid or viceversa.\n"
            
            "---------------------------------------\n"
    );
}



enum Colors{
        Red,
        Green
    };

Colors ColorSelector(GLFWwindow* window)
{
    static Colors color = Red;

    static int state = 0;

    bool Condition = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;

    STATE_MACHINE(Condition, state, color, Green, Red);
    return color;
}

enum ObjectTypes{
        Rectangle,
        Sphere
    };

ObjectTypes ObjectTypeSelector(GLFWwindow* window)
{

    static ObjectTypes objectType = Rectangle;

    static int state = 0;

    STATE_MACHINE(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT), state, objectType, Sphere, Rectangle);
    
    return objectType;
}

static int DrawingTypeSelector(GLFWwindow* window)
{

    static int DrawingType = GL_LINE_LOOP;

    static int state = 0;

    STATE_MACHINE(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT), state, DrawingType, GL_TRIANGLE_FAN, GL_LINE_LOOP);
    
    return DrawingType;
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
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_2_PRESSED = true;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_3_PRESSED = true;
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_4_PRESSED = true;
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_6_PRESSED = true;
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_7_PRESSED = true;
    }
    if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        keyProperties_extern.KEY_8_PRESSED = true;
    }
}

