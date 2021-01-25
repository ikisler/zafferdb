#include <openssl/sha.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Database {
 public:
  bool setValue(std::string key, std::string value);
  bool deleteValue(std::string key);
  bool exists(std::string key);
  std::string getValue(std::string key);

 private:
  std::string sha256(const std::string str);
};
