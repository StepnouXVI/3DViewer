#pragma once

#include <QColor>
#include <QDial>
#include <QPainter>
#include <cmath>

class CustomCircleSlider : public QDial {
  Q_OBJECT

 private:
  double value_ = 0;
  double prevValue_ = 0;
  int countOfTurns_ = 0;

  enum class Rotate { NONE, CLOCKWISE, COUNTERCLOCKWISE };

  CustomCircleSlider::Rotate isRotate();

 public:
  CustomCircleSlider(QWidget *parent = nullptr);
  double getValue();
  void setValue(const double &value);

 protected:
  void paintEvent(QPaintEvent *event) override;

 signals:
  void valueChanged(double value);

 private slots:
  void updateValue();
};
