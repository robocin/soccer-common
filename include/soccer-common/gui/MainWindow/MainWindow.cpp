#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QSettings>

QWidget* MainWindow::dockWidgetInfoContents() {
  return ui->dockWidgetInfoContents;
}

QWidget* MainWindow::dockWidgetRobotsContents() {
  return ui->dockWidgetRobotsContents;
}

QWidget* MainWindow::dockWidgetModulesContents() {
  return ui->dockWidgetModulesContents;
}

QWidget* MainWindow::visualizationWidget() {
  return ui->visualizationWidget;
}

MainWindow::MainWindow(int maxRobots, QWidget* parent) :
    QMainWindow(parent),
    WidgetSettings(this, nullptr),
    RobotsWidgets(maxRobots),
    ui(new Ui::MainWindow),
    mainWindowMenuBar(this) {
  /* performing the setup of ui and each interface (the order matters) */ {
    ui->setupUi(this); // first setup.
    setupInfoWidgets(this);
    setupModulesWidgets(this);
    setupRobotsWidgets(this);
    setupVisualizationWidget(this);
  }
  /* setting dock widget corners */ {
    auto features = QDockWidget::DockWidgetClosable |
                    QDockWidget::DockWidgetMovable |
                    QDockWidget::DockWidgetFloatable;

    ui->dockWidgetInfo->setFeatures(features);
    ui->dockWidgetModules->setFeatures(features);
    ui->dockWidgetRobots->setFeatures(features);

    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  }
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::setup(const QString& name,
                       const QString& version,
                       const QString& path) {
  /* setting project language to english */ {
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
  }
  /* storing project info to use later */ {
    setupWidgetSettings(name,
                        version,
                        path,
                        path + "/config/local/",
                        QDateTime::currentDateTime().toString("dd.MM.yyyy"),
                        QTime::currentTime().toString("h:m:s"));
    /* creating if don't exists */ {
      QDir().mkdir(path + "config/local/");
      QDir().mkdir(path + "config/shared/");
    }
  }
  /* setting window title with name and version */ {
    setWindowTitle(projectName() + " " + projectVersion());
  }
  /* menubar cannot be initialized before all modules insertion */ {
    setupMenuBar(mainWindowMenuBar);
  }
  /* loading configs */ {
    qWarning() << "starting to load configuration...";
    loadEvent();
    qWarning() << "the configuration has been loaded.";
  }
}

void MainWindow::saveEventAndLog() {
  saveEvent();

  QString logpath = localConfigPath() + "logs/" + executionDateTime() + "/" +
                    executionTime() + "/";
  QDir().mkdir(logpath);

  saveEvent(logpath);
  qWarning() << "the configuration has been saved.";
}

void MainWindow::loadEvent(std::optional<QString> optPath) {
  if (optPath) {
    if (!optPath->endsWith('/')) {
      optPath->append('/');
    }
  }
  QString path = optPath.value_or(localConfigPath());
  QString filename = path + "config";
  /* loading 'ini' and json settings. */ {
    std::unique_ptr<QSettings> settings;
    std::optional<QTemporaryFile> tmpFile;
    if (QDir(path).exists("config.ini")) {
      settings =
          std::make_unique<QSettings>(filename + ".ini", QSettings::IniFormat);
    } else {
      /* QSettings is not copyable and always requires write file. So, it is
       * necessary to create a temporary file to write, and the use of a
       * std::unique_ptr is to offset the fact that it is not copyable.*/
      tmpFile.emplace();
      Q_ASSERT(tmpFile->open());
      settings = std::make_unique<QSettings>(tmpFile->fileName(),
                                             QSettings::IniFormat);
      qWarning() << "the file \"config.ini\" has not been opened.";
    }

    QJsonObject json;
    if (QFile file(filename + ".json"); file.open(QIODevice::ReadOnly)) {
      json = QJsonDocument::fromJson(file.readAll()).object();
      file.close();
    } else {
      qWarning() << "the file \"config.json\" has not been opened.";
    }

    loadSettings(*settings, json);
  }
}

void MainWindow::saveEvent(std::optional<QString> optPath) {
  if (optPath) {
    if (!optPath->endsWith('/')) {
      optPath->append('/');
    }
  }
  QString filename = optPath.value_or(localConfigPath()) + "config";
  /* storing and/or creating 'ini' and json settings. */ {
    QSettings settings(filename + ".ini", QSettings::IniFormat);
    QJsonObject json;
    writeSettings(settings, json);
    if (QFile file(filename + ".json"); file.open(
            QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
      file.write(QJsonDocument(json)
                     .toJson(QJsonDocument::Indented)
                     .replace(QByteArray(4, ' '), QByteArray(2, ' ')));
      file.close();
    } else {
      qWarning() << "the file" << filename << "has not been opened.";
    }
  }
}

void MainWindow::closeEvent(QCloseEvent*) {
  saveEventAndLog();
}

void MainWindow::writeLocalSettings(QSettings& settings) {
  settings.setValue("geometry", saveGeometry());
  settings.setValue("windowState", saveState());
}

void MainWindow::loadLocalSettings(const QSettings& settings) {
  QByteArray geometryValue = settings.value("geometry").value<QByteArray>();
  restoreGeometry(geometryValue);

  QByteArray windowState = settings.value("windowState").value<QByteArray>();
  restoreState(windowState);
}

void MainWindow::putWidgetActions(MainWindowMenuBar& menubar) {
  /* file exit */ {
    QAction* exit = new QAction("Exit", &menubar["File"]);
    exit->setShortcuts({QKeySequence("Ctrl+C"), QKeySequence("Ctrl+Q")});
    QObject::connect(exit, &QAction::triggered, this, &MainWindow::close);
    menubar["File"].addAction(exit);
  }

  /* save config */ {
    QAction* save = new QAction("Save", &menubar["File"]);
    save->setShortcut(QKeySequence("Ctrl+S"));
    QObject::connect(save, &QAction::triggered, this, [this]() {
      saveEventAndLog();
    });
    menubar["File"].addAction(save);
  }

  /* save as config */ {
    QAction* saveAs = new QAction("Save As...", &menubar["File"]);
    saveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));
    QDir().mkdir(localConfigPath() + "custom/");
    QObject::connect(saveAs, &QAction::triggered, this, [this]() {
      QString path =
          QFileDialog::getExistingDirectory(this,
                                            "Save config to folder:",
                                            localConfigPath() + "custom/");
      if (!path.isEmpty()) {
        saveEvent(path);
        qWarning().nospace()
            << "the configuration has been saved to " << path << ".";
      } else {
        qWarning() << "path is empty.";
      }
    });
    menubar["File"].addAction(saveAs);
  }

  /* open config */ {
    QAction* open = new QAction("Open...", &menubar["File"]);
    open->setShortcut(QKeySequence("Ctrl+O"));
    /* enabled only when the game is paused. */ {
      open->setEnabled(!playPauseButton()->isClicked());
      QObject::connect(playPauseButton(),
                       &PlayPauseWidget::onPushButtonClicked,
                       open,
                       [open](bool checked) {
                         open->setEnabled(!checked);
                       });
    }
    QObject::connect(open, &QAction::triggered, this, [this]() {
      QString path =
          QFileDialog::getExistingDirectory(this,
                                            "Open config from folder:",
                                            localConfigPath() + "custom/");
      if (!path.isEmpty()) {
        if (QDir(path).exists("config.ini") ||
            QDir(path).exists("config.json")) {
          loadEvent(path);
          qWarning().nospace()
              << "the configuration has been loaded from " << path << ".";
        } else {
          qWarning() << "the selected folder" << path
                     << "doesn't have the necessary files to load.";
        }
      } else {
        qWarning() << "path is empty.";
      }
    });
    menubar["File"].addAction(open);
  }

  /* view fullscreen */ {
    QAction* fullscreen = new QAction("Fullscreen", &menubar["View"]);
    fullscreen->setShortcut(QKeySequence("Ctrl+Shift+F11"));
    QObject::connect(fullscreen, &QAction::triggered, this, [this]() {
      isFullScreen() ? showNormal() : showFullScreen();
    });
    menubar["View"].addAction(fullscreen);
    menubar["View"].addSeparator();
  }

  /* view dockwidgets */ {
    QMenu* menu = new QMenu("DockWidgets", &menubar["View"]);
    menu->addAction(ui->dockWidgetInfo->toggleViewAction());
    menu->addAction(ui->dockWidgetRobots->toggleViewAction());
    menu->addAction(ui->dockWidgetModules->toggleViewAction());
    menubar["View"].addMenu(menu);
  }
}
