#version 410

flat in vec3 startPos;
in vec3 vertPos;

out vec4 fragColor;

uniform vec2  Resolution;
uniform float DashSize;
uniform float GapSize;
uniform vec4 PointColor;

void main()
{
    vec2  dir  = (vertPos.xy-startPos.xy) * Resolution/2.0;
    float dist = length(dir);

    if (fract(dist / (DashSize + GapSize)) > DashSize/(DashSize + GapSize))
        discard;
    fragColor = PointColor;
}