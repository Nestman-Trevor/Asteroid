/***********************************************************************
 * Source File:
 *    Velocity: A point in motion
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a point in motion, including
 *    Velocity addition (additive Velocitys) and subtraction (distance)
 ************************************************************************/

#include "velocity.h"
#include <cassert>
#include <cmath>
#include <limits>

#define EQUALDELTA    0.001

/**************************************
 * Velocity : Equality
 ************************************/
bool Velocity::operator == (const Velocity & rhs)
{
  return fabs(rhs.getX() - getX()) < EQUALDELTA &&
    fabs(rhs.getY() - getY()) < EQUALDELTA &&
    fabs(rhs.getDx() - getDx()) < EQUALDELTA &&
    fabs(rhs.getDy() - getDy()) < EQUALDELTA;
}

/****************************************
 * VELOCITY : ASSIGNMENT
 ****************************************/
const Velocity & Velocity::operator = (const Velocity & rhs)
{
   setX(rhs.getX());
   setY(rhs.getY());
   setDx(rhs.getDx());
   setDy(rhs.getDy());
   setWrap(rhs.getWrap());
   setCheck(rhs.getCheck());

   return *this;
}

/****************************************
 * VELOCITY : ASSIGNMENT
 ****************************************/
const Velocity & Velocity::operator = (const Point & rhs)
{
   setX(rhs.getX());
   setY(rhs.getY());
   setWrap(rhs.getWrap());
   setCheck(rhs.getCheck());

   return *this;
}

/**************************************
 * Velocity : Not Equality
 ************************************/
bool Velocity::operator != (const Velocity & rhs)
{
   return !(*this == rhs);
}

/****************************************
 * VELOCITY : Compare <
 ****************************************/
bool Velocity::operator < (const float scalar)
{
   double mag = sqrt(dx * dx + dy * dy);
   return (mag < scalar);
}

/****************************************
 * VELOCITY : Compare >
 ****************************************/
bool Velocity::operator > (const float scalar)
{
   double mag = sqrt(dx * dx + dy * dy);
   return (mag > scalar);
}

/****************************************
 * VELOCITY : Compare <=
 ****************************************/
bool Velocity::operator <= (const float scalar)
{
   double mag = sqrt(dx * dx + dy * dy);
   return (mag <= scalar);
}

/****************************************
 * VELOCITY : Compare >=
 ****************************************/
bool Velocity::operator >= (const float scalar)
{
   double mag = sqrt(dx * dx + dy * dy);
   return (mag >= scalar);
}

/***************************************
 * Velocity : GET POINT
 * Fetch the point out of a Velocity
 ***************************************/
Point Velocity::getPoint() const
{
   Point point(getX(), getY());
   point.setWrap(getWrap());
   point.setCheck(getCheck());
   return point;
}

/************************************
 * Velocity : SET MAG
 * Set the speed or magnitude of the velocity
 ***********************************/
void Velocity::setMag(float mag)
{
   float angle = deg2rad(getAngle());
   dx = -cos(angle) * mag;
   dy = -sin(angle) * mag;
}

/**********************************
 * Velocity : SET ANGLE
 * Set the angle of the current velocity
 *********************************/
void Velocity::setAngle(float angleDegrees)
{
   float angleRadians = deg2rad(angleDegrees);
   float speed = getMag();
   dx = -cos(angleRadians) * speed;
   dy = -sin(angleRadians) * speed;
}

/**************************************
 * Velocity : SET VELOCITY
 *          Set Dx and Dy for the Velocity
 * INPUT angleDegrees : new angle in degrees
 *       speed        : magnitude of the vecotr
 **************************************/
void Velocity::setVelocity(float angleDegrees, float speed)
{
   float angleRadians = deg2rad(angleDegrees);
   dx = -cos(angleRadians) * speed;
   dy = -sin(angleRadians) * speed;
}


/***************************************
 * Velocity : POSTFIX INCREMENT
 * Advance the Velocity by one time unit
 **************************************/
Velocity Velocity::operator ++ (int postfix)
{
   Velocity v = *this;
   addX(dx);
   addY(dy);
   return v;
}

/***************************************
 * Velocity : PREFIX INCREMENT
 * Advance the Velocity by one time unit
 **************************************/
Velocity & Velocity::operator ++ ()
{
   addX(dx);
   addY(dy);
   return *this;
}

/**************************************
 * Velocity : ADDITION
 * Add two Velocitys
 *************************************/
Velocity Velocity::operator + (const Velocity & rhs) const
{
   Velocity vReturn(*this);
   vReturn += rhs;
   return vReturn;
}

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))


/**************************************
 * Velocity : SUBTRACTION
 * Find the minimal distance between two Velocitys
 *************************************/
float Velocity::operator - (const Velocity & vRhs) const
{
   // find the maximum distance traveled
   using std::abs;
   float dMax = MAX(abs(dx), abs(dy));
   dMax = MAX(dMax, abs(vRhs.getDx()));
   dMax = MAX(dMax, abs(vRhs.getDy()));
   dMax = MAX(dMax, 0.1);
   
   // we will advance by this number
   float distMin = std::numeric_limits<float>::max();

   for (float i = 0.0; i <= dMax; i++)
   {
      Point pointLhs(     getX() + (dx * i / dMax),
                          getY() + (dy * i / dMax));
      Point pointRhs(vRhs.getX() + (vRhs.getDx() * i / dMax),
                     vRhs.getY() + (vRhs.getDy() * i / dMax));

      float distSquared =
         ((pointLhs.getX() - pointRhs.getX()) *
          (pointLhs.getX() - pointRhs.getX())) +
         ((pointLhs.getY() - pointRhs.getY()) *
          (pointLhs.getY() - pointRhs.getY()));
      distMin = MIN(distMin, distSquared);
   }

   return sqrt(distMin);
}


/**********************************************
 * Velocity +=
 *        Add the dx, dy of the rhs onto the current
 *        Velocity
 *********************************************/
Velocity & Velocity::operator += ( const Velocity & rhs)
{
   dx += rhs.getDx();
   dy += rhs.getDy();
   return *this;
}

/******************************************
 * Velocity insertion
 *       Display a Velocity on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Velocity & v)
{
   out << v.getPoint()
       << " [" << v.getDx() << ", " << v.getDy() << "]";
   return out;
}

/*******************************************
 * Velocity extraction
 *        Prompt for Velocity coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Velocity & v)
{
   float x;
   float y;
   float dx;
   float dy;
   in >> x >> y >> dx >> dy;

   v.setX(x);
   v.setY(y);
   v.setDx(dx);
   v.setDy(dy);
   
   return in;
}
