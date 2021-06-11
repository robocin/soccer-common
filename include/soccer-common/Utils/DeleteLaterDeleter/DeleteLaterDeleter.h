//
// Created by jose-cruz on 11/06/2021.
//

#ifndef VSS_UNIFICATION_DELETELATERDELETER_H
#define VSS_UNIFICATION_DELETELATERDELETER_H

#include <QScopedPointerObjectDeleteLater>

struct DeleteLaterDeleter {
  DeleteLaterDeleter() = default;
  template <class T>
  inline void operator()(T* ptr) const {
    QScopedPointerObjectDeleteLater<T>::cleanup(ptr);
  }
  template <class T>
  static inline void cleanup(T* ptr) {
    return QScopedPointerObjectDeleteLater<T>::cleanup(ptr);
  }
};

#endif // VSS_UNIFICATION_DELETELATERDELETER_H
