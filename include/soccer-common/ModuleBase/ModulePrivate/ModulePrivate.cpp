#include "ModulePrivate.h"

ModulePrivate::ModulePrivate(QThreadPool* threadPool) : QObject(nullptr), threadPool(threadPool) {
  QRunnable::setAutoDelete(false);
}

void ModulePrivate::runInParallel() {
  if ([[maybe_unused]] std::unique_lock locker{execMutex, std::try_to_lock}) {
    if (QThreadPool* tp = threadPool) {
      tp->start(static_cast<QRunnable*>(this));
    }
  }
}

void ModulePrivate::prepareToDelete() {
  qWarning().nospace() << "scheduling the deletion of " << this << ".";
  disconnect(); // disconnecting outgoing connections.
  using namespace std::chrono_literals;
  QTimer::singleShot(1s, this, [this] {
    return ModulePrivate::waitOrDelete(this);
  });
}

void ModulePrivate::update() {
}

void ModulePrivate::parametersUpdate() {
  Parameters::UpdateRequests updates = updateRequests.apply([](Parameters::UpdateRequests& ur) {
    Parameters::UpdateRequests updates = ur;
    ur.clear();
    return updates;
  });
  if (!updates.empty()) {
    parametersHandler.update(updates);
  }
}

void ModulePrivate::run() {
  if ([[maybe_unused]] std::unique_lock locker{execMutex, std::try_to_lock}) {
    parametersUpdate();
    update();
    exec();
  }
}

void ModulePrivate::waitOrDelete(ModulePrivate* object) {
  using namespace std::chrono_literals;
  if (!object) {
    return;
  }
  if ([[maybe_unused]] std::unique_lock locker{object->execMutex, std::try_to_lock}) {
    if (QThreadPool* tp = object->threadPool) {
      // will avoid put this instance inside threadPool again.
      object->threadPool.store(nullptr, std::memory_order_release);
      while (tp->tryTake(static_cast<QRunnable*>(object))) {
        qWarning() << "removing all" << object << "uninitiated calls.";
        // removing all uninitiated calls.
      }
    }
    QTimer::singleShot(1s, object, &ModulePrivate::deleteLater);
  } else {
    QTimer::singleShot(1s, object, [object] {
      return ModulePrivate::waitOrDelete(object);
    });
  }
}
