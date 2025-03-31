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

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform Light light2;
uniform sampler2D texture_diffuse;

vec3 CalcLight(Light light, vec3 norm, vec3 viewDir) {
    // Ambient
    vec3 ambient = light.ambient * material.ambient;
    
    // Diffuse
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Calculamos la contribución de ambas luces
    vec3 result = CalcLight(light, norm, viewDir) + CalcLight(light2, norm, viewDir);
    
    // Aplicamos la textura al color final
    FragColor = vec4(result, 1.0f) * texture(texture_diffuse, TexCoords);
}