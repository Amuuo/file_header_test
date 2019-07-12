#include "main.h"




int main()
{
  get_file_signatures_from_file();
  test_input_for_matches("testinput.txt");
}




void get_file_signatures_from_file()
{
  ifstream    header_file{ "file_headers.txt" };
  string      current_line;
  smatch      regex_matches{};  

  while (header_file.good()) {

    getline(header_file, current_line);
    regex_search(current_line, regex_matches, regex_pattern);

    check_for_matches(regex_matches);
  }
  // print matches
  for (auto header : patterns)
    header.print_header_info();
}




void check_for_matches(smatch& regex_matches) {

  if (regex_matches[EXTENSION].matched) {
    patterns.push_back(regex_matches[EXTENSION].str());
    if (regex_matches[HEADER].matched) {
      patterns.back().import_header_byte_array(regex_matches[HEADER].str());
      if (regex_matches[FOOTER].matched) 
        patterns.back().import_footer_byte_array(regex_matches[FOOTER].str());
      if (regex_matches[MAX_SIZE].matched) 
        patterns.back().max_carve_size = stol(regex_matches[MAX_SIZE].str());
      else {
        cerr << "Error with max size formatting. Exiting..." << endl;
        exit(1);
      }
    }
    else {
      cerr << "Error with header signature formatting. Exiting..." << endl;
      exit(1);
    }
  }
}




void test_input_for_matches(const char* input_file)
{
  char            current_byte;
  ifstream        testFile{ input_file, ios::ate }; // open to EOF to get size
  PatternMatcher  PM{ patterns };
  
  auto file_size = testFile.tellg();
  
  // allocate array of filesize  
  uint8_t* test_array = new uint8_t[file_size];
  testFile.seekg(0, testFile.beg);
  
  // copy file into array
  testFile.read((char*)test_array, file_size);

  PM.find_matches(test_array, file_size);

  for (int i = 0; i < PM.positions.size(); i++) {
    printf("\n%s: ", patterns[i].file_extension.c_str());
    
    for (auto header : patterns[i].header_byte_array)
      printf("%-02x ", static_cast<int>(header));    
    cout << endl;
    
    for (auto itr =  PM.positions[i].begin(); itr != PM.positions[i].end(); ++itr)
      printf("\t-%d\n", static_cast<int>(*itr) - (patterns[i].header_byte_array.size() - 1));        
    cout << endl;
  }
}
