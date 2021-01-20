// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>

#include "JsonStorage.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

JsonStorage::JsonStorage(const std::string& filename) : filename_(filename) {}
json JsonStorage::get_storage() const { return storage_; }
void JsonStorage::Load() {
  try {
    std::ifstream in(filename_);
    in >> storage_;
  } catch (const std::exception& exception) {
    std::cout << exception.what() << std::endl;
  }
}
