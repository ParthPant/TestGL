#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 Normal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{

    normal = mat3(transpose(inverse(u_model))) * Normal;
    fragPos = vec3(u_model * position);
    gl_Position = u_projection * u_view * u_model * position;
   //v_texCord = texCord;
};

#shader fragment
#version 330 core

in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform vec3 u_viewPos;

void main()
{
   //vec4 TexColor = texture(u_Texture, v_texCord);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;
   
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_lightColor;

    vec3 result = (ambient + diffuse + specular) * u_objectColor;
    FragColor = vec4(result, 1.0);
};