#pragma once

#include <iostream>
#include <string>
#include <functional>

//#include "ScopeGuard.hpp"

// forward definitions
namespace RdKafka {
  class Topic;
  class Consumer;
}


// actually a "kafka streamer"
class Streamer {
public:
  Streamer(const std::string& topic, const std::string& server);
  Streamer(const Streamer& other); // MISSING
  //  ~Streamer(); // disconnect

  // receives from stream and apply callback
  template<class T>
  int recv(T& f) { std::cout << "fake_recv\n"; return -1; }
  
private:
  RdKafka::Topic *topic;
  RdKafka::Consumer *consumer;
  int32_t partition = 0;
  
  template<class T>
  int recv_impl(T& f, void*) { };
};



template<> int Streamer::recv<std::function<void(void*)> >(std::function<void(void*)>&);
template<> int Streamer::recv_impl<std::function<void(void*)> >(std::function<void(void*)>&, void*);
