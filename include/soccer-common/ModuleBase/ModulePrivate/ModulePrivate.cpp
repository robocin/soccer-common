#include "ModulePrivate.h"
#include <mutex>

ModulePrivate::ModulePrivate(QThreadPool* threadPool) :
    QObject(nullptr),
    threadPool(threadPool) {
  QRunnable::setAutoDelete(false);
}

ModulePrivate::~ModulePrivate() {
  if (threadPool) {
    while (threadPool->tryTake(static_cast<QRunnable*>(this))) {
      // removing all uninitiated calls.
    }
  }
}

void ModulePrivate::runInParallel() {
  if (threadPool) {
    threadPool->start(static_cast<QRunnable*>(this));
  }
}

void ModulePrivate::update() {
}

void ModulePrivate::wasSkipped() {
}

void ModulePrivate::parametersUpdate() {
  Parameters::UpdateRequests updates;
  while (!spscUpdateRequests.empty()) {
    spscUpdateRequests.pop(updates);
    parametersHandler.update(updates);
  }
}

void ModulePrivate::run() {
  if (std::unique_lock locker{execMutex, std::try_to_lock}) {
    parametersUpdate();
    update();
    exec();
  } else {
    wasSkipped();
  }
}
