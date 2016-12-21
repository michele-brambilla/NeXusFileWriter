#include <gtest/gtest.h>
#include <algorithm>
#include <stdexcept>

#include <Streamer.hpp>

std::string broker;
std::string topic("test");

struct MockConsumer {
  static void process_data(void* data) {
    data_size = sizeof(*static_cast<int64_t*>(data));
  }
  static int data_size;
};
int MockConsumer::data_size=0;

TEST (Streamer, MissingTopicFailure) {
  ASSERT_THROW(Streamer(std::string(""),std::string("data_server:1234")),std::runtime_error);
}

TEST (Streamer, ConstructionSuccess) {
  ASSERT_NO_THROW(Streamer(topic,broker));
}

TEST (Streamer, Receive) {
  Streamer s(topic,broker);
  int f;
  ASSERT_EQ( s.recv(f) , -1) ;
  
  std::function<void(void*)> f1 = [](void*) { std::cout << "hello!" << std::endl; };
  ASSERT_NE( s.recv(f1), -1);

  MockConsumer m;
  s.recv(m.process_data);
  ASSERT_GT(m.data_size,0);
}



int main(int argc, char **argv) {


  ::testing::InitGoogleTest(&argc, argv);
  for(int i=1;i<argc;++i) {
    std::string opt(argv[i]);
    size_t found = opt.find("=");
    if( opt.substr(0,found) == "--kafka_broker")
      broker = opt.substr(found+1);
    if( opt.substr(0,found) ==  "--kafka_topic")
      topic = opt.substr(found+1);
    if( opt.substr(0,found) ==  "--help" ) {
      std::cout << "\nOptions: " << "\n"
                << "\t--kafka_broker=<host>:<port>[default = 9092]\n"
                << "\t--kafka_topic=<topic>\n";
    }

  }

  
  return RUN_ALL_TESTS();
}
