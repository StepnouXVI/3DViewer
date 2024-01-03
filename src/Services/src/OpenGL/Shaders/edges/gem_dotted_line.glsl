#version 410 core

layout (lines) in;
layout (line_strip, max_vertices = 4) out;

uniform mat4 projection;
uniform mat4 modelview;
uniform vec2 linePattern;
uniform float pointFrequency;
uniform float pointSize;

void drawDottedLine()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    float distance = length(gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy);
    float numPoints = distance * pointFrequency;
    float stepSize = 1.0 / numPoints;

    for (float t = 0.0; t <= 1.0; t += stepSize) {
        gl_Position = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, t);
        EmitVertex();
    }

    gl_Position = vec4(gl_in[1].gl_Position.xy + linePattern * (gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy), 0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(gl_in[0].gl_Position.xy + linePattern * (gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy), 0.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void main()
{
    gl_Position = projection * modelview * gl_in[0].gl_Position;
    gl_PointSize = pointSize;
    drawDottedLine();
}
