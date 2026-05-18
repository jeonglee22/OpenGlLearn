#version 330 core
struct PointLight{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform PointLight pointLight;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 viewPos;

// void main()
// {    
//     FragColor = texture(texture_diffuse1, TexCoords);

    
// }

void main()
{
    vec3 result = vec3(0.0);
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lightDir = normalize(pointLight.position - FragPos);
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));  

    vec3 ambient = pointLight.ambient * vec3(texture(texture_diffuse1, TexCoords));

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = pointLight.diffuse * (diff * vec3(texture(texture_diffuse1, TexCoords)));

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specularTex = vec3(texture(texture_specular1, TexCoords));
    vec3 specular = pointLight.specular * (spec * specularTex);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}