#version 410 core
layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

flat out vec3 startPos;
out vec3 vertPos;

void main() {
  vec4 pos = projection * view * model * vec4(position, 1.0);
  gl_Position = pos;
  vertPos = pos.xyz / pos.w;
  startPos = vertPos;
}
