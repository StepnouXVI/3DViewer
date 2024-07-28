#pragma once

#include <QOpenGLTexture>

namespace Domain
{
struct Texture
{
    QOpenGLTexture Data;
    QString Path;
    Texture();
};
using TexturePtr = std::shared_ptr<Texture>;
} // namespace Domain
