#version 410 core

in vec2 texCoord;

out vec4 fragmentColor;

uniform sampler2D texture;

void main() { fragmentColor = texture2D(texture, texCoord); }
