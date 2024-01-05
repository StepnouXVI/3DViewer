#pragma once

#include <Views/Components/Builder/Builder.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/Composite/ConcreteCompositor.h>
#include <Views/Components/MenuElements/EntityInfo.h>

#include <stdexcept>

class InfoStackedWidget : public Composite {
  Q_OBJECT
 private:
  QVector<QString> titles_;
  StackedWidget *stackedWidget_;
  int activePage_ = 0;
  bool isDefaultPage_ = false;

 public:
  InfoStackedWidget(const QVector<QString> &titles, QWidget *parent = nullptr);
  InfoStackedWidget(EntityInfo *entityInfo, QWidget *parent = nullptr);

  void setSpeed(int speed);
  void setButtons(Button *prev, Button *next);
  void setDefaultPage();
  void addPage(const QVector<QString> &data);
  void removePage(const int &index);
  int count();
  StackedWidget *getStackedWidget();
  Component *getTitleLabel(const QString &title);
  Component *getDataLabel(const QString &data);
  void setEnabled(bool enabled);

 protected:
  void resizeEvent(QResizeEvent *);

 signals:
  void pageChanged(int activePage);
};
