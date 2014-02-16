#ifndef LOCCLOUD_H
#define LOCCLOUD_H

#include "ofMain.h"
#include "sParticle.h"

class locCloud
{
    public:
        locCloud();

        //Methods
        void initCloud(ofPoint, int);
        void calcParticlePositions(int, float, float);
        void setCloudPath(vector<ofPoint>);
        void drawPath();
        void drawMic();
        void drawCloud();
        void updateParticleWeights();
        void updateParticleProperties(int, float, float, float, float);
        float eval_norm_pdf(float, float, float);
        int simulateHist(vector<float>, vector<float>);

        //Properties
        ofPoint micPosition;
        int numParticles;
        int numPathLines;
        vector<sParticle> particles;
        ofPolyline cloudPath;
        vector<float> doaHist;

};

#endif // LOCCLOUD_H
