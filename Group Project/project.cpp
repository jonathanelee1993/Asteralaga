#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include "context.h"
#include "menus.h"
#include "asteroids.h"
  
using namespace std;
  
Gamestate* game; // instance of class Gamestate
Asteroid* asteroid; // instance of class Asteroid
Menu* menu; // instance of class Menu
Buttons* buttons; // instance of class Buttons
  
// instances of classes Ship and Shot
Ship* ship1;
Ship* ship2;
Ship* ship3;
Shot* shot1;
Shot* shot2;
Shot* shot3;
  
// variables used to determine when a shot should be shot and when it should stop being drawn and be reset to its ship
int stopyshot; 
double wait_to_shoot; 
  
// variable that stores the id of the game window
int Win_id;
  
// variables that store the size of the window
GLfloat xwindowsize, ywindowsize;
  
// variables that store the x and y coordinates of where the mouse is clicked and released, respectively
GLfloat xcoord, ycoord, xrad, yrad;
  
// variables that store the radius and size (equivalent value but converted between coordinate systems) of the asteroid
GLfloat radius, size;
  
// variables that store the x and y velocity of the asteroid
GLfloat asteroid_xvel, asteroid_yvel;
  
// variables that store the x and y position of the asteroid
GLfloat glX_asteroid, glY_asteroid;
  
// variables used in printing text to the screen
string t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;
  
