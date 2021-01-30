#include "FileHandler.h"

FileHandler::FileHandler() {}

FileHandler::FileHandler(const FileHandler &fh) { filename = fh.filename; }

FileHandler::FileHandler(FileHandler &&fh) { filename = fh.filename; }

FileHandler &FileHandler::operator=(const FileHandler &fh) {
  filename = fh.filename;
  return *this;
}

FileHandler &FileHandler::operator=(FileHandler &&fh) {
  filename = fh.filename;
  return *this;
}

FileHandler::~FileHandler() {
  if (file.is_open()) {
    file.close();
  }
}

std::fstream *FileHandler::getAppendFile() {
  if (file.is_open()) {
    file.close();
  }
  file.open(filename, std::ios::app);
  return &file;
}

std::fstream *FileHandler::getWriteFile() {
  if (file.is_open()) {
    file.close();
  }

  file.open(filename, std::ios::out);
  return &file;
}

std::fstream *FileHandler::getReadFile() {
  if (file.is_open()) {
    file.close();
  }
  file.open(filename, std::ios::in);
  return &file;
}
