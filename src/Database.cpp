#include "FileHandler.h"
#include "Database.h"

#include <openssl/sha.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

Database::Database()
{
  dataFile = FileHandler(Database::DATA_FILE_NAME);
  tempFile = FileHandler(Database::TEMP_FILE_NAME);
}

// https://stackoverflow.com/a/10632725
std::string Database::sha256(const std::string str) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return ss.str();
}

std::string Database::getValueForStorage(std::string hashedKey, std::string value)
{
  return hashedKey + ":::::" + value;
}

bool Database::createFileAndAddValue(std::string hashedKey, std::string value)
{
    std::ofstream dataFile;
    dataFile.open(Database::DATA_FILE_NAME.c_str(), std::ios::app);
    if (!dataFile.is_open()) {
      return false;
    }
    dataFile << getValueForStorage(hashedKey, value) << std::endl;
    dataFile.close();
    return true;
}

bool Database::setValueInFile(std::string hashedKey, std::string value)
{
    std::fstream dataFile;
    dataFile.open(Database::DATA_FILE_NAME.c_str());

    std::ofstream temp;
    temp.open(Database::TEMP_FILE_NAME.c_str());

    if (!dataFile.is_open() || !temp.is_open()) {
      return false;
    }

    bool updated = false;
    std::string line;
    while (std::getline(dataFile, line, ':')) {
      if (line != hashedKey) {
        temp << line << ":";  // have to make up for the ":" that getline ate
        std::getline(dataFile, line); // get the rest of the data for this line and pipe it in too
        temp << line << std::endl;
        continue;
      } else {
        temp << getValueForStorage(hashedKey, value) << std::endl;
        std::getline(dataFile, line);
        updated = true;
      }
    }

    if (!updated) {
      dataFile.close();
      std::ofstream dataFile;
      dataFile.open(Database::DATA_FILE_NAME.c_str(), std::ios::app);
      dataFile << getValueForStorage(hashedKey, value) << std::endl;
    }

    dataFile.close();
    temp.close();

    if (updated) {
      remove(Database::DATA_FILE_NAME.c_str());
      rename(Database::TEMP_FILE_NAME.c_str(), Database::DATA_FILE_NAME.c_str());
    } else {
      remove(Database::TEMP_FILE_NAME.c_str());
    }
    return true;
}

bool Database::setValue(std::string key, std::string value) {
  std::string hashedKey = sha256(key);

  if (std::filesystem::exists(Database::DATA_FILE_NAME.c_str())) {
    setValueInFile(hashedKey, value);
  } else {
    return createFileAndAddValue(hashedKey, value);
  }

  return true;
}

bool Database::deleteValue(std::string key) {
  std::ifstream dataFile;
  dataFile.open(Database::DATA_FILE_NAME.c_str());

  std::ofstream temp;
  temp.open(Database::TEMP_FILE_NAME.c_str());

  if (!dataFile.is_open() || !temp.is_open()) {
    return false;
  }

  std::string hashedKey = sha256(key);

  std::string line;
  while (std::getline(dataFile, line, ':')) {
    if (line != hashedKey) {
      temp << line << ":";  // have to make up for the ":" that getline ate
      std::getline(dataFile, line);
      temp << line << std::endl;
    } else {
      std::getline(dataFile, line);
    }
  }

  dataFile.close();
  temp.close();

  remove(Database::DATA_FILE_NAME.c_str());
  rename(Database::TEMP_FILE_NAME.c_str(), Database::DATA_FILE_NAME.c_str());

  return true;
}

bool Database::exists(std::string key) {
  std::string hashedKey = sha256(key);

  std::ifstream readFile;
  readFile.open(Database::DATA_FILE_NAME.c_str());
  if (!readFile.is_open()) {
    return "";
  }

  std::string line;
  while (std::getline(readFile, line, ':')) {
    if (line != hashedKey) {
      std::getline(readFile, line);
    } else {
      readFile.close();
      return true;
    }
  }

  readFile.close();

  return false;
}

std::string Database::getValue(std::string key) {
  std::string hashedKey = sha256(key);

  std::ifstream readFile;
  readFile.open(Database::DATA_FILE_NAME.c_str());
  if (!readFile.is_open()) {
    return "";
  }

  std::string line;
  while (std::getline(readFile, line, ':')) {
    if (line != hashedKey) {
      std::getline(readFile, line);
      continue;
    }

    std::getline(readFile, line, ':');
    std::getline(readFile, line, ':');
    std::getline(readFile, line, ':');
    std::getline(readFile, line, ':');

    std::getline(readFile, line);
    break;
  }

  readFile.close();
  return line;
}
