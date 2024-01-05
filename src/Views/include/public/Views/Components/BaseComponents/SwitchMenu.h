#pragma once

#include <Views/Components/Composite/Leaf.h>
#include <Views/Components/CustomComponents/CustomSwitchMenu.h>

class SwitchMenu : public Leaf {
  Q_OBJECT

 private:
  CustomSwitchMenu *switchMenu_;

 public:
  SwitchMenu(QWidget *parent = nullptr);

  int getSelectedIndex();
  QString getSelectedText();
  void addItems(const QVector<QString> &items);
  void setEnabledItems(std::initializer_list<int> items);
  void setDisabledItems(std::initializer_list<int> items);
  CustomSwitchMenu *getWidget() const override;
  void setEnabled(bool enabled);

 protected:
  void resizeEvent(QResizeEvent *event) override;

 signals:
  void activeItemChanged(int newActiveItemIndex);
};
