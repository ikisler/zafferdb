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
  std::string getValueForStorage(std::string hashedKey, std::string value);
  bool createFileAndAddValue(std::string hashedKey, std::string value);
  bool setValueInFile(std::string hashedKey, std::string value);
  const std::string DATA_FILE_NAME = "data.dat";
  const std::string TEMP_FILE_NAME = "temp.dat";
};
