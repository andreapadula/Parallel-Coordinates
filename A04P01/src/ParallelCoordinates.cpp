//
//  ParallelCoordinates.cpp
//  homework4
//
//  Created by Andrea Padula on 3/14/17.
//
//

#include "ParallelCoordinates.h"
#include <string>

void ParallelCoordinates::setup(TableReader table,int width, int height, int x, int y){
    int limit=table.getAttributesize();
    int space= width/limit+10;
    ofRegisterMouseEvents(this);
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    int var2=70;
    int var=105;
    myFont.load("verdana.ttf", 10, true, true); //set the font
    myFont2.load("verdana.ttf", 8, true, true); //set the font
    this->table=table;
    for(int i=0;i<table.getAttributesize();i++){
        ofRectangle r;
        if(i>0){
            r.set(var, 20, 40, 40);
            var=var+space;
            rectButton.push_back(r);
        }
        r.set(var2, 680+60, 40, 40);
        var2=var2+space;
        rectButton2.push_back(r);
        flip.push_back(false);
        
        names.push_back(table.get_column_name(i));
        std::vector<Data> temp;
        if (table.type(i)) {
            std::vector<float> f=table.get_columnf(i);
            for (int j = 0; j<f.size(); j++) {
                Data d;
                d.isNum=true;
                d.value=f[j];
                temp.push_back(d);
            }
            data.push_back(temp);
        }
        else{
            
            std::vector<string> f=table.get_columns(i);
            for (int j = 0; j<f.size(); j++) {
                Data d;
                d.isNum=false;
                d.s=f[j];
                temp.push_back(d);
            }
            data.push_back(temp);
        }
        
        
    }
    int px=x-10;
    for(int i=0;i<data.size();i++){
        if (data[i][0].isNum==1){
            range(table.get_columnf(i));
            std::tuple<float,float> foo (max,min);
            r.push_back(foo);
        }
        else{
            rangeString(i);
            std::tuple<float,float> foo (max,min);
            r.push_back(foo);
        }
        std::tuple<float,float,float,float> foo (px,y, px+20, y);
        std::tuple<float,float,float,float> foo2 (px,y+600, px+20, y+600);
        bar.push_back(foo);
        bar.push_back(foo2);
        px=px+space;
    }
    
//    std::get<3>(bar[0])=500;
    //cout<<std::get<3>(bar[2])-y<<endl;
//    cout<<std::get<3>(bar[3])<<endl;
    for(int i=0; i<data.size(); i++) {
        //cout<<data[i].size()<<endl;
        std::vector<bool> temp;
        for(int j=0;j<data[i].size();j++){
            temp.push_back(false);}
        sections.push_back(temp);
    }
    for(int i=0; i<data[2].size(); i++) {
        section.push_back(false);
    }
    
}

