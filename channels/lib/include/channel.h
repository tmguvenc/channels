#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "fifo.h"
#include "receiver.h"
#include "sender.h"
#include <memory>
#include <tuple>

namespace channels {

template <typename T> struct SenderReceiverPair {
  SenderReceiverPair(FifoPtr fifo)
      : sender(new Sender<T>(fifo)), receiver(new Receiver<T>(fifo)) {}

  std::unique_ptr<Sender<T>> sender;
  std::unique_ptr<Receiver<T>> receiver;
};

template <typename T> class Channel {
  static_assert(std::is_default_constructible_v<T>,
                "T must be default constructable");
  static_assert(!std::is_pointer_v<T>, "T must be non-pointer type");

public:
  static SenderReceiverPair<T> Open() { return {std::make_shared<Fifo>()}; }
};

} // namespace channels

#endif // CHANNEL_H_
