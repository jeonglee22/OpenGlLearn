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

out vec4 FragColor;

uniform Material material;
uniform vec3 lightColor;
uniform Light light;
// uniform vec3 objectColor;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 ligthDir = normalize(light.position - FragPos);
    float diff = max(dot(ligthDir, norm), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-ligthDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular); 

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}