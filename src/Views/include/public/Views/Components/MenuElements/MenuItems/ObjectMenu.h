#pragma once

#include <Views/Components/BaseComponents/InfoStackedWidget.h>
#include <Views/Components/Builder/Builder.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/MenuElements/EntityInfo.h>
#include <Views/Components/MenuElements/IMenu.h>

class ObjectMenu : public IMenu {
 private:
  struct UiComponents {
    InfoStackedWidget *modelsStackedWidget;
    InfoStackedWidget *objectsStackedWidget;

    Button *prevModelButton;
    Button *nextModelButton;

    Button *prevObjectButton;
    Button *nextObjectButton;

    Title *activeModelBlockTitle = Builder::getTitle("Active Model", false);
    Title *activeObjectBlockTitle = Builder::getTitle("Active Object", false);
    Title *textureBlockTitle = Builder::getTitle("Texture", true);
    Title *visualPropertiesBlockTitle =
        Builder::getTitle("Visual Properties", true);

    Label *textureLabel = Builder::getLabel("Texture");
    Label *transparencyLabel = Builder::getLabel("Transparency");
    Label *refractionLabel = Builder::getLabel("Refraction");
    Label *reflectionLabel = Builder::getLabel("Reflection");
    Label *surfaceLabel = Builder::getLabel("Surface");
    Label *edgePropertiesLabel = Builder::getLabel("Edge properties");

    Button *loadTextureButton = Builder::getButton("Load texture");
    Button *removeTextureButton = Builder::getButton("Remove texture");

    SwitchMenu *textureStatusSwitchMenu = Builder::getSwitchMenu({"off", "on"});
    SwitchMenu *edgePropertiesSwitchMenu =
        Builder::getSwitchMenu({"off", "on"});

    TextBox *transparencyTextBox = Builder::getTextBox("");
    TextBox *refractionTextBox = Builder::getTextBox("");
    TextBox *reflectionTextBox = Builder::getTextBox("");
    TextBox *surfaceTextBox = Builder::getTextBox("");
  };

  UiComponents ui;

  controllers::SceneObjectControllerPtr model_;
  controllers::SceneObjectControllerPtr object_;

 public:
  ObjectMenu(controllers::SceneObjectControllerPtr model,
             controllers::SceneObjectControllerPtr object,
             QWidget *parent = nullptr)
      : IMenu(parent, "Object"), model_(model), object_(object) {
    initUI();
    setupConnections();
    lockUnimplementedComponents();
    composeUI();
  }

  void lockUnimplementedComponents() {
    ui.activeObjectBlockTitle->setEnabled(false);
    ui.textureBlockTitle->setEnabled(false);
    ui.visualPropertiesBlockTitle->setEnabled(false);

    ui.textureLabel->setEnabled(false);
    ui.transparencyLabel->setEnabled(false);
    ui.refractionLabel->setEnabled(false);
    ui.reflectionLabel->setEnabled(false);
    ui.surfaceLabel->setEnabled(false);
    ui.edgePropertiesLabel->setEnabled(false);

    ui.loadTextureButton->setEnabled(false);
    ui.removeTextureButton->setEnabled(false);

    ui.textureStatusSwitchMenu->setEnabled(false);
    ui.edgePropertiesSwitchMenu->setEnabled(false);

    ui.transparencyTextBox->setEnabled(false);
    ui.refractionTextBox->setEnabled(false);
    ui.reflectionTextBox->setEnabled(false);
    ui.surfaceTextBox->setEnabled(false);

    ui.objectsStackedWidget->setEnabled(false);
    ui.prevModelButton->setEnabled(false);
    ui.nextModelButton->setEnabled(false);
    ui.prevObjectButton->setEnabled(false);
    ui.nextObjectButton->setEnabled(false);
  }

  void setupConnections() {
    connect(
        ui.modelsStackedWidget, &InfoStackedWidget::pageChanged, this,
        [this](int activeModel) { model_->setActiveChildIdx(activeModel); });

    connect(
        ui.objectsStackedWidget, &InfoStackedWidget::pageChanged, this,
        [this](int activeObject) { object_->setActiveChildIdx(activeObject); });
  }

  void initUI() {
    initStackedWidget(ui.modelsStackedWidget, ModelInfo::getModelInfo().get(),
                      ui.prevModelButton, ui.nextModelButton);
    initStackedWidget(ui.objectsStackedWidget,
                      ObjectInfo::getObjectInfo().get(), ui.prevObjectButton,
                      ui.nextObjectButton);
  }

  void composeUI() {
    auto objectMenuPage = ConcreteCompositor::getPage(
        {getActiveModelBlock(), getActiveObjectBlock(), getTextureBlock(),
         getVisualPropertiesBlock()},
        spacing_ * 2, spacing_ * 2, spacing_, spacing_ * 2, spacing_ * 2);

    this->setFixedHeight(objectMenuPage->height());
    objectMenuPage->fill(this);
  }

  Composite *getActiveModelBlock() {
    return ConcreteCompositor::getBlock({
        ConcreteCompositor::getRow({ui.activeModelBlockTitle}),
        ConcreteCompositor::getRow(
            {ui.prevModelButton, ui.modelsStackedWidget, ui.nextModelButton}),
    });
  }

  Composite *getActiveObjectBlock() {
    return ConcreteCompositor::getBlock({
        ConcreteCompositor::getRow({ui.activeObjectBlockTitle}),
        ConcreteCompositor::getRow({ui.prevObjectButton,
                                    ui.objectsStackedWidget,
                                    ui.nextObjectButton}),
    });
  }

  Composite *getTextureBlock() {
    return ConcreteCompositor::getBlock({
        ConcreteCompositor::getRow({ui.textureBlockTitle}),
        ConcreteCompositor::getRow(
            {ui.textureLabel, ui.textureStatusSwitchMenu}),
        ConcreteCompositor::getRow(
            {ui.loadTextureButton, ui.removeTextureButton}),
    });
  }

  Composite *getVisualPropertiesBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.visualPropertiesBlockTitle}),
         ConcreteCompositor::getRow(
             {ui.transparencyLabel, ui.transparencyTextBox}),
         ConcreteCompositor::getRow({ui.refractionLabel, ui.refractionTextBox}),
         ConcreteCompositor::getRow({ui.reflectionLabel, ui.reflectionTextBox}),
         ConcreteCompositor::getRow({ui.surfaceLabel, ui.surfaceTextBox}),
         ConcreteCompositor::getRow(
             {ui.edgePropertiesLabel, ui.edgePropertiesSwitchMenu})},
        spacing_ / 2);
  }
};
