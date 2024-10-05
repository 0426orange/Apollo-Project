#ifndef ACCELERATION_H
#define ACCELERATION_H

#include "angle.h"

class Acceleration {
private:
    double ddx; // Change in x-velocity
    double ddy; // Change in y-velocity

public:
    Acceleration(); // Default constructor
    Acceleration(double ddx, double ddy); // Parameterized constructor

    double getDDX() const; // Get ddx
    double getDDY() const; // Get ddy
    void setDDX(double ddx); // Set ddx
    void setDDY(double ddy); // Set ddy
    void set(const Angle& angle, double magnitude); // Set acceleration based on angle and magnitude
    void addDDX(double ddx); // Add to ddx
    void addDDY(double ddy); // Add to ddy
    void add(const Acceleration& rhs); // Add another Acceleration
};

#endif
