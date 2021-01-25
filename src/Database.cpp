#include "include/Database.h"

#include <openssl/sha.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

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

bool Database::setValue(std::string key, std::string value) {
  std::string hashedKey = sha256(key);

  if (std::filesystem::exists("data.dat")) {
    std::fstream dataFile;
    dataFile.open("data.dat");

    std::ofstream temp;
    temp.open("temp.dat");

    if (!dataFile.is_open() || !temp.is_open()) {
      return false;
    }

    bool updated = false;
    std::string line;
    while (std::getline(dataFile, line, ':')) {
      if (line != hashedKey) {
        temp << line << ":";  // have to make up for the ":" that getline ate
        std::getline(dataFile, line);
        temp << line << "\n";
        continue;
      } else {
        temp << hashedKey << ":::::" << value << "\n";
        std::getline(dataFile, line);
        updated = true;
      }
    }

    if (!updated) {
      dataFile.close();
      std::ofstream dataFile;
      dataFile.open("data.dat", std::ios::app);
      dataFile << hashedKey << ":::::" << value << "\n";
    }

    dataFile.close();
    temp.close();

    if (updated) {
      remove("data.dat");
      rename("temp.dat", "data.dat");
    } else {
      remove("temp.dat");
    }
  } else {
    std::ofstream dataFile;
    dataFile.open("data.dat", std::ios::app);
    if (!dataFile.is_open()) {
      return false;
    }
    dataFile << hashedKey << ":::::" << value << "\n";
    dataFile.close();
  }

  return true;
}

bool Database::deleteValue(std::string key) {
  std::ifstream dataFile;
  dataFile.open("data.dat");

  std::ofstream temp;
  temp.open("temp.dat");

  if (!dataFile.is_open() || !temp.is_open()) {
    return false;
  }

  std::string hashedKey = sha256(key);

  std::string line;
  while (std::getline(dataFile, line, ':')) {
    if (line != hashedKey) {
      temp << line << ":";  // have to make up for the ":" that getline ate
      std::getline(dataFile, line);
      temp << line << "\n";
    } else {
      std::getline(dataFile, line);
    }
  }

  dataFile.close();
  temp.close();

  remove("data.dat");
  rename("temp.dat", "data.dat");

  return true;
}

bool Database::exists(std::string key) {
  std::string hashedKey = sha256(key);

  std::ifstream readFile;
  readFile.open("data.dat");
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
  readFile.open("data.dat");
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
