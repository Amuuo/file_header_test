#pragma once
#include <cstdio>
#include <map>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include "fileHeader.h"

using namespace std;
typedef unsigned long long disk_pos;

struct PatternMatcher {

  PatternMatcher() {}
  PatternMatcher(const vector<FileHeader>&);

  vector<FileHeader>            patterns;
  map<int, map<uint8_t, int>>   go_to{};
  map<int, vector<uint8_t>>     output{};
  vector<list<uint8_t>>         positions{};
  vector<uint8_t>               failure{};

  void create_goto(const vector<FileHeader>& patterns);
  void create_failure();
  void find_matches(uint8_t*, disk_pos);
};
