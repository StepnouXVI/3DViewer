#version 410 core

out vec4 fragmentColor;
uniform vec4 FaceColor;

void main() { fragmentColor = FaceColor; }
