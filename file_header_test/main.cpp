#include "main.h"



int main()
{
  PatternMatcher matcher;

  // import signatures from file named "file_headers.txt"
  matcher.import_file_signatures_and_setup_patterns();
  matcher.test_input_for_matches("testinput.txt");
}


