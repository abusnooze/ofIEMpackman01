#ifndef IEMLOGO_H
#define IEMLOGO_H

#include "ofMain.h"
#include "sParticle.h"

class iemLogo
{
    public:
        iemLogo();
        void updateDotPos(float nAmount, float nStep, float dotR, float gridSp, ofPoint posIn);

        //Methods
        void draw();

        ofPoint pos;
        float dotRadius;
        float gridSpacing;
        int alpha;
        float noiseAmount;
        float noiseStep;
        int numDots;
        int numDotsX;
        int numDotsY;

        vector<int> pattern; // 0/1 matrix defining the pattern (populated in constructor)
        vector<sParticle> iemDots;
};





#endif
