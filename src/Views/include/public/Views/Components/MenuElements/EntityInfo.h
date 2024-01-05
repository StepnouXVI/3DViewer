#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>

class EntityInfo : public QObject {
  Q_OBJECT
 private:
  QVector<QString> titles_;
  QVector<QVector<QString>> data_;
  int titlesSize;

 public:
  EntityInfo(const QVector<QString> &titles)
      : QObject(nullptr), titles_(titles) {
    titlesSize = titles.size();
  }

  void addModel(const QVector<QString> &data) {
    if (titlesSize != data.size()) {
      throw std::runtime_error("Data size is not equal to EntityInfo size.");
    }
    data_.push_back(data);
    emit dataAdded(data);
  }

  QVector<QString> &getTitles() { return titles_; }

  QVector<QVector<QString>> &getData() { return data_; }

 signals:
  void dataAdded(const QVector<QString> &data);
};

class ModelInfo : public EntityInfo {
 public:
  static std::shared_ptr<ModelInfo> getModelInfo() {
    if (!modelInfo) {
      modelInfo = std::shared_ptr<ModelInfo>(new ModelInfo());
    }
    return modelInfo;
  }

 private:
  ModelInfo()
      : EntityInfo({"File name", "Count of edges", "Count of vertexes"}) {}
  static std::shared_ptr<ModelInfo> modelInfo;
};

class ObjectInfo : public EntityInfo {
 public:
  static std::shared_ptr<ObjectInfo> getObjectInfo() {
    if (!objectInfo) {
      objectInfo = std::shared_ptr<ObjectInfo>(new ObjectInfo());
    }
    return objectInfo;
  }

 private:
  ObjectInfo()
      : EntityInfo({"Object name", "Count of edges", "Count of vertexes"}) {}
  static std::shared_ptr<ObjectInfo> objectInfo;
};

class StandardModelInfo : public EntityInfo {
 public:
  static std::shared_ptr<StandardModelInfo> getStandardModelInfo() {
    if (!standardModelInfo) {
      standardModelInfo =
          std::shared_ptr<StandardModelInfo>(new StandardModelInfo());
    }
    return standardModelInfo;
  }

 private:
  QVector<QString> standardModels_ = {"Sphere", "Cylinder", "Cone", "Cube",
                                      "Pyramid"};

  StandardModelInfo() : EntityInfo({"Model name"}) {
    for (const auto &it : standardModels_) {
      addModel({it});
    }
  }

  static std::shared_ptr<StandardModelInfo> standardModelInfo;
};
