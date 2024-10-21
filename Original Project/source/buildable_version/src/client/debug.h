/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-06 18:13:42
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-06 18:44:30
 */

#pragma once

#include <string>
#include <vector>

class Debug {
public:
  static void AddStringToDebugDisplay(std::string *pString);
  static void RemoveStringFromDebugDisplay(std::string *pString);
  static void Draw();

private:
  static std::vector<std::string *> stringPointers;
};
