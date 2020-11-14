#include "Package.h"

long long Package::timestamp() const {
  return m_timestamp;
}

const QString& Package::name() const {
  return m_name;
}

const std::any& Package::data() const {
  return m_data;
}
