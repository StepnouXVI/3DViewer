#include <Models/SceneObject/SceneObject.h>
#include <Views/ViewerMainWindow.h>

#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QStyle>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  int fontNats = QFontDatabase::addApplicationFont(
      ":/Views/resources/Fonts/NATS-Regular.ttf");
  int fontNicoMoji = QFontDatabase::addApplicationFont(
      ":/Views/resources/Fonts/NicoMoji-Regular.ttf");
  app.setFont(QFont("NATS"));

  QFile styleFile(":/Views/resources/Style/style.qss");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  ViewerMainWindow mainWindow;
  mainWindow.setStyleSheet(style);

  mainWindow.style()->unpolish(&mainWindow);
  mainWindow.style()->polish(&mainWindow);
  mainWindow.update();

  mainWindow.show();

  return app.exec();
}
