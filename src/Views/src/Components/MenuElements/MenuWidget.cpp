#include <Views/Components/MenuElements/MenuWidget.h>

MenuWidget::MenuWidget(controllers::SceneControllerPtr scene,
                       controllers::SceneObjectControllerPtr model,
                       controllers::SceneObjectControllerPtr object)
    : scene_(scene), model_(model), object_(object) {
  composeUI();
}

void MenuWidget::composeUI() {
  openGLWidget_ = Builder::getOpenGLWidget();
  controlMenu_ = new ControlMenu(scene_, model_, object_, openGLWidget_);

  CreationMenu *creationMenu = new CreationMenu(scene_, model_);
  SceneMenu *sceneMenu = new SceneMenu(openGLWidget_);
  ObjectMenu *objectMenu = new ObjectMenu(model_, object_);
  SaveMenu *saveMenu = new SaveMenu(openGLWidget_);

  std::vector<IMenu *> items = {creationMenu, sceneMenu, objectMenu, saveMenu};

  prevMenuElement = Builder::getPrevButton();
  nextMenuElement = Builder::getNextButton();

  prevMenuElement->setObjectName("header_button");
  nextMenuElement->setObjectName("header_button");

  for (const auto &it : items) {
    menuTitles.append(Builder::getTitle(it->getMenuTitle(), false));
    menuElements.append(Builder::getScrollWidget(it));
  }

  StackedWidget *menuStackedWidget =
      Builder::getStackedWidget(menuElements, prevMenuElement, nextMenuElement);
  StackedWidget *headerStackedWidget =
      Builder::getStackedWidget(menuTitles, prevMenuElement, nextMenuElement);

  header_ = ConcreteCompositor::getRow(
      {prevMenuElement, headerStackedWidget, nextMenuElement});
  menu_ = menuStackedWidget;
}

Composite *MenuWidget::getHeader() { return header_; }

Composite *MenuWidget::getMenu() { return menu_; }

Composite *MenuWidget::getControlMenu() { return controlMenu_; }

OpenGLWidget *MenuWidget::getOpenGLWidget() { return openGLWidget_; }