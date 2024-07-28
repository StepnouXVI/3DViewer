#pragma once
#include <QVector2D>
#include <QVector3D>


namespace Domain
{
struct Vertex
{
    QVector3D Point;
    QVector2D TexCoords;
    QVector3D Normal;
    QVector3D Tangent;
    QVector3D BiTangent;
};
} // namespace Domain