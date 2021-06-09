//
// Created by jose-cruz on 01/03/2021.
//

#ifndef SOCCER_COMMON_ITHSENDER_H
#define SOCCER_COMMON_ITHSENDER_H

#include <QObject>

template <class Sender>
class IthSender {
  QObject* m_parent{};
  QHash<int, Sender*> m_sender{};

 public:
  explicit IthSender(QObject* parent) : m_parent(parent) {
  }

  inline Sender* ithSender(int i) {
    auto& sender = m_sender[i];
    return (!sender) ? (sender = new Sender(m_parent)) : sender;
  }
};

#endif // SOCCER_COMMON_ITHSENDER_H
