#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <fcntl.h>
#include <unistd.h>  // for close
#include "fifo.h"

namespace channels {

template<typename T>
class Channel;

template<typename T>
class Receiver {
  friend class Channel<T>;
  explicit Receiver(FifoPtr fifo_ptr)
  : fifo_ptr_(std::move(fifo_ptr)) {
    fd_ = open(fifo_ptr->GetPath().c_str(), O_RDWR);
  }

public:
  ~Receiver() {
    if(fd_ != -1) {
      close(fd_);
    }
  }

  T Receive() {
    T item{};
    read(fd_, &item, sizeof(T));
    return item;
  }

private:
  int fd_{-1};
  FifoPtr fifo_ptr_;
};

} // namespace channels

#endif // RECEIVER_H_
