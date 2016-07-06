#version 410 core

in vec2 fTexCoord;
in vec3 fNormal;
in vec3 fFragPos;

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

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform sampler2D tex;

out vec4 color;

void main()
{
  vec3 ambient = light.ambient * material.ambient;

  vec3 norm = normalize(fNormal);
  vec3 lightDir = normalize(light.position - fFragPos);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * diff * material.diffuse;

  vec3 viewDir = normalize(viewPos - fFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * material.specular;

  color = texture(tex, fTexCoord) * vec4(ambient + diffuse, 1.0f) + vec4(specular, 1.0f);
}
