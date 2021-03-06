#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Defs.h"

// Represents the game GUI
// This class is the ONLY one that interacts with the user
// This class is also the ONLY one aware of the graphics library being used
// That is, if the graphics library was to be changes, this class is the only thing to be changed
class GUI
{
private:
    sf::RenderWindow window;  // Represents the game window
    sf::RenderWindow messagePrompt;//Represents the messageBox window
    
    const sf::Color  // Colors used for drawing (can change the whole theme of the game)
        backgroundColor = sf::Color::White,
        outlineColor = sf::Color:: Black,
        ballFillColor = sf::Color::White,
        flipperFillColor = sf::Color::White;
    const float outlineThickness = -1.0f;  // Negative sign means inwards


    sf::RectangleShape textRect, playRect, diceRect, okButton; // Rectangle edges of the board components
    sf::Texture diceTexture[3];// dicesides
    sf::Text   text;// load Text
    int  numberOfRolling = 0, lastRoll = 0; // For rolling dice
    bool diceIsRolled = 0;// variable for checking if the dice is rolled
 
public:
    GUI();  // Constructor
    void getControls(bool & exit);  // Detects exit button pressed
    void clear();  // Clears the frame (first step in rendering a new frame)
    void display();  // Displays the frame (last step in rendering a new frame)
    
   
    void loadPlayImage(string path, float offsetPositionX, float offsetPositionY, float scaleX, float scaleY);//Loading image as a texture and drawing the texture using sprite
    void loadText(string inText);//For drawing text
    void drawMessageBox();// Drawing message box object
    void drawMenuItems();// Drawng Tool bar menu
    void drawText(); //draw the text on the board
    void drawEdge(float position, bool EdgeDir);// Draws boarders of the spaces, The positions can be read from a file
    void loadDiceSides();//load dice side in textures
    void drawRollDice();// rolling the dice
};
