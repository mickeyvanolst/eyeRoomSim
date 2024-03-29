#pragma once

#include "ofMain.h"
#include "ofx3DModelLoader.h"
#include "ofxAssimpModelLoader.h"
#include "ofxTweener.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofLight light;
    
    ofx3DModelLoader model;
    //ofxAssimpModelLoader model;
    ofMesh mesh;
    ofEasyCam cam;

    ofPoint position;
    float radius;

    ofVideoPlayer*  curMov;
};
	
