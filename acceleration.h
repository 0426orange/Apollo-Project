/***********************************************************************
 * Header File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about acceleration
 ************************************************************************/


#pragma once
#define GRAVITY -1.63

class TestAcceleration;
class TestVelocity;
class TestPosition;
class TestLander;
class Angle;


/*********************************************
 * Acceleration
 * Let's get moving
 *********************************************/
class Acceleration
{
    friend TestPosition;
    friend TestVelocity;
    friend TestAcceleration;
    friend TestLander;
    
public:
    // constructors
    Acceleration() : ddx(0.0), ddy(0.0){}// Default constructor
    Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy){} // Parameterized constructor
    
    // getters
    double getDDX() const {return ddx;}; // Get ddx
    double getDDY() const {return ddy;}; // Get ddy
    
    // setters
    void setDDX(double ddx)           { this->ddx = ddx; }
    void setDDY(double ddy)           { this->ddy = ddy; }
    void set(const Angle & a, double magnitude);
    void addDDX(double ddx)           { this->ddx += ddx; }
    void addDDY(double ddy)           { this->ddy += ddy; }
    void add(const Acceleration& rhs);
    
private:
    double ddx;     // horizontal acceleration
    double ddy;     // vertical acceleration
};
