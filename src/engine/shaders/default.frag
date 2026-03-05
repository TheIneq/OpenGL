#version 460

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main() {
   float ambientStrength = 0.1;
   vec3 ambient = ambientStrength * lightColor;

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;

   float specularStrength = 0.5;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightColor;

   float distance = length(lightPos - FragPos);
   float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

   ambient *= attenuation;
   diffuse *= attenuation;
   specular *= attenuation;

   vec3 result = (ambient + diffuse + specular) * texture(texture_diffuse1, TexCoords).rgb;
   FragColor = vec4(result, 1.0);
}