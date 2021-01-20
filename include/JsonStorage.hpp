// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>
#ifndef TEMPLATE_JSONSTORAGE_H
#define TEMPLATE_JSONSTORAGE_H
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;

class JsonStorage {
 public:
  explicit JsonStorage(const std::string& filename);
  json get_storage() const;
  void Load();

 private:
  std::string filename_;
  json storage_;
};
#endif  // TEMPLATE_JSONSTORAGE_H
