/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"


/***************************************************************
 * RESET
 * Reset the lander and its position to start the game over
 ***************************************************************/
void Lander::reset(const Position & posUpperRight)
{
    angle.setUp();
    status = PLAYING; // set status to PLAYING when resetting
    fuel = 5000.0; // refill the fuel
    // set horizontal and vertical velocities to random values
    velocity.setDX(random(-10.0, -4.0));
    velocity.setDY(random(-2.0, 2.0));
    // set the position near the right edge of the screen and random vertical position
    pos.setX(posUpperRight.getX() - 1.0);
    pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust & thrust, ogstream & gout) const
{
    gout.drawLander(pos, angle.getRadians());
    if (isFlying() && fuel > 0.0)
    {
        gout.drawLanderFlames(pos, angle.getRadians(), thrust.isMain(), thrust.isClock(), thrust.isCounter());
    }
}

/***************************************************************
 * INPUT
 * Accept input from the user
 ***************************************************************/
Acceleration Lander::input(const Thrust& thrust, double gravity)
{
    Acceleration accel;
    double thrust_mag = 0.0;
    
    if (fuel > 0.0) // Check if there's enough fuel
    {
        // Apply thrust from the main engine
        if (thrust.isMain())
        {
            fuel -= 10.0;
            // Here you would apply the main engine thrust
            thrust_mag = thrust.mainEngineThrust();
        }

        // Handle rotational thrust
        if (thrust.isClock() || thrust.isCounter())
        {
            fuel -= 1.0;
            angle.setRadians(angle.getRadians() + thrust.rotation()); // Adjust angle for clockwise
        }
    }
    accel.set(angle, thrust_mag);
    accel.addDDY(gravity);
    return accel;
}


/******************************************************************
 * COAST
 * What happens when we coast?
 * s = s + v t + 1/2 a t^2
 *******************************************************************/
void Lander::coast(Acceleration & acceleration, double time)
{

    // update position based on the updated velocity
    pos.addX(velocity.getDX() * time + 0.5 * acceleration.getDDX() * pow(time, 2.0));
    pos.addY(velocity.getDY() * time + 0.5 * acceleration.getDDY() * pow(time, 2.0));
    
    
    // update velocity using the acceleration
    velocity.add(acceleration, time);
}
