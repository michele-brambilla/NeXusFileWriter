# NeXus File Writer

Initial implementation and tests.




## Streamer

    According to the design the _Streamer_ connects to Kafka (other
    sources to be implemented) and consumes a message in the specified topic. It
    acts according to the function passed as argument (the idea is that the
    function is defined in StreamMaster)


## Running tests

    Usage:
    ```bash
        tests/streamer_test --kafka_broker=<broker>:<port>  --kafka_topic="<topic
        name>"```
    Tests are implemented using the gtest suite. They support all the command
    line option provided by gtest.
