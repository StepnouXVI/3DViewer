#pragma once

#include <Services/SceneFileData.h>
#include <Services/SceneFileOBJReader.h>
#include <Views/Components/BaseComponents/InfoStackedWidget.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/MenuElements/EntityInfo.h>
#include <Views/Components/MenuElements/IMenu.h>

#include <QFileDialog>
#include <iostream>
#include <unordered_map>

class CreationMenu : public IMenu {
  Q_OBJECT

 private:
  QString imagesPath_ = ":/Views/resources/StandardModels/%1.png";
  QString standardModelImageObjectName_ = "standard_model_image";
  QString standardModelImageStyle_ =
      "background-image: url(%1); border-radius: 10;";
  QSize standardModelImageSize_ = QSize(100, 100);

  struct UiComponents {
    Button *prevModelButton;
    Button *nextModelButton;

    Button *prevStandardModelButton;
    Button *nextStandardModelButton;

    InfoStackedWidget *modelsStackedWidget;
    InfoStackedWidget *standardModelsStackedWidget;

    Title *modelBlockTitle = Builder::getTitle("Model", false);
    Title *standardModelBlockTitle = Builder::getTitle("Standard Pool", false);

    Button *loadModelButton = Builder::getButton("Load Model");
    Button *loadStandardModelButton = Builder::getButton("Set Model");
  };

  UiComponents ui;

  controllers::SceneControllerPtr scene_;
  controllers::SceneObjectControllerPtr model_;

 public:
  CreationMenu(controllers::SceneControllerPtr scene,
               controllers::SceneObjectControllerPtr model,
               QWidget *parent = nullptr)
      : IMenu(parent, "Create"), scene_(scene), model_(model) {
    initUI();
    setupConnections();
    lockUnimplementedComponents();
    composeUI();
  }

 private:
  void setupConnections() {
    connect(ui.loadModelButton, &Button::clicked, this,
            &CreationMenu::loadModel);
  }

  void lockUnimplementedComponents() {
    ui.prevModelButton->setEnabled(false);
    ui.nextModelButton->setEnabled(false);

    ui.prevStandardModelButton->setEnabled(false);
    ui.nextStandardModelButton->setEnabled(false);

    ui.standardModelsStackedWidget->setEnabled(false);

    ui.standardModelBlockTitle->setEnabled(false);

    ui.loadStandardModelButton->setEnabled(false);
  }

  void loadModel() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Open File", "/Users/yesenias/Downloads/obj",
        "Object Files (*.obj)");
    if (!filePath.isEmpty()) {
      model_->injectModel(scene_->loadModel(filePath.toStdString()));

      QFileInfo fileInfo(filePath);
      ModelInfo::getModelInfo()->addModel(
          {fileInfo.baseName(),
           QString::number(model_->getSceneObject()->getVertices().size()),
           QString::number(model_->getSceneObject()->getEdges().size())});
    }
  }

  void composeUI() {
    auto page =
        ConcreteCompositor::getPage({getModelBlock(), getStandardModelBlock()});
    this->setFixedHeight(page->height());
    page->fill(this);
  }

  void initUI() {
    initStackedWidget(ui.modelsStackedWidget, ModelInfo::getModelInfo().get(),
                      ui.prevModelButton, ui.nextModelButton);
    initStackedWidget(ui.standardModelsStackedWidget,
                      StandardModelInfo::getStandardModelInfo().get(),
                      ui.prevStandardModelButton, ui.nextStandardModelButton);
  }

  Composite *getModelBlock() {
    auto block = ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.modelBlockTitle}),
         ConcreteCompositor::getRow(
             {ui.prevModelButton, ui.modelsStackedWidget, ui.nextModelButton}),
         ConcreteCompositor::getRow({ui.loadModelButton}, 0, spacing_ * 4, 0,
                                    spacing_ * 4, 0)});

    return block;
  }

  Composite *getStandardModelBlock() {
    auto block = ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.standardModelBlockTitle}),
         ConcreteCompositor::getRow({ui.standardModelsStackedWidget}),
         ConcreteCompositor::getRow({ui.prevStandardModelButton,
                                     getStandardModelImagesStackedWidget(),
                                     ui.nextStandardModelButton}),
         ConcreteCompositor::getRow({ui.loadStandardModelButton}, 0,
                                    spacing_ * 4, 0, spacing_ * 4, 0)});

    return block;
  }

  Composite *getStandardModelImagesStackedWidget() {
    QVector<Component *> standardModelImages;

    for (const auto &it :
         StandardModelInfo::getStandardModelInfo().get()->getData()) {
      standardModelImages.append(getStandardModelImage(it[0]));
    }

    StackedWidget *images = Builder::getStackedWidget(
        standardModelImages, ui.prevStandardModelButton,
        ui.nextStandardModelButton);
    images->setFixedHeight(standardModelImageSize_.height());

    return images;
  }

  Component *getStandardModelImage(const QString &modelName) {
    Component *image = new Composite();

    image->setFixedSize(standardModelImageSize_);
    image->setObjectName(standardModelImageObjectName_);
    image->setStyleSheet(
        standardModelImageStyle_.arg(imagesPath_.arg(modelName)));

    return image;
  }
};
