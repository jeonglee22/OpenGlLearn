#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

struct Light {
    // vec3 position;
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

uniform Material material;
uniform vec3 lightColor;
uniform Light light;
// uniform vec3 objectColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTex = vec3(texture(material.specular, TexCoords));
    vec3 specular = light.specular * (spec * specularTex); 

    // vec3 emission = specularTex == vec3(0.0) ? texture(material.emission, TexCoords).rgb : vec3(0.0);

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}