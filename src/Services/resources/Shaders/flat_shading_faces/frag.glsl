#version 410 core
attribute highp vec3 u_position;
attribute vec3 u_normal;
attribute vec2 u_texCoords;
attribute vec3 u_tangent;
attribute vec3 u_bitangent;

#define PI 3.1415926538

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 FragColor;

struct Material {
  sampler2D Ambient;
  sampler2D Diffuse;
  sampler2D Specular;
  sampler2D Normal;

  float Shininess;
  float transparency;
  float Roughness;
  float Refraction;
  float Reflection;
};

struct DirLight {
  vec3 direction;

  vec3 Ambient;
  vec3 D;
  vec3 Specular;
};

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 Ambient;
  vec3 D;
  vec3 Specular;
};

struct SpotLight {
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;

  float constant;
  float linear;
  float quadratic;

  vec3 Ambient;
  vec3 D;
  vec3 Specular;
};

mat3 TBN;

uniform vec3 viewPos;
uniform DirLight dirLight[20];
uniform PointLight pointLight[20];
uniform SpotLight spotLight[20];
uniform Material material;
uniform int CountdirLight;
uniform int CountpointLight;
uniform int CountspotLight;
uniform samplerCube skybox;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 Normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 Normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 Normal, vec3 fragPos, vec3 viewDir);
float DistributionGGX(vec3 N, vec3 H, float roughness);

mat3 CalcTBNMatrix()

void main() {
  vec3 FragPos = vec3(model * vec4(u_position, 1.0));

  vec3 T = normalize(vec3(model * vec4(u_tangent, 0.0)));
  vec3 B = normalize(vec3(model * vec4(u_bitangent, 0.0)));
  vec3 N = normalize(vec3(model * vec4(normalize(u_normal), 0.0)));

  // properties
  vec3 norm = texture(material.Normal, u_texCoords).rgb;
  norm = normalize(norm * 2.0 - 1.0);

  T = normalize(T - dot(T, N) * N);
  TBN = transpose(mat3(T, B, N));

  vec3 viewDir = TBN * normalize(viewPos - FragPos);

  vec3 result = vec3(0.0);
  result += CalcDirLights(norm, viewDir);
  result += CalcPointLights(norm, FragPos, viewDir);
  result += CalcSpotLights(norm, FragPos, viewDir);


  vec3 I1 = normalize(FragPos - viewPos);
  vec3 R1 = reflect(I1, norm);
  result = mix(result, vec3(texture(skybox, R1).rgb), material.Reflection);

  // скорее всего просто присвой material.Refraction
  float ratio = 1.00 / 1.52;
  vec3 I2 = normalize(FragPos - viewPos);
  vec3 R2 = refract(I2, norm, ratio);
  result = mix(result, vec3(texture(skybox, R2).rgb), material.Refraction);

  FragColor = vec4(result, material.transparency);

  gl_Position = projection * view * vec4(FragPos, 1.0);
}

vec3 CalcDirLights(vec3 normal, vec3 viewDir) {
  vec3 result = vec3(0.0);
  for (int i = 0; i < CountdirLight; i++) {
    result += CalcDirLight(dirLight[i], normal, viewDir);
  }
  return result;
}

vec3 CalcDirLight(DirLight light, vec3 Normal, vec3 viewDir) {
  vec3 lightDir = TBN * normalize(-light.direction);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  // D shading
  float diff = max(dot(Normal, lightDir), 0.0);
  // Specular shading
  vec3 reflectDir = reflect(-lightDir, Normal);
  float spec = pow(max(dot(Normal, halfwayDir), 0.0), material.Shininess);
  // combine results
  vec3 Ambient = light.Ambient * vec3(texture(material.Ambient, u_texCoords));
  vec3 D = light.D * diff * vec3(texture(material.D, u_texCoords));
  vec3 Specular = DistributionGGX(Normal, halfwayDir, material.Roughness) *
                  light.Specular * spec *
                  vec3(texture(material.Specular, u_texCoords));
  return (Ambient + D + Specular);
}

vec3 CalcPointLights(vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 result = vec3(0.0);
  for (int i = 0; i < CountpointLight; i++) {
    result += CalcPointLight(pointLight[i], norm, FragPos, viewDir);
  }
  return result;
}

vec3 CalcPointLight(PointLight light, vec3 Normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = TBN * normalize(light.position - fragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  // D shading
  float diff = max(dot(Normal, lightDir), 0.0);
  // Specular shading
  vec3 reflectDir = reflect(-lightDir, Normal);
  float spec = pow(max(dot(Normal, halfwayDir), 0.0), material.Shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  // combine results
  vec3 Ambient = light.Ambient * vec3(texture(material.Ambient, u_texCoords));
  vec3 D = light.D * diff * vec3(texture(material.D, u_texCoords));
  vec3 Specular = DistributionGGX(Normal, halfwayDir, material.Roughness) *
                  light.Specular * spec *
                  vec3(texture(material.Specular, u_texCoords));
  Ambient *= attenuation;
  D *= attenuation;
  Specular *= attenuation;
  return (Ambient + D + Specular);
}


vec3 CalcSpotLights(vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 result = vec3(0.0);
  for (int i = 0; i < CountpointLight; i++) {
    result += CalcSpotLight(pointLight[i], norm, FragPos, viewDir);
  }
  return result;
}


vec3 CalcSpotLight(SpotLight light, vec3 Normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = TBN * normalize(light.position - fragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  // D shading
  float diff = max(dot(Normal, lightDir), 0.0);
  // Specular shading
  vec3 reflectDir = reflect(-lightDir, Normal);
  float spec = pow(max(dot(Normal, halfwayDir), 0.0), material.Shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  // spotlight intensity
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
  // combine results
  vec3 Ambient = light.Ambient * vec3(texture(material.Ambient, u_texCoords));
  vec3 D = light.D * diff * vec3(texture(material.D, u_texCoords));
  vec3 Specular = DistributionGGX(Normal, halfwayDir, material.Roughness) *
                  light.Specular * spec *
                  vec3(texture(material.Specular, u_texCoords));
  Ambient *= attenuation * intensity;
  D *= attenuation * intensity;
  Specular *= attenuation * intensity;
  return (Ambient + D + Specular);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
  float roughness_quad = roughness * roughness;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH * NdotH;

  float nom = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return nom / denom;
}
