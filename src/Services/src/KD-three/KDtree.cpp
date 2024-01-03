#include "Services/KD-three/KDtree.h"

#include <limits>
#include <numeric>

namespace services::kd_tree {

float KDtree::getMinForAxis(const BoundingBox3D &box, Axis axis) {
  switch (axis) {
    case Axis::X:
      return box.xMin;
    case Axis::Y:
      return box.yMin;
    case Axis::Z:
      return box.zMin;
  }
  return 0;
}

float KDtree::getMaxForAxis(const BoundingBox3D &box, Axis axis) {
  switch (axis) {
    case Axis::X:
      return box.xMax;
    case Axis::Y:
      return box.yMax;
    case Axis::Z:
      return box.zMax;
  }
  return 0;
}

void KDtree::fillArrays(int *lowArray, int *highArray, KDNode &parentNode,
                        Axis axis) {
  float min = getMinForAxis(parentNode.boundingBox, axis),
        max = getMaxForAxis(parentNode.boundingBox, axis);
  float step = (max - min) / (float)NUMBER_OF_PARTS;

  for (auto ind_obj : parentNode.objects) {
    float obj_min = getMinForAxis(objects[ind_obj].boundingBox, axis);
    float obj_max = getMaxForAxis(objects[ind_obj].boundingBox, axis);
    int find_low = 0, find_high = 0, i = 0;

    while (!(find_high && find_low)) {
      if (obj_min < min + i * step && obj_min < min + (i + 1) * step) {
        find_low = 1;
        lowArray[i] += 1;
      }
      if (obj_max > max - i * step && obj_max > max - (i + 1) * step) {
        find_high = 1;
        highArray[i] += 1;
      }
      i++;
    }
  }
}

void KDtree::createPrefixArrays(int *lowArray, int *highArray,
                                KDNode &parentNode, Axis axis) {
  fillArrays(lowArray, highArray, parentNode, axis);

  for (int i = 0; i < NUMBER_OF_PARTS - 1; i++) {
    lowArray[i + 1] = lowArray[i + 1] + lowArray[i];
    highArray[NUMBER_OF_PARTS - i - 2] =
        highArray[NUMBER_OF_PARTS - i - 2] + highArray[NUMBER_OF_PARTS - i - 1];
  }
}

float KDtree::SAH(int leftAmount, float leftSquare, int rightAmount,
                  float rightSquare, int square) {
  return CT + CL *
                  (float)(leftAmount * leftSquare + rightAmount * rightSquare) /
                  (float)square;
}

float KDtree::getValueForSplit(KDNode &parentNode, Axis axis, float &out_SAH,
                               int &out_LeftAmount, int &out_RightAmount) {
  int lowArray[NUMBER_OF_PARTS] = {0}, highArray[NUMBER_OF_PARTS] = {0};
  createPrefixArrays(lowArray, highArray, parentNode, axis);

  int i_min = 0;
  float min_sah = std::numeric_limits<float>::max();

  for (int i = 0; i < NUMBER_OF_PARTS - 1; i++) {
    float value = SAH(highArray[i], i + 1, lowArray[i + 1],
                      NUMBER_OF_PARTS - i - 1, NUMBER_OF_PARTS);

    if (value < min_sah) {
      min_sah = value;
      i_min = i;
    }
  }

  out_SAH = min_sah;
  out_LeftAmount = highArray[i_min];
  out_RightAmount = lowArray[i_min + 1];

  // min + step * i_min
  return getMinForAxis(parentNode.boundingBox, axis) +
         (getMaxForAxis(parentNode.boundingBox, axis) -
          getMinForAxis(parentNode.boundingBox, axis)) *
             (float)i_min;
}

KDtree::KDtree(const std::vector<Object3D> &objects, BoundingBox3D &scene) {
  this->objects = objects;
  KDNode firstNode;
  std::iota(firstNode.objects.begin(), firstNode.objects.end(), 0);
  firstNode.leftChild = 0;
  firstNode.rightChild = 0;
  firstNode.boundingBox = scene;

  nodes.push_back(firstNode);
}

bool KDtree::SplitNode(KDNode &node, Axis axis) {
  float min_SAH_for_split = std::numeric_limits<float>::max();
  int leftChildrenAmount, rightChildrenAmount;

  float valueForSplit = getValueForSplit(
      node, axis, min_SAH_for_split, leftChildrenAmount, rightChildrenAmount);

  if (min_SAH_for_split > node.objects.size() * CL) {
    return false;
  }

  KDNode leftNode, rightNode;

  leftNode.objects.reserve(leftChildrenAmount);
  rightNode.objects.reserve(rightChildrenAmount);
  std::vector<int> newParentVector(node.objects.size() - leftChildrenAmount -
                                   rightChildrenAmount);

  fillChildren(node, newParentVector, leftNode, rightNode, valueForSplit, axis);
  node.objects = std::move(newParentVector);

  nodes.push_back(leftNode);
  nodes.push_back(rightNode);

  node.leftChild = nodes.size() - 2;
  node.rightChild = nodes.size() - 1;

  return true;
}

void KDtree::fillChildren(const KDNode &parent, std::vector<int> newParentObjs,
                          KDNode &left, KDNode &right, float value, Axis axis) {
  for (int index : parent.objects) {
    float obj_min = getMinForAxis(objects[index].boundingBox, axis);
    float obj_max = getMaxForAxis(objects[index].boundingBox, axis);

    if (obj_min < value && obj_max < value) {
      left.objects.push_back(index);
    } else if (obj_min > value && obj_max > value) {
      right.objects.push_back(index);
    } else {
      newParentObjs.push_back(index);
    }
  }
}

void KDtree::build(KDNode &node, Axis axis) {
  axis = (Axis)(((int)axis + 1) % 3);
  bool res = SplitNode(node, axis);
  if (res) {
    build(nodes[node.leftChild], axis);
    build(nodes[node.rightChild], axis);
  }
}

bool KDtree::Build() {
  if (objects.size() > 0) {
    build(nodes[0], Axis::X);
    return true;
  }

  return false;
}
}  // namespace services::kd_tree