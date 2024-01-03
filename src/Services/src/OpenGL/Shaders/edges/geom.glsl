#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 12) out;

uniform vec2 u_viewportInvSize;
uniform float u_thickness;

void AddOffsetVertexForEdge(vec4 p1, vec4 p2) {
  //получение вектора от первой виршины ко второй
  vec2 dir = normalize((p2.xy / p2.w - p1.xy / p1.w) * u_viewportInvSize);
  //смешение перпендекулярное dir нужно для создания новых вершин
  // умножение и деление регулирует масштаб смещения, что задаёт толщину
  // итоговой линии.
  vec2 offset = vec2(-dir.y, dir.x) * u_thickness / u_viewportInvSize;

  // Создание дополнительных вершин

  gl_Position = p1 + vec4(offset.xy * p1.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p1 - vec4(offset.xy * p1.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p2 + vec4(offset.xy * p2.w, 0.0, 0.0);
  EmitVertex();
  gl_Position = p2 - vec4(offset.xy * p2.w, 0.0, 0.0);
  EmitVertex();
}

void main() {
  vec4 p1 = gl_in[0].gl_Position;
  vec4 p2 = gl_in[1].gl_Position;
  vec4 p3 = gl_in[2].gl_Position;

  AddOffsetVertexForEdge(p1, p2);
  AddOffsetVertexForEdge(p2, p3);
  AddOffsetVertexForEdge(P3, p1);

  EndPrimitive();
}
