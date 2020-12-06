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
  Package(long long timestamp, T&& data) :
      m_timestamp(timestamp),
      m_name(Utils::nameOfType<T>()),
      m_data(std::forward<T>(data)) {
  }

  long long timestamp() const;
  QString name() const;
  std::any data() const;
};

template <class T>
class PackageOf : public Package {
 public:
  PackageOf(long long timestamp, T&& data) :
      Package(timestamp, std::forward<T>(data)) {
  }
};

#endif // PACKAGE_H
