//
// Created by jose-cruz on 20/07/2021.
//

#ifndef SOCCER_COMMON_PROTOBUF_H
#define SOCCER_COMMON_PROTOBUF_H

#include <QByteArray>

namespace Protobuf {
  template <class Proto>
  QByteArray toByteArray(const Proto& proto) {
    QByteArray datagram(static_cast<int>(proto.ByteSize()), static_cast<char>(0));
    proto.SerializeToArray(datagram.data(), datagram.size());
    return datagram;
  }

  template <class Proto>
  Proto fromByteArray(const QByteArray& datagram) {
    Proto proto;
    proto.ParseFromArray(datagram, static_cast<int>(datagram.size()));
    return proto;
  }
} // namespace Protobuf

#endif // SOCCER_COMMON_PROTOBUF_H
