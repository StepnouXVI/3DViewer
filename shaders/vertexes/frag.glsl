#version 410 core
out vec4 FragColor;

uniform vec4 PointColor;
uniform bool RoundPoint;
uniform float PointSize;

void main() {

    float radius = PointSize / 2.0;

    vec2 coord = gl_PointCoord - vec2(0.5);

    coord *= PointSize;


    if ((dot(coord, coord) > radius * radius) && RoundPoint) {
        discard;
    } else {
        FragColor = PointColor;
    }
}
