#version 330 core
in vec2 aTextureCoordinate;
out vec4 FragColor;

uniform float mixValue;
uniform sampler2D boxTexture;
uniform sampler2D smileTexture;

void main()
{
    FragColor = mix(texture(boxTexture, aTextureCoordinate), texture(smileTexture, vec2(aTextureCoordinate.x, aTextureCoordinate.y)), mixValue);
}
