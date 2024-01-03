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

mat3 CalcTBNMatrix()

    void main() {
  vec3 FragPos = vec3(model * vec4(u_position, 1.0));

  vec3 T = normalize(vec3(model * vec4(u_tangent, 0.0)));
  vec3 B = normalize(vec3(model * vec4(u_bitangent, 0.0)));
  vec3 N = normalize(vec3(model * vec4(normalize(u_normal), 0.0)));

  // properties
}

float CookTorranceBRDF(vec3 normal, vec3 ray, vec3 view, float roughness,
                       float albedo) {
  float lambert = albedo / PI;
}

// @links https://habr.com/ru/articles/426123/
float TrowbridgeReitzGGX_normalDeestribution(vec3 normal, vec3 median,
                                             float roughness) {
  float roughness_2 = roughness * roughness;

  float NdotH = max(dot(N, H), 0.0);
  float NdotH_2 = NdotH * NdotH;

  float denom = (NdotH_2 * (roughness_2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return roughness_2 / denom;
}

float SmithGGX_geometry(vec3 normal, vec3 V, vec3 L, float k) {
  float normalDotView = max(dot(normal, V), 0.0);
  float NdotL = max(dot(normal, L), 0.0);
  float ggx1 = GeometrySchlickGGX(normalDotView, k);
  float ggx2 = GeometrySchlickGGX(NdotL, k);

  return ggx1 * ggx2;
}

float SchlickGGX_geometry(float normalDotView, float k) {
  float nom = normalDotView;
  float denom = normalDotView * (1.0 - k) + k;

  return nom / denom;
}

float FresnelSchlicApproximation(vec3 median, vec3 view, float F0)
{


}
