#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoordinates;

out vec2 TextureCoordinates;
out vec3 VertexNormal;
out vec3 FragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
    VertexNormal = mat3(transpose(inverse(model))) * aNormal;
    FragPosition = vec3(model * vec4(aPosition, 1.0));
    TextureCoordinates = aTextureCoordinates;
    gl_Position = projection * view * model * vec4(FragPosition, 1.0);
    
//    VertexNormal = mat3(transpose(inverse(model))) * aNormal;
//    FragPosition = vec3(model * vec4(aPosition, 1.0));
//    TextureCoordinates = aTextureCoordinates;
//    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
