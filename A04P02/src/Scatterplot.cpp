//
//  Scatterplot.cpp
//  A03
//
//  Created by Andrea Padula on 2/25/17.
//
//

#include "Scatterplot.h"
bool f=false;
ofEvent<vector<bool> > Scatterplot::brushedSelection = ofEvent<vector<bool> >();
Scatterplot::Scatterplot() {
    bRegisteredEvents = false;
    myFont.load("verdana.ttf", 8, true, true); //set the font
}

void Scatterplot::setup(std::vector<float> column1,std::vector<float> column2,int width, int height, int x, int y,std::string name1,std::string name2){
    //section.clear();
    tranX.clear();
    tranY.clear();
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->name1=name1;
    this->name2=name2;
    this->x_data=column1;
    this->y_data=column2;
    this-> maxX= *max_element(x_data.begin(), x_data.end())+1;
    this-> minX= *min_element(x_data.begin(), x_data.end())-1;
    this-> maxY= *max_element(y_data.begin(), y_data.end())+1;
    this-> minY= *min_element(y_data.begin(), y_data.end())-1;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our Canvas class to listen to the mouse events.
        bRegisteredEvents = true;
    }
    //if(f==false){
    for(int i=0; i<x_data.size(); i++) {
        section.push_back(false);
    }
//        f=true;
//    }
    for (int i=0; i<x_data.size(); i++) {
        int x1 ,y1 =0;
        
        x1 = ofMap(x_data[i], minX, maxX, 0, width);
        y1 = ofMap(y_data[i], minY, maxY, 0, height);
        tranX.push_back(x1);
        tranY.push_back(y1);
    }
}

void Scatterplot::setAxis(){
    float mx,my=0;
    ofPushMatrix();
    ofTranslate(x,y);
    ofSetColor(211,211,211);
    ofSetLineWidth(0.5);
    int space=height/ratio;
    int space2=height;
    float value=((float)maxY-float(my))/ratio;
    float t=my;
    for (int i=0; i<=ratio; i++) {
        
        stringstream stream;
        stream << fixed << setprecision(1) << t;
        string s;
        if(t<999){
            stream << fixed << setprecision(1) << t;
            s = stream.str();}
        else{
            stream << fixed << setprecision(0) << t;
            s = stream.str();
        }
        ofSetColor(211,211,211);
        ofDrawLine(width, space2,0, space2);
        ofSetColor(0,0,0);
        //if(i==0 || i==ratio)
        //myFont.drawString(s,  -40,space2);
        space2=space2-space;
        t=t+(value);
    }
    ofSetLineWidth(0.5);
    space=width/ratio;
    space2=0;
    value=((float)maxX-float(mx))/ratio;
    t=mx;
    for (int i=0; i<=ratio; i++) {
        stringstream stream;
        stream << fixed << setprecision(1) << t;
        string s;
        if(t<999){
            stream << fixed << setprecision(1) << t;
            s = stream.str();}
        else{
            stream << fixed << setprecision(0) << t;
            s = stream.str();
        }
        ofSetColor(211,211,211);
        ofDrawLine(space2,0,space2, height);
        ofSetColor(0,0,0);
        //if(i==0 && i==ratio)
        //myFont.drawString(s, space2-10,height+20);
        space2=space2+space;
        t=t+(value);
    }
    
    ofRectangle bounds = myFont.getStringBoundingBox(name1, 0, 0);
    myFont.drawString(name1,(width/2)-(bounds.x/2)-40, height+20);
    
    ofRotateZ(-90.0);
    myFont.drawString(name2, -width/2-40, -10);
    
    ofPopMatrix();
}

void Scatterplot::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(color);
    ofTranslate(x,y);
    ofDrawRectangle(0, 0, width, height);
    
    ofPopStyle();
    ofPopMatrix();
    if (selected) {
        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(0);
        ofDrawRectangle(sx0,sy0,sx1-sx0,sy1-sy0);
        ofFill();
    }
    setAxis();
    ofPushMatrix();
    ofTranslate(x,y);
    ofTranslate(0,height, 0);
    for (int i=0; i<x_data.size(); i++) {
        
        if (!section[i]) {
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(255,0,0);
            ofDrawCircle(tranX[i],-tranY[i],2);
            ofFill();
        }
        
        ofColor color = ofColor::fromHsb(150,tranX[i]/2,200);//choose the color
        ofSetColor( color );//set the color
        
        ofDrawCircle(tranX[i],-tranY[i],1);
    }
    
    ofPopMatrix();
}

void Scatterplot::mouseMoved(ofMouseEventArgs & args){ }

void Scatterplot::mouseDragged(ofMouseEventArgs & args) {
    
    if (selected) {
        sx1 = args.x;
        sy1 = args.y;
        
        if (sx1 < x) {
            sx1 = x;
        }
        if (sx1 > x+width) {
            sx1 = x+width;
        }
        if (sy1 < y) {
            sy1 = y;
        }
        if (sy1 > y+height) {
            sy1 = y+height;
        }
        
        
        for (int i=0; i<tranX.size(); i++) {
            section[i] = true;
            int minx=sx0,maxx=sx1,miny=sy0,maxy=sy1;
            if (sx0 > sx1) {
                minx = sx1; maxx = sx0;
            }
            if (sy0 > sy1) {
                miny = sy1; maxy = sy0;
            }
            if (ofInRange(tranX[i]+x,minx,maxx) &&
                ofInRange(height-tranY[i]+y,miny,maxy)){
                section[i] = false;
            }
        }
        ofNotifyEvent(brushedSelection, section);
    }
}

void Scatterplot::mousePressed(ofMouseEventArgs & args){
    
    if (inside(args.x, args.y)) {
        
        selected = true;
        sx0 = args.x;
        sy0 = args.y;
        sx1 = args.x;
        sy1 = args.y;
        for (int i=0; i<section.size(); i++) {
            
            section[i] = false;
        }
        ofNotifyEvent(brushedSelection, section);
    }
}

void Scatterplot::mouseReleased(ofMouseEventArgs & args){
    
    ofNotifyEvent(brushedSelection, section);
    selected = false;
}
void Scatterplot::mouseScrolled(ofMouseEventArgs & args){}
void Scatterplot::mouseEntered(ofMouseEventArgs & args){}
void Scatterplot::mouseExited(ofMouseEventArgs & args){}

//this function checks if the passed arguments are inside the Canvas.
bool Scatterplot::inside(float _x, float _y ){
    return (ofInRange(_x,this->x,this->x+this->width) &&
            ofInRange(_y,this->y,this->y+this->height));
    
}
bool Scatterplot::onPoint(float _x, float _y ){
    
    for (int i=0; i<tranX.size(); i++) {
        if((ofVec2f(_x-x,height-_y+y).distance(ofVec2f(tranX[i], tranY[i])) <3)==true){
            index=i;
            return true;
        }
    }
}
