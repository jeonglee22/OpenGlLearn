#version 330 core
out vec4 FragColor;
  
uniform vec3 lightColor;
uniform vec3 objectColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 ligthDir = normalize(LightPos - FragPos);

    float diff = max(dot(ligthDir, norm), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-ligthDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}