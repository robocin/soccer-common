#ifndef PACKAGE_H
#define PACKAGE_H

#include "soccer-common/Utils/Utils.h"

template <class T>
class TrackedPackageBase {
  inline static const QString m_name = Utils::nameOfType<T>();
  long long m_timestamp;

 public:
  TrackedPackageBase(long long timestamp) : m_timestamp(timestamp) {
  }
  long long timestamp() const {
    return m_timestamp;
  }
  static QString name() {
    return m_name;
  }
};

#endif // PACKAGE_H
