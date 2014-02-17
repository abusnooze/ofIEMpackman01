#include "testApp.h"


float trueSourceAngle1 = 0; //only to simulate a moving source (needs to be global and i don wanna put it in the class)

//--------------------------------------------------------------
void testApp::setup(){

    ofPoint micCenter1(400,400);
    ofPoint micCenter2(400+400,400);
    int pNum = 70;

    /*GUI*/
    //setup UI elements
    gui.setup();
    //setup each gui element: args = name, default, min, max
    gui.add(particleBuddyShrink.setup( "particleBuddyShrink", 0.8, 0, 1 ));
    gui.add(particleBuddyDistance.setup( "particleBuddyDistance", 7, 1, 40 ));
    gui.add(particleBuddyNum.setup( "particleBuddyNum", 9, 0, 20 ));
    gui.add(noiseAmount.setup( "noiseAmount", 40, 0, 100 ));
    gui.add(noiseStep.setup( "noiseStep", 0.02, 0, 0.4 ));
    gui.add(hist2Radius.setup( "hist2Radius", 1000, 0, 10000 ));

    gui.add(noiseAmountLogo.setup( "logo: noiseAmnt", 4, 0, 100 ));
    gui.add(noiseStepLogo.setup( "logo: noiseStp", 0.02, 0, 0.4 ));
    gui.add(dotRadiusLogo.setup( "logo: radius", 10, 0, 40 ));
    gui.add(gridSpacingLogo.setup( "logo: spacing", 12, 0, 50 ));

    gui.add(histMinR.setup( "histogram: min R", 20, 0, 150 ));
    gui.add(histAmp.setup( "histogram: amp", 1000, 0, 10000 ));

    drawGui = 1; //default;
    drawPath = 0; //default;

    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();


    /*set up microphone 1*/
    m1.initCloud(micCenter1, pNum, hist2Radius);
    vector<ofPoint> cPath1;
    cPath1.push_back(ofPoint(300,500));
    cPath1.push_back(ofPoint(300,300));
    cPath1.push_back(ofPoint(500,300));
    cPath1.push_back(ofPoint(500,500));
    m1.setCloudPath(cPath1);
    m1.calcParticlePositions(particleBuddyNum, particleBuddyDistance, particleBuddyShrink);
    m1.setupHistMesh(histMinR);

    /*set up microphone 2*/
    m2.initCloud(micCenter2, pNum, hist2Radius);
    vector<ofPoint> cPath2;
    cPath2.push_back(ofPoint(400+300,500));
    cPath2.push_back(ofPoint(400+300,300));
    cPath2.push_back(ofPoint(400+500,300));
    cPath2.push_back(ofPoint(400+500,500));
    m2.setCloudPath(cPath2);
    m2.calcParticlePositions(particleBuddyNum, particleBuddyDistance, particleBuddyShrink);


}

//--------------------------------------------------------------
void testApp::update(){

    vector<float> simMeans;
    vector<float> simStdDevs;
    float dt;
    //float curTime;

    dt = ofGetLastFrameTime();
    //curTime = ofGetElapsedTimef();

    float speed1 = 45; //degree per second;
    trueSourceAngle1 += speed1 * dt;
    trueSourceAngle1 = ofWrapDegrees(trueSourceAngle1,0,360);
    simMeans.push_back(trueSourceAngle1);
    simStdDevs.push_back(30);
    simMeans.push_back(trueSourceAngle1+180);
    simStdDevs.push_back(10);
    simMeans.push_back(trueSourceAngle1+90);
    simStdDevs.push_back(40);

    m1.simulateHist(simMeans, simStdDevs);
    m1.updateParticleWeights(hist2Radius);
    m1.updateParticleProperties(particleBuddyNum, particleBuddyDistance, particleBuddyShrink, noiseAmount, noiseStep);
    m1.updateHistMesh(histAmp, histMinR);

    m2.simulateHist(simMeans, simStdDevs);
    m2.updateParticleWeights(hist2Radius);
    m2.updateParticleProperties(particleBuddyNum, particleBuddyDistance, particleBuddyShrink, noiseAmount, noiseStep);

    logoPos.x = 20;
    logoPos.y = ofGetWindowHeight() - logo.numDotsY*gridSpacingLogo - 20;
    logo.updateDotPos(noiseAmountLogo, noiseStepLogo, dotRadiusLogo, gridSpacingLogo, logoPos);

}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(ofColor::blue);
    //ofBackgroundGradient(ofColor::white, ofColor::gray);

    if (drawPath){
        m1.drawPath();
    }
    m1.drawMic();
    m1.drawCloud();

    m1.drawHistMesh();

    if (drawPath){
        m2.drawPath();
    }
    m2.drawMic();
    m2.drawCloud();

    ofSetColor(ofColor::black);
    string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 3);
    ofDrawBitmapString(fpsStr, 10,10);

    //string fpsStr2 = "frame rate: "+ofToString(ofGetLastFrameTime(), 6);
    //ofDrawBitmapString(fpsStr2, 100,300);


    if (drawGui){
        gui.draw();
    }
    logo.draw();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key=='g'){
        if (drawGui){
            drawGui = 0;
        }else{
            drawGui = 1;
        }
    }

    if (key=='p'){
        if (drawPath){
            drawPath = 0;
        }else{
            drawPath = 1;
        }
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
