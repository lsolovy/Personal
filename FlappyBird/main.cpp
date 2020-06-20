
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>

#include "Button.h"


using namespace sf;
using namespace std;
const float W = 1200;
const float H = 800;


void Bird(RenderWindow(&app)){
    CircleShape circle(50.f);
    circle.setFillColor(Color(255,0,0));
    circle.setPosition(200,H/2);
    circle.setPointCount(100);
    app.draw(circle);
    app.display();
}


int main() {

    srand(time(0));

    RenderWindow app(VideoMode(W, H), "FlappyBird!");
    app.setFramerateLimit(60);
    Font font;
    if (!font.loadFromFile("../fonts/Gameplay.ttf")) {
        return EXIT_FAILURE;
    }
    Button btn1("Start", {100,50},20,Color::Green,Color::Black);
    btn1.setFont(font);
    btn1.setPosition({50,200});

    //start of state machine
    enum GameState{
        Welcome_State, Play_State, End_State
    };
    GameState Game;
    Game = Welcome_State;
    while (app.isOpen()) {
        if (Game == Welcome_State) {
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
                if(e.type == Event::MouseMoved){
                    if(btn1.isMouseOver(app)){
                        btn1.setBackColor(Color::White);
                    }
                    else{
                        btn1.setBackColor(Color::Green);
                    }
                }
                if(e.type == Event::MouseButtonPressed){
                    if(btn1.isMouseOver(app)){
                        Game = Play_State;
                    }
                }
            }
            btn1.drawTo(app);
            app.display();
        } else if (Game == Play_State){
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::Space) {
                        Game = End_State;
                    }
                }
            }
            app.clear();
            Bird(app);

        } else {
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
            }
            app.display();
        }
    }

    return 0;
}
