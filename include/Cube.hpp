#pragma once

#include "shaderClass.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Camera.hpp"
#include "MouseProperties.hpp"
#include "KeyProperties.hpp"


#include <map>
#include <algorithm>
#include <typeinfo>
#include <cmath>
#include <cstdlib>
#include <ctime>

#ifndef COLOR_CODES
#define COLOR_CODES
#define RED_COLOR_CODE(x)      abs(1.0f-x), abs(0.0f-x), abs(0.0f-x), 1.0f
#define GREEN_COLOR_CODE(x)    abs(0.0f-x), abs(1.0f-x), abs(0.0f-x), 1.0f
#define BLUE_COLOR_CODE(x)     abs(0.0f-x), abs(0.0f-x), abs(1.0f-x), 1.0f
#define YELLOW_COLOR_CODE(x)   abs(1.0f-x), abs(1.0f-x), abs(0.0f-x), 1.0f
#define ORANGE_COLOR_CODE(x)   abs(1.0f-x), abs(0.4f-x), abs(0.0f-x), 1.0f
#define WHITE_COLOR_CODE(x)    abs(1.0f-x), abs(1.0f-x), abs(1.0f-x), 1.0f
#define BLACK_COLOR_CODE(x)    abs(0.0f-x), abs(0.0f-x), abs(0.0f-x), 1.0f
#endif

#define bas(x)      abs(1.0f-x)

#ifndef BUTTON_MACHINE
#define BUTTON_MACHINE(Condition, rotationWay, Identical,state) ;\
    switch (state) { ;\
    case 0: rotationWay = false; Identical = true; if(Condition){state = 1;}else{state = 0;} break; ;\
    case 1: rotationWay = true;  Identical = false; if(Condition){state = 2;}else{state = 0;} break; ;\
    case 2: rotationWay = false; Identical = true;  if(Condition){state = 2;}else{state = 0;} break; ;\
    } 
#define RESTART_DETECTION_MACHINE(Condition, state) ;\
    switch (state) { ;\
    case 0: if(Condition){state = 1;}else{state = 0;} break; ;\
    case 1: if(Condition){state = 2;}else{state = 0;} break; ;\
    case 2: if(Condition){state = 2;}else{state = 0;} break; ;\
    } 
#define SHUFFLE_DETECTION_MACHINE(Condition, state) ;\
    switch (state) { ;\
    case 0: if(Condition){state = 1;}else{state = 0;} break; ;\
    case 1: if(Condition){state = 2;}else{state = 0;} break; ;\
    case 2: if(Condition){state = 2;}else{state = 0;} break; ;\
    } 
#endif


enum Colors
{
    red,green,blue,yellow,orange,white,black
};

const float LineWidth = 10.0f;

#ifndef PainterMachine
// For the record, This is for some reason doesnot work 
// It is ralted with "uniColor"
// #define DrawTriangle_blue(ElementBuffer,smallCubeProgram) ;\
//     smallCubeProgram.SetUniform4f("uniColor", BLUE_COLOR_CODE); ;\
//     GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define vec3_Printer(x) ;\
    COUT << #x << " : " << x[0] << " , " << x[1] << " , " << x[2] << ENDL

#define vec4_Printer(x) ;\
    COUT << #x << " : " << x[0] << " , " << x[1] << " , " << x[2] << " , " << x[3] << ENDL

