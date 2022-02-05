#include "fifo.h"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace channels {

Fifo::Fifo() : path_("/tmp/channel_" + std::to_string(curr_idx_.fetch_add(1))) {
  if (mkfifo(path_.c_str(), 0666) < 0) {
    std::cerr << std::strerror(errno) << std::endl;
  }
}

Fifo::~Fifo() {
  unlink(path_.c_str());
  curr_idx_.fetch_add(-1);
}

std::string Fifo::GetPath() const { return path_; }

} // namespace channels