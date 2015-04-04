/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

//#define LINUX
#define MAC_XCODE
//#define WIN_VISUAL_STUDIO

#ifdef MAC_XCODE
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // MAC_XCODE

#ifdef LINUX
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // LINUX

#ifdef WIN_VISUAL_STUDIO
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // WIN_VISUAL_STUDIO


#include "point.h"
#include "uiDraw.h"

using namespace std;

#define deg2rad(value) ((M_PI / 180) * (value))

/*********************************************
 * NUMBER OUTLINES
 * We are drawing the text for score and things
 * like that by hand to make it look "old school."
 * These are how we render each individual charactger.
 * Note how -1 indicates "done".  These are paired
 * coordinates where the even are the x and the odd
 * are the y and every 2 pairs represents a point
 ********************************************/
const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit)
{
   // we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   // compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   // go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      //Draw a line based off of the num structure for each number
      Point start;
      start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
      start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
      end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);
         
      drawLine(start, end);
   }
}

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned int number)
{
   // render the number as text
   ostringstream sout;
   sout << number;
   string text = sout.str();

   // walk through the text one digit at a time
   Point point = topLeft;
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}
void drawRedNumber(const Point & topLeft, unsigned int number)
{
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
    // render the number as text
    ostringstream sout;
    sout << number;
    string text = sout.str();
    
    // walk through the text one digit at a time
    Point point = topLeft;
    for (const char *p = text.c_str(); *p; p++)
    {
        assert(isdigit(*p));
        drawDigit(point, *p);
        point.addX(11);
    }
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);

}
void drawBlueNumber(const Point & topLeft, unsigned int number)
{
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
    // render the number as text
    ostringstream sout;
    sout << number;
    string text = sout.str();
    
    // walk through the text one digit at a time
    Point point = topLeft;
    for (const char *p = text.c_str(); *p; p++)
    {
        assert(isdigit(*p));
        drawDigit(point, *p);
        point.addX(11);
    }
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
}
/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Point & topLeft, const char * text)
{
   void *pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

   // prepare to draw the text from the top-left corner
   glRasterPos2f(topLeft.getX(), topLeft.getY());

   // loop through the text
   for (const char *p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   // remember our original point
   Point tmp(false /*check*/);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());

   // find the new values
   point.setX(static_cast<int> (tmp.getX() * cosA -
                                tmp.getY() * sinA) +
              origin.getX());
   point.setY(static_cast<int> (tmp.getX() * sinA +
                                tmp.getY() * cosA) +
              origin.getY());
}

/************************************************************************
 * DRAW ASTEROID
 * This method will draw an asteroid to the screen
 *  INPUT   Point:      Tells the asteroid where to draw the asteroid
 *          rotation:   What rotation the asteroid will print at
 *          size:       Determines the size of all the asteroids
 *************************************************************************/
