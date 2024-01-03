#version 410 core

out vec4 FragColor;

uniform vec4 PointColor;
uniform vec2 Resolution;
uniform float DashSize;
uniform float GapSize;

void main(void) { FragColor = PointColor; }

#version 330

flat in vec3 startPos;
in vec3 vertPos;

out vec4 fragColor;

void main() {
  vec2 dir = (vertPos.xy - startPos.xy) * Resolution / 2.0;
  float dist = length(dir);

  if (fract(dist / (DashSize + GapSize)) > DashSize / (DashSize + GapSize))
    discard;
  fragColor = vec4(1.0);
}
