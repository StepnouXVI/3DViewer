#include <Views/Components/CustomComponents/CustomSwitchMenu.h>

#include <QStyle>
#include <iostream>

CustomSwitchMenu::CustomSwitchMenu(QWidget *parent) : QWidget(parent) {
  background = new QWidget(this);
  background->setObjectName("switch_menu_background");
}

void CustomSwitchMenu::resizeEvent(QResizeEvent *) {
  int indent = height() / 8;

  QVector<QRect> rects = getRects(rect(), indent);
  selectedItemBackground_->setGeometry(rects[0]);

  for (int i = 0; i < countItems_; i++) {
    items_[i]->setGeometry(rects[i]);
    setButtonFont(items_[i]);
  }

  background->setGeometry(rect());
  update();
}

int &CustomSwitchMenu::getSelectedIndex() { return selectedItem_; }

QString CustomSwitchMenu::getSelectedText() {
  return items_[selectedItem_]->text();
}

void CustomSwitchMenu::setPercentFontSize(qreal percent) { percent_ = percent; }

void CustomSwitchMenu::setItems(const QVector<QString> &items) {
  countItems_ = items.size();

  selectedItemBackground_ = new QWidget(this);
  selectedItemBackground_->setObjectName(
      "switch_menu_selected_item_background");

  for (int i = 0; i < countItems_; i++) {
    QPushButton *button = new QPushButton(items[i], this);
    button->setObjectName("switch_menu_item");
    button->setProperty("status", "inactive");
    items_.push_back(button);
    connect(button, &QPushButton::clicked, this,
            [this, i](int) { switchAnimation(i); });
  }

  setActiveButton(0);
}

void CustomSwitchMenu::setButtonFont(QPushButton *button) {
  QFont font;
  int value = button->height() * 0.6 * percent_;

  if (value > 0) {
    font.setPointSize(value);
  } else {
    font.setPointSize(1);
  }

  button->setFont(font);
}

void CustomSwitchMenu::applyStyle(QWidget *widget) {
  widget->style()->unpolish(widget);
  widget->style()->polish(widget);
  widget->update();
}

void CustomSwitchMenu::setActiveButton(int index) {
  items_[index]->setProperty("status", "active");
  applyStyle(items_[index]);
}

void CustomSwitchMenu::setInactiveButton(int index) {
  items_[index]->setProperty("status", "inactive");
  applyStyle(items_[index]);
}

void CustomSwitchMenu::changeActiveButton(int prev, int current) {
  setActiveButton(current);
  setInactiveButton(prev);
}

QVector<QRect> CustomSwitchMenu::getRects(const QRect &mainRect, int indent) {
  QVector<QRect> rects(countItems_);

  int x = indent;
  int y = indent;
  int width = (mainRect.width() - indent * (countItems_ + 1)) / countItems_;
  int height = mainRect.height() - indent * 2;

  int remainingWidth =
      (mainRect.width() - indent * (countItems_ + 1)) % countItems_;
  for (int i = 0; i < countItems_; i++) {
    if (remainingWidth > 1 || (remainingWidth > 0 && (i == countItems_ - 1))) {
      rects[i] = QRect(x, y, width + 1, height);
    } else {
      rects[i] = QRect(x, y, width, height);
    }

    x += width + indent;
  }

  return rects;
}

void CustomSwitchMenu::switchAnimation(int newCurrentIndex, int duration) {
  prevSelectedItem_ = selectedItem_;
  selectedItem_ = newCurrentIndex;

  if (selectedItem_ != prevSelectedItem_) {
    emit activeItemChanged(selectedItem_);
  }

  changeActiveButton(prevSelectedItem_, selectedItem_);

  int x0 = items_[prevSelectedItem_]->x();
  int y0 = items_[prevSelectedItem_]->y();

  int x1 = items_[selectedItem_]->x();
  int y1 = items_[selectedItem_]->y();

  animation_ = new QPropertyAnimation(selectedItemBackground_, "geometry");
  animation_->setDuration(duration);
  animation_->setStartValue(QRect(x0, y0, selectedItemBackground_->width(),
                                  selectedItemBackground_->height()));
  animation_->setEndValue(QRect(x1, y1, selectedItemBackground_->width(),
                                selectedItemBackground_->height()));
  animation_->setEasingCurve(QEasingCurve::InOutQuad);

  animation_->start();
}

void CustomSwitchMenu::setEnabledItems(std::initializer_list<int> items) {
  for (const auto &item : items) {
    items_[item]->setEnabled(true);
  }

  selectedItemBackground_->show();
  switchAnimation(*(items.begin()), 0);
}

void CustomSwitchMenu::setDisabledItems(std::initializer_list<int> items) {
  for (const auto &item : items) {
    items_[item]->setEnabled(false);
  }
}

void CustomSwitchMenu::setEnabled(bool enabled) {
  for (const auto &item : items_) {
    item->setEnabled(enabled);
  }

  if (enabled) {
    selectedItemBackground_->show();
  } else {
    selectedItemBackground_->hide();
  }
}