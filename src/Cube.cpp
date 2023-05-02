#include "../include/Cube.hpp"

GLuint cubeIndices[] =
{
	0, 1, 2, 3, // front
	
    0, 4, 5, 1, // down

	5, 1, 2, 6, // right

	3, 7, 6, 2, // up

	0, 3, 7, 4, // left

	4, 7, 6, 5 // back
};

Cube::Cube(float _cubeLen)
{
    cubeLen = _cubeLen;
    CUBE_vertices = (GLfloat*)malloc(n_point_in_one_cube * n_faces * n_cubes * vec_count * sizeof(GLfloat));
    CubeShaders = (shaderClass*)malloc(n_cubes * sizeof(shaderClass));
    smallCubes = (SmallCube*)malloc(n_cubes * sizeof(SmallCube));
    n_move = 10;
}

void Cube::Init(const::std::string& vertexShader, const::std::string& fragmentShader)
{
    // Set off-sets for the small cubes
    Setoffset();

    // Set the colors of each face
    SetColors();

    // Initilazing every small cube with vertex/fragment shader
    for (int i = 0; i < n_cubes; i++)
    {
        // CubeShaders[i].init(vertexShader, fragmentShader);
        // smallCubes[i].smallCubeProgram.SetProgram(CubeShaders[i].GetProgram());
        smallCubes[i].smallCubeProgram.init(vertexShader, fragmentShader);
        smallCubes[i].CubeID = i;
        smallCubes[i].CubeLen = cubeLen;
        smallCubes[i].center_coor = glm::vec4(getCenterCoor_x() + smallCubes[i].GetOffset_x(), getCenterCoor_y() + smallCubes[i].GetOffset_y(), getCenterCoor_z() + smallCubes[i].GetOffset_z(), 1.0f);
    }

    int loc = glGetUniformLocation(smallCubes[0].smallCubeProgram.GetProgram(), "uniColor");
    

    // Set the vertices of each cube
    SetVertices();

    // Set possible positions
    SetPossiblePositions();
}

void Cube::SetVertices()
{
    for (int i = 0; i < n_cubes; i++)
    {
        // For each small cube_0{x}
        // Set the vertices and indices
        float x_offset, y_offset, z_offset;
        x_offset = smallCubes[i].GetOffset_x(); y_offset = smallCubes[i].GetOffset_y(); z_offset = smallCubes[i].GetOffset_z();
        // 8 point 3 axes 24 = 8 * 3 for each small cube 
        int idx = 0;
        // Point 0
	    smallCubes[i].vertices[idx] = x_offset + cube_center_x - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
	    smallCubes[i].vertices[idx] = y_offset + cube_center_y - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
	    smallCubes[i].vertices[idx] = z_offset + cube_center_z + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        // Point 1
	    smallCubes[i].vertices[idx] = x_offset + cube_center_x + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        // Point 2
	    smallCubes[i].vertices[idx] = x_offset + cube_center_x + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        // Point 3
	    smallCubes[i].vertices[idx] = x_offset + cube_center_x - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        // Point 4
	    smallCubes[i].vertices[idx] = x_offset + cube_center_x - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        // Point 5
        smallCubes[i].vertices[idx] = x_offset + cube_center_x + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        // Point 6
        smallCubes[i].vertices[idx] = x_offset + cube_center_x + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
	    // Point 7
        smallCubes[i].vertices[idx] = x_offset + cube_center_x - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = y_offset + cube_center_y + cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;
        smallCubes[i].vertices[idx] = z_offset + cube_center_z - cubeLen/2; smallCubes[i].indices[idx] = cubeIndices[idx]; idx++;

        smallCubes[i].Config();
    }
}

