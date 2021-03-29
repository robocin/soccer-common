#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "soccer-common/gui/Widgets/Widgets.h"
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"
#include "soccer-common/gui/GameVisualizer/GameVisualizer.h"
#include "MainWindowMenuBar/MainWindowMenuBar.h"

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow,
                   public WidgetSettings,
                   public MenuBarOptions,

                   public InfoWidgets,
                   public ModulesWidgets,
                   public RobotsWidgets,
                   public VisualizationWidget {
  Q_OBJECT
  friend class InfoWidgets;
  QWidget* dockWidgetInfoContents();

  friend class RobotsWidgets;
  QWidget* dockWidgetRobotsContents();

  friend class ModulesWidgets;
  QWidget* dockWidgetModulesContents();

  friend class VisualizationWidget;
  QWidget* visualizationWidget();

 public:
  MainWindow(int maxRobots, const QString &robotsPatternPath,
             QSizeF defaultVisualizerSize,
             QWidget* parent = nullptr);
  ~MainWindow();

  void setup(const QString& name, const QString& version, const QString& path);

 public slots:
  void saveEventAndLog();

 private:
  Ui::MainWindow* ui;
  MainWindowMenuBar mainWindowMenuBar;

  void loadEvent(std::optional<QString> optPath = std::nullopt);
  void saveEvent(std::optional<QString> optPath = std::nullopt);

  void closeEvent(QCloseEvent*) override;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};
#endif // MAINWINDOW_H
