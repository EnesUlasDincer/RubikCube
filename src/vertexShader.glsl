const std::string vertexShader_from = R"glsl(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 move;


void main(){
    gl_Position = vec4(aPos.x + move.x, aPos.y + move.y, 0.0,  1.0);
}
)glsl";

const std::string textureShader_VR_pyr = R"glsl(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    }
    )glsl";

const std::string textureShader_VR = R"glsl(
    #version 330 core

    layout (location = 0) in vec3 aPos;

    out vec3 vertexColor;

    uniform mat4 camMatrix;
    uniform mat4 model;

    void main()
    {
        gl_Position = camMatrix * model * vec4(aPos, 1.0);
    }
    )glsl";