#include "ModuleBase.h"

ModuleBase::ModuleBase(QThreadPool* threadPool) : ModulePrivate(threadPool) {
  /* During construction and destruction, virtual functions aren't virtual.
   * Because of this, an extra function is needed, in this case, 'build()'. */
}

void ModuleBase::build() {
  buildParameters(parametersHandler);
  emit onBuildParameters(parametersHandler);

  emit sendParameters(parametersHandler.jsonObject());
}

void ModuleBase::setup(const Modules* modules) {
  connectModules(modules);
  emit onConnectModules(modules);

  connect(this,
          &ModuleBase::onReceiveUpdateRequests,
          this,
          &ModulePrivate::runInParallel,
          Qt::DirectConnection);

  connect(this, &ModulePrivate::runInParallel, this, &ModuleBase::tryStart, Qt::DirectConnection);
}

void ModuleBase::receiveUpdateRequests(const Parameters::UpdateRequests& updates) {
  if (updateRequests.apply([&updates](auto& ur) {
        ur.append(updates);
        return !ur.empty();
      })) {
    emit onReceiveUpdateRequests();
  }
}

void ModuleBase::buildParameters(Parameters::Handler&) {
}

void ModuleBase::connectModules(const Modules*) {
}

void ModuleBase::init(const Modules*) {
}

// -------------------------------------------------------------------------- //

IndexedModuleBase::IndexedModuleBase(int index, QThreadPool* threadPool) :
    ModuleBase(threadPool),
    m_index(index) {
}

int IndexedModuleBase::index() const {
  return m_index;
}

// -------------------------------------------------------------------------- //

void ModuleExtension::extendedBuildParameters(Parameters::Handler&) {
}

void ModuleExtension::extendedConnectModules(const Modules*) {
}

void ModuleExtension::extendedInit(const Modules*) {
}