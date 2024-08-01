#version 330

out vec4 color;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float secondStrength;

vec2 ReverseColor(in vec2 color)
{
    
    return color;
}

void main()
{
    vec4 firstColor = texture(texture1, ReverseColor(texCoord));
    vec4 secondColor = texture(texture2, texCoord);

    color = mix(firstColor, secondColor, secondStrength);
}
