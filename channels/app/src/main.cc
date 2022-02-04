#include <iostream>
#include "channel.h"

int main() { 
  auto [sender, receiver] = channels::Channel<int>::Open();
  
  return 0; 
}