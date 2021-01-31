#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

class Tokenizer {
 public:
  struct Token {
    std::string command;
    std::string key;
    std::string value;
  };
  Token tokenizeInput(std::istream &stream);
};

#endif
