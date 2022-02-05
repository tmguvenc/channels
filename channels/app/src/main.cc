#include "channel.h"
#include <cassert>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
  auto my_pair = channels::Channel<int>::Open();
  auto rec_thread = std::async([&]() {
    auto rec = std::move(my_pair.receiver);
    std::visit(overloaded{[&](const std::string &err) {
                            std::cerr << err << std::endl;
                          },
                          [&](const int received_data) {
                            std::cerr << "received: " << received_data
                                      << std::endl;
                          },
                          [&](const channels::Timeout & /*timeout*/) {
                            std::cerr << "timeout!" << std::endl;
                          }},
               rec->ReceiveTimeout(1100));
  });

  std::cout << "waiting for data\n";

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  if (const auto ret = my_pair.sender->Send(12); ret.has_value()) {
    std::cerr << *ret << std::endl;
  } else {
    std::cout << "sent: 12\n";
  }

  if (rec_thread.valid()) {
    rec_thread.get();
  }

  return 0;
}