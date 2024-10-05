/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>

#define TWO_PI 6.28318530718

using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
    return fmod((fmod(radians,TWO_PI) + TWO_PI), TWO_PI);
}

double Angle::convertToDegrees(double r) const {
    double rNormalized = normalize(r);
    return rNormalized * (180.0 / M_PI);
}

double Angle::convertToRadians(double d) const {
    return normalize(d * (M_PI / 180.0));
}
