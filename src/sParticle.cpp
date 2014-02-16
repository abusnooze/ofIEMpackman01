#include "sParticle.h"

sParticle::sParticle()
{
    // Set the initial color
    //color.set( ofRandom(255), ofRandom(255), ofRandom(255));
    color.set(ofColor::yellow);
    pos.set(0,0);
    r = 10;
    alpha = 255;
    randomAmp = 10;
    visible = 0;
    repAngle = 0;
    buddyNormVec = ofPoint(0,0);

    buddyDistance = 0;
    numberOfBuddies = 0;
    buddyShrink = 0.5;
    noiseCursor = 0;

    // Initial x position of the ball
    //x = ofRandom( ofGetWindowWidth() );
    // Initial y position of the ball
    //y = ofRandom( ofGetWindowHeight() );
}


void sParticle::moveTo(){

}

void sParticle::draw(){

    ofPoint tmpPt;

    ofSetColor(color,alpha);
    ofFill();

    float displX = noiseAmount * ofSignedNoise(noiseCursor+ofDist(0,0,pos.x,pos.y));
    float displY = noiseAmount * ofSignedNoise(noiseCursor+ofDist(0,0,pos.x,pos.y)+100);
    noiseCursor += noiseStep;
    ofCircle(pos+ofPoint(displX,displY),r); //main particle;

    float buddyR = buddyShrink*r;
    for (int i=0; i<numberOfBuddies; i++){
        tmpPt = pos+(i+1)*buddyDistance*buddyNormVec;
        displX = noiseAmount * ofSignedNoise(noiseCursor+ofDist(0,0,tmpPt.x,tmpPt.y));
        displY = noiseAmount * ofSignedNoise(noiseCursor+ofDist(0,0,tmpPt.x,tmpPt.y)+120);
        ofCircle(tmpPt+ofPoint(displX,displY), buddyR); //buddy 1

        tmpPt = pos-(i+1)*buddyDistance*buddyNormVec;
        displX = noiseAmount * ofSignedNoise(noiseCursor+ofDist(0,0,tmpPt.x,tmpPt.y));
        displY = noiseAmount * ofSignedNoise(noiseCursor+ofDist(0,0,tmpPt.x,tmpPt.y)+120);
        ofCircle(tmpPt+ofPoint(displX,displY), buddyR); //buddy 1

        buddyR = buddyR * buddyShrink;

        /*
        val1 = randomAmp * ofNoise( pos.x*0.4, pos.y*0.7, ofGetElapsedTimef() * 0.8 );
        ofCircle(pos+(i+1)*buddyDistance*buddyNormVec+ofPoint(val1,val1), buddyR); //buddy 1
        val1 = randomAmp * ofNoise( pos.x*0.4, pos.y*0.9, ofGetElapsedTimef() * 0.3 );
        ofCircle(pos-(i+1)*buddyDistance*buddyNormVec+ofPoint(val1,val1), buddyR); //buddy 2
        buddyR = buddyR * buddyShrink;
        */
    }
}
