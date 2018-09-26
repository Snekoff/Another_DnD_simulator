

#include "WorkWithJson.h"

bool WorkWithJson::Write_(int what_) {
  // создаём пустой JSON-объект
  json j;
  // добавляем строку, которая будет храниться как std::string
  j["name"] = "Habrahabr";
  // добавляем пустой вложенный объект
  j["nothing"] = nullptr;
  // число внутри вложенного объекта
  j["answer"]["everything"] = what_;
  // добавляем массив строк (будет храниться как std::vector<std::string>)
// обратите внимание - используются списки инициализации
  j["companies"] = { "Infopulse", "TM" };
  // добавляем ещё один объект - на этот раз используем список инициализации с парами "ключ"-"значение"
  j["user"] = { {"name", "tangro"}, {"active", true} };

  // создание объекта из строкового литерала
  json j1 = "{ \"active\": true, \"pi\": 3.141 }"_json;


// использование raw string
  json j2 = R"(
  {
    "active": true,
    "pi": 3.141
  }
)"_json;


// использование auto
  auto j3 = json::parse("{ \"active\": true, \"pi\": 3.141 }");

  //read
  std::ifstream inp("E:\\Den`s\\programming\\Git_c++\\Another_DnD_simulator\\MyJson1.json");
  json j4 = json::parse(inp);

// использование range-based for
  for (auto element : j4) {
    std::cout << element << '\n';
  }
  std::ofstream outp;
  outp.open("E:\\Den`s\\programming\\Git_c++\\Another_DnD_simulator\\MyJson.json", std::ofstream::out);
  outp << j4;
  outp.close();
  return true;
}