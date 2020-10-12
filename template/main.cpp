#include <QtCore>
#include <QApplication>

int main(int argc, char* argv[]) {
  QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
  QApplication a(argc, argv);
  qDebug() << "Hello, World!" << Qt::endl;
  return a.exec();
}
