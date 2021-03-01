//
// Created by jose-cruz on 01/03/2021.
//

#ifndef SOCCER_COMMON_ITHSENDER_H
#define SOCCER_COMMON_ITHSENDER_H

#include <QObject>

template <class Sender, std::size_t N = 25>
class IthSender {
  QObject* m_parent{};
  std::array<Sender*, N> m_sender{};

 public:
  explicit IthSender(QObject* parent) : m_parent(parent) {
  }

  inline Sender* ithSender(int i) {
    auto& sender = m_sender.at(static_cast<std::size_t>(i));
    return (!sender) ? (sender = new Sender(m_parent)) : sender;
  }
};

#endif // SOCCER_COMMON_ITHSENDER_H
