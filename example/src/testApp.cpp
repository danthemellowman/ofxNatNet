#include "testApp.h"

#include "ofxNatNet.h"

ofxNatNet natnet;
ofEasyCam cam;

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    natNetParams.setName("NatNet");
    natNetParams.add(networkInterface.set("Interface", "en0"));
    natNetParams.add(ipAddress.set("IP Address", "10.0.1.0"));
    
    panel.setup(natNetParams);
    panel.loadFromFile("natnet.xml");
    
    natnet.setup(networkInterface, ipAddress);  // interface name, server ip
    natnet.setScale(100);
    natnet.setDuplicatedPointRemovalDistance(20);
}

//--------------------------------------------------------------
void testApp::update() {
    natnet.update();
    
    frameNum = natnet.getFrameNumber();
    dataRate = natnet.getDataRate();
    connected = natnet.isConnected();
    numMarkerSet = natnet.getNumMarkersSet();
    numMarkers = natnet.getNumMarker();
    numFiltered = natnet.getNumFilterdMarker();
    numRigidbody = natnet.getNumRigidBody();
    numSkeleton = natnet.getNumSkeleton();
}

//--------------------------------------------------------------
void testApp::draw() {
    ofEnableAlphaBlending();
    
    cam.begin();
    
    ofDrawAxis(100);
    
    ofFill();
    
    // draw all markers set
    ofSetColor(255, 0, 255, 128);
    for (int i = 0; i < max(0, (int)natnet.getNumMarkersSet() - 1); i++) {
        for (int j = 0; j < natnet.getMarkersSetAt(i).size(); j++) {
            ofDrawBox(natnet.getMarkersSetAt(i)[j], 3);
        }
    }
    
    // draw all markers
    ofSetColor(255, 255, 0, 30);
    for (int i = 0; i < natnet.getNumMarker(); i++) {
        ofDrawBox(natnet.getMarker(i), 3);
    }
    
    ofNoFill();
    
    // draw filterd markers
    ofSetColor(0, 255, 255);
    for (int i = 0; i < natnet.getNumFilterdMarker(); i++) {
        ofDrawBox(natnet.getFilterdMarker(i), 10);
    }
    
    // draw rigidbodies
    for (int i = 0; i < natnet.getNumRigidBody(); i++) {
        const ofxNatNet::RigidBody &RB = natnet.getRigidBodyAt(i);
        
        if (RB.isActive())
            ofSetColor(0, 255, 0);
        else
            ofSetColor(255, 0, 0);
        
        ofPushMatrix();
        glMultMatrixf(RB.getMatrix().getPtr());
        ofDrawAxis(30);
        ofPopMatrix();
        
        glBegin(GL_LINE_LOOP);
        for (int n = 0; n < RB.markers.size(); n++) {
            glVertex3fv(RB.markers[n].getPtr());
        }
        glEnd();
        
        for (int n = 0; n < RB.markers.size(); n++) {
            ofDrawBox(RB.markers[n], 5);
        }
    }
    
    // draw skeletons
    for (int j = 0;  j < natnet.getNumSkeleton(); j++) {
        const ofxNatNet::Skeleton &S = natnet.getSkeletonAt(j);
        ofSetColor(255, 0, 255, 175);
        
        for (int i = 0; i < S.joints.size(); i++) {
            const ofxNatNet::RigidBody &RB = S.joints[i];
            ofPushMatrix();
            glMultMatrixf(RB.getMatrix().getPtr());
            ofDrawBox(5);
            ofPopMatrix();
        }
    }
    
    cam.end();
    
    
    
    string str;
    str += "interface: " + networkInterface.get()+"\n";
    str += "ipAddress: " + ipAddress.get()+"\n";
    str += "frames: " + ofToString(frameNum) + "\n";
    str += "data rate: " + ofToString(dataRate) + "\n";
    str += string("connected: ") + (connected? "YES" : "NO") + "\n";
    str += "num markers set: " + ofToString(numMarkerSet) + "\n";
    str += "num marker: " + ofToString(numMarkers) + "\n";
    str += "num filterd (non regidbodies) marker: " +
    ofToString(numFiltered) + "\n";
    str += "num rigidbody: " + ofToString(numRigidbody) + "\n";
    str += "num skeleton: " + ofToString(numSkeleton) + "\n";


    ofSetColor(255);
    ofDrawBitmapString(str, 10, 20);
    
//    panel.draw();
}
void testApp::exit(){
    panel.saveToFile("natnet.xml");
}

