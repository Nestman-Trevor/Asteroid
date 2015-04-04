/***********************************************************************
 * Source File:
 *    Skeet ++ - main file for this game
 * Author:
 *    Br. Comeau
 * Summary:
 *    This project will impliment the Skeet game outlined in the cs165
 *    textbook.
 ************************************************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "movable.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include <vector>
#include <list>
#include <string>
#include <sstream>

using namespace std;

#define X_SIZE          1000
#define Y_SIZE          800
#define SCORE_LIMIT     9000
#define NUM_ASTEROIDS_ADD   4

// set the bounds of the drawing rectangle
float Point::xMin = -(X_SIZE / 2.0);
float Point::xMax =  (X_SIZE / 2.0);
float Point::yMin = -(Y_SIZE / 2.0);
float Point::yMax =  (Y_SIZE / 2.0);

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : gameOver(false) {}
   
   // handle user input
   void input(const Interface & ui);

   // advance the game
   void advance();
         
   // draw stuff
   void draw(const Interface & ui);
    
 
   
private:
   
   // Sample code on how to use a vector
   // delete it if you don't need it
   list<Point> points;

   bool gameOver;
    double blueScore = 0;
    double redScore = 0;
    int numAsteroids = 0;
   
   // TODO: Create ship, bullets and rocks
    Ship shipBlue;
    Ship shipRed;
    list<Bullet> blueBullets;
    list<Bullet> redBullets;
    list<Asteroid> asteroids;
    list<Asteroid> tempAst;
    
   // TODO: add any objects or variables that are required

   void detectHits();
   void removeDeadObjects();
   void restart();
};

/***************************************
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // TODO: advance anything that moves
    shipBlue.advance();
    shipRed.advance();
    
    for (list<Bullet>::iterator it = blueBullets.begin(); it != blueBullets.end(); ++it)
    {
        (*it).advance();
        (*it).addCounter();
    }
    for (list<Bullet>::iterator it = redBullets.begin(); it != redBullets.end(); ++it)
    {
        (*it).advance();
        (*it).addCounter();
    }
    
    int totalAsteroids = 0;
    for (list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
    {
        (*it).advanceAst();
        totalAsteroids++;
    }
    
    
   // Decide if anything died, the game is over, etc...
   detectHits();
    
    if (blueScore > SCORE_LIMIT)
    {
        gameOver = true;
        
            Point upperMid = Point(-40, (Y_SIZE / 2) - 60);

            drawText(upperMid, "BLUE WINS!!!");
        
    }
    if (redScore > SCORE_LIMIT)
    {
        gameOver = true;
            Point upperMid = Point(-40, (Y_SIZE / 2) - 60);
            
            drawText(upperMid, "RED WINS!!!");
    }
    
   // TODO - is the game over? or did the user shoot all of the rocks?
    if (totalAsteroids <= 0)
        restart();
    if (shipRed.shipDead() && shipBlue.shipDead())
        restart();
}

//restarts the game........ round.
void Game :: restart()
{
    shipBlue.setX(150);
    shipBlue.setY(0);
    shipBlue.setDx(0);
    shipBlue.setDy(0);
    shipBlue.setRotation(0);
    shipBlue.deadStatus(false);
    
    shipRed.setX(-150);
    shipRed.setY(0);
    shipRed.setDx(0);
    shipRed.setDy(0);
    shipRed.setRotation(180);
    shipRed.deadStatus(false);
    
    for (int i = 0; i < numAsteroids; i++)
    {
        int NESW = random(0, 4);
        switch (NESW) {
            case 0:  //North side
                asteroids.push_back(Asteroid(random(0, X_SIZE) - ((X_SIZE / 2) - 10), ((Y_SIZE / 2) - 10), random(-2, 3), random(-2, 0), random(0, 360), 9));
                break;
            case 1:  //East side
                asteroids.push_back(Asteroid(((X_SIZE / 2) - 10), random(0, Y_SIZE) - ((Y_SIZE / 2) - 10), random(1, 3), random(-2, 3), random(0, 360), 9));
                break;
            case 2:  //South side
                asteroids.push_back(Asteroid(random(0, X_SIZE) - ((X_SIZE / 2) - 10), (-(Y_SIZE / 2) + 10), random(-2, 3), random(1, 3), random(0, 360), 9));
                break;
            case 3:  //West side
                asteroids.push_back(Asteroid((-(X_SIZE / 2) + 10), random(0, Y_SIZE) - ((Y_SIZE / 2) - 10), random(-2, 0), random(-2, 3), random(0, 360), 9));
                break;
            default:
                break;
                //Asteroid(float x, float y, float dX, float dY, int rotation, int newSize)
        }
    }
    blueBullets.clear();
    redBullets.clear();
    numAsteroids += NUM_ASTEROIDS_ADD;
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   // TODO: handle user input

   // Note that you can discover keys that were pressed by checking
   // methods such as ui.isUp(), ui.isLeft(), etc.
   // see Pong for an example
    if (!gameOver)
    {
    if (ui.isRight() || ui.isLeft())
    {
        shipBlue.rotate(ui.isRight(), ui.isLeft());
        //std::cout << "Turn!!!!!\n";
    }
    if (ui.isUp())
    {
        shipBlue.forward(ui.isUp());
        //std::cout << "Forward-----\n";
    }
    if (ui.isSpace() || ui.isM())
    {
        blueBullets.push_back(Bullet(shipBlue.getRotation(), shipBlue.getX(), shipBlue.getY(), shipBlue.getDx(), shipBlue.getDy()));
        blueScore += .5;
    }
    
    if (ui.isV() || ui.isX())
    {
        shipRed.rotate(ui.isV(), ui.isX());
    }
    if (ui.isC())
    {
        shipRed.forward(ui.isC());
    }
    if (ui.isA())
    {
        redBullets.push_back(Bullet(shipRed.getRotation(), shipRed.getX(), shipRed.getY(), shipRed.getDx(), shipRed.getDy()));
        redScore += .5;
    }
    /*
  // Vector example
  if (ui.isUp())
  {
    // create 10 random points and add them to the vector
    for (int i = 0; i < 1000; i++)
    {
      points.push_back(Point(random(Point::xMin, Point::xMax), random(Point::xMin, Point::xMax)));
    }
  }

  if (ui.isDown() && (points.size() > 0))
  {
    // go through all points and kill some of them
    // Notice that the For loop doesn't increment "it" in the normal place 
    for (list<Point>::iterator it = points.begin(); it != points.end();)
    {
      // delete some random points
      if (random(1, 10) == 5)
      {
          // When you delete a point, don't move the iterator
          it = points.erase(it);
      }
      else
      {
        // Move to the next point in the vector
	++it;
      }
    }
  }*/
    }
}
string convertIntToString(int input)
{
    stringstream ss; //create a stringstream
    ss << input;     //add number to the stream
    return ss.str(); //return a string with the contents of the stream
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
    Point upperLeft(-(X_SIZE / 2.0) + 10, (Y_SIZE / 2.0) - 10);
    if (redScore >= 0)
        drawNumber(upperLeft, redScore);
    else
    {
        upperLeft.addY(-10);
        drawText(upperLeft, "-");
        upperLeft.addX(9);
        upperLeft.addY(10);
        drawNumber(upperLeft, -(redScore));
        upperLeft.addX(-9);
    }
    upperLeft.addY(-30);
    drawText(upperLeft, "RED SCORE");
    
    Point upperRight((X_SIZE / 2.0) - 80, (Y_SIZE / 2.0) - 10);
    if (blueScore >= 0)
        drawNumber(upperRight, blueScore);
    else
    {
        upperRight.addX(-9);
        upperRight.addY(-10);
        drawText(upperRight, "-");
        upperRight.addY(10);
        upperRight.addX(9);
        drawNumber(upperRight,-(blueScore));
    }
    upperRight.addY(-30);
    drawText(upperRight, "BLUE SCORE");
    
    // TODO: draw anything you need to display in the game
    if (!shipBlue.shipDead())
    {
    shipBlue.drawBlue();
    for (list<Bullet>::iterator it = blueBullets.begin(); it != blueBullets.end(); ++it)
    {
        (*it).drawBlue();
    }
    }
    if (!shipRed.shipDead())
    {
    shipRed.drawRed();
    for (list<Bullet>::iterator it = redBullets.begin(); it != redBullets.end(); ++it)
    {
        (*it).drawRed();
    }
    }
    for (list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
    {
        (*it).draw();
    }
    
    /*
     *This shows how to use list or a vector
     *
     
  // Vector example
  Point pt(-50, 0);
  drawText(pt, "Press UP and DOWN");

  string str = "Point count = " + convertIntToString(points.size());
  pt.addY(-20);
  drawText(pt, str.c_str());

  // draw all of the points
  for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
  {
    drawDot(*it);
  }*/
}

/*********************************************
 * GAME :: detectHits
 * Detect any rocks hitting bullets and ship and make them "dead"
 * Note: decide if the game is over here
 *********************************************/
void Game::detectHits()
{
    
  // did any bullets hit a rock?
    for (list<Bullet>::iterator itb = blueBullets.begin(); itb != blueBullets.end();itb++)
    {
        for (list<Asteroid>::iterator ita = asteroids.begin(); ita != asteroids.end();ita++)
        {
            if (powf(((*itb).getX() - (*ita).getX()), 2) +
                 powf(((*itb).getY() - (*ita).getY()), 2) <
                 powf((*ita).getSize() * 6, 2))
            {
                (*itb).kill();
                (*ita).kill();
                blueScore += 20;
            }
        }
        if ((*itb).getCounter() > X_SIZE / 1.75)
            (*itb).kill();
    }
    for (list<Bullet>::iterator itb = redBullets.begin(); itb != redBullets.end();itb++)
    {
        for (list<Asteroid>::iterator ita = asteroids.begin(); ita != asteroids.end();ita++)
        {
            if (powf(((*itb).getX() - (*ita).getX()), 2) +
                powf(((*itb).getY() - (*ita).getY()), 2) <
                powf((*ita).getSize() * 6, 2))
            {
                (*itb).kill();
                (*ita).kill();
                redScore += 20;
            }
        }
        if ((*itb).getCounter() > X_SIZE / 1.75)
            (*itb).kill();
    }
    
    
  // did the ship hit a rock?... naaaaaa
    if(!shipBlue.shipDead() && !gameOver)
    {
    for (list<Asteroid>::iterator ita = asteroids.begin(); ita != asteroids.end();ita++)
    {
        if (powf((shipBlue.getX() - (*ita).getX()), 2) +
            powf((shipBlue.getY() - (*ita).getY()), 2) <
            powf((*ita).getSize() * 6, 2))
        {
            shipBlue.deadStatus(true);
            (*ita).kill();
            blueScore -= 500;
            break;
        }
    }
    }
    if(!shipRed.shipDead() && !gameOver)
    {
    for (list<Asteroid>::iterator ita = asteroids.begin(); ita != asteroids.end();ita++)
    {
        if (powf((shipRed.getX() - (*ita).getX()), 2) +
            powf((shipRed.getY() - (*ita).getY()), 2) <
            powf((*ita).getSize() * 6, 2))
        {
            shipRed.deadStatus(true);
            (*ita).kill();
            redScore -= 500;
            break;
        }
    }
    }
  // remove the dead
  removeDeadObjects();
}

/*********************************************
 * GAME :: removeDeadObjects
 * remove any "dead" rocks, bullets, etc...
 *********************************************/
void Game::removeDeadObjects()
{
  // TODO: Remove any dead objects (ie., rocks, bullets, etc...)
    for (list<Bullet>::iterator it = blueBullets.begin(); it != blueBullets.end(); ++it)
    {
        if (!(*it).alive())
        {
            it = blueBullets.erase(it);
            //std::cout << "Erased Bullet\n";
        }
    }
    
    for (list<Bullet>::iterator it = redBullets.begin(); it != redBullets.end(); ++it)
    {
        if (!(*it).alive())
        {
            it = redBullets.erase(it);
            //std::cout << "Erased Bullet\n";
        }
    }
    
    for (list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end();)
    {
        if (!(*it).alive())
        {
            //std::cout << "Erase Asteroid\n";
            if ((*it).getSize() > 4)
            {
                tempAst.push_back(Asteroid((*it).getX(),(*it).getY(), (*it).getDx(), (*it).getDy(), (*it).getSize()));
                tempAst.push_back(Asteroid((*it).getX(),(*it).getY(), (*it).getDx(), (*it).getDy(), (*it).getSize()));
                tempAst.push_back(Asteroid((*it).getX(),(*it).getY(), (*it).getDx(), (*it).getDy(), (*it).getSize()));
            }
            it = asteroids.erase(it);
        }
        else
            it++;
    }
    for (list<Asteroid>::iterator it = tempAst.begin(); it != tempAst.end();)
    {
        asteroids.push_back(Asteroid(*it));
        it = tempAst.erase(it);
    }
  // TODO: Create any new rocks (Large rock -> mid rock and mid -> small)
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;

   pGame->advance();
   pGame->input(*pUI);
   pGame->draw(*pUI);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Skeet");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
