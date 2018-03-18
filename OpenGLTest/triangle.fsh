#version 330 core
in vec2 aTextureCoordinate;
out vec4 FragColor;

//uniform float mixValue;
//uniform sampler2D boxTexture;
//uniform sampler2D smileTexture;
uniform vec3 boxColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor * boxColor, 1.0);
}
