#include "acceleration.h"
#include <cmath> // Needed for cos() and sin()

// Default constructor
Acceleration::Acceleration() : ddx(0), ddy(0) {}

// Parameterized constructor
Acceleration::Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

// Get ddx
double Acceleration::getDDX() const {
    return ddx;
}

// Get ddy
double Acceleration::getDDY() const {
    return ddy;
}

// Set ddx
void Acceleration::setDDX(double ddx) {
    this->ddx = ddx;
}

// Set ddy
void Acceleration::setDDY(double ddy) {
    this->ddy = ddy;
}

// Set acceleration based on angle and magnitude
void Acceleration::set(const Angle& angle, double magnitude) {
    this->ddx = magnitude * cos(angle.getRadians());
    this->ddy = magnitude * sin(angle.getRadians());
}

// Add to ddx
void Acceleration::addDDX(double ddx) {
    this->ddx += ddx;
}

// Add to ddy
void Acceleration::addDDY(double ddy) {
    this->ddy += ddy;
}

// Add another Acceleration
void Acceleration::add(const Acceleration& rhs) {
    this->ddx += rhs.ddx;
    this->ddy += rhs.ddy;
}
