#include <QtCore>
#include <QPoint>
#include <optional>
#include <QTextStream>

int main() {
  std::optional<QPoint> op;
  qDebug() << "Hello World with Qt!" << op.value_or(QPoint(10, 20)) << Qt::endl;
  return 0;
}
