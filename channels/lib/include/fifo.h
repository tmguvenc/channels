#ifndef FIFO_H_
#define FIFO_H_

#include <atomic>
#include <memory>
#include <string>

namespace channels {

class Fifo {
public:
  Fifo();
  ~Fifo();

  std::string GetPath() const;

  Fifo(const Fifo &other) noexcept = delete;
  Fifo &operator=(const Fifo &other) noexcept = delete;
  Fifo(Fifo &&other) noexcept = delete;
  Fifo &operator=(Fifo &&other) noexcept = delete;

private:
  std::atomic_uint32_t curr_idx_{1};
  std::string path_;
};

using FifoPtr = std::shared_ptr<Fifo>;

} // namespace channels

#endif // FIFO_H_
