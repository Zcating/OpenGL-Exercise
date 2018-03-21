#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 viewPosition;

uniform Material material;
uniform Light light;


in vec3 vertexNormal;
in vec3 fragPosition;


void main()
{
    // 环境光
    vec3 ambient = light.ambient * material.ambient;

    // 漫反射
    vec3 normal = normalize(vertexNormal);
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // 镜面光
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    // Phong Shader mai
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}
