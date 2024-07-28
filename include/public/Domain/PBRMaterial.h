#pragma once
#include <QVector3D>

namespace Domain
{
enum class IlluminationModel : unsigned int
{
    ColorOnAndAmbientOff = 0,
    ColorOnAndAmbientOn = 1,
    HighlightOn = 2,
    ReflectionOnAndRayTraceOn = 3,
    TransparencyGlassOn = 4,
    ReflectionRayTraceOn = 5,
    TransparencyRefractionOnRayTraceOn = 6,
    TransparencyRefractionOnRayTraceOnFresnelOn = 7,
    TransparencyRefractionOnRayTraceOff = 8,
    ReflectionRayTraceOff = 9,
    CastShadowsOnInvisibleSurfaces = 10
};

struct PBRMaterial
{
    QVector3D AmbientColor;
    QVector3D DiffuseColor;
    QVector3D SpecularColor;
    QVector3D EmissionColor;
    float IOR;
    float Shininess;
    float Opacity;
    IlluminationModel IlluminationModel;
};

using PBRMaterialPtr = std::shared_ptr<PBRMaterial>;
} // namespace Domain
