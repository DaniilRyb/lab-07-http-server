// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class suggestionsCollection {
 public:
  suggestionsCollection();
  void Update(json storage);
  json Suggest(const std::string& input);

 private:
  json suggestions_;
};
#endif  // INCLUDE_HEADER_HPP_
