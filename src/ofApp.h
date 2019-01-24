#pragma once

#include "ofMain.h"

struct Bin
{
    ofPoint tl;
    float w, h;
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void updateBins();
    
    void save();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    
    //  Input image
    ofImage gif;
    
    //  Colors
    vector<ofColor> colors;
    
    //  Bins
    vector<Bin> bins;
    
    //  Control
    int selColorIdx = -1;
    
    //  Window
    float w, h;
};
