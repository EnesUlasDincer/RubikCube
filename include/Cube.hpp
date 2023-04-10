#pragma once

#include "shaderClass.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Camera.hpp"

#include <map>
#include <algorithm>
#include <typeinfo>

#ifndef COLOR_CODES
#define COLOR_CODES
#define RED_COLOR_CODE      1.0f, 0.0f, 0.0f, 1.0f
#define GREEN_COLOR_CODE    0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR_CODE     0.0f, 0.0f, 1.0f, 1.0f
#define YELLOW_COLOR_CODE   1.0f, 1.0f, 0.0f, 1.0f
#define ORANGE_COLOR_CODE   1.0f, 0.4f, 0.0f, 1.0f
#define WHITE_COLOR_CODE    1.0f, 1.0f, 1.0f, 1.0f
#define BLACK_COLOR_CODE    0.0f, 0.0f, 0.0f, 1.0f
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

#define DrawTriangle_red(ElementBuffer,smallCubeProgram) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), RED_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_blue(ElementBuffer,smallCubeProgram) ;\
        glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), BLUE_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_green(ElementBuffer,smallCubeProgram) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), GREEN_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_orange(ElementBuffer,smallCubeProgram) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), ORANGE_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_white(ElementBuffer,smallCubeProgram) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), WHITE_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_yellow(ElementBuffer,smallCubeProgram) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), YELLOW_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawTriangle_black(ElementBuffer,smallCubeProgram) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), BLACK_COLOR_CODE); ;\
    GLCall(glDrawElements(GL_TRIANGLE_FAN, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) ;\
    glUniform4f(glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor"), BLACK_COLOR_CODE); ;\
    glLineWidth((GLfloat)10); ;\
    GLCall(glDrawElements(GL_LINE_LOOP, ElementBuffer.GetCount(), GL_UNSIGNED_INT, 0));

#define PainterMachine(ElementBuffer,FaceColor,smallCubeProgram,LineWidth) ;\
    ElementBuffer.Bind() ;\
    if( FaceColor == Colors::red     ) { DrawTriangle_red(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::green   ) { DrawTriangle_green(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::blue    ) { DrawTriangle_blue(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::yellow  ) { DrawTriangle_yellow(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::orange  ) { DrawTriangle_orange(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::white   ) { DrawTriangle_white(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    if( FaceColor == Colors::black   ) { DrawTriangle_black(ElementBuffer,smallCubeProgram) DrawBorder(ElementBuffer,smallCubeProgram,LineWidth) } ;\
    ElementBuffer.UnBind();

#define PAINTER(face_ebos,faceColors,smallCubeProgram, LineWidth);\
    PainterMachine(face_ebos.backFace, faceColors.ColorBackFace, smallCubeProgram, LineWidth);\
    PainterMachine(face_ebos.frontFace, faceColors.ColorFrontFace, smallCubeProgram, LineWidth);\
    PainterMachine(face_ebos.rightFace, faceColors.ColorRightFace, smallCubeProgram, LineWidth);\
    PainterMachine(face_ebos.leftFace, faceColors.ColorLeftFace, smallCubeProgram, LineWidth);\
    PainterMachine(face_ebos.upFace, faceColors.ColorUpFace, smallCubeProgram, LineWidth);\
    PainterMachine(face_ebos.downFace, faceColors.ColorDownFace, smallCubeProgram, LineWidth)

#endif


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

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    // Configure the program, vertex array, vertex buffer and element buffer
    void Config()
    {
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
    }

    // index tells us which cube we are drawing

    // Green --> 0 , 1 , 0 , 1 should be enumare

    // Rigthnow, ı need the following info.s
    // Which cube I am drawing and
    // What is the color of the faces of the cube
    float rotation = 0.0f;
    void Draw(glm::mat4& CameraMatix, GLFWwindow* window, double prevTime)
    {
        // Bind the shader and Vertex array
        smallCubeProgram.Activate();
        int loc = glGetUniformLocation(smallCubeProgram.GetProgram(), "uniColor");
        
        va.Bind();

        // if( faceColors.ColorBackFace == Colors::red     ) { 
        //     glUniform4f(loc, RED_COLOR_CODE);
        //     GLCall(glDrawElements(GL_TRIANGLE_FAN, face_ebos.backFace.GetCount(), GL_UNSIGNED_INT, 0));
        //     //DrawBorder(ElementBuffer,smallCubeProgram,LineWidth); 
        //     } 

        // if( faceColors.ColorBackFace == Colors::black     ) { 
        //     glUniform4f(loc, BLACK_COLOR_CODE);
        //     GLCall(glDrawElements(GL_TRIANGLE_FAN, face_ebos.backFace.GetCount(), GL_UNSIGNED_INT, 0));
        //     //DrawBorder(ElementBuffer,smallCubeProgram,LineWidth); 
        //     } 
        modelMatrix = glm::mat4(1.0f);

        int modelLoc = glGetUniformLocation(smallCubeProgram.GetProgram(), "model");
        int camLoc = glGetUniformLocation(smallCubeProgram.GetProgram(), "camMatrix");



        // motion start

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	    {
            double crntTime = glfwGetTime();
            if (crntTime - prevTime >= 1 / 60)
            {
                rotation += 0.5f;
                prevTime = crntTime;
            }
            // if(abs(rotation) > 90.0f)
                // rotation = 0.0f;
            modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            
            //modelMatrix = glm::translate(modelMatrix, glm::vec3( sin(glm::radians(rotation)) * CubeLen*sqrt(2), 0.0f , -sin(glm::radians(rotation)) * CubeLen*sqrt(2) ));
	    }else{
            //rotation = 0.0f;
            modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        
        // motion finish

        // multiply final matric with vertices and center coor. of the small cube 
        // glm::mat4 mo = glm::mat4(1.0f);
        // mo = glm::rotate(mo, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // center_coor = mo * center_coor;
        // center_coor_x = center_coor[0]; center_coor_y = center_coor[1]; center_coor_z = center_coor[2];

        // Loading the matrices to the shader
        glm::mat4 test = glm::mat4(1.0f);
        // GLCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(test)));
        GLCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix)));
        GLCall(glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(CameraMatix)));

        glm::vec4 test_vec = CameraMatix * modelMatrix * center_coor;
        //vec4_Printer(center_coor);
        //vec4_Printer(test_vec);
        //COUT << " -- " << ENDL;

        // Paints the All faces of the smallCube
        PAINTER(face_ebos,faceColors,smallCubeProgram, LineWidth)
        va.UnBind();
        smallCubeProgram.Deactivate();
    }

    void GetCenterCoor();
    float GetOffset_x(){return x_offset;}
    float GetOffset_y(){return y_offset;}
    float GetOffset_z(){return z_offset;}

};

// void SmallCube::GetCenterCoor_x(){
    
// }

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

    SmallCube* smallCubes;


    GLfloat* CUBE_vertices;
    shaderClass* CubeShaders;

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
    void SelectSmallCube(glm::mat4& CameraMatrix,glm::mat4& ViewMatrix, glm::mat4& ProjectionMatrix, GLFWwindow* window);

};

double map(double value, int inputMin, int inputMax, int outputMin, int outputMax);
void invertMatrix4x4(glm::mat4 matrixIN, glm::mat4 MatrixOUT);
double cosine_similarity(glm::vec3 RayDir, glm::vec4 SmallCubeCenter);
// void printMatrix(const glm::mat4& matrix);