void Cube::Setoffset()
{
    for (int i = 0; i < n_cubes; i++)
    {
        // z offset
        if(i % 3 == 0){
            smallCubes[i].z_offset =  cubeLen;}
        if(i % 3 == 1){
            smallCubes[i].z_offset =  0.0f;}
        if(i % 3 == 2){
            smallCubes[i].z_offset = -cubeLen;}
        
        // y offset
        if (0 <= i && i < 9)
        {
            smallCubes[i].y_offset = cubeLen;
        }else if(9 <= i && i < 18)
        {
            smallCubes[i].y_offset = 0.0f;
        }else if(18 <= i && i < 27)
        {
            smallCubes[i].y_offset = -cubeLen;
        }
            
        // x offset
        int k = i%9;
        if (0 <= k && k < 3)
        {
            smallCubes[i].x_offset = cubeLen;
        }else if(3 <= k && k < 6)
        {
            smallCubes[i].x_offset = 0.0f;
        }else if(6 <= k && k < 9)
        {
            smallCubes[i].x_offset = -cubeLen;
        }

    }
    
}

void Cube::SetColors()
{
    #pragma region Up & Down Face Colors
    for (int i = 0; i < n_cubes; i++)
    {

        if (i < 9)
        {
            smallCubes[i].faceColors.ColorUpFace = red;
            smallCubes[i].faceColors.ColorDownFace = black;}
        else if(9 <= i && i < 18){
            smallCubes[i].faceColors.ColorUpFace = black;
            smallCubes[i].faceColors.ColorDownFace = black;
        }
        else if(18 <= i && i < n_cubes){
            smallCubes[i].faceColors.ColorUpFace = black;
            smallCubes[i].faceColors.ColorDownFace = yellow;
        }
    }
    #pragma endregion Up & Down Face Colors

    #pragma region FirstRow
    smallCubes[0].faceColors.ColorFrontFace = green;
    smallCubes[0].faceColors.ColorBackFace  = black;
    smallCubes[0].faceColors.ColorRightFace = blue;
    smallCubes[0].faceColors.ColorLeftFace  = black;

    smallCubes[1].faceColors.ColorFrontFace = black;
    smallCubes[1].faceColors.ColorBackFace  = black;
    smallCubes[1].faceColors.ColorRightFace = blue;
    smallCubes[1].faceColors.ColorLeftFace  = black;

    smallCubes[2].faceColors.ColorFrontFace = black;
    smallCubes[2].faceColors.ColorBackFace  = white;
    smallCubes[2].faceColors.ColorRightFace = blue;
    smallCubes[2].faceColors.ColorLeftFace  = black;

    smallCubes[3].faceColors.ColorFrontFace = green;
    smallCubes[3].faceColors.ColorBackFace  = black;
    smallCubes[3].faceColors.ColorRightFace = black;
    smallCubes[3].faceColors.ColorLeftFace  = black;

    smallCubes[4].faceColors.ColorFrontFace = black;
    smallCubes[4].faceColors.ColorBackFace  = black;
    smallCubes[4].faceColors.ColorRightFace = black;
    smallCubes[4].faceColors.ColorLeftFace  = black;

    smallCubes[5].faceColors.ColorFrontFace = black;
    smallCubes[5].faceColors.ColorBackFace  = white;
    smallCubes[5].faceColors.ColorRightFace = black;
    smallCubes[5].faceColors.ColorLeftFace  = black;

    smallCubes[6].faceColors.ColorFrontFace = green;
    smallCubes[6].faceColors.ColorBackFace  = black;
    smallCubes[6].faceColors.ColorRightFace = black;
    smallCubes[6].faceColors.ColorLeftFace  = orange;

    smallCubes[7].faceColors.ColorFrontFace = black;
    smallCubes[7].faceColors.ColorBackFace  = black;
    smallCubes[7].faceColors.ColorRightFace = black;
    smallCubes[7].faceColors.ColorLeftFace  = orange;

    smallCubes[8].faceColors.ColorFrontFace = black;
    smallCubes[8].faceColors.ColorBackFace  = white;
    smallCubes[8].faceColors.ColorRightFace = black;
    smallCubes[8].faceColors.ColorLeftFace  = orange;
    #pragma endregion FirstRow

    #pragma region SecondRow
    smallCubes[9].faceColors.ColorFrontFace = green;
    smallCubes[9].faceColors.ColorBackFace  = black;
    smallCubes[9].faceColors.ColorRightFace = blue;
    smallCubes[9].faceColors.ColorLeftFace  = black;

    smallCubes[10].faceColors.ColorFrontFace = black;
    smallCubes[10].faceColors.ColorBackFace  = black;
    smallCubes[10].faceColors.ColorRightFace = blue;
    smallCubes[10].faceColors.ColorLeftFace  = black;

    smallCubes[11].faceColors.ColorFrontFace = black;
    smallCubes[11].faceColors.ColorBackFace  = white;
    smallCubes[11].faceColors.ColorRightFace = blue;
    smallCubes[11].faceColors.ColorLeftFace  = black;

    smallCubes[12].faceColors.ColorFrontFace = green;
    smallCubes[12].faceColors.ColorBackFace  = black;
    smallCubes[12].faceColors.ColorRightFace = black;
    smallCubes[12].faceColors.ColorLeftFace  = black;

    smallCubes[13].faceColors.ColorFrontFace = black;
    smallCubes[13].faceColors.ColorBackFace  = black;
    smallCubes[13].faceColors.ColorRightFace = black;
    smallCubes[13].faceColors.ColorLeftFace  = black;

    smallCubes[14].faceColors.ColorFrontFace = black;
    smallCubes[14].faceColors.ColorBackFace  = white;
    smallCubes[14].faceColors.ColorRightFace = black;
    smallCubes[14].faceColors.ColorLeftFace  = black;

    smallCubes[15].faceColors.ColorFrontFace = green;
    smallCubes[15].faceColors.ColorBackFace  = black;
    smallCubes[15].faceColors.ColorRightFace = black;
    smallCubes[15].faceColors.ColorLeftFace  = orange;

    smallCubes[16].faceColors.ColorFrontFace = black;
    smallCubes[16].faceColors.ColorBackFace  = black;
    smallCubes[16].faceColors.ColorRightFace = black;
    smallCubes[16].faceColors.ColorLeftFace  = orange;

    smallCubes[17].faceColors.ColorFrontFace = black;
    smallCubes[17].faceColors.ColorBackFace  = white;
    smallCubes[17].faceColors.ColorRightFace = black;
    smallCubes[17].faceColors.ColorLeftFace  = orange;
    #pragma endregion SecondRow

    #pragma region ThirdRow
    smallCubes[18].faceColors.ColorFrontFace = green;
    smallCubes[18].faceColors.ColorBackFace  = black;
    smallCubes[18].faceColors.ColorRightFace = blue;
    smallCubes[18].faceColors.ColorLeftFace  = black;

    smallCubes[19].faceColors.ColorFrontFace = black;
    smallCubes[19].faceColors.ColorBackFace  = black;
    smallCubes[19].faceColors.ColorRightFace = blue;
    smallCubes[19].faceColors.ColorLeftFace  = black;

    smallCubes[20].faceColors.ColorFrontFace = black;
    smallCubes[20].faceColors.ColorBackFace  = white;
    smallCubes[20].faceColors.ColorRightFace = blue;
    smallCubes[20].faceColors.ColorLeftFace  = black;

    smallCubes[21].faceColors.ColorFrontFace = green;
    smallCubes[21].faceColors.ColorBackFace  = black;
    smallCubes[21].faceColors.ColorRightFace = black;
    smallCubes[21].faceColors.ColorLeftFace  = black;

    smallCubes[22].faceColors.ColorFrontFace = black;
    smallCubes[22].faceColors.ColorBackFace  = black;
    smallCubes[22].faceColors.ColorRightFace = black;
    smallCubes[22].faceColors.ColorLeftFace  = black;

    smallCubes[23].faceColors.ColorFrontFace = black;
    smallCubes[23].faceColors.ColorBackFace  = white;
    smallCubes[23].faceColors.ColorRightFace = black;
    smallCubes[23].faceColors.ColorLeftFace  = black;

    smallCubes[24].faceColors.ColorFrontFace = green;
    smallCubes[24].faceColors.ColorBackFace  = black;
    smallCubes[24].faceColors.ColorRightFace = black;
    smallCubes[24].faceColors.ColorLeftFace  = orange;

    smallCubes[25].faceColors.ColorFrontFace = black;
    smallCubes[25].faceColors.ColorBackFace  = black;
    smallCubes[25].faceColors.ColorRightFace = black;
    smallCubes[25].faceColors.ColorLeftFace  = orange;

    smallCubes[26].faceColors.ColorFrontFace = black;
    smallCubes[26].faceColors.ColorBackFace  = white;
    smallCubes[26].faceColors.ColorRightFace = black;
    smallCubes[26].faceColors.ColorLeftFace  = orange;
    #pragma endregion ThirdRow
}

