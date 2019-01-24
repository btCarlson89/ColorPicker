#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //  OF Settings
    ofSetFrameRate(30);
    
    //  Window information
    w = ofGetWidth();
    h = ofGetHeight();
    
    //  Load Image
    gif.load("colors.gif");
    
    //  Read Colors from file
    for(int y = 0; y < gif.getHeight(); ++y){
        for(int x = 0; x < gif.getWidth(); ++x){
            ofColor lookupColor = gif.getColor(x, y);
            bool addColor = true;
            for(auto color : colors){
                if(color == lookupColor){
                    addColor = false;
                    break;
                }
            }
            if(addColor){
                colors.push_back(lookupColor);
                bins.push_back(Bin());
            }
        }
    }
    
    //  Initiate Bins
    updateBins();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //  Draw colors
    int i = 0;
    for(auto color : colors){
        auto bin = bins.at(i);
        ofSetColor(color);
        ofDrawRectangle(bin.tl, bin.w, bin.h);
        ++i;
    }
    
    //  Draw selection
    if(selColorIdx != -1){
        ofPushStyle();
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofDrawRectangle(bins.at(selColorIdx).tl, bins.at(selColorIdx).w, bins.at(selColorIdx).h);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::save(){
    ofFile file;
    file.open(ofToDataPath("colors.txt"), ofFile::Mode::WriteOnly, false);

    string colorStr;
    int i = 0;
    for(auto color : colors){
        string hex = "#" + ofToHex(color.getHex());
        hex.erase(hex.begin()+1);
        hex.erase(hex.begin()+1);
        colorStr.append(hex);
        if(i + 1 < colors.size())
            colorStr.append(", ");
        ++i;
    }
    
    file << colorStr;
    file.close();
}

//--------------------------------------------------------------
void ofApp::updateBins(){
    
    float binW = w / bins.size();
    float binH = h;
    int i = 0;
    for(auto& bin : bins){
        bin.w = binW;
        bin.h = binH;
        bin.tl = ofPoint(bin.w * i, 0);
        ++i;
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key)
    {
        case OF_KEY_BACKSPACE:
            if(selColorIdx != -1){
                colors.erase(colors.begin() + selColorIdx);
                bins.erase(bins.begin() + selColorIdx);
                updateBins();
                selColorIdx = -1;
            }
            break;
        case OF_KEY_LEFT:
            if(selColorIdx > 0){
                iter_swap(colors.begin() + selColorIdx - 1, colors.begin() + selColorIdx);
                --selColorIdx;
            }
            break;
        case OF_KEY_RIGHT:
            if(selColorIdx >= 0 && selColorIdx < colors.size() - 1){
                iter_swap(colors.begin() + selColorIdx, colors.begin() + selColorIdx + 1);
                ++selColorIdx;
            }
            break;
        case 's':
            save();
            break;
        default:
            break;
    }
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

    int xIdx = (x / w) * bins.size();
    if(xIdx == selColorIdx)
        selColorIdx = -1;
    else
        selColorIdx = xIdx;
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
