#pragma once
#include <QVector4D>

#include <utility>
#include <vector>

namespace Domain
{

enum class ProjectionType
{
    PARALLEL,
    CENTRAL,
};

enum class ObjectsDisplayType
{
    WIREFRAME,
    SOLID
};

enum class ShadersType
{
    NONE,
    FLAT,
    SOFT
};

enum class RayTracingMode
{
    OFF,
    ON
};

enum class EdgeDisplayType
{
    SOLID,
    DOTTED
};

enum class VertexDisplayType
{
    NONE,
    CIRCLE,
    SQUARE
};

enum class FloorDisplayType
{
    COLOR,
    IMAGE,
    ABSENT
};

enum class BackgroundDisplayType
{
    COLOR,
    IMAGE,
    ABSENT
};

enum class Lighting
{
    NONE,
    SIMPLE,
    DIRECTED,
    GLOBAL
};

struct EdgeSettings
{
    EdgeDisplayType Type;
    QVector4D Color;
    int PointSize;
};

struct VertexSettings
{
    VertexDisplayType Type;
    QVector4D Color;
    int PointSize;
};

struct FloorSettings
{
    QVector4D Color;
    FloorDisplayType DisplayType;
    bool ShowGrid;
};

struct SceneDisplaySettings
{
    QVector2D InvSizes;
    float AspectRatio;
    ProjectionType ProjectionType;
    ObjectsDisplayType ObjDisplayType;
    ShadersType Shader;
    RayTracingMode RayTracing;
    BackgroundDisplayType BackgroundDisplayType;
};

class SceneSettings
{
  private:
    SceneSettings();

  public:
    static SceneSettings &GetInstance();
    SceneSettings &operator=(const SceneSettings &) = delete;
    SceneSettings(const SceneSettings &) = delete;

    SceneDisplaySettings &GetDisplaySettings();
    FloorSettings &GetFloorSettings();
    VertexSettings &GetVertexSettings();
    EdgeSettings &GetEdgeSettings();

  private:
    SceneDisplaySettings displayType_;
    FloorSettings floorSettings_;
    VertexSettings vertexSettings_;
    EdgeSettings edgeSettings_;
};

} // namespace Domain