shaderClass& Cube::GetShader()
{
    return smallCubes[0].smallCubeProgram;
}

void Cube::Draw(glm::mat4& CameraMatrix, GLFWwindow* window, double prevTime)
{
    for (int i = 0; i < n_cubes; i++)
    {
        smallCubes[i].Draw(CameraMatrix, window, prevTime,false);
    }
}

void Cube::Motion(glm::mat4& CameraMatrix,glm::mat4& ViewMatrix, glm::mat4& ProjectionMatrix, GLFWwindow* window, MouseProperties mouseProperties_extern, KeyProperties keyProperties_extern)
{
    static bool click = false;
    
    if (click == true && !mouseProperties_extern.MOUSE_RIGHT_CLICK){click = false;}
    
    
    if (click == false && mouseProperties_extern.MOUSE_RIGHT_CLICK) {
        // Disable double buffering

        int window_width, window_height;
        glfwGetWindowSize(window, &window_width, &window_height);
        // Create off-screen FBO
        GLuint fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        // create renderbuffer object for color attachment
        GLuint color_rb;
        glGenRenderbuffers(1, &color_rb);
        glBindRenderbuffer(GL_RENDERBUFFER, color_rb);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, window_width, window_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_rb);

        // Create depth buffer renderbuffer for FBO
        GLuint depthRenderbuffer;
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, window_width, window_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

        // check FBO completeness
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "Failed to create FBO\n");
            exit(1);
        }

        click = mouseProperties_extern.MOUSE_RIGHT_CLICK;
        // Render the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < n_cubes; i++)
        {
            smallCubes[i].Draw(CameraMatrix, window, 0.0, true);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glFlush(); //forces all drawing commands to be sent to the graphics card and executed immediately.

        // Run this in your main loop since rightnow we have not rendered the back buffer
        unsigned char ClickedPixel[4];
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glReadPixels(mouseProperties_extern.ndcMouseX, mouseProperties_extern.ndcMouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, ClickedPixel);
        
        SelectedSmallCube = IdentifySmallCube(ClickedPixel);
        //COUT << SelectedSmallCube << ENDL;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // get the view and projection matrices
        glm::mat4 viewMatrix = ViewMatrix;
        glm::mat4 projectionMatrix = ProjectionMatrix;
        
    }

    GetKeyword(keyProperties_extern);

    // Change some of the smallCube's "model" matrix

    ApplyRotation(ViewMatrix);

    if(click == false || (click && mouseProperties_extern.MOUSE_RIGHT_CLICK))
    {
        for (int i = 0; i < n_cubes; i++)
        {
            smallCubes[i].Draw(CameraMatrix, window, 0.0,false);
        }
    }

}

