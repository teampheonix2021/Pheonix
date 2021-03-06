#include "GUI.h"


GUI::GUI()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Remove this line if the Board was too laggy
    window.create(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), " Bank of Luck Simulation");
    window.setVerticalSyncEnabled(true);

//load the dice sides array 
   loadDiceSides();
}
// Function for getting control on any event such as keyboard or mouse 
void GUI::getControls(bool& exit)
{
    sf::Event event;

    //check the window events
    while (window.pollEvent(event))
        
    {
        //if ESC button is pressed the game window is closed!
       exit = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

      
       // check if the closed button of window is closed
       if (event.type == event.Closed)
       {
           window.close();
       }
       //check if the left button of the mouse is pressed
       if (event.MouseButtonReleased&& event.mouseButton.button==sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect diceBtnBounds = diceRect.getGlobalBounds();
            sf::FloatRect playBtnBounds = playRect.getGlobalBounds();

            //if the mouse left button is pressed on the dice button, the side is changed
            if (diceBtnBounds.contains(mousePos))
            {
                if (!diceIsRolled)
                {
                    lastRoll = 0;
                    numberOfRolling = 0;

                }
            }

            //if mouse left button is pressed on the play button, The message box is appread
            if (playBtnBounds.contains(mousePos))
            {
                sf::ContextSettings settings;
                settings.antialiasingLevel = 8;  // Remove this line if the Board was too laggy
                messagePrompt.create(sf::VideoMode(265, 166), "messageBox", sf::Style::Titlebar, settings);
                messagePrompt.setVerticalSyncEnabled(true);

            }


        }
    }//loop of window event

    //check the messagebox events
    while (messagePrompt.pollEvent(event))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePos = messagePrompt.mapPixelToCoords(sf::Mouse::getPosition(messagePrompt));
            sf::FloatRect okButtonBounds = okButton.getGlobalBounds();

            if (okButtonBounds.contains(mousePos))
            {
                messagePrompt.close();

            }

        }
    }//loop of messagebox events
}

void GUI::clear()
{
    window.clear(backgroundColor);
}

void GUI::display()
{
    window.display();
}
//This function can be changes to load arrays of images  according to the game components
void GUI::loadPlayImage(std::string path, float setPositionX, float setPositionY, float scaleX,float scaleY)
{
    //Create the texture
    sf::Texture texture;
    texture.loadFromFile(path);
    //Use the sprite to load the image and scale it,  another method in loadDiceSides() function
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(setPositionX, setPositionY)); // offset relative to the original position(0,0)
    sprite.scale(sf::Vector2f(scaleX, scaleY)); // factor relative to the current scale
    // Create play Edge
    playRect.setSize(sf::Vector2f(65.0f, 65.0f));
    playRect.setOutlineThickness(outlineThickness);
    playRect.setOutlineColor(outlineColor);
    playRect.setPosition(40, 40);

    window.draw(playRect);
    window.draw(sprite);

    
}
//This function can be changes to load arrays of text  according to the game components and adding more arguments for the positions
void GUI::loadText(string inText)
{
    
    // select the font
    sf::Font font;
    font.loadFromFile(ARIAL_FONT);
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString(inText);
    // set the character size
    text.setCharacterSize(15); // in pixels, not points!
    // set the color
    text.setFillColor(outlineColor);
    // set the text style
    text.setStyle(sf::Text::Bold);
    //set the text position
    text.setPosition(650.0f, 650.0f);
    
   // Create Dice Edge, which can be used for applying events on the text
    textRect.setSize(sf::Vector2f(450.0f, 35.0f));
    textRect.setOutlineThickness(0); // can be outlineThickness to show border
    textRect.setOutlineColor(outlineColor);
    textRect.setPosition(530.0f, 650.0f);


    window.draw(textRect, sf::RenderStates());
    window.draw(text, sf::RenderStates());
   

}


//This function is invoked from the game object to allocate the menucomponents
void GUI::drawMenuItems()
{

    loadPlayImage("Images\\playImage.png", 50, 50, 0.5, 0.5);
    
}
void GUI::drawText()
{

    loadText("Please click here to roll the dice");
}


//this function is invoked from messagebox object to popup the message box
void GUI::drawMessageBox()
{
    sf::Font arialFont;
    arialFont.loadFromFile(ARIAL_FONT);
    sf::Text messageTitle;
    messageTitle.setString("Welcome");
    messageTitle.setCharacterSize(25);
    messageTitle.setFont(arialFont);
    messageTitle.setPosition(15.0f, 15.0f);
    messageTitle.setFillColor(outlineColor);

    sf::Text messageText;
    messageText.setFont(arialFont);
    messageText.setString("Press on Ok button to Close!");
    messageText.setPosition(15.0f, 75.0f);
    messageText.setCharacterSize(15);
    messageText.setFillColor(outlineColor);

  
    sf::Texture okButtonTexture;
    okButtonTexture.loadFromFile("Images\\ok.png");
    okButton.setSize(sf::Vector2f(40.0f, 40.0f));
    okButton.setTexture(&okButtonTexture);
    okButton.setPosition(120.0f, 125.0f);
    okButton.setOutlineThickness(outlineThickness);
    okButton.setOutlineColor(outlineColor);
    okButtonTexture.setSmooth(true);

     messagePrompt.clear(backgroundColor);

        messagePrompt.draw(messageTitle);
        messagePrompt.draw(messageText);
        messagePrompt.draw(okButton);

    messagePrompt.display();
  }



// a smiliar function can be used for drawing individual lines
void GUI::drawEdge(float position, bool EdgeDir)
{
    if (EdgeDir == 0) //condition for drawing the vertical Edges
    {
        sf::Vertex line[] =
        {
                sf::Vertex(sf::Vector2f(position,200), outlineColor),
                sf::Vertex(sf::Vector2f(position, BOARD_HEIGHT - 200), outlineColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    else if (EdgeDir == 1) // Condition for drawing the horizontal Edge

    {
        sf::Vertex line[] =
        {
          sf::Vertex(sf::Vector2f(200, position), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, position), outlineColor)
        };
        window.draw(line, 2, sf::Lines);
    }



}



// Create pool of dice sides
void GUI::loadDiceSides()
{

    diceRect.setSize(sf::Vector2f(DICEX, DICEY));
    diceRect.setPosition(732.0f, 590.0f);
    //You should add more lines and images for more dice sides
    diceTexture[0].loadFromFile("Images/dice/1.png");
    diceTexture[1].loadFromFile("Images/dice/2.png");
    diceTexture[2].loadFromFile("Images/dice/3.png");
    for (int i = 0; i < 3; i++)
        diceTexture[i].setSmooth(true);    
}
// //this function is invoked from dice object to roll the dice
void GUI::drawRollDice()
{
    // decrease the second condition to see the suffeling among dice sides ex: numberOfRolling - lastRoll == 8
    if (numberOfRolling <= 100 && numberOfRolling - lastRoll == 35)
    {
       int  dicePicNumber = rand() % 3;
        diceRect.setTexture(&diceTexture[dicePicNumber]);
        lastRoll = numberOfRolling;
       
    }
   //draw the new side
   window.draw(diceRect);

    if (numberOfRolling <= 100) numberOfRolling++;
}