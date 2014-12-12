#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
  
class Menu {
    public:
        Menu() { // constructor
            main_menu = true;
            complete_level_menu = false;
            failed_level_menu = false;
        }
           
        bool MainMenu() { // is main menu being drawn?
            return main_menu == true;
        }
  
        void main_menu_on() { // set main_menu to true
            main_menu = true;
        }
  
        void main_menu_off() { // set main_menu to false
            main_menu = false;
        }
  
        bool CompleteLevelMenu() { // is the complete level menu being drawn?
            return complete_level_menu;
        }
  
        void complete_level_menu_on() { // set complete_level_menu to true
            complete_level_menu = true;
        }
  
        void complete_level_menu_off() { // set complete_level_menu to false
            complete_level_menu = false;
        }
  
        bool FailedLevelMenu() { // is the failed level menu being drawn?
            return failed_level_menu;
        }
  
        void failed_level_menu_on() { // set failed_level_menu to true
            failed_level_menu = true;
        }
  
        void failed_level_menu_off() { // set failed_level_menu to false
            failed_level_menu = false;
        }
  
    private:
        bool main_menu; // boolean value for if the main menu is being drawn
        bool complete_level_menu; // boolean value for if the complete level menu is being drawn
        bool failed_level_menu; // boolean value for if the failed level menu is being drawn
};
  
class Buttons {
    public:
        Buttons() { // constructor
            mouse_clicked = false; 
            mouse_released = false;
        }
  
        bool buttonClicked() { // has this button been clicked?
            return mouse_clicked == true;
        }
  
        void disableButton() { // set mouse_clicked to false
            mouse_clicked = false;
        }
  
        void enableButton() { // set mouse_clicked to true
            mouse_clicked = true;
        }
  
        bool buttonReleased() { // has this button been released?
            return mouse_released == true;
        }
  
        void buttonOn() { // set mouse_released to false
            mouse_released = false;
        }
  
        void buttonOff() { // set mouse_released to true
            mouse_released = true;
        }
  
    private:
        bool mouse_clicked; // boolean value for if the button has been clicked
        bool mouse_released; // boolean value for it the button has been released
};