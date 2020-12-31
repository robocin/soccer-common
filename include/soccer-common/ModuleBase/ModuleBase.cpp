#include "ModuleBase.h"

ModuleBase::ModuleBase() {
}

ModuleBase::~ModuleBase() {
  qWarning().nospace() << "deleting " << this << ".";
}

void ModuleBase::build(QThreadPool* threadPool) {
  buildPrivate(threadPool);
  buildParameters();
  emit sendParameters(parameters().jsonObject());
}

void ModuleBase::setup(const Modules* modules) {
  connectModules(modules);
  init(modules);
}

void ModuleBase::buildParameters() {
}

void ModuleBase::connectModules(const Modules*) {
}

void ModuleBase::init(const Modules*) {
}

// -------------------------------------------------------------------------- //

IndexedModuleBase::IndexedModuleBase() : m_index(-1) {
}

IndexedModuleBase::~IndexedModuleBase() {
}

void IndexedModuleBase::build(int index, QThreadPool* threadPool) {
  m_index = index;
  build(threadPool);
}

int IndexedModuleBase::index() const {
  return m_index;
}
