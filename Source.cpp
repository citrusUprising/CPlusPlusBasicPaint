#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


int main()
{
    // create the window
    //enables anti-aliasing level 8 to all shapes
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Legit MSPaint", sf::Style::Default, settings);

    // various states
    bool erase = false;
    sf::Color hue = sf::Color(150, 150, 150); //brush color
    float size = 10; //brush size
    float sizeMax = 200; //brush size maximum
    int state = 0; //brush shape
    int stateMax = 3; //amount of brush shapes
    sf::Vector2f localPosition = sf::Vector2f (0.f,0.f); //mouse position
    sf::Vector2f position1a = sf::Vector2f(0.f, 0.f); //mouse position adjusted for 1a
    sf::Vector2f position1b = sf::Vector2f(0.f, 0.f); //mouse position adjusted for 1b
    sf::CircleShape brush0(size); //brush 0
    sf::RectangleShape brush1a(sf::Vector2f(size*2, size/2));
    sf::RectangleShape brush1b(sf::Vector2f(size/2, size*2));
    sf::CircleShape brush2(size,3); //brush 2
    int frameC = 0; //duration of button holding for colors
    int frameS = 0; //duration of button holding for sizes

    // run the program as long as the window is open
    window.clear(sf::Color::White);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Change color
        int red = hue.r;
        int green = hue.g;
        int blue = hue.b;

        //increment color controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            frameC += 1;
        }
        else frameC = 0;

        //Change Color
        if (frameC >= 20) frameC = 0; //sets frame to loop limiting rate of color change
        if (frameC == 0) { //limits speed of color change
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                red++;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                red--;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                green++;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                green--;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                blue++;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                blue--;
            //cout << "current color is " << red << ", " << green << ", "<<blue;
        }

        //Increment Size Controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            frameS += 1;
        }
        else frameS = 0;

        //Change Color
        if (frameS >= 60) frameS = 0; //sets frame to loop limiting rate of size change
        if (frameS == 0) { //limits speed of size change
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                size++;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                size--;
          
            //cout << "size is " << size;
        }


        //change brush
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            state = 0;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            state = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            state = 2;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            state = 3;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            state = 4;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            state = 5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            state = 6;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            state = 7;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            state = 8;
           
        //catch limits
        if (size > sizeMax) size = sizeMax; //set maximum size to sizeMax
        if (size < 1) size = 1; //set minimum size to 1

        //color bounding limits
        if (red > 255) red = 255;
        else if (red < 0) red = 0;
        if (green > 255) green = 255;
        else if (green < 0) green = 0;
        if (blue > 255) blue = 255;
        else if (blue < 0) blue = 0;

        //Set Brushes
        hue = sf::Color(red, green, blue);
        localPosition = sf::Vector2f(sf::Mouse::getPosition(window).x-size, sf::Mouse::getPosition(window).y-size);
        if (state == 0) {
            brush0.setPosition(localPosition);
            brush0.setRadius(size);
            brush0.setFillColor(hue);
        }
        else if (state == 1) {
            position1a = sf::Vector2f(sf::Mouse::getPosition(window).x - size, sf::Mouse::getPosition(window).y- size/4);
            position1b = sf::Vector2f(sf::Mouse::getPosition(window).x - size/4, sf::Mouse::getPosition(window).y - size);
            brush1a.setPosition(position1a);
            brush1b.setPosition(position1b);
            brush1a.setSize(sf::Vector2f(size*2, size/2));
            brush1b.setSize(sf::Vector2f(size/2, size*2));
            brush1a.setFillColor(hue);
            brush1b.setFillColor(hue);
        }
        else {
            brush2 = sf::CircleShape (size, state+1);
            brush2.setPosition(localPosition);
            brush2.setFillColor(sf::Color(hue.r,hue.g,hue.b, 100));
        }

        // clear the window with white color
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))window.clear(sf::Color::White); //manual to allow for persistence

        // draw everything here...
        if (sf::Mouse::isButtonPressed(sf:: Mouse::Left)) {
            if(state == 0){
                window.draw(brush0);
            }
            else if (state == 1) {
                window.draw(brush1a);
                window.draw(brush1b);
            }
            else {
                window.draw(brush2);
            }
            
        }

        // end the current frame
        window.display();
    }

    return 0;
}