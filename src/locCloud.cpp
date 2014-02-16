#include "locCloud.h"

locCloud::locCloud()
{
    //ctor
}

void locCloud::initCloud(ofPoint micpos, int num, float hist2rFac)
{

    micPosition.set(micpos);
    //micPosition.set()

    histogram2RadiusFactor = hist2rFac;
    numParticles = num;
    particles.resize(numParticles);
    doaHist.resize(numParticles);


}

void locCloud::drawCloud()
{
    for (int i=0; i<numParticles; i++)
    {
        //particles[i].pos.x = i*10;
        //particles[i].pos.y = i*10;
        if (particles[i].visible == 1)
        {
            particles[i].draw();
        }

    }
}

void locCloud::setCloudPath(vector<ofPoint> cPath)
{
    //cout << cPath.size();
    cloudPath.addVertices(cPath);
    numPathLines = cPath.size() - 1;
}

void locCloud::drawPath()
{
    ofSetColor(ofColor::black);
    cloudPath.draw();

}

void locCloud::drawMic()
{
    ofSetColor(255,0,0);
    ofFill();
    ofCircle(micPosition,10);
}

/*computing the potential particle positions along the specified path for the given microphone position*/
void locCloud::calcParticlePositions(int numBuddies, float buddyDist, float buddyShrink)
{
    ofPoint interSec;
    ofPoint endDir;
    float angRes;
    ofPoint tmpP;
    ofVec2f tmpV1;
    ofVec2f tmpV2;
    bool hit = 0;

    angRes = 360/numParticles;

    vector<ofPoint> pathVertices;

    pathVertices = cloudPath.getVertices();

    for (int i=0; i<numParticles; i++)
    {
        particles[i].repAngle = i*angRes;
        endDir.x = micPosition.x + 800*cos(ofDegToRad(i*angRes));
        endDir.y = micPosition.y - 800*sin(ofDegToRad(i*angRes));

        for (int jj=0; jj<numPathLines; jj++)
        {
            hit = ofLineSegmentIntersection(micPosition,endDir,pathVertices[jj],pathVertices[jj+1], interSec);
            if (hit)
            {
                particles[i].pos.x = interSec.x;
                particles[i].pos.y = interSec.y;
                particles[i].visible = 1;
                particles[i].buddyDistance = buddyDist;

                tmpP = pathVertices[jj] - pathVertices[jj+1];
                tmpV1.set(tmpP.x,tmpP.y);
                tmpV2 = tmpV1.getPerpendicular();

                particles[i].buddyNormVec.set(tmpV2.x,tmpV2.y);
                particles[i].numberOfBuddies = numBuddies;

                particles[i].buddyShrink = buddyShrink;
            }
        }

    }

}

void locCloud::updateParticleProperties(int numBuddies, float buddyDist, float buddyShrink, float noiseAmount, float noiseStep)
{
    for (int i=0; i<numParticles; i++)
    {
        particles[i].numberOfBuddies = numBuddies;
        particles[i].buddyShrink = buddyShrink;
        particles[i].buddyDistance = buddyDist;
        particles[i].noiseAmount = noiseAmount;
        particles[i].noiseStep = noiseStep;
    }


}

void locCloud::updateParticleWeights(float hist2R)
{
    histogram2RadiusFactor = hist2R;
    for (int i=0; i<numParticles; i++)
    {
        particles[i].r = histogram2RadiusFactor*doaHist[i];
    }

}


float locCloud::eval_norm_pdf(float x, float nMean, float nStdDev){

    float ret;

    ret = (1.0/ (nStdDev * sqrt(2.0 * M_PI) )) * exp( -(x-nMean)*(x-nMean)/(2*nStdDev*nStdDev));

    return ret;
}

int locCloud::simulateHist(vector<float> nMeans, vector<float> nStdDevs)
{
    float x, tmp;
    int numGaussians = nMeans.size();

    if ( nMeans.size() != nStdDevs.size() ){
        return -1;
    }

    for (int ii=0; ii < numParticles; ii++){
        x = particles[ii].repAngle;
        tmp = 0;
        for (int jj=0; jj<numGaussians; jj++){
            tmp += eval_norm_pdf(x, nMeans[jj], nStdDevs[jj]);
            tmp += eval_norm_pdf(x-360, nMeans[jj], nStdDevs[jj]);
            tmp += eval_norm_pdf(x+360, nMeans[jj], nStdDevs[jj]);
        }
        float noiseFac = ofRandomf()+1; //random numer between 0 and 2
        noiseFac = 1;
        doaHist[ii] = noiseFac*tmp;
    }

    return 0;
}





