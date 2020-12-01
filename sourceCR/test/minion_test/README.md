## Tests for minion program
This utility contains 3 tests for the minion program in ascending difficulty order: test1, test2 and test3.
The tests generates write and read requests for minions using the following UDP protocol:
+ Send to minion:
  + type: 1 byte (0 - read, 1 - write) 
  + uid: 8 bytes (with network endianess)
  + block index: 8 bytes (with network endianess)
  + In case of write request - Data (4kb)

+ Reply from minion:
  + type: 1 byte (0 - read, 1 - write) 
  + uid: 8 bytes (with network endianess)
  + status: 1 byte
  + In case of read request - Data (4kb)


### Notes:
+ You should run your minion program before running the test.
+ All tests receive the minion IP address and port number as command line parameters. (for example: ./test1 127.0.0.1 12345).
+ If you fail in the test as a result of data corruption,
  you can compare your data block to the expected data block using the following command:
  ```cmd
    diff <(xxd your minion's block file) <(xxd the test's block file)
  
  ```
    Note: The test's blocks files are generated inside blocks directory.