#include "ModuleBase.h"

ModuleBase::ModuleBase(QThreadPool* threadPool) : ModulePrivate(threadPool) {
  /* During construction and destruction, virtual functions aren't virtual.
   * Because of this, an extra function is needed, in this case, 'build()'. */
}

void ModuleBase::build() {
  buildParameters();
  emit sendParameters(parameters().jsonObject());
}

void ModuleBase::setup(const Modules* modules) {
  connectModules(modules);
  init(modules);
}

void ModuleBase::receiveUpdateRequests(
    const Parameters::UpdateRequests& updates) {
  updateRequests->append(updates);
}

Parameters::Handler& ModuleBase::parameters() {
  return parametersHandler;
}

void ModuleBase::buildParameters() {
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
