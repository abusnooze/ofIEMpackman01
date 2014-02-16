#ifndef SPARTICLE_H
#define SPARTICLE_H


#include "ofMain.h"

class sParticle
{
    public:

        //Constructor
        sParticle();

         // Methods
        void moveTo();
        void draw();

        // Properties
        ofPoint pos;
        int     r;
        ofColor color;
        int     alpha;
        float   randomAmp;
        bool    visible;
        float   repAngle; //this is the directional angle that this particle is representing
        int     numberOfBuddies;
        ofPoint buddyNormVec;
        float   buddyDistance;
        float  buddyShrink;
        float  noiseCursor;
        float  noiseStep;
        float  noiseAmount;




};

#endif // SPARTICLE_H
