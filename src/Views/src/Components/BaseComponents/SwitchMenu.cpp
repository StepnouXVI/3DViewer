#include <Views/Components/BaseComponents/SwitchMenu.h>

SwitchMenu::SwitchMenu(QWidget *parent)
    : switchMenu_(new CustomSwitchMenu(this)) {
  setParent(parent);
  connect(switchMenu_, &CustomSwitchMenu::activeItemChanged, [this]() {
    emit activeItemChanged(switchMenu_->getSelectedIndex());
  });
}

int SwitchMenu::getSelectedIndex() { return switchMenu_->getSelectedIndex(); }

QString SwitchMenu::getSelectedText() { return switchMenu_->getSelectedText(); }

void SwitchMenu::resizeEvent(QResizeEvent *event) {
  switchMenu_->resize(size());
}

CustomSwitchMenu *SwitchMenu::getWidget() const { return switchMenu_; }

void SwitchMenu::addItems(const QVector<QString> &items) {
  switchMenu_->setItems(items);
}

void SwitchMenu::setEnabledItems(std::initializer_list<int> items) {
  switchMenu_->setEnabledItems(items);
}

void SwitchMenu::setDisabledItems(std::initializer_list<int> items) {
  switchMenu_->setDisabledItems(items);
}

void SwitchMenu::setEnabled(bool enabled) { switchMenu_->setEnabled(enabled); }
