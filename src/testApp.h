#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "locCloud.h"
#include "iemLogo.h"

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

		ofxPanel gui;
        ofxFloatSlider particleBuddyShrink;
        ofxFloatSlider particleBuddyDistance;
        ofxIntSlider   particleBuddyNum;
        ofxFloatSlider noiseAmount;
        ofxFloatSlider noiseStep;
        ofxFloatSlider hist2Radius;
        ofxFloatSlider noiseAmountLogo;
        ofxFloatSlider noiseStepLogo;
        ofxFloatSlider dotRadiusLogo;
        ofxFloatSlider gridSpacingLogo;

        ofPoint logoPos;
        iemLogo logo;

        locCloud m1,m2; //I should use a vector of locCloud objects but I'll leave this for now;

        int drawGui;


};
