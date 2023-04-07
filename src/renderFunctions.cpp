#include "../include/renderFunctions.hpp"


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

static bool InitBallPose(GLFWwindow* window)
{
    static bool initBallPose = false;

    static int state = 0;

    STATE_MACHINE(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS, state, initBallPose, false, true);
    
    return initBallPose;
}



static bool GAME_FLAG = false;
static bool GAME_PAUSE = false;
void display(GLFWwindow* window, unsigned int shaderProgram, VertexArray* vertexArray_arr, ElementBuffer* elementBuffer_arr)
{   
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        GAME_PAUSE = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        GAME_PAUSE = false;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        infoHelp();
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || GAME_FLAG)
    {
        // once it is start, there is no need another s press
        GAME_FLAG = true;
        if( !GAME_PAUSE ){
            // ball start
            
        }


        int DrawingType = DrawingTypeSelector(window);
        ObjectTypes objectType = ObjectTypeSelector(window);
        Colors color = ColorSelector(window);

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");
        if (color == Colors::Green)
        {
            GLCall(glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f));
        }else if(color == Colors::Red)
        {
            GLCall(glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f));
        }
        

        if (objectType == ObjectTypes::Sphere)
        {
            vertexArray_arr[1].Bind();
            GLCall(glDrawElements(DrawingType, elementBuffer_arr[1].GetCount(), GL_UNSIGNED_INT, 0));
            vertexArray_arr[1].UnBind();
            elementBuffer_arr[1].UnBind();
        }
        if (objectType == ObjectTypes::Rectangle)
        {
            vertexArray_arr[0].Bind();
            GLCall(glDrawElements(DrawingType, elementBuffer_arr[0].GetCount(), GL_UNSIGNED_INT, 0));
            vertexArray_arr[0].UnBind();
            elementBuffer_arr[0].UnBind();
        }
        glUseProgram(0);
    }
}

void dispTexture(GLFWwindow* window, Texture& textureObj, shaderClass& shader_text, VertexArray& vertexArray, ElementBuffer& elementBuffer)
{
    shader_text.Activate();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureObj.ID);
    // textureObj.Bind();
    vertexArray.Bind();
    glDrawElements(GL_TRIANGLES, elementBuffer.GetCount(), GL_UNSIGNED_INT, 0);

    vertexArray.UnBind();
    elementBuffer.UnBind();
    shader_text.Deactivate();
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
