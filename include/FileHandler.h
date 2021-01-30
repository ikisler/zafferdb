#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class FileHandler {
 public:
  FileHandler();
  FileHandler(const std::string &file) : filename{file} {}
  FileHandler(const FileHandler &fh);
  FileHandler(FileHandler &&fh);
  FileHandler &operator=(const FileHandler &fh);
  FileHandler &operator=(FileHandler &&fh);
  ~FileHandler();
  std::fstream *getAppendFile();
  std::fstream *getWriteFile();
  std::fstream *getReadFile();

 private:
  std::string filename;
  std::fstream file;
};

#endif
