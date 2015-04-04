//
//  bullet.h
//  asteroids
//
//  Created by Trevor on 4/1/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#ifndef __asteroids__bullet__
#define __asteroids__bullet__

#include <stdio.h>
#include "movable.h"
#include "velocity.h"

class Bullet : public Movable
{
public:
    Bullet() : Movable(), bulletSpeed(7), isAlive(true), counter(0){};
    Bullet(int angle, float shipX, float shipY, float shipDx, float shipDy)
    : Movable(), bulletSpeed(7), isAlive(true), counter(0)
    {fire(angle, shipX, shipY, shipDx, shipDy);};
    
    int getBulletSpeed()  {return bulletSpeed;};
    
    void fire(int angle, float shipX, float shipY, float shipDx, float shipDy);
    void draw() const;
    void drawBlue() const;
    void drawRed() const;
    void kill() {isAlive = false;};
    bool alive() {return isAlive;};
    void addCounter() {counter += velocity.getMag();};
    float getCounter() {return counter;};
    
private:
    bool isAlive;
    float bulletSpeed;
    bool penetrating;
    float counter;
};

#endif /* defined(__asteroids__bullet__) */
