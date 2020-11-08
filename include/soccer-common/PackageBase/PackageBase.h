#ifndef PACKAGEBASE_H
#define PACKAGEBASE_H

class QString;

class PackageBase {
  long long m_timestamp;

 public:
  PackageBase(long long _timestamp);

  long long timestamp() const;
  virtual QString name() = 0;
};

#endif // PACKAGEBASE_H
