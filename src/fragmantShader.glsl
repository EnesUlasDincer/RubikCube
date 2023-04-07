const std::string textureShader_Frag = R"glsl(
    #version 330 core
    out vec4 FragColor;

    in vec2 TexCoord;

    // texture sampler
    uniform sampler2D texture1;

    void main()
    {
        FragColor = texture(texture1, TexCoord);
    }
    )glsl";

 const std::string fragmentShader_fr = R"glsl(
    #version 330 core
    layout(location = 0) out vec4 color;

    in vec3 vertexColor;

    void main()
    {
        color = vec4(vertexColor, 1.0);
    }
    )glsl";

const std::string fragmentShader = R"glsl(
#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 uniColor; // we set this variable in the OpenGL code.

void main(){
    color = uniColor;
}
)glsl";