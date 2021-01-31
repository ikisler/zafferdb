#include <iostream>
#include <limits>
#include <string>

#include "Database.h"
#include "Tokenizer.h"

int main() {
  Database db;

  std::cout << "ZafferDB" << std::endl;
  std::cout << "Created by Isabeau Kisler, 2021" << std::endl;
  std::cout << std::endl;

  std::string command;
  std::string key;
  std::string value;

  Tokenizer tokenizer;

  while (true) {
    std::cout << "zafferdb> ";

    Tokenizer::Token token = tokenizer.tokenizeInput(std::cin);

    std::cout << token.command << std::endl;
    std::cout << token.key << std::endl;
    std::cout << token.value << std::endl;

    if (token.command == "exit") {
      std::cout << std::endl << "Adieu" << std::endl;
      break;
    }
  }
  return 0;

  std::cout << "Set value: FIRST, FIRST CONTENT"
            << db.setValue("FIRST", "FIRST CONTENT") << std::endl;
  std::cout << "Set value: SECOND, SECOND CONTENT"
            << db.setValue("SECOND", "SECOND CONTENT") << std::endl;
  std::cout << "Set value: THIRD, THIRD CONTENT"
            << db.setValue("THIRD", "THIRD CONTENT") << std::endl;
  std::cout << "Set value: THIRD, THIRD UPDATED"
            << db.setValue("THIRD", "THIRD UPDATED") << std::endl;

  std::cout << "Get value FIRST: " << db.getValue("FIRST") << std::endl;
  std::cout << "Get value THIRD: " << db.getValue("THIRD") << std::endl;

  std::cout << "Check if FIRST exists..." << db.exists("FIRST") << std::endl;
  std::cout << "Check if NULL exists..." << db.exists("NULL") << std::endl;

  std::cout << "DELETE SECOND" << db.deleteValue("SECOND") << std::endl;
  return 0;
}
