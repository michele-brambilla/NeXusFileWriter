# NeXus File Writer

The overall design of the file writer is described in [NeXusFileWriterDesign](NeXusFileWriterDesign.md) (Mark). It is used as a sort of "guideline". A pictorial representation of the implementation is ![File Writer overall design](FileWriter.jpg)

## Streamer

According to the design the Streamer connects to Kafka (other
sources to be implemented) and consumes a message in the specified topic. Some features:
* one Streamer per topic
* (eventually) multiple Source per streamer
* acts according the function ```f( msg->payload() )``` specified in ```recv(f)```
* has to be able to search back in the kafka queue for the first message. Some
  slow sources can be (much) older than the DAQ starts and updated not
  frequently, we must be able to retrieve the
  informations. ```search_backward(f)``` implements some algorithm that uses the
  function ```f``` to find the older message with good timestamp. Different
  sources can have data in different point of the queue: Source has to discard
  invalid (according to timestamp) data
* if the broker is not valid (_e.g._ a change of IP address) it should notify
  the FileMaster, retrieve the new configuration and reconnect

## Source

## StreamMaster


## Running tests

Usage:
```bash
   tests/streamer_test --kafka_broker=<broker>:<port>  --kafka_topic="<topic name>"
   ```
Tests are implemented using the gtest suite. They support all the command
line option provided by gtest.