void drawAsteroid(const Point & center, int size, int rotation)
{
    //initially create all the points and set them to the asteroid position
    Point A1( center);   //upper left quadrant
    Point A2( center);   //upper left quadrant
    Point A3( center);   //upper left quadrant
    Point B1( center);   //upper right quadrant
    Point B2( center);   //upper right quadrant
    Point B3( center);   //upper right quadrant
    Point C1( center);   //lower left quadrant
    Point C2( center);   //lower left quadrant
    Point C3( center);   //lower left quadrant
    Point C4( center);   //lower left quadrant
    Point D1( center);   //lower right quadrant
    Point D2( center);   //lower right quadrant
    Point D3( center);   //lower right quadrant
    
    Point E1( center);   //upper left quadrant crater
    Point E2( center);   //upper right quadrant crater
    Point E3( center);   //lower left quadrant crater
    
    //Change all the points to their right position
    A1.addX(-4 * size);
    A1.addY(5 * size);
    
    A2.addX(-4 * size);
    A2.addY(4 * size);
    
    A3.addX(-6 * size);
    A3.addY(3 * size);
    
    B1.addX(2 * size);
    B1.addY(6 * size);
    
    B2.addX(5 * size);
    B2.addY(3 * size);
    
    B3.addX(6 * size);
    //B3 Y stays at this point
    
    C1.addX(-6 * size);
    C1.addY(-1 * size);
    
    C2.addX(-5 * size);
    C2.addY(-4 * size);
    
    C3.addX(-3 * size);
    C3.addY(-4 * size);
    
    //C4 X stays the same
    C4.addY(-6 * size);
    
    D1.addX(2 * size);
    D1.addY(-2 * size);
    
    D2.addX(4 * size);
    D2.addY(-3 * size);
    
    D3.addX(6 * size);
    D3.addY(-2 * size);
    
    E1.addX(-3 * size);
    E1.addY(2 * size);
    
    E2.addX(1 * size);
    E2.addY(1 * size);
    
    E3.addX(-1 * size);
    E3.addY(-2 * size);
    
    A1.setWrap(false);
    A2.setWrap(false);
    A3.setWrap(false);
    B1.setWrap(false);
    B2.setWrap(false);
    B3.setWrap(false);
    C1.setWrap(false);
    C2.setWrap(false);
    C3.setWrap(false);
    C4.setWrap(false);
    D1.setWrap(false);
    D2.setWrap(false);
    D3.setWrap(false);
    E1.setWrap(false);
    E2.setWrap(false);
    E3.setWrap(false);
    
    //Rotate everything
    rotate(A1, center, rotation);
    rotate(A2, center, rotation);
    rotate(A3, center, rotation);
    rotate(B1, center, rotation);
    rotate(B2, center, rotation);
    rotate(B3, center, rotation);
    rotate(C1, center, rotation);
    rotate(C2, center, rotation);
    rotate(C3, center, rotation);
    rotate(C4, center, rotation);
    rotate(D1, center, rotation);
    rotate(D2, center, rotation);
    rotate(D3, center, rotation);
    rotate(E1, center, rotation);
    rotate(E2, center, rotation);
    rotate(E3, center, rotation);
    
    //Draw everything
    glBegin(GL_LINE_STRIP);
    glVertex2f(A1.getX(), A1.getY());
    glVertex2f(A2.getX(), A2.getY());
    glVertex2f(A3.getX(), A3.getY());
    glVertex2f(C1.getX(), C1.getY());
    glVertex2f(C2.getX(), C2.getY());
    glVertex2f(C3.getX(), C3.getY());
    glVertex2f(C4.getX(), C4.getY());
    glVertex2f(D1.getX(), D1.getY());
    glVertex2f(D2.getX(), D2.getY());
    glVertex2f(D3.getX(), D3.getY());
    glVertex2f(B3.getX(), B3.getY());
    glVertex2f(B2.getX(), B2.getY());
    glVertex2f(B1.getX(), B1.getY());
    glVertex2f(A1.getX(), A1.getY());
    glEnd();
    
    drawCircle(E1, size);
    drawCircle(E2, 2 * size);
    drawCircle(E3, size);
    }

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *  INPUT  center    Center of the rectangle
 *         width     Horizontal size
 *         height    Vertical size
 *         rotation  Orientation
 *************************************************************************/
void drawRect(const Point & center, char width, char height, int rotation)
{
   Point tl(false /*check*/); // top left
   Point tr(false /*check*/); // top right 
   Point bl(false /*check*/); // bottom left
   Point br(false /*check*/); // bottom right

   //Top Left point
   tl.setX(center.getX() - (width  / 2));
   tl.setY(center.getY() + (height / 2));

   //Top right point
   tr.setX(center.getX() + (width  / 2));
   tr.setY(center.getY() + (height / 2));

   //Bottom left point
   bl.setX(center.getX() - (width  / 2));
   bl.setY(center.getY() - (height / 2));

   //Bottom right point
   br.setX(center.getX() + (width  / 2));
   br.setY(center.getY() - (height / 2));

   //Rotate all points the given degrees
   rotate(tl, center, rotation);
   rotate(tr, center, rotation);
   rotate(bl, center, rotation);
   rotate(br, center, rotation);

   //Finally draw the rectangle
   glBegin(GL_LINE_STRIP);
   glVertex2f(tl.getX(), tl.getY());
   glVertex2f(tr.getX(), tr.getY());
   glVertex2f(br.getX(), br.getY());
   glVertex2f(bl.getX(), bl.getY());
   glVertex2f(tl.getX(), tl.getY());
   glEnd();
}

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 *          points   How many points will we draw it.  Larger the number,
 *                   the more line segments we will use
 *          rotation True circles are rotation independent.  However, if you
 *                   are drawing a 3-sided circle (triangle), this matters!
 *************************************************************************/
