#include <iostream>
#include <limits>
#include <string>

#include "Database.h"
#include "Parser.h"
#include "Tokenizer.h"

void simpleOutputHandler(bool success) {
  std::cout << (success ? "Success!" : "Failure") << std::endl;
}

int main() {
  Database db;

  std::cout << "ZafferDB" << std::endl;
  std::cout << "Created by Isabeau Kisler, 2021" << std::endl;
  std::cout << std::endl;

  std::string command;
  std::string key;
  std::string value;

  Tokenizer tokenizer;
  Parser parser;
  bool success;

  while (true) {
    std::cout << "zafferdb> ";

    Tokenizer::Token token = tokenizer.tokenizeInput(std::cin);

    Command command = parser.parse(token);

    switch (command) {
      case Command::exit:
        std::cout << std::endl << "Adieu" << std::endl;
        return 0;
      case Command::set:
        success = db.setValue(token.key, token.value);
        simpleOutputHandler(success);
        break;
      case Command::get:
        std::cout << db.getValue(token.key) << std::endl;
        break;
      case Command::exists:
        success = db.exists(token.key);
        simpleOutputHandler(success);
        break;
      case Command::remove:
        success = db.deleteValue(token.key);
        simpleOutputHandler(success);
        break;
      case Command::invalid:
        std::cout << "Invalid command" << std::endl;
        break;
    }
  }
  return 0;
}
