#include "ModulePrivate.h"
#include <mutex>

ModulePrivate::ModulePrivate() : threadPool(nullptr) {
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

void ModulePrivate::buildPrivate(QThreadPool* thread) {
  setParent(thread);
  threadPool = thread;
}

Parameters::Handler& ModulePrivate::parameters() {
  return parametersHandler;
}

void ModulePrivate::update() {
}

void ModulePrivate::run() {
  if (std::unique_lock locker{execMutex, std::try_to_lock}) {
    update();
    exec();
  } else {
    wasSkipped();
  }
}

void ModulePrivate::wasSkipped() {
}