int Cube::IdentifySmallCube(unsigned char* ClickedPixel)
{
    int R_channel = ClickedPixel[0];
    int G_channel = ClickedPixel[1];
    int B_channel = ClickedPixel[2];
    for (int i = 0; i < n_cubes; i++)
    {
        if(smallCubes[i].faceColors.ColorBackFace == Colors::black) // black 0 0 0
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorBackFace == Colors::blue) // blue 0 0 1
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorBackFace == Colors::green) // green 0 1 0
        {
            if (R_channel == i + 0 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorBackFace == Colors::orange) // orange 1 0.4 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 0.4*255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorBackFace == Colors::red) // red 1 0 0
        {
            if (R_channel == -i + 255 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorBackFace == Colors::white) // white 1 1 1
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorBackFace == Colors::yellow) // yellow 1 1 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }

        if(smallCubes[i].faceColors.ColorDownFace == Colors::black) // black 0 0 0
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorDownFace == Colors::blue) // blue 0 0 1
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorDownFace == Colors::green) // green 0 1 0
        {
            if (R_channel == i + 0 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorDownFace == Colors::orange) // orange 1 0.4 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 0.4*255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorDownFace == Colors::red) // red 1 0 0
        {
            if (R_channel == -i + 255 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorDownFace == Colors::white) // white 1 1 1
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorDownFace == Colors::yellow) // yellow 1 1 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::black) // black 0 0 0
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::blue) // blue 0 0 1
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::green) // green 0 1 0
        {
            if (R_channel == i + 0 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::orange) // orange 1 0.4 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 0.4*255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::red) // red 1 0 0
        {
            if (R_channel == -i + 255 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::white) // white 1 1 1
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorFrontFace == Colors::yellow) // yellow 1 1 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::black) // black 0 0 0
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::blue) // blue 0 0 1
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::green) // green 0 1 0
        {
            if (R_channel == i + 0 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::orange) // orange 1 0.4 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 0.4*255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::red) // red 1 0 0
        {
            if (R_channel == -i + 255 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::white) // white 1 1 1
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorLeftFace == Colors::yellow) // yellow 1 1 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        
        if(smallCubes[i].faceColors.ColorRightFace == Colors::black) // black 0 0 0
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorRightFace == Colors::blue) // blue 0 0 1
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorRightFace == Colors::green) // green 0 1 0
        {
            if (R_channel == i + 0 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorRightFace == Colors::orange) // orange 1 0.4 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 0.4*255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorRightFace == Colors::red) // red 1 0 0
        {
            if (R_channel == -i + 255 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorRightFace == Colors::white) // white 1 1 1
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorRightFace == Colors::yellow) // yellow 1 1 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }

        if(smallCubes[i].faceColors.ColorUpFace == Colors::black) // black 0 0 0
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorUpFace == Colors::blue) // blue 0 0 1
        {
            if (R_channel == i + 0 && G_channel == i + 0 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorUpFace == Colors::green) // green 0 1 0
        {
            if (R_channel == i + 0 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorUpFace == Colors::orange) // orange 1 0.4 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 0.4*255 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorUpFace == Colors::red) // red 1 0 0
        {
            if (R_channel == -i + 255 && G_channel == i + 0 && B_channel == i + 0)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorUpFace == Colors::white) // white 1 1 1
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == -i + 255)
            {
                return i;
            }
        }
        if(smallCubes[i].faceColors.ColorUpFace == Colors::yellow) // yellow 1 1 0
        {
            if (R_channel == -i + 255 && G_channel == -i + 255 && B_channel == i + 0)
            {
                return i;
            }
        }

    }
    
}

