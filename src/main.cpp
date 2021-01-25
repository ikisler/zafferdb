#include <iostream>
#include <string>

#include "Database.h"

int main() {
  std::cout << "HELLO" << std::endl;

  Database db;

  std::cout << "Set value: FIRST, FIRST CONTENT"
            << db.setValue("FIRST", "FIRST CONTENT") << std::endl;
  std::cout << "Set value: SECOND, SECOND CONTENT"
            << db.setValue("SECOND", "SECOND CONTENT") << std::endl;
  std::cout << "Set value: THIRD, THIRD CONTENT"
            << db.setValue("THIRD", "THIRD CONTENT") << std::endl;
  std::cout << "Set value: THIRD, THIRD UPDATED"
            << db.setValue("THIRD", "THIRD UPDATED") << std::endl;

  std::cout << "Get value FIRST: " << db.getValue("FIRST") << std::endl;
  std::cout << "Get value THIRD: " << db.getValue("THIRD") << std::endl;

  std::cout << "Check if FIRST exists..." << db.exists("FIRST") << std::endl;
  std::cout << "Check if NULL exists..." << db.exists("NULL") << std::endl;

  std::cout << "DELETE SECOND" << db.deleteValue("SECOND") << std::endl;
  return 0;
}
