#include <Views/Components/CustomComponents/CustomCircleSlider.h>

#include <iostream>

CustomCircleSlider::CustomCircleSlider(QWidget *parent) : QDial(parent) {
  setWrapping(false);
  setMinimum(0);
  setMaximum(100);
  setSingleStep(1);
}

void CustomCircleSlider::updateValue() {
  Rotate rotation = isRotate();

  if (rotation == Rotate::CLOCKWISE) {
    countOfTurns_++;
  } else if (rotation == Rotate::COUNTERCLOCKWISE) {
    countOfTurns_--;
  }

  value_ = static_cast<double>(value()) / 100 + countOfTurns_;
  prevValue_ = value();

  emit valueChanged(value_);
}

CustomCircleSlider::Rotate CustomCircleSlider::isRotate() {
  if (prevValue_ == maximum() && value() == minimum()) {
    return CustomCircleSlider::Rotate::CLOCKWISE;
  } else if (prevValue_ == minimum() && value() == maximum()) {
    return CustomCircleSlider::Rotate::COUNTERCLOCKWISE;
  }
  return CustomCircleSlider::Rotate::NONE;
}

double CustomCircleSlider::getValue() { return value_; }

void CustomCircleSlider::setValue(const double &value) {
  value_ = value;
  prevValue_ = value;
  countOfTurns_ = static_cast<int>(value_);

  int dialValue = (std::abs(value_) - std::abs(countOfTurns_)) * 100;
  if (std::signbit(value_)) {
    dialValue = 100 - dialValue;
    countOfTurns_ -= 1;
  }

  QDial::setValue(dialValue);
  update();
}

void CustomCircleSlider::paintEvent(QPaintEvent *) {
  updateValue();

  const double degree360 = 2 * M_PI;

  QPainter painter(this);
  painter.setBackgroundMode(Qt::OpaqueMode);
  painter.setRenderHint(QPainter::Antialiasing);

  QColor backgroundColor = QColor(16, 16, 16);

  double outerRadius = height() / 2.0;
  double outerBorderWidth = 0.03 * outerRadius;
  painter.setPen(QPen(QColor(23, 23, 24), outerBorderWidth));
  painter.setBrush(backgroundColor);
  painter.drawEllipse(outerBorderWidth / 2.0, outerBorderWidth / 2.0,
                      height() - outerBorderWidth, height() - outerBorderWidth);

  double innerRadius = height() * 0.7 / 2.0;
  double innerBorderWidth = 0.015 * innerRadius;
  painter.setPen(QPen(QColor(23, 23, 24), innerBorderWidth));
  painter.setBrush(QColor(28, 28, 30));
  painter.drawEllipse(QRectF(height() / 2.0 - innerRadius,
                             height() / 2.0 - innerRadius, innerRadius * 2.0,
                             innerRadius * 2.0));

  double knobRadius = (outerRadius - innerRadius - 2 * outerBorderWidth) / 2.0;
  double knobMargin = 0.03 * outerRadius;

  double ratio =
      static_cast<double>(value() - minimum()) / (maximum() - minimum());
  double angle = abs(ratio * degree360) + M_PI / 2;

  double r = innerRadius + knobMargin +
             (outerRadius - innerRadius - knobMargin - knobRadius -
              outerBorderWidth * 2);

  double y = sin(angle) * r + height() / 2.0;
  double x = cos(angle) * r + height() / 2.0;

  painter.setPen(Qt::NoPen);
  painter.setBrush(QColor(58, 58, 60));
  painter.drawEllipse(QPointF(x, y), knobRadius, knobRadius);

  painter.setPen(QColor(173, 173, 173));
  painter.setFont(QFont("NATS", height() * 0.25));
  painter.setBrush(QColor(0, 0, 0, 0));
  painter.setBackground(QBrush(QColor(0, 0, 0, 0)));
  QString dataText = QString::number(value_, 'f', 2);
  painter.drawText(rect(), Qt::AlignCenter, dataText);
}
