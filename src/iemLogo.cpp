#include "iemLogo.h"

iemLogo::iemLogo()
{
    //alpha = alphaIn;
    alpha = 255;
    numDotsX = 16;
    numDotsY = 7;
    numDots = numDotsX * numDotsY;
    iemDots.resize(numDots);

    pattern.resize(numDots);

    /*iem LOGO PATTERN*/
    for (int i = 0; i<numDots; i++)
    {
        pattern[i] = 0;
    }
    pattern[2] = 1;
    pattern[6] = 1;
    pattern[7] = 1;
    pattern[9] = 1;
    pattern[10] = 1;
    pattern[11] = 1;
    pattern[12] = 1;
    pattern[13] = 1;
    pattern[20] = 1;
    pattern[31] = 1;
    pattern[32] = 1;
    pattern[33] = 1;
    pattern[37] = 1;
    pattern[39] = 1;
    pattern[41] = 1;
    pattern[44] = 1;
    pattern[46] = 1;
    pattern[48] = 1;
    pattern[51] = 1;
    pattern[53] = 1;
    pattern[55] = 1;
    pattern[59] = 1;
    pattern[60] = 1;
    pattern[62] = 1;
    pattern[79] = 1;
    pattern[80] = 1;
    pattern[81] = 1;
    pattern[82] = 1;
    pattern[83] = 1;
    pattern[86] = 1;
    pattern[93] = 1;
    pattern[94] = 1;
    pattern[95] = 1;
    pattern[96] = 1;
    pattern[97] = 1;
    pattern[100] = 1;
    pattern[108] = 1;
    pattern[109] = 1;
    pattern[110] = 1;
    pattern[111] = 1;
    /*----------------*/
}


void iemLogo::updateDotPos(float nAmount, float nStep, float dotR, float gridSp, ofPoint posIn)
{
    pos.set(posIn);
    noiseAmount = nAmount;
    noiseStep = nStep;
    dotRadius = dotR;
    gridSpacing = gridSp;

    /*for (int i=0; i<numDots; i++)
    {
        iemDots[i].noiseAmount = noiseAmount;
        iemDots[i].noiseStep = noiseStep;
        iemDots[i].r = dotRadius;
    }*/

    int counter = 0;
    for (int i=0; i < numDotsX; i++)
    {
        for (int j=0; j< numDotsY; j++)
        {
                iemDots[counter].noiseAmount = noiseAmount;
                iemDots[counter].noiseStep = noiseStep;
                iemDots[counter].pos.x = pos.x + i*gridSpacing;
                iemDots[counter].pos.y = pos.y + j*gridSpacing;
                iemDots[counter].r = dotRadius;
                iemDots[counter].alpha = alpha;
                if (pattern[counter]==1){
                    iemDots[counter].visible = 1;
                }else{
                    iemDots[counter].visible = 1;
                    iemDots[counter].alpha = 50;
                }
                counter++;
        }
    }

}


void iemLogo::draw()
{
    for (int i=0; i<numDots; i++)
    {
        if (iemDots[i].visible == 1)
        {
            iemDots[i].draw();
        }

    }
}

