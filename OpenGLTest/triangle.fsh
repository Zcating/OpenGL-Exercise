#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform float mixValue;
uniform sampler2D boxTexture;
uniform sampler2D smileTexture;

void main()
{
//    color = mix(texture(boxTexture, TexCoord), texture(smileTexture, TexCoord), 0.1);
    
    color = mix(texture(boxTexture, TexCoord), texture(smileTexture, vec2(TexCoord.x, TexCoord.y)), mixValue);
}
