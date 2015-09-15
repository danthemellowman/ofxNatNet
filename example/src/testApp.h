#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void exit();

    ofxPanel panel;
    ofParameterGroup natNetParams;
    ofParameter<string> networkInterface;
    ofParameter<string> ipAddress;
    
    ofParameter<int> frameNum;
    ofParameter<int> dataRate;
    ofParameter<bool> connected;
    ofParameter<int> numMarkerSet;
    ofParameter<int> numMarkers;
    ofParameter<int> numFiltered;
    ofParameter<int> numRigidbody;
    ofParameter<int> numSkeleton;
    
    
    
};