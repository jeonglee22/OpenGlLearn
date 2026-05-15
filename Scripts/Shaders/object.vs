#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 lightColor;

//out vec3 Normal;
//out vec3 FragPos;
//out vec3 LightPos;
out vec3 LightingColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    vec3 FragPos = vec3(view * model * vec4(aPos, 1.0f));
    vec3 Normal = mat3(transpose(inverse(view * model))) * aNormal;
    vec3 LightPos = vec3(view * vec4(lightPos, 1.0f));

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 ligthDir = normalize(LightPos - FragPos);

    float diff = max(dot(ligthDir, norm), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-ligthDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * lightColor; 

    LightingColor = ambient + diffuse + specular;
}