// Sets size and location of text
void drawText(const char* text, int length, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX,matrix);
    glLoadIdentity();
    glOrtho(0,800,0,600,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
  
    for (int i = 0; i < length; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
  
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
  
// Turns a menu on and calls drawText to print menu options
void drawMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
  
    string text1, text2, text3, text4;
    if (menu->MainMenu() == true) {
        text1 = "WELCOME TO ASTERALAGA!!!";
        text2 = "(ENTER) Play level";
        text3 = "(H) Help";
        text4 = "(ESC) Quit";
    } else if (menu->CompleteLevelMenu() == true) {
        text1 = "CONGRATULATIONS, YOU BEAT THE LEVEL!!!";
        text2 = "(ENTER) Play again";
        text3 = "(SPACEBAR) Next level";
        text4 = "(ESC) Quit";
    } else if (menu->FailedLevelMenu() == true) {
        text1 = "YOU FAILED THIS LEVEL. BETTER LUCK NEXT TIME.";
        text2 = " ";
        text3 = "(ENTER) Play again";
        text4 = "(ESC) Quit";
    } else if (game->display_help() == true) {
        menu->main_menu_off();
        game->help();
        t1 = "HOW TO PLAY: ";
        t2 = "Click once within the white lines to start drawing asteroid, then release to draw it.";
        t3 = "Asteroid size will increase as the mouse is dragged farther away.";
        t4 = "Your pressure will decrease at a faster rate if you draw smaller asteroids.";
        t5 = "Your asteroid will go in the direction that you drag your mouse.";
        t6 = "To beat the level, destroy all three ships before you lose all your lives.";
        t7 = "You have 3 lives per level. If you lose all of your lives, you fail the level.";
        t8 = "Also, if you run out of pressure, you lose the level. Use it wisely!";
        t9 = "Within the game, press 'BACKSPACE' to pause, or 'ESC' to quit the game.";
        t10 = "Good luck.";
        t11 = "(BACKSPACE) Return to main menu";
  
        glClear(GL_COLOR_BUFFER_BIT);
  
        glColor3f(0.0, 1.0, 0.0);
        drawText(t1.data(),t1.size(),25,550);
        glColor3f(1.0, 1.0, 0.0);
        drawText(t2.data(),t2.size(),25,500);
        drawText(t3.data(),t3.size(),25,450);
        drawText(t4.data(),t4.size(),25,400);
        drawText(t5.data(),t5.size(),25,350);
        drawText(t6.data(),t6.size(),25,300);
        drawText(t7.data(),t7.size(),25,250);
        drawText(t8.data(),t8.size(),25,200);
        drawText(t9.data(),t9.size(),25,150);
        drawText(t10.data(),t10.size(),25,100);
        drawText(t11.data(),t11.size(),25,50);
  
        glutSwapBuffers();
    }
  
    if (!(game->display_help())) {
        glColor3f(0.0, 1.0, 0.0);
        drawText(text1.data(),text1.size(),325,575);
        glColor3f(1.0, 1.0, 0.0);
        drawText(text2.data(),text2.size(),325,300);
        drawText(text3.data(),text3.size(),325,200);
        drawText(text4.data(),text4.size(),325,100);
  
        glutSwapBuffers();
    }
}
  
// manages player level, player lives, and asteroid pressure
void drawLevel() {
    // retreives and prints levels
    ostringstream s;
    s << game->getLevel();
    string level = "LEVEL: " + s.str();
    s.str("");
    s.clear();
  
    // retreives and prints pressure
    ostringstream t;
    t << game->getPressure();
    string p = "PRESSURE: " + t.str() + "%";
    t.str("");
    t.clear();
  
    // retreives and prints lives
    ostringstream u;
    u << game->getLives();
    string q = "LIVES: " + u.str();
    u.str("");
    u.clear();
  
    string pause1 = "GAME PAUSED";
    string pause2 = "PRESS ENTER TO CONTINUE";
    string pause3 = "OR PRESS 'Q' TO QUIT";
  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
  
    glColor3f(1.0, 1.0, 0.0);
  
    // when playing - sets location to display level, lives, and pressure
    // when paused - sets location to display options to continue or exit
    if (!(game->isGamePaused())) {
        drawText(level.data(),level.size(),100,500);
        drawText(p.data(),p.size(),100,450);
        drawText(q.data(),q.size(),100,400);
    } else if (game->isGamePaused()) {
        drawText(pause1.data(),pause1.size(),300,500);
        drawText(pause2.data(),pause2.size(),300,450);
        drawText(pause3.data(),pause3.size(),300,400);
    }
  
    glLineWidth((GLfloat)0.1);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex2f((GLfloat)-1.0,(GLfloat)0.9);
    glVertex2f((GLfloat)1.0,(GLfloat)0.9);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-1.0,0.25);
    glVertex2f(1.0,0.25);
    glEnd();
  
    glColor3f(1.0,0.0,0.0);
   
    // draws ships, moves shot
	if (ship1->getX_botleft() <= -1 || ship1->getX_botright() >= 1
		|| ship2->getX_botleft() <= -1 || ship2->getX_botright() >= 1
		|| ship3->getX_botleft() <= -1 || ship3->getX_botright() >= 1) {
		ship1->reverseSpeed();
		ship2->reverseSpeed();
		ship3->reverseSpeed();
	}

    ship1->draw();
    ship2->draw();
    ship3->draw();
      
    GLfloat ship1_xmid = ship1->getX_mid();
    GLfloat ship2_xmid = ship2->getX_mid();
    GLfloat ship3_xmid = ship3->getX_mid();
   
    // determines when and where to draw shot
    while (stopyshot<=0) {
        shot1->update(ship1_xmid);
        shot2->update(ship2_xmid);
        shot3->update(ship3_xmid);
        stopyshot++;
    }
    // only increment the time when the game is not paused
    if (!(game->isGamePaused())) {
        wait_to_shoot++;
    }
    // reset the position of the shot to be in line with its corresponding ship when it is time to shoot again
    if (wait_to_shoot >= game->getFrequency()) {                    
        wait_to_shoot = 0;
        stopyshot = 0;
        shot1->resetshot(ship1_xmid, ship1->getY_top());
        shot2->resetshot(ship2_xmid, ship2->getY_top());
        shot3->resetshot(ship3_xmid, ship3->getY_top());
    }   
  
    // determine which ships are alive in order to determine which shots should be shot
    if (ship1->ship_alive()) {
        shot1->draw();
    }
    if (ship2->ship_alive()) {
        shot2->draw();
    }
    if (ship3->ship_alive()) {
        shot3->draw();
    }
  
    // draws sample size asteroid when button is clicked
    if (buttons->buttonClicked()) {
        GLfloat draw_rad1 = (GLfloat)0.05;
        GLfloat draw_rad2 = (GLfloat)0.1;
        GLfloat draw_rad3 = (GLfloat)0.15;
        GLfloat draw_rad4 = (GLfloat)0.2;
        GLfloat glX_radii = (GLfloat)((xcoord/(xwindowsize/2))-1);
        GLfloat glY_radii = (GLfloat)(1-(ycoord/(ywindowsize/2))); 
        asteroid->drawExampleAsteroid(0,0,1,glX_radii,glY_radii,draw_rad4);
        asteroid->drawExampleAsteroid(1,0,0,glX_radii,glY_radii,draw_rad3);
        asteroid->drawExampleAsteroid(0,1,0,glX_radii,glY_radii,draw_rad2);
        asteroid->drawExampleAsteroid(1,1,1,glX_radii,glY_radii,draw_rad1);
    }
  
    // when button is clicked and released, draws an asteroid centered where the cursor clicked
    // radius equals cursor displacement
    if (buttons->buttonClicked() && buttons->buttonReleased() && !(asteroid->draw_asteroid())) {
          
        GLfloat xdif, ydif;
        xdif = xcoord - xrad;
        ydif = ycoord - yrad;
        GLfloat xdif_square = xdif*xdif;
        GLfloat ydif_square = ydif*ydif;
        radius = sqrt(xdif_square + ydif_square);
  
        if (radius > 10) {
            glX_asteroid = (xcoord/(xwindowsize/2))-1;
            glY_asteroid = 1-(ycoord/(ywindowsize/2));
  
            if (glY_asteroid < 0.9 && glY_asteroid > 0.25) {
                GLfloat asteroid_size;
  
                // asteroid size determined by displacement between mouse click and mouse release as follows
                // pressure reduced by the percentages seen below based on each size
                if (radius < 20) {
                    asteroid_size = (GLfloat)0.05;
                    game->reducePressure(20);
                } else if (radius >= 20 && radius < 40) {
                    asteroid_size = (GLfloat)0.05;
                    game->reducePressure(20);
                } else if (radius >= 40 && radius < 60) {
                    asteroid_size = (GLfloat)0.10;
                    game->reducePressure(15);
                } else if (radius >= 60 && radius < 80) {
                    asteroid_size = (GLfloat)0.15;
                    game->reducePressure(10);
                } else {
                    asteroid_size = (GLfloat)0.2;
                    game->reducePressure(5);
                }
  
                // x and y velocities
                asteroid_xvel = (-1)*(xdif/radius) / 400;
                asteroid_yvel = (ydif/radius) / 400;
  
                // set asteroid with all necessary values, and then draw it to the screen
                asteroid->setValues(asteroid_size, asteroid_xvel, asteroid_yvel, glX_asteroid, glY_asteroid);
                asteroid->draw_start(); 
            }
        }
        // mouse clicked and mouse released booleans set to false, user must wait before being able to draw another asteroid
        buttons->disableButton();
        buttons->buttonOn();
    } else if (asteroid->draw_asteroid()) {
        buttons->disableButton();
        buttons->buttonOn();
    }
  
    if (asteroid->draw_asteroid()) {
        // draws asteroid at its current x and y positions
        asteroid->drawAsteroid(glX_asteroid,glY_asteroid);
  
        // stops drawing when asteroid is off the screen
        if (asteroid->getY_Position()-asteroid->getSize() <= -1.3) {
            asteroid->draw_stop();
        }
  
        // updates asteroid position
        glX_asteroid += (GLfloat)(asteroid->get_vx()); 
        glY_asteroid += (GLfloat)(asteroid->get_vy());
        asteroid->motion();
  
        // reverses x_direction when asteroid hits the left or right side of frame
        if (asteroid->getSize() + asteroid->getX_Position() >= 1 || asteroid->getX_Position() - asteroid->getSize() <= -1) {
            asteroid->changeXAngle();
        }
  
        // reverses y_direction if asteroid hits top of screen
        if (asteroid->getSize() + asteroid->getY_Position() >= 1) {
            asteroid->changeYAngle();
        }
    }
  
    glutSwapBuffers();
  
    // if asteroid hits a ship, stop drawing the asteroid, the ship, and that ship's shots
    if (asteroid->draw_asteroid()) {
        if (asteroid->collisionShip(ship1) && ship1->ship_alive()) {
            game->shipDestroyed();
            // move asteroid off screen
            if (game->getNumberShipsAlive() > 0) {
                asteroid->setValues(0,0,0,-2,-2);
            }
            shot1->shot_is_not_alive();
            ship1->destroyship();
            asteroid->draw_stop();
        }
        else if (asteroid->collisionShip(ship2) && ship2->ship_alive()) {
            game->shipDestroyed();
            // move asteroid off screen
            if (game->getNumberShipsAlive() > 0) {
                asteroid->setValues(0,0,0,-2,-2);
            }
            shot2->shot_is_not_alive();
            ship2->destroyship();
            asteroid->draw_stop();
        }
        else if (asteroid->collisionShip(ship3) && ship3->ship_alive()) {
            game->shipDestroyed();
            // move asteroid off screen
            if (game->getNumberShipsAlive() > 0) {
                asteroid->setValues(0,0,0,-2,-2);
            }
            shot3->shot_is_not_alive();
            ship3->destroyship();
            asteroid->draw_stop();
        }
  
        // if asteroid hits a shot, stop drawing the asteroid and lose a life
        else if (asteroid->collisionShot(shot1) && shot1->is_shot_alive()) {
            game->loseLife();
            // move asteroid off screen
            if (game->getNumberShipsAlive() > 0) {
                asteroid->setValues(0,0,0,-2,-2);
            }
            asteroid->draw_stop();
        }
        else if (asteroid->collisionShot(shot2) && shot2->is_shot_alive()) {
            game->loseLife();
            // move asteroid off screen
            if (game->getNumberShipsAlive() > 0) {
                asteroid->setValues(0,0,0,-2,-2);
            }
            asteroid->draw_stop();
        }
        else if (asteroid->collisionShot(shot3) && shot3->is_shot_alive()) {
            game->loseLife();
            // move asteroid off screen
            if (game->getNumberShipsAlive() > 0) {
                asteroid->setValues(0,0,0,-2,-2);
            }
            asteroid->draw_stop();
        }
    }
  
    // display failed_level_menu when pressure or lives run out
    if (game->getPressure() <= 0 || game->getLives() == 0) {
        game->draw_stop();
        menu->failed_level_menu_on();
        glutDisplayFunc(drawMenu);
        game->onMenu();
        asteroid->draw_stop();
        asteroid->setValues(0,0,0,-2,-2);
        // reset ships and shots
        ship1->reset();
        ship2->reset();
        ship3->reset();
		game->restoreAllShips();
        if (!(ship1->ship_alive())) {
            ship1->restoreShip();
        }
        if (!(ship2->ship_alive())) {
            ship2->restoreShip();
        }
        if (!(ship3->ship_alive())) {
            ship3->restoreShip();
        }
        if (!(shot1->is_shot_alive())) {
            shot1->shot_is_alive();
        }
        if (!(shot2->is_shot_alive())) {
            shot2->shot_is_alive();
        }
        if (!(shot3->is_shot_alive())) {
            shot3->shot_is_alive();
        }
		shot1->resetshot(ship1->getX_mid(),ship1->getY_mid());
        shot2->resetshot(ship2->getX_mid(),ship2->getY_mid());
        shot3->resetshot(ship3->getX_mid(),ship3->getY_mid());
        // reset lives
        game->resetLives();
		// reset pressure
		game->resetPressure();
    }
  
    // display complete_level_menu if all ships are destroyed
    // reset all ships and shots as necessary
    if (game->getNumberShipsAlive() == 0) {
        game->draw_stop();
        menu->complete_level_menu_on();
        glutDisplayFunc(drawMenu);
        game->onMenu();
        game->resetLives();
        asteroid->draw_stop();
        ship1->reset();
        ship2->reset();
        ship3->reset();
        shot1->resetshot(ship1->getX_mid(),ship1->getY_mid());
        shot2->resetshot(ship2->getX_mid(),ship2->getY_mid());
        shot3->resetshot(ship3->getX_mid(),ship3->getY_mid());
        ship1->restoreShip();
        ship2->restoreShip();
        ship3->restoreShip();
        if (!(shot1->is_shot_alive())) {
            shot1->shot_is_alive();
        }
        if (!(shot2->is_shot_alive())) {
            shot2->shot_is_alive();
        }
        if (!(shot3->is_shot_alive())) {
            shot3->shot_is_alive();
        }
    }
  
    game->gameStart();
}
  
