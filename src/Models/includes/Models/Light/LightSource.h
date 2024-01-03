#include <DTO/Color.h>
#include <DTO/Point3D.h>

namespace models {

class LightSource {
 public:
  dto::Color color;
  dto::Point3D position;
  float intensity;
};

}  // namespace models