#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "enemies.h"
   
const double pi = 3.1415926535897932384626433832795; // Constant for the value of pi
const double rad = pi/180; // Used for conversion to radians
int value = 500; // Value used in the creation of asteroids
   
class Asteroid {
    private:
        GLfloat s; // size
        GLfloat a; // angle
        GLfloat p_x; // position x
        GLfloat p_y; // position y
        double vx; // horizontal velocity 
        double vy; // vertical velocity
        double v; // velocity value used to calculate vx and vy
        bool draw; // boolean for drawing asteroid
        bool destroyed; // boolean for if the asteroid has been destroyed
   
    public:
        Asteroid(GLfloat s, double vx, double vy, GLfloat p_x, GLfloat p_y) { // constructor
            this->vx = vx; 
            this->vy = vy; 
            this->s = s;
            this->p_x = p_x;
            this->p_y = p_y;
            draw = false;
            destroyed = false;
        }
  
        void setValues(GLfloat s, double vx, double vy, GLfloat p_x, GLfloat p_y) { // Used to reset values when asteroid is redrawn
            this->vx = vx;
            this->vy = vy;
            this->s = s;
            this->p_x = p_x;
            this->p_y = p_y;
            if (draw == true) {
                draw = false;
            }
            if (destroyed == true) {
                destroyed = false;
            }
        }
   
        GLfloat getSize() { // return asteroid size
            return s;
        }
   
        double get_vx() { // return asteroid horizontal velocity
            return vx;
        }
   
        double get_vy() { // return asteroid vertical velocity
            return vy;
        }
   
        void set_vx(double x) { // set asteroid horizontal velocity
            vx = x;
        }
  
        void set_vy(double y) { // set asteroid vertical velocity
            vy = y;
        }
  
        void pauseAsteroidXVel() { // set asteroid horizontal velocity to 0
            vx = 0;
        }
  
        void pauseAsteroidYVel() { // set asteroid vertical velocity to 0
            vy = 0;
        }
   
        GLfloat getX_Position() { // return asteroid x position
            return p_x;
        }
           
        GLfloat getY_Position() { // return asteroid y position
            return p_y;
        }
   
        GLfloat getXCenter() { // return asteroid x center position
            return p_x;
        }
   
        GLfloat getYCenter() { // return asteroid y center position
            return p_y;
        } 
   
        void drawAsteroid(GLfloat x, GLfloat y) { // draw asteroid
            GLfloat draw_size = s;
  
            glColor3f((GLfloat)0.3,(GLfloat)0.2,(GLfloat)0.5);
            glBegin(GL_POLYGON);
            for (double a = 0; a < 2*pi; a += pi/value) {
                glVertex3f((GLfloat)(x+cos(a)*s),(GLfloat)(y+sin(a)*s),(GLfloat)(0.0));
            }
            glEnd();
        }
  
        void drawExampleAsteroid(GLfloat color1, GLfloat color2, GLfloat color3, GLfloat x, GLfloat y, GLfloat rad) { // draw example asteroids
            GLfloat draw_size = rad;
  
            glColor3f(color1,color2,color3);
            glBegin(GL_POLYGON);
            for (double a = 0; a < 2*pi; a += pi/value) {
                glVertex3f((GLfloat)(x+cos(a)*rad),(GLfloat)(y+sin(a)*rad),(GLfloat)0.0);
            }
            glEnd();
        }
   
        void motion() { // change asteroid x and y position based on its velocity
            p_x += (GLfloat)vx;
            p_y += (GLfloat)vy;
        }
   
        void changeXAngle() { // reverse the horizontal direction of the asteroid
            vx *= (GLfloat)-1;
        }
  
        void changeYAngle() { // reverse the vertical direction of the asteroid
            vy *= (GLfloat)-1;
        }
  
        bool draw_asteroid() { // is the asteroid being drawn?
            return draw == true;
        }
  
        void draw_stop() { // set draw to false
            draw = false;
        }
  
        void draw_start() { // set draw to true
            draw = true;
        }
  
        void destroy_asteroid() { // set destroyed to true
            destroyed = true;
        }
  
        void restore_asteroid() { // set destroyed to false
            destroyed = false;
        }
  
        bool is_destroyed() { // has the asteroid been destroyed?
            return destroyed == true;
        }
  
        bool collisionShip(Ship* ship) { // check for collision between asteroid and any of the ships
            // get coordinates of the ship's vertices and edges
            GLfloat c1x = ship->getX_mid() - this->getXCenter();
            GLfloat c1y = ship->getY_top() - this->getYCenter();
            GLfloat c2x = ship->getX_botleft() - this->getXCenter();
            GLfloat c2y = ship->getY_bot() - this->getYCenter();
            GLfloat c3x = ship->getX_botright() - this->getXCenter();
            GLfloat c3y = ship->getY_bot() - this->getYCenter();
  
            GLfloat s1x = c1x;
            GLfloat s1y = c2y;
            // get center position of the ship's edges
            GLfloat s2x = (c2x + c1x) / 2;
            GLfloat s2y = (c2y + c1y) / 2;
            GLfloat s3x = (c3x + c1x) / 2;
            GLfloat s3y = (c3y + c1y) / 2;
  
            // return true if collision between asteroid and any of the ships vertices or edges is detected
            GLfloat a1 = sqrt(c1x*c1x + c1y*c1y);
            GLfloat a2 = sqrt(c2x*c2x + c2y*c2y);
            GLfloat a3 = sqrt(c3x*c3x + c3y*c3y);
            GLfloat a4 = sqrt(s1x*s1x + s1y*s1y);
            GLfloat a5 = sqrt(s2x*s2x + s2y*s2y);
            GLfloat a6 = sqrt(s3x*s3x + s3y*s3y);
  
            if (a1 <= this->s) { 
                return true;
            }
            else if (a2 <= this->s) {
                return true;
            }
            else if (a3 <= this->s) {
                return true;
            }
            if (a4 <= this->s) {
                return true;
            }
            else if (a5 <= this->s) {
                return true;
            }
            else if (a6 <= this->s) {
                return true;
            }
            else return false;
        }
  
        bool collisionShot(Shot* shot) { // check for collision between asteroid and any of the shots
            // get coordinates of the shot vertices
            GLfloat c1x = shot->getX_botleft() - this->getXCenter();
            GLfloat c1y = shot->getY_top() - this->getYCenter();
            GLfloat c2x = shot->getX_botright() - this->getXCenter();
            GLfloat c2y = shot->getY_top() - this->getYCenter();
            GLfloat c3x = shot->getX_botleft() - this->getXCenter();
            GLfloat c3y = shot->getY_bot() - this->getYCenter();
            GLfloat c4x = shot->getX_botright() - this->getXCenter();
            GLfloat c4y = shot->getY_bot() - this->getYCenter();
  
            // return true if collision between asteroid and any of the shot's edges is detected
            GLfloat a1 = (GLfloat)sqrt(c1x*c1x + c1y*c1y);
            GLfloat a2 = (GLfloat)sqrt(c2x*c2x + c2y*c2y);
            GLfloat a3 = (GLfloat)sqrt(c3x*c3x + c3y*c3y);
            GLfloat a4 = (GLfloat)sqrt(c4x*c4x + c4y*c4y);
  
            if (a1 <= this->s) {
                return true;
            }
            else if (a2 <= this->s) {
                return true;
            }
            else if (a3 <= this->s) {
                return true;
            }
            else if (a4 <= this->s) {
                return true;
            }
            else return false;
        }
};