void ParallelCoordinates::draw(){
    points.clear();
    int limit=table.getAttributesize();
    int space= width/limit+10;
    int xc=120;
    int xc2=130;
    for(int i=0;i<rectButton.size();i++){
        ofNoFill();
        ofRect(rectButton[i]);
        ofDrawLine(xc,40, xc2,40);
        ofFill();
        ofDrawTriangle(xc, 40-5, xc, 40+5, xc-5, 40);
        ofDrawTriangle(xc2, 40-5, xc2, 40+5, xc2+5, 40);
        xc=xc+space;
        xc2=xc2+space;
    }
    for(int i=0;i<rectButton2.size();i++){
        ofNoFill();
        ofRect(rectButton2[i]);
        myFont.drawString("Flip",rectButton2[i].getX()+10 , rectButton2[i].getY()+20);
    }

    int px=x-10;
    
    for (int i=0; i<bar.size(); i=i+2) {
         ofSetColor(255,0,0);
        ofSetLineWidth(2);
        ofDrawLine(std::get<0>(bar[i]),std::get<1>(bar[i]), std::get<2>(bar[i]), std::get<3>(bar[i]));
        ofDrawLine(std::get<0>(bar[i+1]),std::get<1>(bar[i+1]), std::get<2>(bar[i+1]), std::get<3>(bar[i+1]));
        ofDrawLine(std::get<0>(bar[i]),std::get<1>(bar[i]), std::get<0>(bar[i]), std::get<3>(bar[i+1]));
        ofDrawLine(std::get<2>(bar[i]),std::get<1>(bar[i]), std::get<2>(bar[i]), std::get<3>(bar[i+1]));
    
    }
     ofSetColor(0,0,0);
    ofTranslate(x,y);
    ofPushMatrix(); // Save the coordinate system before we shift it horizontally
    int m=0;
    int index=0;
    for (int cols=0; cols<limit; cols++) {
        vector<float> temp;
        ofSetColor(0);
        ofSetLineWidth(2);
        ofDrawLine(0, 0, 0, 600);
        ofSetLineWidth(1);
        
            for (int j=0; j<data[cols].size(); j++) {
                float y1,y2;
                
                if (data[cols][j].isNum==1) {
                    ofSetColor(0);
                    std::tuple<float,float> foo=r[cols];
                    this-> max=std::get<0>(foo);
                    this-> min=std::get<1>(foo);
                     y1 = ofMap(data[cols][j].value, min, max, 0, 600);
                }
                else{
                    std::tuple<float,float> foo=r[cols];
                    this-> max=std::get<0>(foo);
                    this-> min=std::get<1>(foo);
                     y1 = ofMap(convert(data[cols][j].s), min, max, 0, 600);
                }
                if(flip[cols]==true){
                    y1=y1;
                }
                else{
                    y1=600-y1;
                }
                temp.push_back(y1);
                if(cols<limit-1){
                if (data[cols+1][j].isNum==1) {
                    std::tuple<float,float> foo=r[cols+1];
                    this-> max=std::get<0>(foo);
                    this-> min=std::get<1>(foo);
                    y2 = ofMap(data[cols+1][j].value, min, max, 0, 600);
                }
                else{
                    std::tuple<float,float> foo=r[cols+1];
                    this-> max=std::get<0>(foo);
                    this-> min=std::get<1>(foo);
                    y2 = ofMap(convert(data[cols+1][j].s), min, max, 0, 600);
                }
                
                if(flip[cols+1]==true){
                    y2=y2;
                }
                else{
                    y2=600-y2;
                }
                
//
                
                if (section[j]==true){
                    
                    ofSetColor(255,255,255);
                }
                else{
                    ofSetColor(0,0,255);
               
                    ofDrawLine(0, y1, space, y2);}
                
                }
                
                
                }
            points.push_back(temp);
            m=m+2;
            
        
        ofSetColor(0);
        std::tuple<float,float> foo=r[cols];
        if(data[cols][0].isNum){
            int max=std::get<0>(foo);
            int min=std::get<1>(foo);
            if(flip[cols]){
                myFont.drawString(to_string(min), -10, -10);
                myFont.drawString(to_string(max), -10, 620);
            }
            else{
                myFont.drawString(to_string(max), -10, -10);
                myFont.drawString(to_string(min), -10, 620);
            }
        
        }
        else{
            int n=data[cols][0].index1;
            int n2=data[cols][0].index2;
            setupString(space,cols, n, n2);

        }
        

        ofRectangle bounds = myFont2.getStringBoundingBox(names[cols], 0, 0);
        if(bounds.getWidth()>space){
            myFont2.drawString(split(names[cols]), -10, 650);
        }
        else{
            myFont2.drawString(names[cols], -10, 650);
            
        }
        
        ofTranslate(space, 0); // Shift horizontally
    }
    ofPopMatrix(); // Return to the coordinate system before we shifted it horizontally

}
void ParallelCoordinates::setupString(int space, int cols, int n, int n2){
    if(flip[cols]){
        ofRectangle bounds = myFont2.getStringBoundingBox(data[cols][n].s, 0, 0);
        if(bounds.getWidth()>space){
            myFont2.drawString(split(data[cols][n].s), -10, -10);
        }
        else{
            myFont2.drawString(data[cols][n].s, -10, -10);
            
        }
        bounds = myFont2.getStringBoundingBox(data[cols][n2].s, 0, 0);
        if(bounds.getWidth()>space){
            myFont2.drawString(split(data[cols][n2].s), -10, 620);
        }
        else{
            myFont2.drawString(data[cols][n2].s, -10, 620);
            
        }
    
    }
    else{
        ofRectangle bounds = myFont2.getStringBoundingBox(data[cols][n2].s, 0, 0);
        if(bounds.getWidth()>space){
            myFont2.drawString(split(data[cols][n2].s), -10, -10);
        }
        else{
            myFont2.drawString(data[cols][n2].s, -10, -10);
            
        }
        bounds = myFont2.getStringBoundingBox(data[cols][n].s, 0, 0);
        if(bounds.getWidth()>space){
            myFont2.drawString(split(data[cols][n].s), -10, 620);
        }
        else{
            myFont2.drawString(data[cols][n].s, -10, 620);
            
        }
    
    }

}
std::string ParallelCoordinates::split(string s) {
    string str(s);
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    
    vector<string> tokens; // Create vector to hold our words
    
    while (ss >> buf)
        tokens.push_back(buf);
    return tokens[tokens.size()-1];
}


