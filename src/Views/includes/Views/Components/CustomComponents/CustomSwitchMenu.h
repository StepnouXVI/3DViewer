#pragma once

#include <Views/Components/Composite/Leaf.h>

#include <QPropertyAnimation>
#include <QPushButton>
#include <QWidget>

class CustomSwitchMenu : public QWidget {
  Q_OBJECT

 private:
  qreal percent_ = 1;
  QVector<QPushButton *> items_;
  int countItems_;
  int selectedItem_ = 0;
  int prevSelectedItem_ = 0;
  QWidget *selectedItemBackground_;
  QPropertyAnimation *animation_;
  QWidget *background;

  void resizeEvent(QResizeEvent *event) override;

 public:
  CustomSwitchMenu(QWidget *parent = nullptr);

  int &getSelectedIndex();
  QString getSelectedText();
  void setPercentFontSize(qreal percent);
  void setItems(const QVector<QString> &items);
  void setEnabledItems(std::initializer_list<int> items);
  void setDisabledItems(std::initializer_list<int> items);
  void setEnabled(bool enabled);

 private:
  void setActiveButton(int index);
  void setInactiveButton(int index);
  void applyStyle(QWidget *widget);
  void changeActiveButton(int prev, int current);

  void setButtonFont(QPushButton *button);

  QVector<QRect> getRects(const QRect &mainRect, int indent);
  void switchAnimation(int newCurrentIndex, int duration = 200);

 signals:
  void activeItemChanged(int newActiveItemIndex);
};
