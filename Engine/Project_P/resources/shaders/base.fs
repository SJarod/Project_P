#version 450 core

in vec2 uv;

out vec4 FragColor;

uniform sampler2D texColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0) * texture(texColor, uv);
};