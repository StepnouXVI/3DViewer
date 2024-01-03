#version 410 core

out vec4 fragmentColor;
uniform vec4 faceColor;

void main() { fragmentColor = faceColor; }
