//
//  TableReader.cpp
//  A03
//
//  Created by Andrea Padula on 2/25/17.
//
//

#include "TableReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void TableReader::read_data(std::string& filename){
    ofFile file;
    file.open(ofToDataPath(filename), ofFile::ReadWrite, false);
    string temp;
    int countLine=0;
    countAtt=0;
    std::vector<string>  t;
    while(getline(file, temp)) {//store the contents of the file in a vector of int
        istringstream iss(temp);
        string token;
        while(std::getline(iss, token, '\t')){
            if(countLine==0){
                t.push_back(token);
                countAtt++;
            }
            else{
                //cout << token << " : newline" << endl;
                //float f=stof((token).c_str(),0);
                if (token.compare("") == 0)    {
                    columnValue.push_back("0");
                }
                else
                    columnValue.push_back(token);
            }
            
        }
        
        
        countLine=countLine+1;
        
    }
    columnName=t;
    return;
}

bool TableReader::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
void TableReader::get_column(int which_column){
    
    int found=0;
    for (int i=which_column; i< columnValue.size(); i=i+countAtt) {
        //temp.push_back(columnValue[i]);
        if (is_number(columnValue[i])){
            
            if(found==2){
                cout<<"error"<<endl;}
            found=1;
            get_columnf(which_column);
        }
        else{
            if(found==1){
                cout<<"error"<<endl;}
            found=2;
            get_columns(which_column);
        }
    }
    
}
bool TableReader::type(int which_column){
    int found=0;
    for (int i=which_column; i< columnValue.size(); i=i+countAtt) {
        if (is_number(columnValue[i])){
            return true;
        }
        else{
            return false;
        }
    }
    
}
std::vector<string> TableReader::get_columns(int which_column){
    if(which_column>countAtt){
        cout<<"error"<<endl;
    }
    std::vector<string> temp;
    
    for (int i=which_column; i< columnValue.size(); i=i+countAtt) {
        temp.push_back(columnValue[i]);
        
    }
    return temp;
}
std::vector<float> TableReader::get_columnf2(int which_column){
    if(which_column>countAtt){
        cout<<"error"<<endl;
    }
    if (type(which_column)) {
        return get_columnf(which_column);
    }
    else{
        std::vector<float> temp;
        for (int i=which_column; i< columnValue.size(); i=i+countAtt) {
            float f=convert((columnValue[i]));
            temp.push_back(f);
            
        }
        return temp;
    
    }
}
float TableReader::convert(string s){
    float result=0;
    for (int i = 0; i < s.length(); i++)
    {
        char x = s[i];
        result=result+x;
    }
    return result;
}
std::vector<float> TableReader::get_columnf(int which_column){
    if(which_column>countAtt){
        cout<<"error"<<endl;
    }
    std::vector<float> temp;
    
    for (int i=which_column; i< columnValue.size(); i=i+countAtt) {
        float f=stof((columnValue[i]).c_str(),0);
        temp.push_back(f);
        
    }
    return temp;
}
std::string TableReader::get_column_name(int which_column){
    return columnName[which_column];
    
}
int TableReader::getAttributesize(){
    return countAtt;
    
}
