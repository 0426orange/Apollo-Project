/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
using namespace std;

#define MAX_STARS 50

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
    Simulator(const Position & posUpperRight) : ground(posUpperRight), lander(posUpperRight)
    {
        for (int i = 0; i < MAX_STARS; i++)
        {
            stars[i].reset(posUpperRight.getX(), posUpperRight.getY());
        }
    }
    void display(Thrust &thrust);
                                                       
private:
    Ground ground;
    Star stars[MAX_STARS];
    Lander lander;
};

void Simulator::display(Thrust &thrust)
{
    ogstream gout;
    Acceleration accel;
    
    for (int i = 0; i < MAX_STARS; i++)
    {
        stars[i].draw(gout);
    }
    // draw the ground
    ground.draw(gout);
    
    if (lander.isFlying())
    {
        accel = lander.input(thrust, GRAVITY);
        lander.coast(accel, 0.1);
        if (ground.hitGround(lander.getPosition(), lander.getWidth()))
        {
            lander.crash();
        }
        else if (ground.onPlatform(lander.getPosition(), lander.getWidth()))
        {
            lander.land();
        }
        
    }
    lander.draw(thrust, gout);
    
    
}


/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL.
    Simulator * pSimulator = (Simulator *)p;
    Thrust thrust;
    thrust.set(pUI);
    pSimulator->display(thrust);
    
    
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
                   _In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR pCmdLine,
                   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Run the unit tests
    testRunner();
    
    
    // Initialize OpenGL
    Position posUpperRight(400, 400);
    Interface ui("Lunar Lander", posUpperRight);
    
    // Initialize the game class
    Simulator simulator(posUpperRight);
    
    // set everything into action
    ui.run(callBack, (void *)&simulator);
    
    return 0;
}
