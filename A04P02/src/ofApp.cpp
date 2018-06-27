#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    string path;

    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
        path = result.getPath();
        table.read_data(path);
        
       
    }

   
    plot.setup(table, 800, 800, 80, 80);
//    Scatterplot.setup(table.get_columnf(plot.click1), table.get_columnf(plot.click2), 200, 200, 200, 700,table.get_column_name(plot.click1), table.get_column_name(plot.click2));
    ofAddListener(plot.brushedSelection,this,&ofApp::onMouseInCanvas);
    ofAddListener(plot.s.brushedSelection,this,&ofApp::onMouseInCanvas);
    gui.setup(); // most of the time you don't need a name
}

//--------------------------------------------------------------
void ofApp::update(){
    
}
void ofApp::onMouseInCanvas(vector<bool> & e){
    plot.section = e;
    plot.s.section = e;
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,255,255);
    //gui.draw();
    plot.draw();
//    Scatterplot.setup(table.get_columnf(plot.click1), table.get_columnf(plot.click2), 200, 200, 200, 700,table.get_column_name(plot.click1), table.get_column_name(plot.click2));
//    Scatterplot.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
