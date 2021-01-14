#include "ModuleBase.h"

ModuleBase::ModuleBase(QThreadPool* threadPool) : ModulePrivate(threadPool) {
  /* during construction, virtual functions aren't virtual. Because of this, an
   * extra function is needed, in this case, 'build()'. */
}

ModuleBase::~ModuleBase() {
  qWarning().nospace() << "deleting " << this << ".";
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
  if (spscUpdateRequests.write_available() > 0) {
    spscUpdateRequests.push(updates);
  } else {
    // cannot discard any update.
    Parameters::UpdateRequests top;
    spscUpdateRequests.pop(top);
    spscUpdateRequests.push(top + updates);
  }
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

IndexedModuleBase::~IndexedModuleBase() {
}

int IndexedModuleBase::index() const {
  return m_index;
}
