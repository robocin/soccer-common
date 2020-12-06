#include "Package.h"

long long Package::timestamp() const {
  return m_timestamp;
}

QString Package::name() const {
  return m_name;
}

std::any Package::data() const {
  return m_data;
}
