#include "main.h"


vector<FileHeader> patterns;

enum matches{MATCH_EXTENSION=1, 
             MATCH_HEADER, 
             MATCH_FOOTER, 
             MATCH_MAX_SIZE };




int main(){

  ifstream       header_file;
  string         current_line;  
  
  // regex to parse the file signature file
  regex regex_pattern { 
    "([[:w:]]+)[[:s:]]+"
    "\\[[[:s:]]((?:[[:xdigit:]]{2}[[:s:]])+)\\][[:s:]]*"
    "(?:\\[[[:s:]]((?:[[:xdigit:]]{2}[[:s:]])+)\\][[:s:]]*)?"
    "([[:digit:]]+)[[:s:]]*"    
  };
  smatch regex_matches{};
  header_file.open("file_headers.txt");
  getline(header_file, current_line);

  while (!header_file.eof())
  {
    getline(header_file, current_line);
    regex_search(current_line, regex_matches, regex_pattern);    
    
    if (regex_matches[MATCH_EXTENSION].matched) {
      patterns.push_back(regex_matches[MATCH_EXTENSION].str());
      if (regex_matches[MATCH_HEADER].matched) {
        patterns.back().import_header_byte_array(regex_matches[MATCH_HEADER].str());
        if (regex_matches[MATCH_FOOTER].matched)
          patterns.back().import_footer_byte_array(regex_matches[MATCH_FOOTER].str());        
        if (regex_matches[MATCH_MAX_SIZE].matched)
          patterns.back().max_carve_size = stol(regex_matches[MATCH_MAX_SIZE].str());
        else {
          cerr << "Error with max size formatting. Exiting..." << endl;
          exit(1);
        }
      } else {
        cerr << "Error with header signature formatting. Exiting..." << endl;
        exit(1);
      }      
    }
  }
  for (auto header : patterns) 
    header.print_header_info();
    
  ifstream testFile{"testinput.txt"};
  vector<uint8_t> test_array;
  uint8_t current_byte;
  
  while (!testFile.eof()) {
    
    testFile >> setw(2) >> setfill('0') >> hex >> current_byte;
    
    if (current_byte != '\n')
      test_array.push_back(current_byte);    
  }

  PatternMatcher PM{patterns};
  PM.find_matches(&test_array[0], test_array.size());

  for (int i = 0; i < PM.positions.size(); i++)
  {
    cout << endl << patterns[i].file_extension << ": "; 
    //PM.positions
    for (auto header : patterns[i].header_byte_array) {
      cout << hex <<setw(2) << setfill('0') << (int)header << " ";      
    }        
    cout << endl;
    for (auto itr = PM.positions[i].begin(); itr != PM.positions[i].end(); ++itr)
      cout << "\t-" << dec << (int)* itr - (patterns[i].header_byte_array.size() - 1) << endl;      
    cout << endl;
  }
  return 0;
}