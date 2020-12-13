#include "ModulePrivate.h"
#include <mutex>

ModulePrivate::ModulePrivate(QThreadPool* threadPool) :
    QObject(threadPool),
    threadPool(threadPool) {
  QRunnable::setAutoDelete(false);
}

ModulePrivate::~ModulePrivate() {
}

void ModulePrivate::runInParallel() {
  if (threadPool) {
    threadPool->start(this);
  }
}

Parameters::ParametersHandler& ModulePrivate::parameters() {
  return parametersHandler;
}

void ModulePrivate::wasSkipped() {
}

void ModulePrivate::run() {
  if (std::unique_lock locker{execMutex, std::try_to_lock}) {
    exec();
  } else {
    wasSkipped();
  }
}
