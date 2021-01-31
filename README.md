# ZafferDB

This project is a simple key-store database.  It contains both a client and a server, which communicate over sockets.  Data is stored in plain text, rendering it easy to use, import, or export to other projects.

## How to Run
### Dependencies

### Compiling and Running

## Code Structure


## How this Project Meets the Rubric
Criteria:
> The project demonstrates an understanding of C++ functions and control structures.
Meets this criteria by using various control structures, includling `while` loops, `if/else` statements, as seen in te code links below:


> The project reads data from a file and process the data, or the program writes data to a file.
Meets this criteria by using file as the main system for the DB.  Project both reads and writes to files, as seen here:

> The project accepts user input and processes the input.
Meets this criteria by taking user commands and parsing it first through a tokenizer, and then a parser, as seen here:

> The project uses Object Oriented Programming techniques.
Meets criteria by organizing the project into classes, such as Database, Tokenizer, and FileHandler, as linked below:

> The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
Meets criteria by using RAII to handle file handle resources, as seen in the FileHandler class:

> The project follows the Rule of 5.
Meets criteria by using the Rule of 5 for the FileHandler class:


