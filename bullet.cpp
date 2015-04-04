//
//  bullet.cpp
//  asteroids
//
//  Created by Trevor on 4/1/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#include "bullet.h"

void Bullet::draw() const
{
    drawDot(velocity.getPoint());
}
void Bullet::drawBlue() const
{
    drawBlueDot(velocity.getPoint());
}
void Bullet::drawRed() const
{
    drawRedDot(velocity.getPoint());
}
void Bullet::fire(int angle, float shipX, float shipY, float shipDx, float shipDy)
{
    velocity.setPoint(Point(shipX, shipY));
    float angleRadians = deg2rad(angle);
    velocity.setDx(shipDx + ((-cos(angleRadians) * bulletSpeed)));
    velocity.setDy(shipDy + ((-sin(angleRadians) * bulletSpeed)));
}