void Cube::GetKeyword(KeyProperties keyProperties_extern)
{
    static int state_for_2 = 0;
    BUTTON_MACHINE(keyProperties_extern.KEY_2_PRESSED, rotationWay.Back_2_Front, rotationWay.Identical, state_for_2)

    static int state_for_8 = 0;
    BUTTON_MACHINE(keyProperties_extern.KEY_8_PRESSED, rotationWay.Front_2_Back, rotationWay.Identical, state_for_8)

    static int state_for_7 = 0;
    BUTTON_MACHINE(keyProperties_extern.KEY_7_PRESSED, rotationWay.CCW, rotationWay.Identical, state_for_7)

    static int state_for_3 = 0;
    BUTTON_MACHINE(keyProperties_extern.KEY_3_PRESSED, rotationWay.CW, rotationWay.Identical, state_for_3)

    static int state_for_4 = 0;
    BUTTON_MACHINE(keyProperties_extern.KEY_4_PRESSED, rotationWay.Right_2_Left, rotationWay.Identical, state_for_4)

    static int state_for_6 = 0;
    BUTTON_MACHINE(keyProperties_extern.KEY_6_PRESSED, rotationWay.Left_2_Right, rotationWay.Identical, state_for_6)

    static int state_for_ReStart = 0;
    RESTART_DETECTION_MACHINE(keyProperties_extern.KEY_RESTART_PRESSED, state_for_ReStart)

    static int state_for_Shuffle = 0;
    static bool shuffleFlag = false;
    static int n_move_counter = 0;
    SHUFFLE_DETECTION_MACHINE(keyProperties_extern.KEY_SHUFFLE_PRESSED, state_for_Shuffle)

    
    if (rotationWay.Back_2_Front == false && rotationWay.Front_2_Back == false && rotationWay.CCW == false && rotationWay.CW == false && rotationWay.Left_2_Right == false && rotationWay.Right_2_Left == false)
    {
        rotationWay.Identical = true;
    }else{
        rotationWay.Identical = false;
    }
    
    if (state_for_ReStart == 1 && IsRotating() == 0)
    {
        Restart();
    }

    if (state_for_Shuffle == 1 || (shuffleFlag && state_for_Shuffle == 0))
    {
        shuffleFlag = true;
        if (IsRotating() == 0)
        {
            Shuffle();
            n_move_counter++;
        }
        if (n_move_counter == n_move)
        {
            shuffleFlag = false;
            n_move_counter = 0;
        }
    }
}