void ParallelCoordinates::range(std::vector<float> v){
    this-> max= *max_element(v.begin(), v.end())+1;
    this-> min= *min_element(v.begin(), v.end())-1;
}
void ParallelCoordinates::rangeString(int c){
    std::vector<int> v;
    for (int i=0; i<table.get_columns(c).size(); i++) {
        int temp=convert(data[c][i].s);
        v.push_back(temp);
    }
    int mn=1000;
    int mx=0;
    for (int i=0; i<v.size(); i++) {
        if(mx<v[i]){
            mx=v[i];
            data[c][0].index2=i;
        }
        if(mn> v[i]){
            mn=v[i];
            data[c][0].index1=i;
        }
    }
    this-> max= mx;
    this-> min=mn;

}
int ParallelCoordinates::convert(string s){
    int result=0;
    for (int i = 0; i < s.length(); i++)
    {
        char x = s[i];
        result=result+x;
    }
    return result;
}
void ParallelCoordinates::swap(int i){
    std::vector<Data> temp;
    temp=data[i];
    data[i]=data[i+1];
    data[i+1]=temp;
    std::tuple<float,float> foo;
    foo=r[i];
    r[i]=r[i+1];
    r[i+1]=foo;
    string s;
    s=names[i];
    names[i]=names[1+i];
    names[i+1]=s;

}

void ParallelCoordinates::mouseMoved(ofMouseEventArgs & args){ }

void ParallelCoordinates::mouseDragged(ofMouseEventArgs & args) {

    if (inside(args.x, args.y)){
        selected=true;
        if(args.y>=335 && args.y<=345 ){
            return;
        }
        if(args.y>=680/2){
            
            recY2=args.y;
            std::get<1>(bar[h*2+1])=recY2;
            std::get<3>(bar[h*2+1])=recY2;
            //    cout<<std::get<3>(bar[0])<<endl;
            
        }
        else{
            recY=args.y;
            std::get<1>(bar[h*2])=recY;
            std::get<3>(bar[h*2])=recY;
            
        }
        
//        cout<<h<<endl;
        for (int i=0; i<points[h].size(); i++) {
            if (!ofInRange(points[h][i], std::get<3>(bar[h*2])-x, std::get<3>(bar[h*2+1])-y)){
                sections[h][i]=true;
            }
            else
                sections[h][i]=false;
        }
        
            for(int j=0;j<sections[1].size();j++){
                int var=0;
                for(int i=0; i<sections.size(); i++){
                    if (sections[i][j]==false) {
                        var++;
                    }
                }
                if (var==sections.size()) {
                    section[j]=false;
                }
                else
                    section[j]=true;
            }
        
    }
}
void ParallelCoordinates::reset(){
    int limit=table.getAttributesize();
    int space= width/limit+10;
    int px=x-10;
    bar.clear();
    for(int i=0;i<data.size();i++){
        std::tuple<float,float,float,float> foo (px,y, px+20, y);
        std::tuple<float,float,float,float> foo2 (px,y+600, px+20, y+600);
        bar.push_back(foo);
        bar.push_back(foo2);
        px=px+space;
    }
}
void ParallelCoordinates::mousePressed(ofMouseEventArgs & args){
    for (int i=0; i< rectButton.size(); i++) {
        if (rectButton[i].inside(args.x, args.y)) {
            swap(i);
            for(int i=0; i<data[2].size(); i++) {
                section[i]=false;
            }
            reset();
        }
    }
    for (int i=0; i< rectButton2.size(); i++) {

        if (rectButton2[i].inside(args.x, args.y)) {
            flip[i]=!flip[i];
        }
    }
    
}

void ParallelCoordinates::mouseReleased(ofMouseEventArgs & args){
}
void ParallelCoordinates::mouseScrolled(ofMouseEventArgs & args){}
void ParallelCoordinates::mouseEntered(ofMouseEventArgs & args){}
void ParallelCoordinates::mouseExited(ofMouseEventArgs & args){}
bool ParallelCoordinates::inside(float _x, float _y ){
    int limit=table.getAttributesize();
    int space= width/limit+10;
    int px=55;
    int py=90;
    for (int i=0; i<data.size(); i++) {
        if(ofInRange(_x,px,py)&& ofInRange(_y,80,680)){
            //cout<<i<<endl;
            h=i;
            return true;
        }
        px=px+space;
        py=py+space;
        
    }
    return false;
    
}
