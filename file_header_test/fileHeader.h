#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include <cctype>
using namespace std;


struct FileHeader {

    FileHeader();
    FileHeader(string);

    string          file_extension{};
    vector<uint8_t> header_byte_array{};
    vector<uint8_t> footer_byte_array{};
    int             max_carve_size{};

    void import_header_byte_array(string);
    void import_footer_byte_array(string);
    uint8_t convert_hex(string&);
    void print_header_info();
};