void drawCircle(const Point & center, char radius, int points, int rotation)
{
   // begin drawing
   glBegin(GL_LINE_LOOP);

   //loop around a circle the given number of times drawing a line from
   //one point to the next
   for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
   {
      Point temp(false /*check*/);
      temp.setX(center.getX() + static_cast<int>(radius * cos(i)));
      temp.setY(center.getY() + static_cast<int>(radius * sin(i)));
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }
   
   // complete drawing
   glEnd();

}
void drawCircle(const Point & center, int radius)
{
    assert(radius > 1.0);
    const double increment = 1.0 / (double)radius;
    
    // begin drawing
    glBegin(GL_LINE_LOOP);
    
    // go around the circle
    for (double radians = 0; radians < M_PI * 2.0; radians += increment)
        glVertex2f(center.getX() + (radius * cos(radians)),
                   center.getY() + (radius * sin(radians)));
    
    // complete drawing
    glEnd();
    
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void drawLine(const Point & begin, const Point & end,
              float red, float green, float blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f(red, green, blue);


   // Note how we scale the lines by a factor of two
   glVertex2f(begin.getX(), begin.getY());
   glVertex2f(  end.getX(),   end.getY());
   glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);

   // complete drawing.
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point & point)
{
   // Get ready, get set...
   glBegin(GL_POINTS);

   // Go...
   glVertex2f(point.getX(),     point.getY()    );
   glVertex2f(point.getX() + 1, point.getY()    );
   glVertex2f(point.getX() + 1, point.getY() + 1);
   glVertex2f(point.getX(),     point.getY() + 1);

   // Done!  OK, that was a bit too dramatic
   glEnd();
}
void drawRedDot(const Point & point)
{
    // Get ready, get set...
    glBegin(GL_POINTS);
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
    // Go...
    glVertex2f(point.getX(),     point.getY()    );
    glVertex2f(point.getX() + 1, point.getY()    );
    glVertex2f(point.getX() + 1, point.getY() + 1);
    glVertex2f(point.getX(),     point.getY() + 1);
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    // Done!  OK, that was a bit too dramatic
    glEnd();
}
void drawBlueDot(const Point & point)
{
    // Get ready, get set...
    glBegin(GL_POINTS);
    glColor3f(0.0 /* red % */, 0.0 /* green % */, 1.0 /* blue % */);
    // Go...
    glVertex2f(point.getX(),     point.getY()    );
    glVertex2f(point.getX() + 1, point.getY()    );
    glVertex2f(point.getX() + 1, point.getY() + 1);
    glVertex2f(point.getX(),     point.getY() + 1);
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    // Done!  OK, that was a bit too dramatic
    glEnd();
}
/************************************************************************
 * DRAW Ship
 * Draw a spaceship on the screen
 *  INPUT point   The position of the ship
 *        angle   Which direction it is ponted
 *************************************************************************/
void drawShip(const Point & center, int rotation)
{
   // Get ready, get set...
   glBegin(GL_LINE_STRIP);

   Point bow(      center); // front
   Point stern(    center); // back
   Point starboard(center); // right
   Point port(     center); // left

   bow.addX(-6);

   stern.addX(2);

   starboard.addY(3);
   starboard.addX(3);

   port.addY(-3);
   port.addX( 3);
   
    stern.setWrap(false);
    starboard.setWrap(false);
    port.setWrap(false);
    bow.setWrap(false);
    
   //Rotate all points the given degrees
   rotate(bow,       center, rotation);
   rotate(stern,     center, rotation);
   rotate(starboard, center, rotation);
   rotate(port,      center, rotation);

   //Finally draw the rectangle
   glBegin(GL_LINE_STRIP);
   glVertex2f(      bow.getX(),       bow.getY());
   glVertex2f(starboard.getX(), starboard.getY());
   glVertex2f(    stern.getX(),     stern.getY());
   glVertex2f(     port.getX(),      port.getY());
   glVertex2f(      bow.getX(),       bow.getY());
   
   // Done!  OK, that was a bit too dramatic
   glEnd();   
}
void drawRedShip(const Point & center, int rotation)       //Red
{
    // Get ready, get set...
    glBegin(GL_LINE_STRIP);
    
    Point bow(      center); // front
    Point stern(    center); // back
    Point starboard(center); // right
    Point port(     center); // left
    
    bow.addX(-9);
    
    stern.addX(3);
    
    starboard.addY(5);
    starboard.addX(5);
    
    port.addY(-5);
    port.addX( 5);
    
    stern.setWrap(false);
    starboard.setWrap(false);
    port.setWrap(false);
    bow.setWrap(false);
    
    //Rotate all points the given degrees
    rotate(bow,       center, rotation);
    rotate(stern,     center, rotation);
    rotate(starboard, center, rotation);
    rotate(port,      center, rotation);
    
    //Finally draw the rectangle
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
    
    glVertex2f(      bow.getX(),       bow.getY());
    glVertex2f(starboard.getX(), starboard.getY());
    glVertex2f(    stern.getX(),     stern.getY());
    glVertex2f(     port.getX(),      port.getY());
    glVertex2f(      bow.getX(),       bow.getY());
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    // Done!  OK, that was a bit too dramatic
    glEnd();
}
void drawBlueShip(const Point & center, int rotation)       //Blue
{
    // Get ready, get set...
    glBegin(GL_LINE_STRIP);
    
    Point bow(      center); // front
    Point stern(    center); // back
    Point starboard(center); // right
    Point port(     center); // left
    
    bow.addX(-9);
    
    stern.addX(3);
    
    starboard.addY(5);
    starboard.addX(5);
    
    port.addY(-5);
    port.addX( 5);
    
    stern.setWrap(false);
    starboard.setWrap(false);
    port.setWrap(false);
    bow.setWrap(false);
    
    //Rotate all points the given degrees
    rotate(bow,       center, rotation);
    rotate(stern,     center, rotation);
    rotate(starboard, center, rotation);
    rotate(port,      center, rotation);
    
    //Finally draw the rectangle
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0 /* red % */, 0.0 /* green % */, 1.0 /* blue % */);
    
    glVertex2f(      bow.getX(),       bow.getY());
    glVertex2f(starboard.getX(), starboard.getY());
    glVertex2f(    stern.getX(),     stern.getY());
    glVertex2f(     port.getX(),      port.getY());
    glVertex2f(      bow.getX(),       bow.getY());
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    // Done!  OK, that was a bit too dramatic
    glEnd();   
}
/***********************************************************************
 * DRAW Lander
 * Draw a moon-lander spaceship on the screen at a given point
 ***********************************************************************/
