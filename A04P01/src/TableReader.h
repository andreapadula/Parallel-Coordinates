//
//  TableReader.hpp
//  A03
//
//  Created by Andrea Padula on 2/25/17.
//
//

#pragma once

#include "ofMain.h"

class TableReader {
    
public:
    void read_data(std::string& filename);
    int countAtt=0;
    std::vector<string>  columnName;
    std::vector<string> columnValue;
    bool is_number(const std::string& s);
    void get_column(int which_column);
    std::vector<string> get_columns(int which_column);
    std::vector<float> get_columnf(int which_column);
    std::string get_column_name(int which_column);
    int getAttributesize();
    bool type(int which_column);
};
