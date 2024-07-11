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