void Cube::ApplyRotation(glm::mat4& ViewMatrix){
    float tolerance = 0.001;
    // The coordinates of the selected cube
    glm::vec3 selectedCenterCoor = smallCubes[SelectedSmallCube].GetCenterCoor();
    float selectedCenterCoor_axes;
    int AXES_CHOICE;

    glm::mat3 RotatioPartnViewMatrix = glm::mat3(ViewMatrix);
    glm::vec3 axes_x = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 axes_y = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 axes_z = glm::vec3(0.0f, 0.0f, 1.0f);

    bool _IsRotating = IsRotating();

    // Find the other small cubes in the rotation way (aka roation plane)
    if (rotationWay.CCW || rotationWay.CW)
    {   // SmallCubes that have the same Z component
        axes_z = glm::transpose(RotatioPartnViewMatrix)*axes_z;
        if ((abs(axes_z[0]) > abs(axes_z[1])) && (abs(axes_z[0]) > abs(axes_z[2])) )
        {
            // world x axes
            AXES_CHOICE = 0;
        }
        else if ((abs(axes_z[1]) > abs(axes_z[0])) && (abs(axes_z[1]) > abs(axes_z[2])) )
        {
            // world y axes
            AXES_CHOICE = 1;
        }else if ((abs(axes_z[2]) > abs(axes_z[0])) && (abs(axes_z[2]) > abs(axes_z[0])) )
        {
            // world z axes
            AXES_CHOICE = 2;
        }

        for (int i = 0; i < n_cubes; i++)
        {
            if(abs(selectedCenterCoor[AXES_CHOICE] - smallCubes[i].GetCenterCoor(AXES_CHOICE)) < tolerance)
            {
                // smallCubes[i].ApplyRotation(00.0, 2);
                if (!rotationWay.Identical)
                {
                    if (rotationWay.CCW)
                    {
                        smallCubes[i].ApplyRotation((std::signbit(axes_z[AXES_CHOICE]) ? -1 : 1) * 90.0, AXES_CHOICE, _IsRotating);
                    }else if(rotationWay.CW){
                        smallCubes[i].ApplyRotation((std::signbit(axes_z[AXES_CHOICE]) ? -1 : 1) *-90.0, AXES_CHOICE, _IsRotating);
                    }   
                }else{
                        smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
                }
            }else
            {
                smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
            }
        }
    }
    if (rotationWay.Right_2_Left || rotationWay.Left_2_Right)
    {   // SmallCubes that have the same Y component
        axes_y = glm::transpose(RotatioPartnViewMatrix)*axes_y;
        if ((abs(axes_y[0]) > abs(axes_y[1])) && (abs(axes_y[0]) > abs(axes_y[2])) )
        {
            // world x axes
            AXES_CHOICE = 0;
        }
        else if ((abs(axes_y[1]) > abs(axes_y[0])) && (abs(axes_y[1]) > abs(axes_y[2])) )
        {
            // world y axes
            AXES_CHOICE = 1;
        }else if ((abs(axes_y[2]) > abs(axes_y[0])) && (abs(axes_y[2]) > abs(axes_y[0])) )
        {
            // world z axes
            AXES_CHOICE = 2;
        }
        for (int i = 0; i < n_cubes; i++)
        {
            if(abs(selectedCenterCoor[AXES_CHOICE] - smallCubes[i].GetCenterCoor(AXES_CHOICE)) < tolerance)
            {
                if (!rotationWay.Identical)
                {
                    if (rotationWay.Left_2_Right)
                    {
                        smallCubes[i].ApplyRotation((std::signbit(axes_y[AXES_CHOICE]) ? -1 : 1) * 90.0, AXES_CHOICE, _IsRotating);
                    }else if(rotationWay.Right_2_Left)
                    {
                        smallCubes[i].ApplyRotation((std::signbit(axes_y[AXES_CHOICE]) ? -1 : 1) * -90.0, AXES_CHOICE, _IsRotating);
                    }
                }else{
                        smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
                }
            }else
            {
                smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
            }
        }
    }
    if (rotationWay.Back_2_Front || rotationWay.Front_2_Back)
    {   // SmallCubes that have the same X component
        axes_x = glm::transpose(RotatioPartnViewMatrix)*axes_x;
        if ((abs(axes_x[0]) > abs(axes_x[1])) && (abs(axes_x[0]) > abs(axes_x[2])) )
        {
            // world x axes
            AXES_CHOICE = 0;
        }
        else if ((abs(axes_x[1]) > abs(axes_x[0])) && (abs(axes_x[1]) > abs(axes_x[2])) )
        {
            // world y axes
            AXES_CHOICE = 1;
        }else if ((abs(axes_x[2]) > abs(axes_x[0])) && (abs(axes_x[2]) > abs(axes_x[0])) )
        {
            // world z axes
            AXES_CHOICE = 2;
        }
        for (int i = 0; i < n_cubes; i++)
        {
            if(abs(selectedCenterCoor[AXES_CHOICE] - smallCubes[i].GetCenterCoor(AXES_CHOICE)) < tolerance)
            {
                if (!rotationWay.Identical)
                {
                    if (rotationWay.Back_2_Front)
                    {
                        smallCubes[i].ApplyRotation((std::signbit(axes_x[AXES_CHOICE]) ? -1 : 1) * 90.0, AXES_CHOICE, _IsRotating);
                    }else if(rotationWay.Front_2_Back)
                    {
                        smallCubes[i].ApplyRotation((std::signbit(axes_x[AXES_CHOICE]) ? -1 : 1) * -90.0, AXES_CHOICE, _IsRotating);
                    }
                }else{
                        smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
                }
            }else
            {
                        smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
            }
        }    
    }
    if (rotationWay.Identical)
    {
        for(int i = 0; i < n_cubes; i++)
        {
            smallCubes[i].ApplyRotation(0.0, -1, _IsRotating);
        }
    }
    
}

