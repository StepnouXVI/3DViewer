#version 410 core

in vec2 Center;
out vec4 FragColor;

uniform vec4 PointColor;
uniform bool RoundPoint;
uniform float PointSize;


void main() {
  if ((dot(gl_PointCoord - 0.5, gl_PointCoord - 0.5) > 0.25) && RoundPoint) {
      discard;
  } else {
      FragColor =  PointColor;
  }
}
