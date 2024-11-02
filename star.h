/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
    void reset(double width, double height)
    {
        phase = random(0, 255);
        pos.setX(random(0.0, width));
        pos.setY(random(0.0, height));
    }
    void draw(ogstream &gout)
    {
        gout.drawStar(pos, phase);
        phase += 1;
        
    }
    
private:
    Position pos;
    char phase;

};
