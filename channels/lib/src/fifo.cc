#include "fifo.h"
#include <atomic>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

std::atomic_uint32_t gCurrentFifoIdx{1};

namespace channels {

Fifo::Fifo() {
  path_ = "/tmp/channel_" + std::to_string(gCurrentFifoIdx.fetch_add(1));
  mkfifo(path_.c_str(), 0666);
}

Fifo::~Fifo() {
  unlink(path_.c_str());
  gCurrentFifoIdx.fetch_add(-1);
}

std::string Fifo::GetPath() const {
  return path_;
}

} // namespace channels