#include <iostream>
#include <fstream>
#include "json_nlohmann/single_include/nlohmann/json.hpp"

#ifndef ANOTHER_DND_SIMULATOR_WORKWITHJSON_H
#define ANOTHER_DND_SIMULATOR_WORKWITHJSON_H

using json = nlohmann::json;

class WorkWithJson {
 private:
  int what;
 public:
  WorkWithJson() = default;
  bool Write_(int what_);

};

#endif //ANOTHER_DND_SIMULATOR_WORKWITHJSON_H
