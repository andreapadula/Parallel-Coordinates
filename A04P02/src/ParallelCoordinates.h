/* ParallelCoordinates_hpp */
//
//  A04
//
//  Created by Andrea Padula on 2/25/17.
//
//
#pragma once

#include "ofMain.h"
#include "TableReader.h"
#include "Scatterplot.h"
#include "ofxGui.h"
#include "Data.h"

class ParallelCoordinates {
public:
    static ofEvent<vector<bool> > brushedSelection;
    void setup(TableReader table,int width, int height, int x, int y);
    int convert(string s);
    void rangeString(int c);
    void draw();
    void setAxis();
    int width, height, x, y;
    void setValue();
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);
    void mouseEntered(ofMouseEventArgs & args);
    void mouseExited(ofMouseEventArgs & args);
    void range(std::vector<float> v);
    bool inside2(float _x, float _y );
    ofTrueTypeFont myFont;
    ofTrueTypeFont myFont2;
    TableReader table;
    int max, min;
    std::vector<vector<Data>> data;
    std::vector<string> names;
    std::vector<tuple<float,float>> r;
    std::vector<ofRectangle> rectButton;
    std::vector<ofRectangle> rectButton2;
    std::vector<bool> flip;
    void swap(int i);
    bool inside(float _x, float _y );
    float sx0,sx1,sy1,sy0;
    std::vector<vector<bool>> sections;
    std::vector<bool> section;
    std::vector<vector<float>> points;
    bool selected;
    void reset();
    bool inRange(float v,float max,float min);
    std::vector<tuple<float,float,float,float>> bar;
    float recY2=680.0f;
    float recY=80.0f;
    int h;
    int click1=4,click2=5;
    bool sw=false;
    std::string split(string s);
    Scatterplot s;
    void setupString(int space, int cols, int n, int n2);
    int clickx, clicky;
    std::vector<float> get_vector(int which_column);
};
