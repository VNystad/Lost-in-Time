#include "testapp.h"

TestApp::TestApp() : config(config), window(window)
{
    //Create window
    window = new sf::RenderWindow;
    window->create(sf::VideoMode(800, 600), "Test game with animation");
    window->setVerticalSyncEnabled(true);

    //Create player
    p = new PlayerTest(200, 250, config, window);

    //Create platforms
    platform1 = new TestCollidablePlatform(200, 200, config, window);
    platform2 = new TestCollidablePlatform(100, 300, config, window);

    clock = new sf::Clock;
    clock->restart();
}

bool TestApp::Tick()
{
    sf::Event event;
    float delta = clock->restart().asSeconds();

    // Get events from OS
    while (window->pollEvent(event))
    {
        // Close the window if the user clicks the x button
        if (event.type == sf::Event::Closed)
        {
            window->close();
            return false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
        return false;
    }

    Move(delta);

    window->clear(sf::Color::Black);

    p->DrawMe();
    platform1->DrawMe();
    platform2->DrawMe();

    window->display();

    return true;
}

void TestApp::Move(float delta)
{
    //This function will make the object able to move and fall, with correlation to any hinderings such as gravity.
    //The delta float is there for smoothness.

    Movement(delta);
    Gravity(delta);

    // Keep the box within screen borders
    p->SetPositionX(std::max(p->GetPositionX(), 0.f));
    p->SetPositionX(std::min(p->GetPositionX(), (float)(config.screenWidth - p->GetSize())));
    p->SetPositionX(std::min(p->GetPositionX(), (float)(config.screenWidth - p->GetSize())));
    p->SetPositionY(std::max(p->GetPositionY(), 0.f));
    p->SetPositionY(std::min(p->GetPositionY(), (float)(config.screenHeight - p->GetSize())));
}

void TestApp::Gravity(float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
    if(Grounded())
    {
        p->SetJumpCheck(false);
        p->SetFallSpeed(0);
        float temp = p->GetOrigJumpSpeed();
        p->SetJumpSpeed(temp);
    }

        //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(!p->GetJumpCheck())
    {
        p->SetJumpCheck(true);
        p->SetApexCheck(true);
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !p->GetJumpCheck())
    {
        p->SetJumpCheck(true);
        p->SetApexCheck(false);
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(p->GetJumpCheck())
    {
        if(p->GetVertiCollCD() <= delta)
            p->SetVertiCollCD(p->GetVertiCollCD() + delta);
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(p->GetJumpSpeed() >= 0 && !p->GetApexCheck())
        {
            float pixelstomove = (( p->GetJumpPower() * p->GetJumpSpeed() ) / p->GetGravity() ) * (delta);
            p->SetJumpSpeed(p->GetJumpSpeed() - 1);

            for(float i = pixelstomove; i >= 0; i -= 1 )
            {
                if(Grounded() && p->GetVertiCollCD() > delta)
                {
                    i = -1;
                    p->SetPositionY(p->GetPositionY() + 1);
                    p->SetApexCheck(true);
                }

                else
                    p->SetPositionY(p->GetPositionY() - 1);
                p->DrawMe();
            }
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            p->SetVertiCollCD(0);
            p->SetApexCheck(true);
            float pixelstomove = (p->GetJumpPower() * p->GetFallSpeed() / p->GetGravity() * (delta));

            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(Grounded())
                {
                    i = -1;
                }

                else
                    p->SetPositionY(p->GetPositionY() + 1);
                p->DrawMe();;
            }

            //Fallspeed cannot exceed the max fallspeed, the real life equivalent of wind resistance limiting
            //a falling objects fallspeed.
            if(p->GetFallSpeed() < p->GetMaxFallSpeed())
            {
                p->SetFallSpeed(p->GetFallSpeed() + 1);
            }
        }
    }
    //Gravity End-------------------------------------------------------------------------------------------------------
}

void TestApp::Movement(float delta)
{
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    if(Grounded())
    {
        p->SetHoriCollCD(0);
    }
    else
        p->SetHoriCollCD(p->GetHoriCollCD() + delta );

    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        p->SetMovDir(0); //Means to the left
        p->SetSlowDownL(false);
    }
    else
        p->SetSlowDownL(true); //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        p->SetMovDir(1); //Means to the right
        p->SetSlowDownR(false);
    }
    else
        //Object does not accelerate to the right, should slow down if moving to the right
        p->SetSlowDownR(true);

    //Left speed handler
    //If the object is moving to the left OR the movespeed to the left is greater than zero

    if(p->GetMovDir() == 1 || p->GetMoveSpeedL() > 0)
    {
        if(p->GetSlowDownL())
        {
            if(p->GetMoveSpeedL() >= p->GetMovePower() * p->GetHorBrake() && p->GetMovDir() == 0 )
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                p->SetMoveSpeedL(p->GetMoveSpeedL() - p->GetMovePower() * p->GetHorBrake());
            }
            else if(p->GetMoveSpeedL() >= p->GetMovePower() *p->GetRegularBrake())
            {
                //Not accelerating nor trying to stop, slows down slowly
                p->SetMoveSpeedL(p->GetMoveSpeedL() - p->GetMovePower() * p->GetRegularBrake());
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                p->SetMoveSpeedL(0);
        }
        else if(p->GetMoveSpeedL() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedL(p->GetMoveSpeedR() + p->GetMovePower());

        //The object is actually being moved
        float pixelstomove = p->GetMoveSpeedR() * delta;

        for(float i = pixelstomove; i >= 0; i -= 1 )
        {
            if(Grounded() && p->GetHoriCollCD() >= delta)
            {
                i = -1;
                p->SetPositionX(p->GetPositionX() -1 );
            }

            else if(i != 0)
                p->SetPositionX(p->GetPositionX() +1 );
            p->DrawMe();
        }
    }

    //Right speed handler
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if(p->GetMovDir() == 1 || p->GetMoveSpeedR() > 0)
    {
        if(p->GetSlowDownR())
        {
            if(p->GetMoveSpeedR() >= p->GetMovePower() * p->GetHorBrake() && p->GetMovDir() == 0 )
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                p->SetMoveSpeedR(p->GetMoveSpeedR() - p->GetMovePower() * p->GetHorBrake());
            }
            else if(p->GetMoveSpeedR() >= p->GetMovePower() *p->GetRegularBrake())
            {
                //Not accelerating nor trying to stop, slows down slowly
                p->SetMoveSpeedR(p->GetMoveSpeedR() - p->GetMovePower() * p->GetRegularBrake());
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                p->SetMoveSpeedR(0);
        }
        else if(p->GetMoveSpeedR() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedR(p->GetMoveSpeedR() + p->GetMovePower());

        //The object is actually being moved
        float pixelstomove = p->GetMoveSpeedR() * delta;

        for(float i = pixelstomove; i >= 0; i -= 1 )
        {
            if(Grounded() && p->GetHoriCollCD() >= delta)
            {
                i = -1;
                p->SetPositionX(p->GetPositionX() -1 );
            }

            else if(i != 0)
                p->SetPositionX(p->GetPositionX() +1 );
            p->DrawMe();
        }
    }
}
bool TestApp::Grounded()
{
    //Simply checks if the object is currently on the ground
    if(p->GetCharacter().getLocalBounds().intersects(platform1->GetPlatform().getLocalBounds())
       || p->GetCharacter().getLocalBounds().intersects(platform2->GetPlatform().getLocalBounds()))
    {
        return true;
    }
    else
        return false;
}
