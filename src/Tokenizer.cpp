#include "Tokenizer.h"

Tokenizer::Token Tokenizer::tokenizeInput(std::istream &stream) {
  std::string out;
  Token token;
  std::string key;
  stream >> std::skipws >> token.command;

  std::getline(stream, out, '\n');
  if (out == "") {
    return token;
  }

  std::istringstream linestream(out);
  // ignores any whitespace between command and key start
  linestream.ignore(std::numeric_limits<std::streamsize>::max(), '"');
  std::getline(linestream, token.key, '"');

  // ignores any whitespace between command and value start
  linestream.ignore(std::numeric_limits<std::streamsize>::max(), '"');
  std::getline(linestream, token.value, '"');

  return token;
}
