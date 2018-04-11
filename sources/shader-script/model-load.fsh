#version 330 core
out vec4 FragColor;

in vec2 TextureCoordinates;
in vec3 FragPosition;
in vec3 VertexNormal;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
};

struct PointLight {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform PointLight light;
uniform vec3 viewPosition;
uniform float shininess;


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection, float shininess, Material material, vec2 coordinates)
{
    vec3 lightDirection = normalize(light.position - fragPosition);
    
    // 漫反射
    float diffuse = max(dot(normal, lightDirection), 0.0);
    
    // 镜面反射
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
    
    // 衰减
//    float dist = length(light.position - fragPosition);
//    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
//
    vec3 ambientVector = light.ambient * vec3(texture(material.diffuse, coordinates));
    vec3 diffuseVector = light.diffuse * diffuse * vec3(texture(material.diffuse, coordinates));
    vec3 specularVector = light.specular * specular * vec3(texture(material.specular, coordinates));
    return (ambientVector + diffuseVector + specularVector);
//    vec3 ambientVector = light.ambient * vec3(texture(material.diffuse, coordinates)) * attenuation;
//    vec3 diffuseVector = light.diffuse * diffuse * vec3(texture(material.diffuse, coordinates)) * attenuation;
//    vec3 specularVector = light.specular * specular * vec3(texture(material.specular, coordinates)) * attenuation;
//    return (ambientVector + diffuseVector + specularVector);
}

void main()
{
    vec3 normal = normalize(VertexNormal);
    vec3 viewDirection = normalize(viewPosition - FragPosition);

    vec3 result = CalculatePointLight(light, normal, FragPosition, viewDirection, shininess, material, TextureCoordinates);
    FragColor = vec4(result, 1.0);
//    FragColor = texture(texture_specular1, TextureCoordinates);
}
