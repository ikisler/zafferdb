# ZafferDB

This project is a simple key-store database.  It contains both a client and a server, which communicate over sockets.  Data values are stored in plain text with hashed keys, rendering it easy to use, import, or export to other projects.

## How to Run
**This project will only run on Ubuntu and Ubuntu-like OSes, including WSL -- it will not run directly on Windows, sorry!**

### Dependencies
- cmake >= 3.7
- make >= 4.1
- gcc/g++ >= 5.4
- OpenSSL is a required dependency.  On my version of Ubuntu, this was installed out of the box.

### Compiling and Running
Clone this repo and `cd` into the directory.
To compile:
```
mkdir build && cd build
cmake .. && make
```
This creates two executables:
- zafferdb
- zafferdb_server

Run the server (zafferdb_server) in one terminal and then run the client (zafferdb) in another.  The client will take input similar to a MySQL client.

### Using the Database
**Values stored in the DB cannot include the double quote `"` or newline `\n` characters!
The maximum total size of the key and the value combined cannot exceed 1025 bytes**

Key name and value must be enclosed in double quote (`"`) characters.

Available commands are:
- `exit`
  - Exits the client program
- `set "key name" "value"`
  - Sets a value for a given key.
- `get "key name"`
  - Gets a value for a given key.
- `exists`
  - Returns if a key exists in the database
- `delete`
  - Deletes a key/value from the database

## Code Structure
- `include/`; contains header files
- `src/`
  - `server.cpp`; code for the server-side interactions, including the actual commands for making database calls
  - `client.ccp`; code for the client-side interactions.  This shares tokenizing and parsing code with the server to ensure that invalid calls never make it to the server.
  - `Tokenizer.cpp`; tokenizes raw strings/string streams into a defined parts "command", "key", "value"
  - `Parser.cpp`; maps tokenized command string into enum defined commands for ease of use in switches, etc.
  - `Database.cpp`; the meat of the project -- handles hashing, saving, deleting, and getting key/value pairs.
  - `Filehandler.cpp`; wrapper for raw file handles to comply with RAII.

## How this Project Meets the Rubric
Criteria:
Loops, Functions, I/O:
  1. The project demonstrates an understanding of C++ functions and control structures.
    - Meets this criteria by using various control structures, including `while` loops, `if/else` statements, and `switch`es, as seen in `server.cpp`, line 81, 84, 100.
  2. The project reads data from a file and process the data, or the program writes data to a file.
    - Meets this criteria by using file as the main system for the DB.  Project both reads and writes to files, as seen in `Database.cpp`, lines 64, 141
  3. The project accepts user input and processes the input.
    - Meets this criteria by taking user commands and parsing it first through a tokenizer, and then a parser, as seen in `client.cpp` 59, 63, 64

Object Oriented Programming:
  1. The project uses Object Oriented Programming techniques.
    - Meets criteria by organizing the project into classes, such as Database, Tokenizer, Parser, and FileHandler.
  2. Classes use appropriate access specifiers for class members.
    - Meets criteria by explicitly setting all class members as public, private, or protected in Database, Tokenizer, Parser, and FileHandler.
  3. Class constructors utilize member initialization lists.
    - Meets criteria in `FileHandler.cpp`, line 14

Memory Management:
  1. The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
    - Meets criteria by using RAII to handle file handle resources, as seen in the `FileHandler` class
  2. The project follows the Rule of 5.
    - Meets criteria by using the Rule of 5 for the FileHandler class:


