#include "ModuleBase.h"

ModuleBase::ModuleBase(QThreadPool* threadPool) : ModulePrivate(threadPool) {
}

ModuleBase::~ModuleBase() {
}
