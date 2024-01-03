#pragma once

#include <Views/Components/BaseComponents/InfoStackedWidget.h>
#include <Views/Components/Builder/Builder.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/MenuElements/IMenu.h>

#include <QColorDialog>

class SceneMenu : public IMenu {
 private:
  struct UiComponents {
    Label* projectionTypeLabel = Builder::getLabel("Projection type");
    SwitchMenu* projectionTypeSwitchMenu =
        Builder::getSwitchMenu({"parallel", "central"});

    Label* objectsDisplayTypeLabel = Builder::getLabel("Objects display type");
    SwitchMenu* objectsDisplayTypeSwitchMenu =
        Builder::getSwitchMenu({"wireframe", "solid"});

    Label* shadersLabel = Builder::getLabel("Shaders");
    SwitchMenu* shadersSwitchMenu =
        Builder::getSwitchMenu({"none", "flat", "soft"});

    Label* rayTracingLabel = Builder::getLabel("Ray Tracing");
    SwitchMenu* rayTracingSwitchMenu = Builder::getSwitchMenu({"off", "on"});

    Title* edgeTitle = Builder::getTitle("Edge", true);
    Label* edgeTypeLabel = Builder::getLabel("Edge type");
    SwitchMenu* edgeTypeSwitchMenu =
        Builder::getSwitchMenu({"solid", "dotted"});

    Label* edgeColorLabel = Builder::getLabel("Edge color");
    Button* edgeColorButton = Builder::getButton("Set color");

    Label* edgeThicknessLabel = Builder::getLabel("Edge thickness");
    TextBox* edgeThicknessTextBox = Builder::getTextBox("");

    Title* vertexTitle = Builder::getTitle("Vertex", true);
    Label* vertexTypeLabel = Builder::getLabel("Vertex type");
    SwitchMenu* vertexTypeSwitchMenu =
        Builder::getSwitchMenu({"none", "circle", "square"});

    Label* vertexColorLabel = Builder::getLabel("Vertex color");
    Button* vertexColorButton = Builder::getButton("Set color");

    Label* vertexSizeLabel = Builder::getLabel("Vertex size");
    TextBox* vertexSizeTextBox = Builder::getTextBox("");

    Title* backgroundTitle = Builder::getTitle("Background", true);
    Label* backgroundColorLabel = Builder::getLabel("Background");
    SwitchMenu* backgroundColorSwitchMenu =
        Builder::getSwitchMenu({"none", "color", "image"});

    Button* backgroundColorButton = Builder::getButton("Set color");
    Button* backgroundImageButton = Builder::getButton("Set image");

    Title* floorTitle = Builder::getTitle("Floor", true);
    Label* gridLabel = Builder::getLabel("Grid");
    SwitchMenu* gridSwitchMenu = Builder::getSwitchMenu({"off", "on"});

    Label* floorLabel = Builder::getLabel("Floor");
    SwitchMenu* floorSwitchMenu =
        Builder::getSwitchMenu({"none", "color", "image"});

    Button* floorColorButton = Builder::getButton("Set color");
    Button* floorImageButton = Builder::getButton("Set image");

    Title* lightSourceTitle = Builder::getTitle("Light source", true);
    SwitchMenu* lightSourceSwitchMenu =
        Builder::getSwitchMenu({"none", "simple", "directed", "global"});
    Button* lightSourceColorButton = Builder::getButton("Set color");
    Button* lightSourceIntensityButton = Builder::getButton("Set intensity");

    Label* lightSourcePositionLabel =
        Builder::getLabel("Light source position", Qt::AlignHCenter);

    Label* lightSourcePositionXLabel =
        Builder::getLabel("T(x)", Qt::AlignHCenter);
    Label* lightSourcePositionYLabel =
        Builder::getLabel("T(y)", Qt::AlignHCenter);
    Label* lightSourcePositionZLabel =
        Builder::getLabel("T(z)", Qt::AlignHCenter);

    TextBox* lightSourcePositionXTextBox = Builder::getTextBox("");
    TextBox* lightSourcePositionYTextBox = Builder::getTextBox("");
    TextBox* lightSourcePositionZTextBox = Builder::getTextBox("");
  };

  UiComponents ui;
  OpenGLWidget* openGLWidget_;

 public:
  SceneMenu(OpenGLWidget* openGLWidget, QWidget* parent = nullptr)
      : IMenu(parent, "Scene"), openGLWidget_(openGLWidget) {
    composeUI();
    setupConnections();
    lockUnimplementedComponents();
  }

  void setupConnections() {
    connect(ui.edgeColorButton, &Button::clicked, this, [this]() {
      setColor([this](QColor color) { setEdgeColor(color); });
    });
    connect(ui.backgroundColorButton, &Button::clicked, this, [this]() {
      setColor([this](QColor color) { setBackgroundColor(color); });
    });
    connect(ui.vertexColorButton, &Button::clicked, this, [this]() {
      setColor([this](QColor color) { setVertexColor(color); });
    });
  }

  void setColor(std::function<void(const QColor&)> colorDst) {
    QColorDialog* colorDialog = new QColorDialog();
    connect(colorDialog, &QColorDialog::colorSelected, this,
            [colorDst](QColor selectedColor) { colorDst(selectedColor); });
    colorDialog->show();
  }

