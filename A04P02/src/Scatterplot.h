//
//  Scatterplot.hpp
//  A03
//
//  Created by Andrea Padula on 2/25/17.
//
//
#pragma once

#include "ofMain.h"

class Scatterplot {
public:
    Scatterplot();
    static ofEvent<vector<bool> > brushedSelection;
    void setup(std::vector<float> column1,std::vector<float> column2,int width, int height, int x, int y,std::string name1,std::string name2);
    void draw();
    void setAxis();
    int maxX,maxY,minY,minX;
    int width, height, x, y;
    vector<float> x_data;
    vector<float> y_data;
    std::string name1, name2;
    ofColor color=ofColor::white;
    ofTrueTypeFont myFont;
    ofTrueTypeFont myFont2;
    void setValue();
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);
    void mouseEntered(ofMouseEventArgs & args);
    void mouseExited(ofMouseEventArgs & args);
    bool inside(float _x, float _y );
    bool onPoint(float x, float y );
    vector<float> tranX;
    vector<float> tranY;
    bool selected, view;
    int index;
    int sx0, sy0,sx1,sy1,sx2, sy2,sx3,sy3;
    std::vector<bool> section;
    int ratio=5;
protected:
    bool bRegisteredEvents;
};
