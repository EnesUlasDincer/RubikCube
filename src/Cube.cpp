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
}

void Cube::Init(const::std::string& vertexShader, const::std::string& fragmentShader)
{
    // Initilazing every small cube with vertex/fragment shader
    for (int i = 0; i < n_cubes; i++)
    {
        CubeShaders[i].init(vertexShader, fragmentShader);
        smallCubes[i].smallCubeProgram.SetProgram(CubeShaders[i].GetProgram());
        smallCubes[i].CubeID = i;
    }

    int loc = glGetUniformLocation(smallCubes[0].smallCubeProgram.GetProgram(), "uniColor");
    
    // Set off-sets for the small cubes
    Setoffset();

    // Set the colors of each face
    SetColors();

    // Set the vertices of each cube
    SetVertices();

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

    smallCubes[3].faceColors.ColorFrontFace = black;
    smallCubes[3].faceColors.ColorBackFace  = white;
    smallCubes[3].faceColors.ColorRightFace = black;
    smallCubes[3].faceColors.ColorLeftFace  = black;

    smallCubes[4].faceColors.ColorFrontFace = black;
    smallCubes[4].faceColors.ColorBackFace  = black;
    smallCubes[4].faceColors.ColorRightFace = black;
    smallCubes[4].faceColors.ColorLeftFace  = black;

    smallCubes[5].faceColors.ColorFrontFace = green;
    smallCubes[5].faceColors.ColorBackFace  = black;
    smallCubes[5].faceColors.ColorRightFace = black;
    smallCubes[5].faceColors.ColorLeftFace  = black;

    smallCubes[6].faceColors.ColorFrontFace = black;
    smallCubes[6].faceColors.ColorBackFace  = white;
    smallCubes[6].faceColors.ColorRightFace = black;
    smallCubes[6].faceColors.ColorLeftFace  = orange;

    smallCubes[7].faceColors.ColorFrontFace = black;
    smallCubes[7].faceColors.ColorBackFace  = black;
    smallCubes[7].faceColors.ColorRightFace = black;
    smallCubes[7].faceColors.ColorLeftFace  = orange;

    smallCubes[8].faceColors.ColorFrontFace = green;
    smallCubes[8].faceColors.ColorBackFace  = black;
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

    smallCubes[12].faceColors.ColorFrontFace = black;
    smallCubes[12].faceColors.ColorBackFace  = white;
    smallCubes[12].faceColors.ColorRightFace = black;
    smallCubes[12].faceColors.ColorLeftFace  = black;

    smallCubes[13].faceColors.ColorFrontFace = black;
    smallCubes[13].faceColors.ColorBackFace  = black;
    smallCubes[13].faceColors.ColorRightFace = black;
    smallCubes[13].faceColors.ColorLeftFace  = black;

    smallCubes[14].faceColors.ColorFrontFace = green;
    smallCubes[14].faceColors.ColorBackFace  = black;
    smallCubes[14].faceColors.ColorRightFace = black;
    smallCubes[14].faceColors.ColorLeftFace  = black;

    smallCubes[15].faceColors.ColorFrontFace = black;
    smallCubes[15].faceColors.ColorBackFace  = white;
    smallCubes[15].faceColors.ColorRightFace = black;
    smallCubes[15].faceColors.ColorLeftFace  = orange;

    smallCubes[16].faceColors.ColorFrontFace = black;
    smallCubes[16].faceColors.ColorBackFace  = black;
    smallCubes[16].faceColors.ColorRightFace = black;
    smallCubes[16].faceColors.ColorLeftFace  = orange;

    smallCubes[17].faceColors.ColorFrontFace = green;
    smallCubes[17].faceColors.ColorBackFace  = black;
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

    smallCubes[21].faceColors.ColorFrontFace = black;
    smallCubes[21].faceColors.ColorBackFace  = white;
    smallCubes[21].faceColors.ColorRightFace = black;
    smallCubes[21].faceColors.ColorLeftFace  = black;

    smallCubes[22].faceColors.ColorFrontFace = black;
    smallCubes[22].faceColors.ColorBackFace  = black;
    smallCubes[22].faceColors.ColorRightFace = black;
    smallCubes[22].faceColors.ColorLeftFace  = black;

    smallCubes[23].faceColors.ColorFrontFace = green;
    smallCubes[23].faceColors.ColorBackFace  = black;
    smallCubes[23].faceColors.ColorRightFace = black;
    smallCubes[23].faceColors.ColorLeftFace  = black;

    smallCubes[24].faceColors.ColorFrontFace = black;
    smallCubes[24].faceColors.ColorBackFace  = white;
    smallCubes[24].faceColors.ColorRightFace = black;
    smallCubes[24].faceColors.ColorLeftFace  = orange;

    smallCubes[25].faceColors.ColorFrontFace = black;
    smallCubes[25].faceColors.ColorBackFace  = black;
    smallCubes[25].faceColors.ColorRightFace = black;
    smallCubes[25].faceColors.ColorLeftFace  = orange;

    smallCubes[26].faceColors.ColorFrontFace = green;
    smallCubes[26].faceColors.ColorBackFace  = black;
    smallCubes[26].faceColors.ColorRightFace = black;
    smallCubes[26].faceColors.ColorLeftFace  = orange;
    #pragma endregion ThirdRow
}

void Cube::Draw()
{
    for (int i = 0; i < n_cubes; i++)
    {
        smallCubes[i].Draw();
    }
}