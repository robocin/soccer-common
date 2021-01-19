#include "ModulePrivate.h"
#include <mutex>

ModulePrivate::ModulePrivate(QThreadPool* threadPool) :
    QObject(nullptr),
    threadPool(threadPool) {
  QRunnable::setAutoDelete(false);
}

ModulePrivate::~ModulePrivate() {
  if (QThreadPool* tp = threadPool) {
    threadPool = nullptr;
    while (tp->tryTake(static_cast<QRunnable*>(this))) {
      // removing all uninitiated calls.
    }
  }
}

void ModulePrivate::runInParallel() {
  if (QThreadPool* tp = threadPool) {
    tp->start(static_cast<QRunnable*>(this));
  }
}

void ModulePrivate::update() {
}

void ModulePrivate::wasSkipped() {
}

void ModulePrivate::parametersUpdate() {
  updateRequests.apply([this](Parameters::UpdateRequests& updateRequests) {
    if (!updateRequests.empty()) {
      parametersHandler.update(updateRequests);
      updateRequests.clear();
    }
  });
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
