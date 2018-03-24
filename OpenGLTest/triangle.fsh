#version 330 core
struct Material {
//    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
//    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

out vec4 fragColor;

in vec2 textureCoordinates;
in vec3 vertexNormal;
in vec3 fragPosition;


uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
    // 环境光
    vec3 ambient = light.ambient * texture(material.diffuse, textureCoordinates).rgb;

    // 漫反射
    vec3 normal = normalize(vertexNormal);
    vec3 lightDirection = normalize(light.position - fragPosition);
//    vec3 lightDirection = normalize(-light.direction);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCoordinates).rgb;
    
    // 镜面光
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.specular, textureCoordinates).rgb);
    
    float distance    = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    
    
    // Phong Shader mai
    vec3 result = (ambient + diffuse + specular) * attenuation;
    fragColor = vec4(result, 1.0);
}
