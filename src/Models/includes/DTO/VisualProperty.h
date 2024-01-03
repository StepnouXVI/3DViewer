#pragma once
#include <DTO/Texture.h>

namespace dto {

struct VisualProperty {
  float transparency;
  float refraction;
  float reflection;
  float surface;
  Texture texture;
};
}  // namespace dto