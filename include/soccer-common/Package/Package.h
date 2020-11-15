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

template <class T>
class PackageOf : public Package {
 public:
  PackageOf(long long _timestamp, T&& _data) :
      Package(_timestamp, std::forward<T>(_data)) {
  }

  template <class... Args>
  PackageOf(long long _timestamp, Args&&... _args) :
      Package(_timestamp, T(std::forward<Args>(_args)...)) {
  }
};

#endif // PACKAGE_H
