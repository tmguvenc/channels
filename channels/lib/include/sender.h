#ifndef SENDER_H_
#define SENDER_H_

#include "fifo.h"
#include <fcntl.h>
#include <unistd.h> // for close

namespace channels {

template <typename T> class SenderReceiverPair;

template <typename T> class Sender {
  friend class SenderReceiverPair<T>;
  explicit Sender(FifoPtr fifo_ptr) : fifo_ptr_(fifo_ptr) {
    fd_ = open(fifo_ptr_->GetPath().c_str(), O_RDWR);
  }

public:
  ~Sender() {
    if (fd_ != -1) {
      close(fd_);
    }
  }

  Sender(const Sender &other) noexcept = delete;
  Sender &operator=(const Sender &other) noexcept = delete;
  Sender(Sender &&other) noexcept = delete;
  Sender &operator=(Sender &&other) noexcept = delete;

  int Send(const T &item) { return write(fd_, &item, sizeof(T)); }

private:
  int fd_{-1};
  FifoPtr fifo_ptr_;
};

} // namespace channels

#endif // SENDER_H_