void drawLander(const Point & point)
{
   // ultra simple point
   struct PT
   {
      int x;
      int y;
   } points[] = 
   {
      {-6, 0}, {-10,0}, {-8, 0}, {-8, 3},  // left foot
      {-5, 4}, {-5, 7}, {-8, 3}, {-5, 4},  // left leg
      {-1, 4}, {-3, 2}, { 3, 2}, { 1, 4}, {-1, 4}, // bottom
      { 5, 4}, { 5, 7}, {-5, 7}, {-3, 7},  // engine square
      {-6,10}, {-6,13}, {-3,16}, { 3,16},   // left of habitat
      { 6,13}, { 6,10}, { 3, 7}, { 5, 7},   // right of habitat
      { 5, 4}, { 8, 3}, { 5, 7}, { 5, 4},  // right leg
      { 8, 3}, { 8, 0}, {10, 0}, { 6, 0}   // right foot
   };

   // draw it
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
        glVertex2f(point.getX() + points[i].x,
                   point.getY() + points[i].y);

   // complete drawing
   glEnd();
   
   
}


/***********************************************************************
 * DRAW Lander Flame
 * Draw the flames coming out of a moonlander for thrust
 ***********************************************************************/
void drawLanderFlames(const Point & point, 
                      bool bottom,
                      bool left,
                      bool right)
{
   // simple point
   struct PT
   {
      int x;
      int y;
   };

   int iFlame = random(0, 3);  // so the flame flickers
   
   // draw it
   glBegin(GL_LINE_LOOP);
   glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
   
   // bottom thrust
   if (bottom)
   {
      PT points[3][3] =
      {
         { {-5,  -6}, { 0, -1}, { 3, -10} },
         { {-3,  -6}, {-1, -2}, { 0, -15} },
         { { 2, -12}, { 1,  0}, { 6,  -4} }
      };
      
      glVertex2f(point.getX() - 2, point.getY() + 2);
      for (int i = 0; i < 3; i++)
         glVertex2f(point.getX() + points[iFlame][i].x,
                   point.getY() + points[iFlame][i].y);
      glVertex2f(point.getX() + 2, point.getY() + 2);
   }

   // right thrust
   if (right)
   {
      PT points[3][3] =
      {
         { {10, 14}, { 8, 12}, {12, 12} },
         { {12, 10}, { 8, 10}, {10,  8} },
         { {14, 11}, {14, 11}, {14, 11} }
      };
      
      glVertex2f(point.getX() + 6, point.getY() + 12);
      for (int i = 0; i < 3; i++)
         glVertex2f(point.getX() + points[iFlame][i].x,
                    point.getY() + points[iFlame][i].y);
      glVertex2f(point.getX() + 6, point.getY() + 10);
   }

   // left thrust
   if (left)
   {
      PT points[3][3] =
      {
         { {-10, 14}, { -8, 12}, {-12, 12} },
         { {-12, 10}, { -8, 10}, {-10,  8} },
         { {-14, 11}, {-14, 11}, {-14, 11} }
      };
      
      glVertex2f(point.getX() - 6, point.getY() + 12);
      for (int i = 0; i < 3; i++)
         glVertex2f(point.getX() + points[iFlame][i].x,
                    point.getY() + points[iFlame][i].y);
      glVertex2f(point.getX() - 6, point.getY() + 10);
   }

   glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    glEnd();
}


/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min <= max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   
   assert(min <= num && num <= max);

   return num;
}

