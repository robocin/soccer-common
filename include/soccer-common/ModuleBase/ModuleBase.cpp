#include "ModuleBase.h"

ModuleBase::ModuleBase(QThreadPool* threadPool) : ModulePrivate(threadPool) {
}

ModuleBase::~ModuleBase() {
}

void ModuleBase::connectModules(const Modules*) {
}

void ModuleBase::buildParameters() {
}

void ModuleBase::init(const Modules*) {
}

IndexedModuleBase::IndexedModuleBase(int index, QThreadPool* threadPool) :
    ModuleBase(threadPool),
    m_index(index) {
}

IndexedModuleBase::~IndexedModuleBase() {
}

int IndexedModuleBase::index() const {
  return m_index;
}
