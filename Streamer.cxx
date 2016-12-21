#include <Streamer.hpp>
#include <librdkafka/rdkafkacpp.h>

Streamer::Streamer(const std::string& topic_name, const std::string& broker) {

  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  RdKafka::Conf *tconf  = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

  std::string debug,errstr;
  conf->set("metadata.broker.list", broker, errstr);
  if (!debug.empty()) {
    if (conf->set("debug", debug, errstr) != RdKafka::Conf::CONF_OK) {
      throw std::runtime_error("Failed to initialise configuration: "+errstr);
    }
  }

  conf->set("fetch.message.max.bytes", "1000000000", errstr);
  conf->set("receive.message.max.bytes", "1000000000", errstr);

  if(topic_name.empty()) {
    throw std::runtime_error("Topic required");
  }
  
  if ( !(consumer = RdKafka::Consumer::create(conf, errstr)) ) {
    throw std::runtime_error("Failed to create consumer: "+errstr);
  }

  if ( !(topic = RdKafka::Topic::create(consumer, topic_name,tconf, errstr)) ) {
    throw std::runtime_error("Failed to create topic: "+errstr);
  }
  
  // Start consumer for topic+partition at start offset
  RdKafka::ErrorCode resp = consumer->start(topic, partition, RdKafka::Topic::OFFSET_BEGINNING);
  if (resp != RdKafka::ERR_NO_ERROR) {
    throw std::runtime_error("Failed to start consumer: "+RdKafka::err2str(resp));
  }

}

// Streamer::~Streamer() {
//   consumer->stop(topic,partition);
//   delete consumer;
//   delete topic;
//   //  RdKafka::wait_destroyed(5000);
// }

template<>
int Streamer::recv(std::function<void(void*)>& f) {
  bool success = false;
  RdKafka::Message *msg = consumer->consume(topic, partition, 1000);
  if( msg->err() ==  RdKafka::ERR__PARTITION_EOF) {
    std::cout << "eof reached" << std::endl;
    return 0;
  }
  if( msg->err() !=  RdKafka::ERR_NO_ERROR) {
    std::cout << RdKafka::err2str(msg->err()) << std::endl;
    throw std::runtime_error("Failed to consume message: "+RdKafka::err2str(msg->err()));
  }
  success = recv_impl(f,msg->payload());
  return msg->len();
}

template<>
int Streamer::recv_impl(std::function<void(void*)>& f,void* payload) {
  RdKafka::Message *msg = consumer->consume(topic, partition, 10);  
  f(payload);
  return 1;
}