void Cube::Restart()
{
    for (int i = 0; i < n_cubes; i++)
    {
        smallCubes[i].Restart();
    }
}

void Cube::Shuffle()
{
    static int oldRandomRotation;
    static int oldRandomCube;

    // seed the random number generator with current time
    std::srand(std::time(nullptr));
    int random_Cube = std::rand() % n_cubes;
    SelectedSmallCube = random_Cube;

    if (SelectedSmallCube == oldRandomCube)
    {   // To see differnet rotation
        random_Cube = std::rand() % n_cubes;
    }
    SelectedSmallCube = random_Cube;
    oldRandomCube = SelectedSmallCube;


    rotationWay.Back_2_Front = false;
    rotationWay.Front_2_Back = false;
    rotationWay.Right_2_Left = false;
    rotationWay.Left_2_Right = false;
    rotationWay.CCW = false;
    rotationWay.CW = false;
    rotationWay.Identical = false;
    int randomRotation = std::rand() % 6; // generate a number between 0 and 5

    if (randomRotation == oldRandomRotation)
    {   // To see differnet rotation
        randomRotation = std::rand() % 6; // generate a number between 0 and 5
    }
    
    oldRandomRotation = randomRotation;

    if (randomRotation == 0){ rotationWay.Back_2_Front = true; }
    if (randomRotation == 1){ rotationWay.Front_2_Back = true; }
    if (randomRotation == 2){ rotationWay.Right_2_Left = true; }
    if (randomRotation == 3){ rotationWay.Left_2_Right = true; }
    if (randomRotation == 4){ rotationWay.CCW = true; }
    if (randomRotation == 5){ rotationWay.CW = true; }
}

