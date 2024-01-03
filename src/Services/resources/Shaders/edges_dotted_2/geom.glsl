#version 410

layout(lines) in;
layout(line_strip, max_vertices = 2) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


uniform mat4 pvmMatrix;
uniform mat4 model;
uniform mat4 view;


out vec3 vPosition;  // passed to the fragment shader for plane clipping
out float texCoord;  // passed to the fragment shader for stipple pattern

void main(void)
{
    // to achieve uniform pattern density whatever the line orientation
    // the upper texture coordinate is made proportional to the line's length
    vec3 pos0 = gl_in[0].gl_Position.xyz;
    vec3 pos1 = gl_in[1].gl_Position.xyz;
    float max_u_texture = length(pos1 - pos0);

    // Line Start
    gl_Position = pvmMatrix * (gl_in[0].gl_Position);
    texCoord = 0.0;
    // depth position for clip plane
    vec4 vsPos0 = view * model * gl_Position;
    vPosition = vsPos0.xyz / vsPos0.w;
    EmitVertex();  // one down, one to go

    // Line End
    gl_Position = pvmMatrix * (gl_in[1].gl_Position);
    texCoord = max_u_texture;
    // depth position for clip plane
    vec4 vsPos1 = view * model * gl_Position;
    vPosition = vsPos0.xyz / vsPos0.w;
    EmitVertex();

    // done
    EndPrimitive();
}
