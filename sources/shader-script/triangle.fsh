#version 330 core
struct Material {
//    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct SpotLight {
    vec3 position;
    vec3  direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


out vec4 fragColor;

in vec2 textureCoordinates;
in vec3 vertexNormal;
in vec3 fragPosition;


#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform vec3 viewPosition;
uniform Material material;


vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection, Material material, vec2 coordinates)
{
    vec3 lightDirection = normalize(-directionalLight.direction);
    
    // 漫反射着色
    float diffuse = max(dot(normal, lightDirection), 0.0);

    // 镜面着色
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    
    vec3 ambientVector = directionalLight.ambient * vec3(texture(material.diffuse, coordinates));
    vec3 diffuseVector = directionalLight.diffuse * diffuse * vec3(texture(material.diffuse, coordinates));
    vec3 specularVector = directionalLight.specular * specular * vec3(texture(material.specular, coordinates));
    
    return (ambientVector + diffuseVector + specularVector);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection, Material material, vec2 coordinates)
{
    vec3 lightDirection = normalize(light.position - fragPosition);
    
    // 漫反射
    float diffuse = max(dot(normal, lightDirection), 0.0);

    // 镜面反射
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    
    // 衰减
    float dist = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    
    vec3 ambientVector = directionalLight.ambient * vec3(texture(material.diffuse, coordinates)) * attenuation;
    vec3 diffuseVector = directionalLight.diffuse * diffuse * vec3(texture(material.diffuse, coordinates)) * attenuation;
    vec3 specularVector = directionalLight.specular * specular * vec3(texture(material.specular, coordinates)) * attenuation;
    return (ambientVector + diffuseVector + specularVector);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection, Material material, vec2 coordinates)
{
    vec3 lightDirection = normalize(light.position - fragPosition);
    
    // 漫反射
    float diffuse = max(dot(normal, lightDirection), 0.0);
    
    // 镜面反射
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
   
    // 衰减
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // spotlight intensity
    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambientVector = light.ambient * vec3(texture(material.diffuse, coordinates));
    vec3 diffuseVector = light.diffuse * diffuse * vec3(texture(material.diffuse, coordinates));
    vec3 specularVector = light.specular * specular * vec3(texture(material.specular, coordinates));
    
    ambientVector *= attenuation * intensity;
    diffuseVector *= attenuation * intensity;
    specularVector *= attenuation * intensity;
    return (ambientVector + diffuseVector + specularVector);
}

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 viewDirection = normalize(viewPosition - fragPosition);

    vec3 result = CalculateDirectionalLight(directionalLight, normal, viewDirection, material, textureCoordinates);

    for (int i = 0; i < NR_POINT_LIGHTS; i++) 
    {
        result += CalculatePointLight(pointLights[i], normal, fragPosition, viewDirection, material, textureCoordinates);
    }
    result += CalculateSpotLight(spotLight, normal, fragPosition, viewDirection, material, textureCoordinates);

    fragColor = vec4(result, 1.0);
}



