#pragma once

#include <Views/Components/BaseComponents/InfoStackedWidget.h>
#include <Views/Components/BaseComponents/OpenGLWidget.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/MenuElements/IMenu.h>
#include <Views/lib/Gif/Gif.h>

#include <QFileDialog>
#include <QTimer>
#include <QVector>
#include <QWidget>

class Timer : public QTimer {
  Q_OBJECT

 private:
  QTimer *stopTimer_;

 public:
  Timer(QWidget *parent = nullptr)
      : QTimer(parent), stopTimer_(new QTimer(this)) {
    connect(stopTimer_, &QTimer::timeout, this, &Timer::stop);
  }

  void start(int duration, int interval) {
    stopTimer_->start(duration);
    QTimer::start(interval);
  }

 private:
  void stop() {
    stopTimer_->stop();
    QTimer::stop();
    emit stopped();
  }

 signals:
  void stopped();
};

class SaveMenu : public IMenu {
 private:
  enum Format { JPEG, BMP, PNG, GIF };
  int activeFormat_ = Format::JPEG;

  QString filePath_;
  QVector<QImage> gifImages_;

  Timer *timer_;
  int duration_ = 5;
  int fps_ = 10;

  struct UiComponents {
    Title *formatTitle = Builder::getTitle("Format", true);
    SwitchMenu *formatSwitch =
        Builder::getSwitchMenu({"jpeg", "bmp", "png", "gif"});
    Button *saveButton = Builder::getButton("Save");
  };

  OpenGLWidget *openGLWidget_;

  UiComponents ui;

 public:
  SaveMenu(OpenGLWidget *openGLWidget, QWidget *parent = nullptr)
      : IMenu(parent, "Save"),
        openGLWidget_(openGLWidget),
        timer_(new Timer(this)) {
    initUI();
    setupConnections();
    composeUI();
  }

  void initUI() {}

  void setupConnections() {
    connect(timer_, &Timer::timeout, this, &SaveMenu::addImageToGif);
    connect(timer_, &Timer::stopped, this, &SaveMenu::saveGif);
    connect(ui.formatSwitch, &SwitchMenu::activeItemChanged, this,
            [this](int format) { activeFormat_ = format; });
    connect(ui.saveButton, &Button::clicked, this, &SaveMenu::save);
  }

  void composeUI() {
    Composite *savePage = ConcreteCompositor::getPage(
        {
            ConcreteCompositor::getRow({ui.formatTitle}),
            ConcreteCompositor::getRow({ui.formatSwitch}),
            ConcreteCompositor::getRow({ui.saveButton}),
        },
        spacing_, spacing_ * 4, 0, spacing_ * 4);

    this->setFixedHeight(savePage->height());
    savePage->fill(this);
  }

 private:
  void save() {
    filePath_ =
        QFileDialog::getSaveFileName(nullptr, "Save File", QDir::homePath());
    QString format = ui.formatSwitch->getSelectedText();

    if (!filePath_.isEmpty()) {
      filePath_ += "." + format;
      if (activeFormat_ == Format::GIF) {
        timer_->start(duration_ * 1000, 1000 / fps_);
      } else {
        saveImage(format);
      }
    }
  }

  void saveImage(const QString &format) {
    getImage().save(filePath_, format.toUpper().toUtf8().constData());
  }

  QImage getImage() {
    return QImage(openGLWidget_->getWidget()->grabFramebuffer());
  }

  void saveGif() {
    GifWriter writer = {};

    GifBegin(&writer, filePath_.toLocal8Bit(), openGLWidget_->width(),
             openGLWidget_->height(), duration_, 8, true);
    for (const auto &it : gifImages_) {
      GifWriteFrame(&writer, it.bits(), openGLWidget_->width(),
                    openGLWidget_->height(), duration_, 8, true);
    }
    GifEnd(&writer);
    gifImages_.clear();
  }

  void addImageToGif() { gifImages_.append(getImage()); }
};
