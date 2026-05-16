#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

// struct Light {
//     vec3 position;
//     vec3 direction;
//     float cutOff;
//     float outerCutOff;

//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;

//     float constant;
//     float linear;
//     float quadratic;
// };

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

uniform Material material;
// uniform vec3 lightColor;
// uniform Light light;
uniform vec3 viewPos;
// uniform vec3 objectColor;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 result = vec3(0.0);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    result += CalculateDirectionalLight(dirLight, norm, viewDir);
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    result += CalculateSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTex = vec3(texture(material.specular, TexCoords));
    vec3 specular = light.specular * (spec * specularTex);
    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTex = vec3(texture(material.specular, TexCoords));
    vec3 specular = light.specular * (spec * specularTex);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTex = vec3(texture(material.specular, TexCoords));
    vec3 specular = light.specular * (spec * specularTex);

    ambient *= intensity * attenuation;
    diffuse *= intensity * attenuation;
    specular *= intensity * attenuation;
    return ambient + diffuse + specular;
}


// void main()
// {
//     vec3 lightDir = normalize(light.position - FragPos);
//     float theta = dot(lightDir, normalize(-light.direction));
//     float epsilon = light.cutOff - light.outerCutOff;
//     float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

//     float distance = length(light.position - FragPos);
//     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

//     vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

//     vec3 norm = normalize(Normal);
//     // vec3 lightDir = normalize(-light.direction);
//     float diff = max(dot(lightDir, norm), 0.0);
//     vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specularTex = vec3(texture(material.specular, TexCoords));
//     vec3 specular = light.specular * (spec * specularTex); 

//     // vec3 emission = specularTex == vec3(0.0) ? texture(material.emission, TexCoords).rgb : vec3(0.0);
//     diffuse *= intensity;
//     specular *= intensity;

//     ambient *= attenuation;
//     diffuse *= attenuation;
//     specular *= attenuation;
//     vec3 result = (ambient + diffuse + specular);
//     FragColor = vec4(result, 1.0);
// }