#include "ModuleBase.h"

ModuleBase::ModuleBase(QThreadPool* threadPool) : ModulePrivate(threadPool) {
}

ModuleBase::~ModuleBase() {
}

IndexedModuleBase::IndexedModuleBase(int _index, QThreadPool* threadPool) :
    ModuleBase(threadPool),
    m_index(_index) {
}

IndexedModuleBase::~IndexedModuleBase() {
}
