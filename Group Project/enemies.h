#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
       
// global variable to control ALL ship speeds
GLfloat ship_speed;
      
class Ship {
      
    private:
        // internal fields to keep track of position and speed
        GLfloat x1;
        GLfloat x2;
        GLfloat y1;
        GLfloat y2;
        GLfloat ymid;
        GLfloat xmid;
        GLfloat initx;
        GLfloat inity;
        GLfloat S_space;
        bool alive;
     
    public:
      
        // ship constructor, initializes the ships x and y coordinates and its speed
        Ship(GLfloat x, GLfloat y) {
            S_space = (GLfloat)0.1;
            initx = x;
            inity = y;
            xmid = x;
            ymid = y;
            x1 = x - S_space;
            x2 = x + S_space;
            y1 = y - S_space;
            y2 = y + S_space;
            ship_speed = (GLfloat)0.001;
            alive = true;
        }
              
        // resets the ship to its initial position
        void reset() {
            x1 = (GLfloat)(initx - 0.1);
            x2 = (GLfloat)(initx + 0.1);
            y1 = (GLfloat)(inity - 0.1);
            y2 = (GLfloat)(inity + 0.1);
            xmid = initx;
            ymid = inity;
        }
      
        // draws the ship and changes its position
        void draw() {
            if (alive == true) {
                glBegin(GL_TRIANGLES);
                glVertex2f(x1, y1);
                glVertex2f(xmid, y2);
                glVertex2f(x2, y1);
                x2 = x2 + ship_speed;
                x1 = x1 + ship_speed;
                xmid = xmid + ship_speed;
                glEnd();
            }
        }
            
        // sets the ship to "dead". Called when a ship is hit by an asteroid
        void destroyship() {
            alive = false;
        }
            
        // sets the ship to "alive"
        void restoreShip() {
            alive = true;
        }
    
        // returns whether the ship is "alive" or "dead"
        bool ship_alive() {
            return alive == true;
        }
            
        // the following functions return the values of the ship's position
        GLfloat getX_botleft() {
            return x1;
        }
     
        GLfloat getX_botright() {
            return x2;
        }
     
        GLfloat getX_mid() { 
            return xmid;
        }
     
        GLfloat getY_mid() {
            return ymid;
        }
     
        GLfloat getY_bot() {
            return y1;
        }
     
        GLfloat getY_top() {
            return y2;
        }
            
        // returns the speed of the ship
        GLfloat returnSpeed() {
            return ship_speed;
        }
        // sets the ship_speed variable to an increased value
        void increaseSpeed(GLfloat s) {
            ship_speed = (GLfloat)(abs(ship_speed) + s); 
        }
            
        // resets the ship_speed variable to its initial value of 0.001
        void resetSpeed() {
            ship_speed = (GLfloat)0.001;
        }
            
        // set ship speed to 0
        void pauseShip() {
            ship_speed = 0;
        }
            
        // set ship speed to a custom speed
        void setSpeed(GLfloat s) {
            ship_speed = s;
        }

		// reverses ship direction
		void reverseSpeed() {
			ship_speed *= -1;
		}
};
       
class Shot {
    private:
        // internal fields to keep track of position and speed of the shot
        GLfloat vert1x;
        GLfloat vert2x;
        GLfloat vert3y;
        GLfloat vert4y;
        GLfloat shot_speed;
        GLfloat xcent;
        GLfloat ycent;
        bool shot_alive;
     
    public: 
        // constructor to initialize the Shot
        Shot(GLfloat x, GLfloat y) {
            vert1x = (GLfloat)(x - 0.0025);
            vert2x = (GLfloat)(x + 0.0025);
            vert3y = (GLfloat)(y - 0.01);
            vert4y = (GLfloat)(y + 0.01);
            shot_speed = (GLfloat)0.005;
            xcent = x;
            ycent = y;
            shot_alive = true;
        }
  
        // draws the Shot and changes its position
        void draw() {
            glBegin(GL_QUADS);
            glVertex2f(vert1x, vert3y);
            glVertex2f(vert2x, vert3y);
            glVertex2f(vert2x, vert4y);
            glVertex2f(vert1x, vert4y);
            vert3y = vert3y + shot_speed;
            vert4y = vert4y + shot_speed;
            glEnd();
        }
   
        void update(GLfloat midx) {
            vert1x = (GLfloat)(midx - .005);
            vert2x = (GLfloat)(midx + .005);
        }
    
        // puts the Shot at the designated coordinates
        void resetshot(GLfloat shot_xpos, GLfloat shot_ypos) {
            vert1x = (GLfloat)(shot_xpos - 0.005);
            vert2x = (GLfloat)(shot_xpos + 0.005);
            vert3y = (GLfloat)(shot_ypos - 0.01);
            vert4y = (GLfloat)(shot_ypos + 0.01);
        }
   
        GLfloat getX_botleft() {
            return vert1x;
        }
     
        GLfloat getX_botright() {
            return vert2x;
        }
     
        GLfloat getx_mid() {
            return xcent;
        }
     
        GLfloat getY_mid() {
            return ycent;
        }
     
        GLfloat getY_bot() {
            return vert3y;
        }
     
        GLfloat getY_top() {
            return vert4y;
        }
  
        // return current shot speed
        GLfloat returnSpeed() {
            return shot_speed;
        }
     
        // increase shot speed by a custom amount
        void increaseSpeed(GLfloat s) {
            shot_speed += s;
        }
     
        // reset shot speed to 0.005
        void resetSpeed() {
            shot_speed = (GLfloat)0.005;
        }
     
        // set shot speed to 0 when game is paused
        void pauseShot() {
            shot_speed = (GLfloat)0;
        }
     
        // set shot speed to a custom amount
        void setSpeed(GLfloat s) {
            shot_speed = (GLfloat)s;
        }
  
        // sets the shot to "alive"
        void shot_is_alive() {
            shot_alive = true;
        }
  
        // sets the shot to "dead"
        void shot_is_not_alive() {
            shot_alive = false;
        }
  
        // returns whether the shot is "alive" or "dead"
        bool is_shot_alive() {
            return shot_alive == true;
        }
};