  void setEdgeColor(const QColor& color) {}

  void setVertexColor(const QColor& color) {}

  void setBackgroundColor(const QColor& color) {}

  void lockUnimplementedComponents() {
    ui.objectsDisplayTypeLabel->setEnabled(false);
    ui.objectsDisplayTypeSwitchMenu->setEnabled(false);

    ui.shadersLabel->setEnabled(false);
    ui.shadersSwitchMenu->setEnabled(false);

    ui.rayTracingLabel->setEnabled(false);
    ui.rayTracingSwitchMenu->setEnabled(false);

    ui.backgroundImageButton->setEnabled(false);
    ui.backgroundColorSwitchMenu->setDisabledItems({2});

    ui.floorTitle->setEnabled(false);
    ui.gridLabel->setEnabled(false);
    ui.gridSwitchMenu->setEnabled(false);
    ui.floorLabel->setEnabled(false);
    ui.floorSwitchMenu->setEnabled(false);
    ui.floorColorButton->setEnabled(false);
    ui.floorImageButton->setEnabled(false);

    ui.lightSourceTitle->setEnabled(false);
    ui.lightSourceSwitchMenu->setEnabled(false);
    ui.lightSourceColorButton->setEnabled(false);
    ui.lightSourceIntensityButton->setEnabled(false);

    ui.lightSourcePositionLabel->setEnabled(false);

    ui.lightSourcePositionXLabel->setEnabled(false);
    ui.lightSourcePositionYLabel->setEnabled(false);
    ui.lightSourcePositionZLabel->setEnabled(false);

    ui.lightSourcePositionXTextBox->setEnabled(false);
    ui.lightSourcePositionYTextBox->setEnabled(false);
    ui.lightSourcePositionZTextBox->setEnabled(false);
  }

  void composeUI() {
    auto scenePage = ConcreteCompositor::getPage(
        {getSceneSettingsBlock(), getEdgeSettingsBlock(),
         getVertexSettingsBlock(), getBackgroundSettingsBlock(),
         getFloorSettingsBlock(), getLightSourseSettingsBlock()},
        spacing_ * 2, spacing_ * 2, spacing_ * 2, spacing_ * 2);

    this->setFixedHeight(scenePage->height());
    scenePage->fill(this);
  }

  Composite* getSceneSettingsBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow(
             {ui.projectionTypeLabel, ui.projectionTypeSwitchMenu}),
         ConcreteCompositor::getRow(
             {ui.objectsDisplayTypeLabel, ui.objectsDisplayTypeSwitchMenu}),
         ConcreteCompositor::getRow({ui.shadersLabel, ui.shadersSwitchMenu}),
         ConcreteCompositor::getRow(
             {ui.rayTracingLabel, ui.rayTracingSwitchMenu})});
  }

  Composite* getEdgeSettingsBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.edgeTitle}),
         ConcreteCompositor::getRow({ui.edgeTypeLabel, ui.edgeTypeSwitchMenu}),
         ConcreteCompositor::getRow({ui.edgeColorLabel, ui.edgeColorButton}),
         ConcreteCompositor::getRow(
             {ui.edgeThicknessLabel, ui.edgeThicknessTextBox})});
  }

  Composite* getVertexSettingsBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.vertexTitle}),
         ConcreteCompositor::getRow(
             {ui.vertexTypeLabel, ui.vertexTypeSwitchMenu}),
         ConcreteCompositor::getRow(
             {ui.vertexColorLabel, ui.vertexColorButton}),
         ConcreteCompositor::getRow(
             {ui.vertexSizeLabel, ui.vertexSizeTextBox})});
  }

  Composite* getBackgroundSettingsBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.backgroundTitle}),
         ConcreteCompositor::getRow(
             {ui.backgroundColorLabel, ui.backgroundColorSwitchMenu}),
         ConcreteCompositor::getRow(
             {ui.backgroundColorButton, ui.backgroundImageButton})});
  }

  Composite* getFloorSettingsBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.floorTitle}),
         ConcreteCompositor::getRow({ui.gridLabel, ui.gridSwitchMenu}),
         ConcreteCompositor::getRow({ui.floorLabel, ui.floorSwitchMenu}),
         ConcreteCompositor::getRow(
             {ui.floorColorButton, ui.floorImageButton})});
  }

  Composite* getLightSourseSettingsBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.lightSourceTitle}),
         ConcreteCompositor::getRow({ui.lightSourceSwitchMenu}),
         ConcreteCompositor::getRow(
             {ui.lightSourceColorButton, ui.lightSourceIntensityButton}),
         getPositionLightingBlock()},
        spacing_);
  }

  Composite* getPositionLightingBlock() {
    return ConcreteCompositor::getBlock(
        {ConcreteCompositor::getRow({ui.lightSourcePositionLabel}),
         ConcreteCompositor::getRow({ui.lightSourcePositionXLabel,
                                     ui.lightSourcePositionYLabel,
                                     ui.lightSourcePositionZLabel}),
         ConcreteCompositor::getRow(
             {ui.lightSourcePositionXTextBox, ui.lightSourcePositionYTextBox,
              ui.lightSourcePositionZTextBox},
             spacing_ / 2)},
        0);
  }
};