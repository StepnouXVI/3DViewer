#version 410 core
attribute highp vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float PointSize;
uniform bool RoundPoint;

out vec2 Center;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0);
  gl_PointSize = PointSize;

}
