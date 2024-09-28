/*************************************************************
 * 1. Name:
 *      Alexis Rudy & Tzu Hsu
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was figuring out which functions called each other
 *      to get the correct computations for the lander.
 * 5. How long did it take for you to complete the assignment?
 *      This assignment took about 10 hours.
 **************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath> // for Pi
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double position, double velocity, double acceleration, double time)
{
    double newPosition = position + velocity * time + 0.5 * acceleration * pow(time, 2);
    return newPosition;
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 *     f/m = a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double computeAcceleration (double force, double mass)
{
    return force/mass;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double velocity, double acceleration, double time)
{
    return velocity += acceleration * time;
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 *     y = total(cos(a))
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *   y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComponent(double angle, double total)
{
    double verticalComponent = total * cos(angle);
    return verticalComponent;
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 *     x = total(sin(a))
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double computeHorizontalComponent(double angle, double total)
{
    double horizontalComponent = total * sin(angle);
    return horizontalComponent;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double computeTotalComponent(double x, double y)
{
    double totalComponent = sqrt(pow(x, 2) + pow(y, 2));
    return totalComponent;
}


/*************************************************
 * RADIANS FROM DEGREES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 *     To convert from degrees to radians, multiply the number of degrees by π/180.
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double degreesToRadians(double degrees)
{
    double radians = degrees / 180.0 * M_PI ;
    return radians;
}
/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string message)
{
    double response;
    cout << message;
    cin >> response;
    return response;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx =       prompt("What is your horizontal velocity (m/s)? ");
    double dy =       prompt("What is your vertical velocity (m/s)? ");
    double y =        prompt("What is your altitude (m)? ");
    double x =        prompt("What is your position (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double t =        prompt("What is the time interval (s)? ");
    
    double radians = degreesToRadians(aDegrees);
    double accelerationThrust = computeAcceleration(THRUST, WEIGHT);                          // Acceleration due to thrust
    double ddxThrust = computeHorizontalComponent(radians, accelerationThrust);           // Horizontal acceleration due to thrust
    double ddyThrust = computeVerticalComponent(radians, accelerationThrust);                              // Vertical acceleration due to thrust
    double ddx = ddxThrust;                                    // Total horizontal acceleration
    double ddy = ddyThrust + GRAVITY;                          // Total vertical acceleration
    double v = 0.0;                                                                           // Total velocity

    

    // Go through the simulator five times
      // your code goes here
      // Hint: Update the position _before_ updating the velocity
    for (int i = 0; i < 5; i++)
    {
        // Update position
        x = computeDistance(x, dx, ddx, t);
        y = computeDistance(y, dy, ddy, t);

        dx = computeVelocity(dx, ddx, t);
        dy = computeVelocity(dy, ddy, t);
        v = computeTotalComponent(dx, dy);
        
      // Output
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);
      cout << "\tNew position:   (" <<  x << ", " <<  y << ")m\n";
      cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
      cout << "\tTotal velocity:  " << v << "m/s\n\n";

    }
   return 0;
}
