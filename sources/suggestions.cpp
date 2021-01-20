// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>
#include "suggestions.hpp"

#include <algorithm>

suggestionsCollection::suggestionsCollection() { suggestions_ = {}; }
void suggestionsCollection::Update(json storage) {
  std::sort(storage.begin(), storage.end(),
            [](const json& a, const json& b) -> bool {
              return a.at("cost") < b.at("cost");
            });
  suggestions_ = storage;
}
json suggestionsCollection::Suggest(const std::string& input) {
  json result;
  for (size_t i = 0, m = 0; i < suggestions_.size(); ++i) {
    if (input == suggestions_[i].at("id")) {
      json pos;
      pos["text"] = suggestions_[i].at("name");
      pos["position"] = m++;
      result["suggestions"].push_back(pos);
    }
  }
  return result;
}