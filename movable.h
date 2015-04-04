//
//  movable.h
//  skeet
//
//  Created by Trevor on 3/16/15.
//  Copyright (c) 2015 Trevor. All rights reserved.
//

#ifndef __skeet__movable__
#define __skeet__movable__

#include <stdio.h>
#include "velocity.h"
#include "uiDraw.h"

class Movable
{
public:
    Movable(): velocity() {};
    Movable(Velocity givenVel) : velocity(givenVel) {};
    Movable(float x, float y, float dx, float dy) : velocity(x, y, dx, dy) {};
    
    Point getPoint()    const { return velocity.getPoint(); };
    float getX()        const { return velocity.getX();     };
    float getY()        const { return velocity.getY();     };
    float getDx()       const { return velocity.getDx();    };
    float getDy()       const { return velocity.getDy();    };
    Velocity getVelocity() const { return velocity;         };
    
    void setPoint(Point point)  {velocity.setPoint(point);  };
    void setX(float x)          {velocity.setX(x);          };
    void setY(float y)          {velocity.setY(y);          };
    void setDx(float dx)        {velocity.setDx(dx);        };
    void setDy(float dy)        {velocity.setDy(dy);        };
    
    void advance()  {velocity++;};
    void draw() const {};
    
protected:
    Velocity velocity;
    
private:
    
    
};

#endif /* defined(__skeet__movable__) */
