//
// Created by jose-cruz on 01/03/2021.
//

#ifndef SOCCER_COMMON_ITHSENDER_H
#define SOCCER_COMMON_ITHSENDER_H

#include <QObject>
#include <array>

template <class Sender, size_t N = 16>
class IthSender {
  std::array<Sender*, N> m_senders{};

 public:
  explicit IthSender(QObject* parent) {
    for (auto&& sender : m_senders) {
      sender = new Sender(parent);
    }
  }

  inline Sender* ithSender(int i) const {
    return m_senders.at(i);
  }
};

#endif // SOCCER_COMMON_ITHSENDER_H
