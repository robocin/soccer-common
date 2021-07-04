//
// Created by jose-cruz on 11/06/2021.
//

#ifndef SOCCER_COMMON_DELETELATERDELETER_H
#define SOCCER_COMMON_DELETELATERDELETER_H

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

#endif // SOCCER_COMMON_DELETELATERDELETER_H
