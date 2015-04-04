//
//  asteroid.cpp
//  asteroids
//
//  Created by Trevor on 4/3/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#include "asteroid.h"

void Asteroid::draw()
{
    drawAsteroid(velocity.getPoint(), size, rotation);
}