void Cube::SetPossiblePositions()
{
    PossiblePositions[0] = 0.0;     PossiblePositions[1] = 0.0;      PossiblePositions[2] = 0.0; 
    PossiblePositions[3] = cubeLen; PossiblePositions[4] = 0.0;      PossiblePositions[5] = 0.0; 
    PossiblePositions[6] = 0.0;     PossiblePositions[7] = cubeLen;  PossiblePositions[8] = 0.0; 
    PossiblePositions[9] = 0.0;     PossiblePositions[10] = 0.0;     PossiblePositions[11] = cubeLen; 

    PossiblePositions[12] = cubeLen; PossiblePositions[13] = cubeLen; PossiblePositions[14] = 0.0; 
    PossiblePositions[15] = 0.0;     PossiblePositions[16] = cubeLen; PossiblePositions[17] = cubeLen; 
    PossiblePositions[18] = cubeLen; PossiblePositions[19] = 0.0;     PossiblePositions[20] = cubeLen; 
    PossiblePositions[21] = cubeLen; PossiblePositions[22] = cubeLen; PossiblePositions[23] = cubeLen; 
}

bool Cube::IsRotating()
{
    float tolerance = 0.001;
    for (int i = 0; i < n_cubes; i++)
    {
        int count = 0;
        for (int j = 0; j < 8; j++)
        {
            if (abs(abs(smallCubes[i].center_coor_x) - PossiblePositions[3*j]) < tolerance && abs(abs(smallCubes[i].center_coor_y) - PossiblePositions[3*j + 1]) < tolerance && abs(abs(smallCubes[i].center_coor_z) - PossiblePositions[3*j+2]) < tolerance)
            {
                count++;
            }
        }
        if (count == 0)
        {
            return true; // Cube is rotating
        }
    }
    return false; // Cube is NOT rotating
    
}

void invertMatrix4x4(glm::mat4 matrixIN, glm::mat4 MatrixOUT) {
    MatrixOUT = glm::inverse(matrixIN);
}
    
double map(double value, int inputMin, int inputMax, int outputMin, int outputMax) {
    // Calculate the range of the input and output values
    int inputRange = inputMax - inputMin;
    int outputRange = outputMax - outputMin;

    // Map the input value to the output range
    double mappedValue = (double)((double)((double)((double)(value - inputMin) * outputRange) / inputRange) + outputMin);

    // Return the mapped value
    return mappedValue;
}

double cosine_similarity(glm::vec3 RayDir, glm::vec4 SmallCubeCenter) {
    glm::vec3 smallCubeCenterInVec3 = glm::vec3(SmallCubeCenter[0],SmallCubeCenter[1],SmallCubeCenter[2]);
    double dot_product = 0.0;
    double norm1 = 0.0;
    double norm2 = 0.0;
    
    // Calculate dot product and norms
    for (int i = 0; i < RayDir.length(); i++) {
        dot_product += RayDir[i] * smallCubeCenterInVec3[i];
        norm1 += RayDir[i] * RayDir[i];
        norm2 += smallCubeCenterInVec3[i] * smallCubeCenterInVec3[i];
    }
    
    // Calculate cosine similarity
    double denom = std::sqrt(norm1) * std::sqrt(norm2);
    if (denom == 0.0) {
        return 0.0;
    } else {
        return dot_product / denom;
    }
}