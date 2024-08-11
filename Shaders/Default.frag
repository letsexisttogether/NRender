#version 330

out vec4 color;

in vec2 texCoord;

uniform sampler2D texture1;

vec2 ReverseColor(in vec2 color)
{
    return color;
}

void main()
{
    vec4 firstColor = texture(texture1, ReverseColor(texCoord));

    color = firstColor;
}
