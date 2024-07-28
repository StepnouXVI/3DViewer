#include <Domain/Texture.h>

Domain::Texture::Texture() : Data(QOpenGLTexture::Target2D)
{
    Data.create();
    Data.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::MirroredRepeat);
    Data.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::MirroredRepeat);
    Data.setMinMagFilters(QOpenGLTexture::LinearMipMapNearest, QOpenGLTexture::Nearest);
}