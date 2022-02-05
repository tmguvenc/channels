#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "fifo.h"
#include "receiver.h"
#include "sender.h"
#include <memory>
#include <tuple>

namespace channels {

template <typename T> 
class Channel;

template <typename T> 
struct SRPair {
  friend class Channel<T>;
private:
  SRPair(FifoPtr fifo) noexcept
    : sender(new Sender<T>(fifo)), 
      receiver(new Receiver<T>(fifo)) {}

public:
  ~SRPair() noexcept = default;

  SRPair(const SRPair &other) noexcept = delete;
  SRPair &operator=(const SRPair &other) noexcept = delete;
  SRPair(SRPair &&other) noexcept = delete;
  SRPair &operator=(SRPair &&other) noexcept = delete;

  std::unique_ptr<Sender<T>> sender;
  std::unique_ptr<Receiver<T>> receiver;
};

template <typename T> 
class Channel {
  static_assert(std::is_default_constructible_v<T>,
                "T must be default constructable");
  static_assert(!std::is_pointer_v<T>, "T must be non-pointer type");

public:
  static SRPair<T> Open() { return {std::make_shared<Fifo>()}; }
};

} // namespace channels

#endif // CHANNEL_H_
