#pragma once
#include <QString>

const QString EdgeFragShader = R"(
#version 410 core

out vec4 FragColor;

uniform vec4 PointColor;

void main(void) {
      FragColor = PointColor;
}
)";

const QString EdgeVertShader = R"(
#version 410 core
attribute highp vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void) {
  gl_Position = projection * view * model * vec4(position, 1.0);
}
)";

const QString EdgeGeomShader = R"(
#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 12) out;

uniform vec2 ViewportInvSize;
uniform float Thickness;

void AddOffsetVertexForEdge(vec4 p1, vec4 p2);

void main() {
  vec4 p1 = gl_in[0].gl_Position;
  vec4 p2 = gl_in[1].gl_Position;
  vec4 p3 = gl_in[2].gl_Position;

  vec2 dir = normalize((p2.xy / p2.w - p1.xy / p1.w) * ViewportInvSize);
  vec2 offset = vec2(-dir.y, dir.x) * Thickness / ViewportInvSize;

  gl_Position = p1 + vec4(offset.xy * p1.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p1 - vec4(offset.xy * p1.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p2 + vec4(offset.xy * p2.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p2 - vec4(offset.xy * p2.w, 0.0, 0.0);
  EmitVertex();

  dir = normalize((p3.xy / p3.w - p2.xy / p2.w) * ViewportInvSize);
  offset = vec2(-dir.y, dir.x) * Thickness / ViewportInvSize;

  gl_Position = p2 + vec4(offset.xy * p2.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p2 - vec4(offset.xy * p2.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p3 + vec4(offset.xy * p3.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p3 - vec4(offset.xy * p3.w, 0.0, 0.0);
  EmitVertex();

  dir = normalize((p1.xy / p1.w - p3.xy / p3.w) * ViewportInvSize);
  offset = vec2(-dir.y, dir.x) * Thickness / ViewportInvSize;

  gl_Position = p1 + vec4(offset.xy * p1.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p1 - vec4(offset.xy * p1.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p3 + vec4(offset.xy * p3.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p3 - vec4(offset.xy * p3.w, 0.0, 0.0);
  EmitVertex();

  EndPrimitive();
}
)";

const QString FaceFragShader = R"(
#version 410 core

out vec4 fragmentColor;
uniform vec4 FaceColor;

void main() { fragmentColor = FaceColor; }

)";

const QString FaceVertShader = R"(
#version 410 core

attribute highp vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0);
}
)";

const QString EdgesDottedFragShader = R"(
#version 330

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
)";

const QString EdgesDottedVertShader = R"(
#version 410

flat out vec3 startPos;
out vec3 vertPos;

attribute highp vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{
    vec4 pos    = projection * view * model * vec4(position, 1.0);
    gl_Position = pos;
    vertPos     = pos.xyz / pos.w;
    startPos    = vertPos;
}
)";

const QString EdgesDottedFragShader2 = R"()";
const QString EdgesDottedVertShader2 = R"()";
const QString EdgesDottedGeomShader2 = R"()";

const QString FaceWithTextureFragShader = R"(
#version 410 core

in vec2 texCoord;

out vec4 fragmentColor;

uniform sampler2D texture;

void main() { fragmentColor = texture2D(texture, texCoord); }

)";
const QString FaceWithTextureVertShader = R"(
#version 410 core

attribute highp vec3 position;
attribute highp vec2 vertexTexCoord;

out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0);

  texCoord = vertexTexCoord;
}

)";

const QString SkyBoxFragShader = R"(
#version 410 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
    FragColor = texture(skybox, TexCoords);
}


)";
const QString SkyBoxVertShader = R"(
#version 410 core
attribute highp vec3 position;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoords = position;
    vec4 pos = projection * view * vec4(position, 1.0);
    gl_Position = pos.xyww;
}

)";

const QString VertexFragShader = R"(
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
)";

const QString VertexVertShader = R"(
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

)";

const QString VertexGeomShader = R"(
#version 410 core
layout (points) in;
layout (triangle_strip, max_vertices = 36) out;

uniform bool RoundPoint;
uniform float PointSize;

void main() {
    // Исходная вершина
    vec4 position = gl_in[0].gl_Position;

    if (RoundPoint) {
        // Отрисовка сферы
        const int segments = 10;
        const int rings = 10;

        for (int ring = 0; ring <= rings; ++ring) {
            float phi = float(ring) * 3.14159265359 / float(rings);
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            for (int segment = 0; segment <= segments; ++segment) {
                float theta = float(segment) * 2.0 * 3.14159265359 / float(segments);
                float sinTheta = sin(theta);
                float cosTheta = cos(theta);

                vec4 vertex = position + vec4(PointSize * sinPhi * cosTheta, PointSize * sinPhi * sinTheta, PointSize * cosPhi, 0.0);
                gl_Position = vertex;
                EmitVertex();
            }
            EndPrimitive();
        }
    } else {
        // Отрисовка куба
        vec4 vertices[8] = vec4[](
            vec4(-0.5 * PointSize, -0.5 * PointSize, -0.5 * PointSize, 1.0),
            vec4(-0.5 * PointSize, -0.5 * PointSize, 0.5 * PointSize, 1.0),
            vec4(-0.5 * PointSize, 0.5 * PointSize, -0.5 * PointSize, 1.0),
            vec4(-0.5 * PointSize, 0.5 * PointSize, 0.5 * PointSize, 1.0),
            vec4(0.5 * PointSize, -0.5 * PointSize, -0.5 * PointSize, 1.0),
            vec4(0.5 * PointSize, -0.5 * PointSize, 0.5 * PointSize, 1.0),
            vec4(0.5 * PointSize, 0.5 * PointSize, -0.5 * PointSize, 1.0),
            vec4(0.5 * PointSize, 0.5 * PointSize, 0.5 * PointSize, 1.0)
        );

        int indices[36] = int[](
            0, 1, 2, 1, 3, 2,
            0, 4, 1, 4, 5, 1,
            0, 2, 4, 2, 6, 4,
            7, 4, 6, 7, 5, 4,
            7, 6, 3, 6, 2, 3,
            7, 3, 5, 3, 1, 5
        );

        for (int i = 0; i < 36; ++i) {
            gl_Position = position + vertices[indices[i]];
            EmitVertex();
        }
        EndPrimitive();
    }
}

)";
