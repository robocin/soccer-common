#ifndef PACKAGE_H
#define PACKAGE_H

#include "soccer-common/Utils/Utils.h"
#include <any>

class Package {
  long long m_timestamp;
  QString m_name;
  std::any m_data;

 public:
  template <class T>
  Package(long long _timestamp, T&& _data) :
      m_timestamp(_timestamp),
      m_name(Utils::nameOfType<T>()),
      m_data(std::forward<T>(_data)) {
  }

  long long timestamp() const;
  const QString& name() const;
  const std::any& data() const;
};

#endif // PACKAGE_H
