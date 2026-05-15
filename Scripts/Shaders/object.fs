#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

out vec4 FragColor;
  
uniform Material material;
uniform vec3 lightColor;
// uniform vec3 objectColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

void main()
{
    vec3 ambient = lightColor * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 ligthDir = normalize(LightPos - FragPos);

    float diff = max(dot(ligthDir, norm), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-ligthDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular); 

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}