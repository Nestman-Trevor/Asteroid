//
//  asteroid.h
//  asteroids
//
//  Created by Trevor on 4/3/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#ifndef __asteroids__asteroid__
#define __asteroids__asteroid__

#include <stdio.h>
#include "movable.h"

class Asteroid : public Movable
{
public:
    Asteroid() : Movable(), size(3), rotationSpeed(random(-3, 3)), isAlive(true) {};
    Asteroid(float x, float y, float dX, float dY, int rotation, int newSize):
    Movable(), size(newSize), rotation(rotation), rotationSpeed(random(-3, 4)), isAlive(true)
    {
        velocity.setX(x), velocity.setY(y), velocity.setDx(dX), velocity.setDy(dY);
    };
    Asteroid(float x, float y, float dX, float dY, int currentSize):
    Movable(), size(currentSize - 3), rotation(random(0,360)), rotationSpeed(random(-3, 4)), isAlive(true)
    {
        velocity.setX(x + random(-7, 8)), velocity.setY(y + random(-7, 8)), velocity.setDx(dX + random(-2, 3)), velocity.setDy(dY + random(-2, 3));
    };
    
    int getSize() { return size;};
    
    void advanceAst()
    {
        velocity++;
        rotation += rotationSpeed;
        if (velocity.getDx() == 0 && velocity.getDy() == 0)
        {
            velocity.setDx(random(-1, 2));
            //std::cout <<  "rnd Dx: " << velocity.getDx() << ", ";
            velocity.setDy(random(-1, 2));
            //std::cout << "rnd Dy"  << velocity.getDx() << "\n";
        }
    };
    
    void draw();
    void kill() {isAlive = false;};
    bool alive() {return isAlive;};
    
private:
    int size;
    int rotationSpeed;
    int rotation;
    bool isAlive;
};

#endif /* defined(__asteroids__asteroid__) */
