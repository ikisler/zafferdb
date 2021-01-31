#ifndef PARSER_H_
#define PARSER_H_

#include "Tokenizer.h"

enum class Command { exit, set, get, exists, remove, invalid };

class Parser {
 public:
  Command parse(Tokenizer::Token token);
};

#endif
