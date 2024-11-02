/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
    // Get the current velocites.
    dx = getDX();
    dy = getDY();
    
    this->dx += acceleration.getDDX() * time;
    this->dy += acceleration.getDDY() * time;
    
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *  Equation: s = d/t
 *
 * Paramaters:
 *  none
 * Returns:
 *  Speed calculation = s
 *********************************************/
double Velocity::getSpeed() const
{
    return sqrt(pow(getDX(), 2.0) + pow(getDY(), 2.0));
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *  dx=magnitude×cos(angle)
 *  dy=magnitude×sin(angle)
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
    this->dx = magnitude * sin(angle.getRadians());
    this->dy = magnitude * cos(angle.getRadians());
}
