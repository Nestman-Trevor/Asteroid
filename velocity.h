/***********************************************************************
 * Header File:
 *    VELOCITY: A point in motion
 * Author:
 *    Br. Helfrich and Br. Comeau
 * Summary:
 *    Everything we need to know about a point in motion, including
 *    Velocity addition (additive Velocitys) and subtraction (distance)
 ************************************************************************/

#ifndef _VELOCITY_H
#define _VELOCITY_H

#include <cmath>      // for M_PI, sin() and cos()
#include <iostream>   // for ISTREAM and OSTREAEM
#include "point.h"


#define deg2rad(value) ((M_PI / 180) * (value))
#define rad2deg(value) ((value) * (180 / M_PI))

/*******************************************
 * Velocity
 * A point, plus angle, plus magnitude
 ******************************************/
class Velocity
{
public:
   // constructors
   Velocity() :       point(), dx(0.0), dy(0.0)   {               };
   Velocity(const Velocity &rhs)                  { *this = rhs;  };
   Velocity(float x, float y, float dx, float dy) : point(x, y), dx(dx), dy(dy) {};

   // getters
   Point getPoint()      const;
   float getX()          const { return point.getX();            };
   float getY()          const { return point.getY();            };
   float getDx()         const { return dx;                      };
   float getDy()         const { return dy;                      };
   float getMag()        const { return sqrt(dx * dx + dy * dy); };
   float getAngle()      const { return rad2deg(atan2(-dy, dx)); };
   bool getWrap()        const { return point.getWrap(); };
   bool getCheck()       const { return point.getCheck(); };
   
   // setters
   void setX(float x)          { point.setX(x); };
   void setY(float y)          { point.setY(y); };
   void addX(float x)          { point.addX(x); };
   void addY(float y)          { point.addY(y); };
   void setDx(float dx)        { this->dx = dx; };
   void setDy(float dy)        { this->dy = dy; };

   void setMag(float mag);
   void setAngle(float angle);
   void setVelocity(float angleDegrees, float speed);

   void setWrap(bool wrap)	   { point.setWrap(wrap); };
   void setCheck(bool check)   { point.setCheck(check); };
   void setPoint(Point pt)     { point = pt; };

   // arithemetic 
   Velocity   operator ++ (int postfix);
   Velocity & operator ++ ();       
   float      operator -  (const Velocity &rhs) const;   // minimum distance
   Velocity   operator +  (const Velocity &rhs) const;   // Velocity addition
   Velocity & operator += ( const Velocity & rhs);

   // comparision
   bool operator == (const Velocity & rhs);
   bool operator != (const Velocity & rhs);
   bool operator < (const float scalar);
   bool operator > (const float scalar);
   bool operator <= (const float scalar);
   bool operator >= (const float scalar);

   // assignment
   const Velocity & operator = (const Velocity & rhs);
   const Velocity & operator = (const Point & rhs);
   
private:
   float dx;
   float dy;
   Point point;
};

// for debug purposes
std::ostream & operator << (std::ostream & out, const Velocity & v);
std::istream & operator >> (std::istream & in,        Velocity & v);

#endif
