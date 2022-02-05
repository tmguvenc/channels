#include "channel.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

int main() {
  auto my_pair = channels::Channel<int>::Open();
  my_pair.sender->Send(12);
  std::cout << "sent: 12\n";

  auto rec_thread = std::async([&](){
    auto rec = std::move(my_pair.receiver);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "received: " << rec->Receive() << "\n";
  });

  if(rec_thread.valid()) {
    rec_thread.get();
  }

  return 0;
}