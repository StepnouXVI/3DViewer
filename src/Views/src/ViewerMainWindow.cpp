#include <Views/ViewerMainWindow.h>
#include <Views/lib/AnchorLayout/AnchorLayout.h>
#include <Views/Components/Builder/Builder.h>

#include <QOpenGLContext>

ViewerMainWindow::ViewerMainWindow(models::ISceneDrawerPtr drawer) : Composite() {
  drawer_ = drawer;
  drawer_ = Builder::getOpenGLWidget(this)->getWidget()->getShared();
  
  setFixedSize(1920, 1080);

  Composite *openGLComposite = new Composite(this);
  Composite *menuHeaderComposite = new Composite(this);
  Composite *menuComposite = new Composite(this);
  Composite *controlMenuComposite = new Composite(this);

  scene_ = std::make_shared<controllers::SceneController>(drawer_);
  model_ = std::make_shared<controllers::SceneObjectController>(drawer_);
  object_ = model_;
  MenuWidget *menu = new MenuWidget(scene_, model_, object_);
  menu->getOpenGLWidget()->fill(openGLComposite);
  menu->getHeader()->fill(menuHeaderComposite);
  menu->getMenu()->fill(menuComposite);
  menu->getControlMenu()->fill(controlMenuComposite);


  AnchorLayout *containerLayout = AnchorLayout::get(this);

  AnchorLayout *mainWidgetLayout = ConcreteCompositor::anchor(
      openGLComposite,
      {containerLayout->left(), containerLayout->top(),
       containerLayout->customLine(Qt::Vertical, 0.75),
       containerLayout->bottom()},
      {spacing_, spacing_, 0, spacing_});
  AnchorLayout *menuHeaderWidgetLayout = ConcreteCompositor::anchor(
      menuHeaderComposite,
      {mainWidgetLayout->right(), containerLayout->top(),
       containerLayout->right(),
       containerLayout->customLine(Qt::Horizontal, 0.08)},
      {spacing_, spacing_, spacing_, 0});
  AnchorLayout *controlMenuWidgetLayout = ConcreteCompositor::anchor(
      controlMenuComposite,
      {mainWidgetLayout->right(),
       containerLayout->customLine(Qt::Horizontal, -0.2),
       containerLayout->right(), containerLayout->bottom()},
      {spacing_, 0, spacing_, spacing_});
  AnchorLayout *menuWidgetLayout = ConcreteCompositor::anchor(
      menuComposite,
      {mainWidgetLayout->right(), menuHeaderWidgetLayout->bottom(),
       containerLayout->right(), controlMenuWidgetLayout->top()},
      {spacing_, 0, spacing_, spacing_});

  setObjectName("app_background");
  openGLComposite->setObjectName("main_widget_background");
  menuComposite->setObjectName("menu_widget_background");
  menuHeaderComposite->setObjectName("menu_header_background");
  controlMenuComposite->setObjectName("control_widget_background");
}
