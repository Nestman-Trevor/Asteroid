//
//  ship.cpp
//  asteroids
//
//  Created by Trevor on 4/1/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#include "ship.h"


void Ship::rotate(int right, int left)
{
    if (right)
    {
        if (right < 25)
            rotation -= (right   + 10) / 2;
        else
            rotation -= 25;
        //std::cout << "I'm turning right!\n";
    }
    if (left)
    {
        if (left < 25)
            rotation += (left + 10) / 2;
        else
            rotation += 25;
        //std::cout << "I'm turning left\n";
    }
    
    if (rotation < 0)
        rotation = 360;
    if (rotation > 360)
        rotation = 0;
}

void Ship::forward(int forward)
{
    if (forward)
    {
        float angleRadians = deg2rad(rotation);
        velocity.setDx(velocity.getDx() + ((-cos(angleRadians) * speed)));
        velocity.setDy(velocity.getDy() + ((-sin(angleRadians) * speed)));
    }
    if (velocity.getDx() > maxSpeed)
        velocity.setDx(maxSpeed);
    if (velocity.getDx() < -maxSpeed)
        velocity.setDx(-maxSpeed);
    if (velocity.getDy() > maxSpeed)
        velocity.setDy(maxSpeed);
    if (velocity.getDy() < -maxSpeed)
        velocity.setDy(-maxSpeed);
}