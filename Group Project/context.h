#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
  
class Gamestate {
    public:
        Gamestate() { // constructor
            level = 1;
            lives = 3;
            ships_alive = 3;
            pressure = 100;
            shot_frequency = 500;
            play_level = false;
            draw_level = false;
            help_menu = false;
            game_paused = false;
            game_ended = false;
            storeShipSpeed = 0;
            storeShotSpeed = 0;
            storeAsteroidXVel = 0;
            storeAsteroidYVel = 0;
        } 
  
        int getLevel() { // return level
            return level;
        }
  
        void nextLevel() { // increment to next level
            ++level;
            determineFrequency();
        }
  
        void resetLevel() { // reset level to level 1
            level = 1;
            resetFrequency();
        }
  
        int getLives() { // return number of lives
            return lives;
        }
  
        void loseLife() { // decrement lives
            --lives;
        }
  
        void resetLives() { // reset lives to 3
            lives = 3;
        }
  
        int getNumberShipsAlive() { // return number of ships alive
            return ships_alive;
        }
  
        void shipDestroyed() { // decrement ships_alive
            --ships_alive;
        }
  
        void restoreAllShips() { // reset ships_alive to 3
            ships_alive = 3;
        }
  
        double getPressure() { // return pressure
            return pressure;
        }
  
        void reducePressure(GLfloat s) { // decrement pressure according to formula below (based on size of asteroid)
            pressure = pressure - s;
        }
  
        void resetPressure() { // reset pressure to 100%
            pressure = 100;
        }
  
        double getFrequency() { // return shot frequency
            return shot_frequency;
        }
  
        void determineFrequency() { // determine shot frequency based on the algorithm below
            shot_frequency = shot_frequency - (shot_frequency/100);
        }
  
        void resetFrequency() { // reset frequency 
            shot_frequency = 500;
        }
  
        void gameStart() { // set play_level to true
            play_level = true;
        }
  
        void onMenu() { // set play_level to false
            play_level = false;
        }
  
        bool playGame() { // is level currently being played?
            return play_level == true;
        }
  
        void draw_start() { // set draw_level to true
            draw_level = true;
        }
  
        void draw_stop() { // set draw_level to false
            draw_level = false;
        }
  
        bool level_draw() { // is level being drawn?
            return draw_level == true;
        }
  
        void help() { // set help_menu to true
            help_menu = true;
        }
  
        void help_done() { // set help_menu to false
            help_menu = false;
        }
  
        bool display_help() { // is help menu being displayed?
            return help_menu == true;
        }
  
        void pause_game() { // set game_paused to true
            game_paused = true;
        }
  
        void resume_game() { // set game_paused to false
            game_paused = false;
        }
  
        bool isGamePaused() { // is the game currently paused?
            return game_paused == true;
        }
  
        void game_end() { // set game_ended to true
            game_ended = true;
        }
  
        void restart_game() { // set game_ended to false
            game_ended = false;
        }
  
        void pauseGame(GLfloat ship, GLfloat shot, GLfloat vx, GLfloat vy) { // store values of ship/shot speeds and asteroid velocity for future reference
            storeShipSpeed = ship;
            storeShotSpeed = shot;
            storeAsteroidXVel = vx;
            storeAsteroidYVel = vy;
        }
  
        GLfloat returnShipSpeed() { // return ship speed
            return storeShipSpeed;
        }
  
        GLfloat returnShotSpeed() { // return shot speed
            return storeShotSpeed;
        }
  
        double returnAsteroidXVel() { // return asteroid's horizontal velocity
            return storeAsteroidXVel;
        }
  
        double returnAsteroidYVel() { // return asteroid's vertical velocity
            return storeAsteroidYVel;
        }
  
    private:    
        int level; // int value to store current level
        int lives; // int value to store current number of lives
        int ships_alive; // int value to store amount of ships alive
        double shot_frequency; // int value to determine the frequency with which shots are fired. Will be more frequent as level increases
        double pressure; // double value to store current pressure remaining
        bool play_level; // boolean value to determine whether level is currently being played
        bool draw_level; // boolean value to determine whether level is currently being drawn
        bool help_menu; // boolean value to determine whether the help menu is being displayed
        bool game_paused; // boolean value to determine whether the game is currently paused
        bool game_ended; // boolean value to determine whether the game has ended
        GLfloat storeShipSpeed; // GLfloat value to store the ship's speed
        GLfloat storeShotSpeed; // GLfloat value to store the shot's speed
        GLfloat storeAsteroidXVel; // GLfloat value to store the asteroid's horizontal velocity
        GLfloat storeAsteroidYVel; // GLfloat value to store the asteroid's vertical velocity
};