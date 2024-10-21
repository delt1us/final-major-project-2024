/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-06 18:13:30
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-06 18:50:24
 */

#include "debug.h"
#include "raylib.h"
#include <string>

std::vector<std::string *> Debug::stringPointers;

void Debug::AddStringToDebugDisplay(std::string *pString) {
  stringPointers.push_back(pString);
}

void Debug::RemoveStringFromDebugDisplay(std::string *pString) {
  for (int i = 0; i < stringPointers.size(); i++) {
    if (stringPointers[i] == pString) {
      stringPointers.erase(std::next(stringPointers.begin(), i));
      break;
    }
  }
}

void Debug::Draw() {
  int count = 0;
  for (const std::string *pString : stringPointers) {
    if (pString != nullptr) {
      count++;
      DrawText(pString->c_str(), 0, count * 22, 20, GRAY);
    }
  }
}
