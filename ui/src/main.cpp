#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QApplication::setApplicationName("App");
  QApplication::setOrganizationName("App");

  QQmlApplicationEngine engine;
  QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
  engine.loadFromModule("Main", "Main");

  return app.exec();
}
