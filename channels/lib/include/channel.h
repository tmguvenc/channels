#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "fifo.h"
#include "sender.h"
#include "receiver.h"
#include <tuple>

namespace channels {

template<typename T>
using SenderReceiverPair = std::pair<Sender<T>, Receiver<T>>;

template<typename T>
class Channel {
public:
  static SenderReceiverPair<T> Open() {
    auto fifo = std::make_shared<Fifo>();
    return {
      Sender<T>{fifo},
      Receiver<T>{fifo}
    };
  }
};

} // namespace channels

#endif // CHANNEL_H_
