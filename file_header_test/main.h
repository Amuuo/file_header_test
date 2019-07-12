#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <locale.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <array>
#include <atomic>
#include <condition_variable>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <utility>
#include <functional>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <memory>
#include "patternMatcher.h"
#include <regex>
#include "func.h"




using namespace std;

enum matches {
  MATCH_EXTENSION = 1,
  MATCH_HEADER,
  MATCH_FOOTER,
  MATCH_MAX_SIZE
};

vector<FileHeader> patterns;

// regex to parse the file signature file
regex regex_pattern{
  "([[:w:]]+)[[:s:]]+\\[[[:s:]]((?:[[:xdigit:]]{2}"
  "[[:s:]])+)\\][[:s:]]*(?:\\[[[:s:]]((?:[[:xdigit:]]{2}[[:s:]])+)"
  "\\][[:s:]]*)?([[:digit:]]+)[[:s:]]*"
};



void check_for_matches(smatch&);
void get_file_signatures_from_file();
void test_input_for_matches(const char*);
