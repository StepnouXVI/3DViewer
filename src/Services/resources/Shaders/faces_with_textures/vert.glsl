#version 410 core

attribute highp vec3 position;
attribute highp vec2 vertexTexCoord;

out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0);

  texCoord = vertexTexCoord;
}
