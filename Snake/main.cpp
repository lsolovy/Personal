// Basic code done from FamTrinli on youtube.com - https://www.youtube.com/watch?v=OBBrp43TX3A
// The updates that I have added...reformated code/added a welcome screen and end screen/implemented a score/implemented a state machine
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include "Button.h"

using namespace sf;
using namespace std;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 2;

struct Snake {
    int x, y;
} s[100];

struct Fruit {
    int x, y;
} f;


void Tick() {
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    // direction of snake on grid
    if (dir == 0) { s[0].y += 1; }
    if (dir == 1) { s[0].x -= 1; }
    if (dir == 2) { s[0].x += 1; }
    if (dir == 3) { s[0].y -= 1; }

    // if the snake touches the food it will get added to the end of the snake
    // new food will be generated
    if ((s[0].x == f.x) && (s[0].y == f.y)) {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }
    // if the snake goes off the screen will come back on opposite side
    if (s[0].x > N) { s[0].x = 0; }
    if (s[0].x < 0) { s[0].x = N; }
    if (s[0].y > M) { s[0].y = 0; }
    if (s[0].y < 0) { s[0].y = M; }



}

int main() {
    int maxnum = 0;
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");


    Texture t1, t2, t3;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/green.png");
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Font font;
    if (!font.loadFromFile("../fonts/Gameplay.ttf")) {
        return EXIT_FAILURE;
    }
    Text welcometext;
    welcometext.setFont(font);
    Text scoretext;
    scoretext.setFont(font);
    Text gameovertext;
    gameovertext.setFont(font);
    Text scoretext2;
    scoretext2.setFont(font);

    Button btn1("Easy", {100,50},20,Color::Green,Color::Black);
    btn1.setFont(font);
    btn1.setPosition({50,200});
    Button btn2("Medium", {100,50},20,Color::Green,Color::Black);
    btn2.setFont(font);
    btn2.setPosition({200,200});
    Button btn3("Hard", {100,50},20,Color::Green,Color::Black);
    btn3.setFont(font);
    btn3.setPosition({350,200});
    Button btn4("Restart", {100,50},15,Color::Green,Color::Black);
    btn4.setFont(font);
    btn4.setPosition({50,200});
    Button btn5("Quit", {100,50},15,Color::Green,Color::Black);
    btn5.setFont(font);
    btn5.setPosition({350,200});

    Clock clock;
    float timer = 0, delay = 0.1;

    f.x = 10;
    f.y = 10;

    enum GameState {
        Welcome_State, Play_State, End_State
    };
    GameState Game;
    Game = Welcome_State;
    while (window.isOpen()) {
        if (Game == Welcome_State) {
            Event e;
            maxnum = 0;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                }
                if(e.type == Event::MouseMoved){
                    if(btn1.isMouseOver(window)){
                        btn1.setBackColor(Color::White);
                    }
                    else{
                        btn1.setBackColor(Color::Green);
                    }
                }
                if(e.type == Event::MouseMoved){
                    if(btn2.isMouseOver(window)){
                        btn2.setBackColor(Color::White);
                    }
                    else{
                        btn2.setBackColor(Color::Green);
                    }
                }
                if(e.type == Event::MouseMoved){
                    if(btn3.isMouseOver(window)){
                        btn3.setBackColor(Color::White);
                    }
                    else{
                        btn3.setBackColor(Color::Green);
                    }
                }
                if(e.type == Event::MouseButtonPressed){
                    if(btn1.isMouseOver(window)){
                        Game = Play_State;
                        delay = .5;
                    }
                }
                if(e.type == Event::MouseButtonPressed){
                    if(btn2.isMouseOver(window)){
                        Game = Play_State;
                        delay = 0.1;
                    }
                }
                if(e.type == Event::MouseButtonPressed){
                    if(btn3.isMouseOver(window)){
                        Game = Play_State;
                        delay = 0.05;
                    }
                }
            }
            window.clear();
            welcometext.setString("Welcome to Snake!");
            welcometext.setCharacterSize(22);
            welcometext.setFillColor(sf::Color::Green);
            welcometext.setPosition(110, 100);
            window.draw(welcometext);
            btn1.drawTo(window);
            btn2.drawTo(window);
            btn3.drawTo(window);
            window.display();
        } else if (Game == Play_State) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) { dir = 1; }
            if (Keyboard::isKeyPressed(Keyboard::Right)) { dir = 2; }
            if (Keyboard::isKeyPressed(Keyboard::Up)) { dir = 3; }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {dir = 0;}

            if (timer > delay) {
                timer = 0;
                Tick();

            }
            for (int i = 1; i < num; i++) {
                if (s[0].x == s[i].x && s[0].y == s[i].y) {
                    num = i;
                    Game = End_State;
                }
            }

            if(num > maxnum){
                maxnum = num;
            }
            ////// draw  ///////
            // draws the background
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    sprite1.setPosition(i * size, j * size);
                    window.draw(sprite1);
                }
            }
            // draws the snake
            for (int i = 0; i < num; i++) {
                sprite2.setPosition(s[i].x * size, s[i].y * size);
                window.draw(sprite2);
            }
            // draws the food
            sprite3.setPosition(f.x * size, f.y * size);
            window.draw(sprite3);


            scoretext.setString("Score: " + to_string(num));
            scoretext.setCharacterSize(12);
            scoretext.setFillColor(sf::Color::Red);
            scoretext.setPosition(400,0);
            window.draw(scoretext);
            window.display();
        }
        else{
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                }
            }
            if(e.type == Event::MouseMoved){
                if(btn4.isMouseOver(window)){
                    btn4.setBackColor(Color::White);
                }
                else{
                    btn4.setBackColor(Color::Green);
                }
            }
            if(e.type == Event::MouseButtonPressed){
                if(btn4.isMouseOver(window)){
                    Game = Welcome_State;

                }
            }
            if(e.type == Event::MouseMoved){
                if(btn5.isMouseOver(window)){
                    btn5.setBackColor(Color::White);
                }
                else{
                    btn5.setBackColor(Color::Green);
                }
            }
            if(e.type == Event::MouseButtonPressed){
                if(btn5.isMouseOver(window)){
                    window.close();

                }
            }
            window.clear();
            gameovertext.setString("GAME OVER");
            gameovertext.setCharacterSize(45);
            gameovertext.setPosition(100,100);
            gameovertext.setFillColor(sf::Color::Green);
            scoretext2.setString("Score = " + to_string(maxnum));
            scoretext2.setCharacterSize(25);
            scoretext2.setFillColor(sf::Color::Green);
            scoretext2.setPosition(170,165);
            window.draw(gameovertext);
            window.draw(scoretext2);
            btn4.drawTo(window);
            btn5.drawTo(window);
            window.display();
        }
    }

    return 0;
}
