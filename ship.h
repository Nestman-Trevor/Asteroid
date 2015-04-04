//
//  ship.h
//  asteroids
//
//  Created by Trevor on 4/1/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#ifndef __asteroids__ship__
#define __asteroids__ship__

#include <stdio.h>
#include "movable.h"

class Ship : public Movable
{
public:
    Ship() : Movable(), rotation(180), speed(.2), maxSpeed(5), isDead(false){};
    Ship(float x, float y, int givenRot) :
    Movable(), rotation(givenRot), speed(.2), maxSpeed(5), isDead(false)
    {velocity.setX(x), velocity.setY(y);};
    
    void draw() const {drawShip(getPoint(), rotation);};
    void drawRed() const {drawRedShip(getPoint(), rotation);};
    void drawBlue() const {drawBlueShip(getPoint(), rotation);};
    
    void forward(int forward);
    void stop() {velocity.setDy(0), velocity.setDx(0);};
    void rotate(int right, int left);
    int getRotation() const {return rotation;};
    void setRotation(int newRot) {rotation = newRot;};
    void deadStatus(bool dead) {isDead = dead;};
    bool shipDead() {return isDead;};
    
private:
    int rotation;
    float speed;
    float maxSpeed;
    bool isDead;
};

#endif /* defined(__asteroids__ship__) */
