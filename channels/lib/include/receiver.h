#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "fifo.h"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h> // for close

namespace channels {

template <typename T> class SenderReceiverPair;

template <typename T> class Receiver {
  friend class SenderReceiverPair<T>;
  explicit Receiver(FifoPtr fifo_ptr) : fifo_ptr_(fifo_ptr) {
    fd_ = open(fifo_ptr_->GetPath().c_str(), O_RDWR);

    if (fd_ == -1) {
      std::cerr << std::strerror(errno) << std::endl;
    }
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

  T Receive() {
    T item{};
    if (read(fd_, &item, sizeof(T)) < 0) {
      std::cerr << std::strerror(errno) << std::endl;
    }
    return item;
  }

private:
  int fd_{-1};
  FifoPtr fifo_ptr_;
};

} // namespace channels

#endif // RECEIVER_H_
