#include "Parser.h"

Command Parser::parse(Tokenizer::Token token) {
  Command cmd;
  bool keyIsValid = !token.key.empty();

  if (token.command == "exit") {
    cmd = Command::exit;
  } else if (token.command == "set" && keyIsValid) {
    cmd = Command::set;
  } else if (token.command == "get" && keyIsValid) {
    cmd = Command::get;
  } else if (token.command == "exists" && keyIsValid) {
    cmd = Command::exists;
  } else if (token.command == "delete" && keyIsValid) {
    cmd = Command::remove;
  } else {
    cmd = Command::invalid;
  }

  return cmd;
}
