#pragma once

namespace dto {

struct Color {
  Color() : r(0.0), g(0.0), b(0.0), a(0.0){};
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a){};
  float r, g, b, a;
};

}  // namespace dto
