#pragma once

#include <Domain/Texture.h>

namespace Domain
{
struct TextureMaps
{
    TexturePtr Texture();
    TexturePtr NormalMap();
    TexturePtr HeightMap();
    TexturePtr AmbientOcclusionMap();
    TexturePtr DiffuseMap();
    TexturePtr SpecularMap();
};
using TextureMapsPtr = std::shared_ptr<TextureMaps>;
} // namespace Domain
