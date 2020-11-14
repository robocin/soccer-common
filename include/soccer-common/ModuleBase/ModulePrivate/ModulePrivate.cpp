#include "ModulePrivate.h"
#include "soccer-common/ModuleBase/AnyVisitor/AnyVisitor.h"
#include <mutex>

ModulePrivate::ModulePrivate(QThreadPool* _threadPool) :
    QObject(_threadPool),
    visitor(std::make_unique<AnyVisitor>()),
    threadPool(_threadPool) {
  QRunnable::setAutoDelete(false);
}

ModulePrivate::~ModulePrivate() {
}

void ModulePrivate::receive(const Package& package) {
  try {
    (*visitor)(package.data());
  } catch (...) {
    wasNotReceived(package);
  }
}

void ModulePrivate::runInParallel() {
  if (threadPool) {
    threadPool->start(this);
  }
}

void ModulePrivate::receiveAndRunInParallel(const Package& package) {
  receive(package);
  runInParallel();
}

Parameters::ParametersHandler& ModulePrivate::parameters() {
  return parametersHandler;
}

void ModulePrivate::wasNotReceived(const Package&) {
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
