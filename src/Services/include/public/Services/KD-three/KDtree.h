#include <vector>

namespace services::kd_tree {

struct BoundingBox3D {
  float xMin, yMin, zMin;
  float xMax, yMax, zMax;
};

struct KDNode {
  std::vector<int> objects;
  BoundingBox3D boundingBox;
  int leftChild;
  int rightChild;
};

enum class Axis { X, Y, Z };

struct Object3D {
  BoundingBox3D boundingBox;
};

class KDtree {
 public:
  KDtree(const std::vector<Object3D> &objects, BoundingBox3D &scene);
  bool Build();

 private:
  static const int NUMBER_OF_PARTS = 33;
  static constexpr float CL = 1.5f, CT = 1;

  std::vector<Object3D> objects;
  std::vector<KDNode> nodes;

  float getMinForAxis(const BoundingBox3D &box, Axis axis);

  float getMaxForAxis(const BoundingBox3D &box, Axis axis);

  void fillArrays(int *lowArray, int *highArray, KDNode &parentNode, Axis axis);

  void createPrefixArrays(int *lowArray, int *highArray, KDNode &parentNode,
                          Axis axis);

  float SAH(int leftAmount, float leftSquare, int rightAmount,
            float rightSquare, int square);

  float getValueForSplit(KDNode &parentNode, Axis axis, float &out_SAH,
                         int &out_LeftAmount, int &out_RightAmount);

  bool SplitNode(KDNode &node, Axis axis);

  void fillChildren(const KDNode &parent, std::vector<int> newParentObjs,
                    KDNode &left, KDNode &right, float value, Axis axis);

  void build(KDNode &node, Axis axis);
};

}  // namespace services::kd_tree