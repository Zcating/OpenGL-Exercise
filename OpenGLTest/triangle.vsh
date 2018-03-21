#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexNormal;
out vec3 fragPosition;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    vertexNormal = mat3(transpose(inverse(model))) * aNormal;
    fragPosition = vec3(model * vec4(aPosition, 1.0));
}
