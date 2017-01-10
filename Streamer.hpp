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
  Streamer() : offset(0) { };
  Streamer(const std::string&, const std::string&);
  Streamer(const Streamer&);
  
  //  ~Streamer(); // disconnect

  // receives from stream and apply callback
  template<class T>
  int recv(T& f) { std::cout << "fake_recv\n"; return -1; }

  int connect(const std::string&, const std::string&);
  int disconnect();
  
private:
  RdKafka::Topic *topic;
  RdKafka::Consumer *consumer;
  int32_t partition = 0;
  uint64_t offset;
  //  size_t message_length;
  
  template<class T>
  int recv_impl(T& f, void*) { };
};


template<> int Streamer::recv<std::function<void(void*)> >(std::function<void(void*)>&);
template<> int Streamer::recv_impl<std::function<void(void*)> >(std::function<void(void*)>&, void*);
