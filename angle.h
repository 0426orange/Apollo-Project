/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

#define TWO_PI 6.28318530718


class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   
   // Constructors
   Angle()                 : radians()  {}
    Angle(const Angle& rhs) : radians(rhs.radians)  {}
    Angle(double degrees)   : radians(normalize(convertToRadians(degrees)))  {}

   // Getters
    double getDegrees() const { return convertToDegrees(normalize(radians)); }
    double getRadians() const { return normalize(radians); }

   // Setters
    void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }
    void setRadians(double r)       { radians = normalize(r); }
    void setUp()                    { radians = convertToRadians(0);}
    void setDown()                  { radians = convertToRadians(180); }
    void setRight()                 { radians = convertToRadians(90); }
    void setLeft()                  { radians = convertToRadians(270); }
    void reverse()                  { radians += M_PI;}
    Angle& add(double delta)        { radians += normalize(delta); return *this; }

private:
   double normalize(double radians) const;
    double convertToDegrees(double radians) const;
    double convertToRadians(double degrees) const;

   double radians;   // 360 degrees equals 2 PI radians
};

