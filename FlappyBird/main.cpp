
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <cmath>
#include <SFML/Audio.hpp>
#include <string>


using namespace sf;
using namespace std;
const int W = 1200;
const int H = 800;

int main() {

    srand(time(0));

    RenderWindow app(VideoMode(W, H), "FlappyBird!");
    app.setFramerateLimit(60);


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
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::Space) {
                        Game = Play_State;
                    }
                }
            }
            app.display();
        }
    }


    return 0;
}
