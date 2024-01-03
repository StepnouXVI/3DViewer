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

  // AddOffsetVertexForEdge(p1, p2);
  // AddOffsetVertexForEdge(p2, p3);
  // AddOffsetVertexForEdge(p3, p1);

  EndPrimitive();
}

// void AddOffsetVertexForEdge(vec4 p1, vec4 p2) {
//   //получение вектора от первой виршины ко второй
//   vec2 dir = normalize((p2.xy / p2.w - p1.xy / p1.w) * ViewportInvSize);
//   //смешение перпендекулярное dir нужно для создания новых вершин
//   // умножение и деление регулирует масштаб смещения, что задаёт толщину
//   // итоговой линии.
//   vec2 offset = vec2(-dir.y, dir.x) * Thickness / ViewportInvSize;

//   // Создание дополнительных вершин

//   gl_Position = p1 + vec4(offset.xy * p1.w, 0.0, 0.0);
//   EmitVertex();
//   gl_Position = p1 - vec4(offset.xy * p1.w, 0.0, 0.0);
//   EmitVertex();
//   gl_Position = p2 + vec4(offset.xy * p2.w, 0.0, 0.0);
//   EmitVertex();
//   gl_Position = p2 - vec4(offset.xy * p2.w, 0.0, 0.0);
//   EmitVertex();
// }
