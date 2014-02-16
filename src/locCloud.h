#ifndef LOCCLOUD_H
#define LOCCLOUD_H

#include "ofMain.h"
#include "sParticle.h"

class locCloud
{
    public:
        locCloud();

        //Methods
        void initCloud(ofPoint micpos, int num, float hist2rFac);
        void calcParticlePositions(int, float, float);
        void setCloudPath(vector<ofPoint>);
        void drawPath();
        void drawMic();
        void drawCloud();
        void updateParticleWeights(float hist2R);
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
        float histogram2RadiusFactor;

};

#endif // LOCCLOUD_H