// prevents user from resizing or repositioning window
void viewport(int w, int h) {
    glutReshapeWindow((int)xwindowsize,(int)ywindowsize);
    glutPositionWindow(275,0);
}
  
// allows for rendering
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}
  
void hitKey(unsigned char key, int x, int y) {
    switch(key) {
        case 13: // ENTER KEY
            // if key is pressed while game not paused, reset game
            if (!(game->isGamePaused()) && !(game->display_help())) {
                menu->main_menu_off();
                menu->complete_level_menu_off();
                menu->failed_level_menu_off();
  
                if (!(game->playGame())) {
                    game->resetPressure();
  
                    if (game->getNumberShipsAlive() < 3) {
                        game->restoreAllShips();
                    }
  
                    wait_to_shoot = 0;
                    stopyshot = 0;
                }
  
                game->gameStart();
                glutDisplayFunc(drawLevel);
                game->draw_start();
            } else if (game->isGamePaused()) {
                // unpaused: calling pre-existing speeds of shots, ships, and asteroids
                GLfloat ship_speed = game->returnShipSpeed();
                GLfloat shot_speed = game->returnShotSpeed();
                double asteroidXVel = game->returnAsteroidXVel();
                double asteroidYVel = game->returnAsteroidYVel();
  
                ship1->setSpeed(ship_speed);
                ship2->setSpeed(ship_speed);
                ship3->setSpeed(ship_speed);
                shot1->setSpeed(shot_speed);
                shot2->setSpeed(shot_speed);
                shot3->setSpeed(shot_speed);
                asteroid->set_vx(asteroidXVel);
                asteroid->set_vy(asteroidYVel);
  
                game->resume_game();
            } 
            break;
        case 32: // SPACEBAR
            // If completed level, advances level and resets game
            if (menu->CompleteLevelMenu()) {
                game->gameStart();
                menu->main_menu_off();
                menu->complete_level_menu_off();
                menu->failed_level_menu_off();
                game->nextLevel();
                game->resetPressure();
                game->resetLives();
                if (game->getNumberShipsAlive() < 3) {
                    game->restoreAllShips();
                }
  
                ship1->increaseSpeed((GLfloat)0.00025);
                ship2->increaseSpeed((GLfloat)0.00025);
                ship3->increaseSpeed((GLfloat)0.00025);
  
                shot1->increaseSpeed((GLfloat)0.00025);
                shot2->increaseSpeed((GLfloat)0.00025);
                shot3->increaseSpeed((GLfloat)0.00025);
                  
                wait_to_shoot = 0;
                stopyshot = 0;
  
                glutDisplayFunc(drawLevel);
                game->draw_start();
            }
            break;
        case 8: // BACKSPACE
            if (game->playGame() && !(ship1->returnSpeed() == 0)) {
                // pauses game, and stores ship/shot speeds and asteroid velocity for future reference
                GLfloat ship_speed = 0;
  
                if (ship1->ship_alive()) {
                    ship_speed = ship1->returnSpeed();
                } else if (ship2->ship_alive()) {
                    ship_speed = ship2->returnSpeed();
                } else if (ship3->ship_alive()) {
                    ship_speed = ship3->returnSpeed();
                }
  
                GLfloat shot_speed = shot1->returnSpeed();
  
                game->pauseGame(ship_speed,shot_speed,(GLfloat)asteroid->get_vx(),(GLfloat)asteroid->get_vy());
                  
                ship1->pauseShip();
                ship2->pauseShip();
                ship3->pauseShip();
                shot1->pauseShot();
                shot2->pauseShot();
                shot3->pauseShot();
                asteroid->pauseAsteroidXVel();
                asteroid->pauseAsteroidYVel();
  
                game->pause_game();
            } else if (game->display_help()) {
                // return to the main menu
                menu->main_menu_on();
                game->help_done();
            }
            break;
        case 'q': // 'q' key
            // if pressed while game is paused, return to main menu, reset game to level 1 
            if (game->playGame() || game->isGamePaused()) {
                game->resetLevel();
                game->resetPressure();
                game->resetLives();
  
                if (!(ship1->ship_alive())) {
                    ship1->restoreShip();
                }
                if (!(ship2->ship_alive())) {
                    ship2->restoreShip();
                }
                if (!(ship3->ship_alive())) {
                    ship3->restoreShip();
                }
                if (!(shot1->is_shot_alive())) {
                    shot1->shot_is_alive();
                }
                if (!(shot2->is_shot_alive())) {
                    shot2->shot_is_alive();
                }
                if (!(shot3->is_shot_alive())) {
                    shot3->shot_is_alive();
                }
  
                ship1->reset();
                ship2->reset();
                ship3->reset();
                ship1->resetSpeed();
                ship2->resetSpeed();
                ship3->resetSpeed();
                shot1->resetshot(ship1->getX_mid(),ship1->getY_mid());
                shot2->resetshot(ship2->getX_mid(),ship2->getY_mid());
                shot3->resetshot(ship3->getX_mid(),ship3->getY_mid());
                shot1->resetSpeed();
                shot2->resetSpeed();
                shot3->resetSpeed();
  
                asteroid->setValues(0,0,0,-2,-2);
                menu->main_menu_on();
                glutDisplayFunc(drawMenu);
                game->onMenu();
                game->resume_game();
            }
            break;
        case 'h': // 'h' key
            // if pressed while main menu is on, a help guide will be displayed
            if (menu->MainMenu()) {
                game->help();
                menu->main_menu_off();
            }
            break;
        case 27: // ESC key
            // if pressed at any time, the program will close
            glutDestroyWindow(Win_id);
            exit(0);
            break;
        }
        glutPostRedisplay();
}
  
void hitMouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON: 
            if (state == GLUT_DOWN) {
                // when mouse is clicked, the cursor's current x and y coordinates are stored for use in determining asteroid position
                buttons->enableButton();
                xcoord = (GLfloat)x;
                ycoord = (GLfloat)y;
            } else if (state == GLUT_UP) {
                // when mouse is released, the cursor's current x and y coordinates are stored for use in determining asteroid size
                buttons->buttonOff();
                xrad = (GLfloat)x;
                yrad = (GLfloat)y;
            }
            break;
    }
}
  
// allows for the game to constantly update
void idle() {
    glutPostRedisplay();
}
  
int main(int argc, char** argv) {
    // set the x and y size of the window
    xwindowsize = 800;
    ywindowsize = 800; 
  
    // initiate an instance of all necessary classes
    game = new Gamestate();
    menu = new Menu();
    asteroid = new Asteroid(0,0,0,-2,-2);
    buttons = new Buttons();
    ship1 = new Ship((GLfloat)-0.7,(GLfloat)-0.8);
    ship2 = new Ship((GLfloat)0.0,(GLfloat)-0.8);
    ship3 = new Ship((GLfloat)0.7,(GLfloat)-0.8);
    shot1 = new Shot((GLfloat)0,(GLfloat)0);
    shot2 = new Shot((GLfloat)0,(GLfloat)0);
    shot3 = new Shot((GLfloat)0,(GLfloat)0);
  
    stopyshot = 0; 
    wait_to_shoot = game->getFrequency();
  
    // necessary calls to create and draw a window, determine its size and position
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize((int)xwindowsize,(int)ywindowsize);
    glutInitWindowPosition(275,0);
    Win_id = glutCreateWindow("ASTERALAGA");
    glutReshapeFunc(viewport);
    // calls to methods that allow for keyboard and mouse input, displaying graphics to the screen, and automatic updating
    glutKeyboardFunc(hitKey);
    glutMouseFunc(hitMouse);
    glutDisplayFunc(drawMenu);
    glutIdleFunc(idle);
  
    // error that will be printed if the window cannot be created or is created with an error
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW error");
        return 1;
    } 
  
    // loops through the main menu, allowing for constant calls to necessary functions for the duration of use of this program
    glutMainLoop();
  
    return 0;
}