#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "fifo.h"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <variant>
#include <unistd.h> // for close

namespace channels {

template<typename T>
using ReceiveResult = std::variant<T, std::string>;

template <typename T> class SenderReceiverPair;

template <typename T> class Receiver {
  friend class SenderReceiverPair<T>;
  explicit Receiver(FifoPtr fifo_ptr) : fifo_ptr_(fifo_ptr) {
    fd_ = open(fifo_ptr_->GetPath().c_str(), O_RDWR);
  }

public:
  ~Receiver() {
    if (fd_ != -1) {
      close(fd_);
    }
  }

  Receiver(const Receiver &other) noexcept = delete;
  Receiver &operator=(const Receiver &other) noexcept = delete;
  Receiver(Receiver &&other) noexcept = delete;
  Receiver &operator=(Receiver &&other) noexcept = delete;

  [[nodiscard]] ReceiveResult<T> Receive() {
    T item{};
    const auto bytes = read(fd_, &item, sizeof(T));
    if (bytes < 0) {
      return std::strerror(errno);
    }
    if (bytes < 0) {
      return "channel closed";
    }
    return item;
  }

private:
  int fd_{-1};
  FifoPtr fifo_ptr_;
};

} // namespace channels

#endif // RECEIVER_H_