#define DrawTriangle_red(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), RED_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_blue(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
        glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), BLUE_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_green(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), GREEN_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_orange(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), ORANGE_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_white(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), WHITE_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_yellow(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), YELLOW_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_black(ElementBuffer,smallCubeProgram,ColorDiscount) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), BLACK_COLOR_CODE(ColorDiscount)); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), BLACK_COLOR_CODE(0)); ;\
    glLineWidth((GLfloat)10); ;\
    GLCall(glDrawElements(GL_LINE_LOOP, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define PainterMachine(ElementBuffer,FaceColor,smallCubeProgram,LineWidth,ColorDiscount) ;\
    ElementBuffer.Bind() ;\
    if( FaceColor == Colors::red     ) { DrawTriangle_red(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::green   ) { DrawTriangle_green(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::blue    ) { DrawTriangle_blue(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::yellow  ) { DrawTriangle_yellow(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::orange  ) { DrawTriangle_orange(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::white   ) { DrawTriangle_white(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::black   ) { DrawTriangle_black(ElementBuffer,smallCubeProgram,ColorDiscount) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    ElementBuffer.UnBind();

#define PAINTER(face_ebos,faceColors,smallCubeProgram, LineWidth, ColorDiscount);\
    PainterMachine(face_ebos.backFace, faceColors.ColorBackFace, smallCubeProgram, LineWidth, ColorDiscount);\
    PainterMachine(face_ebos.frontFace, faceColors.ColorFrontFace, smallCubeProgram, LineWidth, ColorDiscount);\
    PainterMachine(face_ebos.rightFace, faceColors.ColorRightFace, smallCubeProgram, LineWidth, ColorDiscount);\
    PainterMachine(face_ebos.leftFace, faceColors.ColorLeftFace, smallCubeProgram, LineWidth, ColorDiscount);\
    PainterMachine(face_ebos.upFace, faceColors.ColorUpFace, smallCubeProgram, LineWidth, ColorDiscount);\
    PainterMachine(face_ebos.downFace, faceColors.ColorDownFace, smallCubeProgram, LineWidth, ColorDiscount)
#endif

struct Rotation
{
    bool Left_2_Right;
    bool Right_2_Left;

    bool CW;  // ClockWise
    bool CCW; // CounterClockWise

    bool Front_2_Back;
    bool Back_2_Front;

    bool Identical;
};

struct FaceColor
{
    Colors ColorFrontFace; 
    Colors ColorBackFace; 
    Colors ColorRightFace; 
    Colors ColorLeftFace; 
    Colors ColorUpFace; 
    Colors ColorDownFace; 
};

struct Faces{
    ElementBuffer frontFace;
    ElementBuffer backFace;
    ElementBuffer rightFace;
    ElementBuffer leftFace;
    ElementBuffer upFace;
    ElementBuffer downFace;

    void UnBind(){
        frontFace.UnBind();
        backFace.UnBind();
        rightFace.UnBind();
        leftFace.UnBind();
        upFace.UnBind();
        downFace.UnBind();
    }
};

struct SmallCube{
    // Cube identity
    int CubeID;
    // Cube Lenght
    float CubeLen;
    // Offset
    float x_offset;
    float y_offset;
    float z_offset;

    // Center coordinate of the small cube
    glm::vec4 center_coor = glm::vec4(1.0f);
    float center_coor_x;
    float center_coor_y;
    float center_coor_z;

    // Shader
    shaderClass smallCubeProgram;

    // Vertex Array & Vertex Buffer & Element Buffers
    VertexArray va;    
    VertexBuffer vb;
    Faces face_ebos;

    // Color of each face
    FaceColor faceColors;

    // Vertice & Indices
    GLfloat vertices[24];
    GLuint indices[24];

    glm::mat4 modelMatrix;

    // Configure the program, vertex array, vertex buffer and element buffer
    void Config()
    {
        modelMatrix = glm::mat4(1.0f);

        smallCubeProgram.Activate();
        va.Config();
        vb.Config(vertices, sizeof(vertices));

        // we need 6 element buffer the cube's faces.
        face_ebos.frontFace.Config(indices + 0, sizeof(indices)/6);
        face_ebos.downFace.Config(indices + 4, sizeof(indices)/6);
        face_ebos.rightFace.Config(indices + 8, sizeof(indices)/6);
        face_ebos.upFace.Config(indices + 12, sizeof(indices)/6);
        face_ebos.leftFace.Config(indices + 16, sizeof(indices)/6);
        face_ebos.backFace.Config(indices + 20, sizeof(indices)/6);
        
        VertexBufferLayout layout;
        layout.Pushf(3,false); // 3 dim / no need to normalization
        va.AddBuffer(vb,layout);
        // Unbind operations
        va.UnBind();
        vb.UnBind();
        face_ebos.UnBind();
        smallCubeProgram.Deactivate();

        StaticLikeAngle = 0.0f;
        StaticLikeAxes = -1;
        AnimationFlag = false;
    }

    // index tells us which cube we are drawing

    // Green --> 0 , 1 , 0 , 1 should be enumare

    // Rigthnow, ı need the following info.s
    // Which cube I am drawing and
    // What is the color of the faces of the cube
    float rotation = 0.0f;
    void Draw(glm::mat4& CameraMatix, GLFWwindow* window, double prevTime, bool DRAW_BACK_BUFFER)
    {
        // Bind the shader and Vertex array
        smallCubeProgram.Activate();
        int loc = glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor");
        
        va.Bind();

        // modelMatrix = glm::mat4(1.0f);
        // printMatrix(modelMatrix);
        
        int modelLoc = glGetUniformLocation(smallCubeProgram.GetProgram(), "model");
        int camLoc = glGetUniformLocation(smallCubeProgram.GetProgram(), "camMatrix");

        // motion start

        // if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	    // {
        //     double crntTime = glfwGetTime();
        //     if (crntTime - prevTime >= 1 / 60)
        //     {
        //         rotation += 0.5f;
        //         prevTime = crntTime;
        //     }
        //     // if(abs(rotation) > 90.0f)
        //         // rotation = 0.0f;
        //     modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            
        //     //modelMatrix = glm::translate(modelMatrix, glm::vec3( sin(glm::radians(rotation)) * CubeLen*sqrt(2), 0.0f , -sin(glm::radians(rotation)) * CubeLen*sqrt(2) ));
	    // }else{
        //     //rotation = 0.0f;
        //     modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        // }
        
        // motion finish


        // Loading the matrices to the shader
        glm::mat4 test = glm::mat4(1.0f);
        // GLCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(test)));
        GLCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix)));
        GLCall(glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(CameraMatix)));

        glm::vec4 test_vec =  modelMatrix * center_coor;
        center_coor_x = test_vec[0];
        center_coor_y = test_vec[1];
        center_coor_z = test_vec[2];
        //vec4_Printer(center_coor);
        //vec4_Printer(test_vec);

        //COUT << " -- " << ENDL;

        // Paints the All faces of the smallCube
        if (DRAW_BACK_BUFFER)
        {
            float discount = 1.0*(float)CubeID / 255.0;
            PAINTER(face_ebos,faceColors,smallCubeProgram, LineWidth, discount);
        }else{
            PAINTER(face_ebos,faceColors,smallCubeProgram, LineWidth, 0.0);
        }
        
        va.UnBind();
        smallCubeProgram.Deactivate();
    }

    float StaticLikeAngle;
    int StaticLikeAxes;
    bool AnimationFlag;
    // Aplly rotation to the small cube
    void ApplyRotation(float angle, int Axes)
    {
        glm::mat3 RotatioPartnModelMatrix = glm::mat3(modelMatrix);
        if (StaticLikeAxes != Axes && StaticLikeAngle != angle && angle != 0.0)
        {
            StaticLikeAngle = angle;
        }
        
        // Increment the angle 
        // Feed to glm::rotate
        float angle_increment = 0.1;
        if (Axes == -1)
        {   // No rotation Case
            
            float a = StaticLikeAngle;
            if (abs( abs(rotation + angle_increment) - abs(a) ) > 0.01)
            {
                rotation += angle_increment;
            }else{
                rotation = 0.0;
                StaticLikeAngle = 0.0;
                StaticLikeAxes = -1;
            }
            // rotation = fmod(rotation,100);
            AnimationFlag = false;
            if (StaticLikeAxes == 0)
            {
                AnimationFlag = true;
                glm::vec3 axes_x = glm::vec3(1.0f, 0.0f, 0.0f);
                axes_x = glm::transpose(RotatioPartnModelMatrix)*axes_x;
                modelMatrix = glm::rotate(modelMatrix, glm::radians((std::signbit(StaticLikeAngle) ? -1 : 1) * angle_increment), axes_x);
            }else if(StaticLikeAxes == 1) // Y axes
            {
                AnimationFlag = true;
                glm::vec3 axes_y = glm::vec3(0.0f, 1.0f, 0.0f);
                axes_y = glm::transpose(RotatioPartnModelMatrix)*axes_y;    
                modelMatrix = glm::rotate(modelMatrix, glm::radians((std::signbit(StaticLikeAngle) ? -1 : 1) * angle_increment), axes_y);
            }else if(StaticLikeAxes == 2) // Z axes
            {
                AnimationFlag = true;
                glm::vec3 axes_z = glm::vec3(0.0f, 0.0f, 1.0f);
                axes_z = glm::transpose(RotatioPartnModelMatrix)*axes_z;    
                modelMatrix = glm::rotate(modelMatrix, glm::radians((std::signbit(StaticLikeAngle) ? -1 : 1) * angle_increment), axes_z);
            }
            

        }
        
        if(Axes == 0 && !(StaticLikeAxes == 0 || StaticLikeAxes == 1 || StaticLikeAxes == 2) ) // X axes
        {
            rotation = 0.0;
            StaticLikeAxes = 0;
            glm::vec3 axes_x = glm::vec3(1.0f, 0.0f, 0.0f);
            axes_x = glm::transpose(RotatioPartnModelMatrix)*axes_x;
            modelMatrix = glm::rotate(modelMatrix, glm::radians((std::signbit(angle) ? -1 : 1) *angle_increment), axes_x);
        }else if(Axes == 1 && !(StaticLikeAxes == 0 || StaticLikeAxes == 1 || StaticLikeAxes == 2)) // Y axes
        {
            rotation = 0.0;
            StaticLikeAxes = 1;
            glm::vec3 axes_y = glm::vec3(0.0f, 1.0f, 0.0f);
            axes_y = glm::transpose(RotatioPartnModelMatrix)*axes_y;    
            modelMatrix = glm::rotate(modelMatrix, glm::radians((std::signbit(angle) ? -1 : 1) *angle_increment), axes_y);
        }else if(Axes == 2 && !(StaticLikeAxes == 0 || StaticLikeAxes == 1 || StaticLikeAxes == 2)) // Z axes
        {
            rotation = 0.0;
            StaticLikeAxes = 2;
            glm::vec3 axes_z = glm::vec3(0.0f, 0.0f, 1.0f);
            axes_z = glm::transpose(RotatioPartnModelMatrix)*axes_z;    
            modelMatrix = glm::rotate(modelMatrix, glm::radians((std::signbit(angle) ? -1 : 1) *angle_increment), axes_z);
        }
    }

    // Restart the model matrix as a identity
    void Restart(){modelMatrix = glm::mat4(1.0f);}


    glm::vec3 GetCenterCoor(){return glm::vec3(center_coor_x,center_coor_y,center_coor_z);}
    float GetCenterCoor(int x){if (x == 0){return center_coor_x;}else if(x == 1){return center_coor_y;}else if(x == 2){return center_coor_z;}}
    float GetOffset_x(){return x_offset;}
    float GetOffset_y(){return y_offset;}
    float GetOffset_z(){return z_offset;}   

};


class Cube
{
private:
    // Sphere_vertices coordinates
    const int n_point_in_one_cube = 8;
    const int n_faces = 6; 
    const int n_cubes = 27;
    const int vec_count = 3;

    // Cube center coordinates
    float cube_center_x = 0.0f;
    float cube_center_y = 0.0f;
    float cube_center_z = 0.0f;

    // Cube length
    float cubeLen; 

    // Small cube array
    SmallCube* smallCubes;
    // Cube vertices
    GLfloat* CUBE_vertices;
    // Shaders for small cubes
    shaderClass* CubeShaders;

    // Selected Small Cube
    int SelectedSmallCube;
    // Rotation
    Rotation rotationWay;
    // Number of movement for shuffling
    int n_move;
public:
    
    
    Cube(float _cubeLen);
    
    //Cube(float* coor, shaderClass& program);

    void setCenterCoor(float* coor){cube_center_x = coor[0];cube_center_y = coor[1];cube_center_z = coor[2];}
    
    float getCenterCoor_x(){return cube_center_x;}
    float getCenterCoor_y(){return cube_center_y;}
    float getCenterCoor_z(){return cube_center_z;}

    //~Cube();

    // Initialize the cube by generating small cubes
    void Init(const::std::string& vertexShader, const::std::string& fragmentShader);

    // Set the vertices of each cube
    void SetVertices();
    // Set off-sets for the small cubes
    void Setoffset();
    // Set the colors of each face
    void SetColors();

    // Draw the cube by drawing small cubes
    void Draw(glm::mat4& CameraMatix,GLFWwindow* window, double prevTime);

    // void SelectSmallCube(glm::mat4& CameraMatrix, GLFWwindow* window);
    void SelectSmallCube(glm::mat4& CameraMatrix,glm::mat4& ViewMatrix, glm::mat4& ProjectionMatrix, GLFWwindow* window, MouseProperties mouseProperties_extern, KeyProperties keyProperties_extern);

    // Identify the Small Cube via clicked pixel's color
    int IdentifySmallCube(unsigned char* ClickedPixel);

    // Get the keyword and decide the rotation
    void GetKeyword(KeyProperties keyProperties_extern);
    
    // Apply rotation to the smallCubes
    void ApplyRotation(glm::mat4& CameraMatrix);

    // Restart the Cube
    void Restart();

    // Shuffle the Cube
    void Shuffle();
};

double map(double value, int inputMin, int inputMax, int outputMin, int outputMax);
void invertMatrix4x4(glm::mat4 matrixIN, glm::mat4 MatrixOUT);
double cosine_similarity(glm::vec3 RayDir, glm::vec4 SmallCubeCenter);
void printMatrix(const glm::mat4& matrix);
