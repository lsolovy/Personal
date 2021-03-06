// Basic code done from FamTrinli on youtube.com - https://www.youtube.com/watch?v=N60lBZDEwJ8
// visual of lightting bolt , http://www.clipartpanda.com/categories/lighting-bolt-png , free use license if non commerical use
// reforemated code, added a visual for the player, added a time element, added a lap component, added if the player is off the road the speed will decrease, also won't let the player fall below screen

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;


int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200; //segment length
float camD = 0.84; //camera depth


void drawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1 - w1, y1));
    shape.setPoint(1, Vector2f(x2 - w2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(shape);
}

struct Line {
    float x, y, z; //3d center of line
    float X, Y, W; //screen coord
    float curve, spriteX, clip, scale;
    Sprite sprite;

    Line() { spriteX = curve = x = y = z = 0; }

    void project(int camX, int camY, int camZ) {
        scale = camD / (z - camZ);
        X = (1 + scale * (x - camX)) * width / 2;
        Y = (1 - scale * (y - camY)) * height / 2;
        W = scale * roadW * width / 2;

    }

    void drawSprite(RenderWindow &app) {
        Sprite s = sprite;
        int w = s.getTextureRect().width;
        int h = s.getTextureRect().height;

        float destX = X + scale * spriteX * width / 2;
        float destY = Y + 4;
        float destW = w * W / 266;
        float destH = h * W / 266;

        destX += destW * spriteX; //offsetX
        destY += destH * (-1);    //offsetY

        float clipH = destY + destH - clip;
        if (clipH < 0) { clipH = 0; }

        if (clipH >= destH) { return; }
        s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
        s.setScale(destW / w, destH / h);
        s.setPosition(destX, destY);
        app.draw(s);
    }

};


int main() {
    RenderWindow app(VideoMode(width, height), "Outrun Racing!");
    app.setFramerateLimit(60);

    Texture t[50];
    Sprite object[50];
    for (int i = 1; i <= 8; i++) {
        t[i].loadFromFile("images/" + std::to_string(i) + ".png");
        t[i].setSmooth(true);
        object[i].setTexture(t[i]);
    }

    Texture bg;
    bg.loadFromFile("images/bg.png");
    bg.setRepeated(true);
    Sprite sBackground(bg);
    sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
    sBackground.setPosition(-2000, 0);

    Font font;
    if (!font.loadFromFile("../fonts/Gameplay.ttf")) {
        return EXIT_FAILURE;
    }
    Text timertext;
    timertext.setFont(font);
    Text laptext;
    laptext.setFont(font);
    Text bolttext;
    bolttext.setFont(font);

    CircleShape circle;
    circle.setRadius(50);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(5);
    float a = 475;
    float b = 600;
    circle.setPosition(a,b);



    float l1 = 0;


    vector<Line> lines;
    // the path of the road with the objects
    for (int i = 0; i < 1600; i++) {
        Line line;
        line.z = i * segL;

        if (i > 300 && i < 700) { line.curve = 0.5; }
        if (i > 1100) { line.curve = -0.7; }

        if (i < 300 && i % 20 == 0) {
            line.spriteX = -2.5;
            line.sprite = object[5];
        }
        if (i % 17 == 0) {
            line.spriteX = 2.0;
            line.sprite = object[6];
        }
        if (i > 300 && i % 20 == 0) {
            line.spriteX = -0.7;
            line.sprite = object[4];
        }
        if (i > 800 && i % 20 == 0) {
            line.spriteX = -1.2;
            line.sprite = object[1];
        }
        if (i == 400) {
            line.spriteX = -1.2;
            line.sprite = object[7];
        }
        if(i == 500){
            double s;
            srand(unsigned(time(NULL)));
            s = rand()% 3;
            line.spriteX = s/10 - .5;
            l1 = line.spriteX;
            cout << line.spriteX << " ";
            line.sprite = object[8];
        }


        if (i > 750) { line.y = sin(i / 30.0) * 1500; }


        lines.push_back(line);

    }
    int N = lines.size();
    float playerX = 0;
    int pos = 0;
    int H = 1500;
    int time = 0;
    int lap = 0;
    int bolts = 0;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed) {
                app.close();
            }
        }

        int speed = 0;

        if(time >= 0){
            time++;
        }


        if (Keyboard::isKeyPressed(Keyboard::Right)) { playerX += 0.1; }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { playerX -= 0.1; }
        if (Keyboard::isKeyPressed(Keyboard::Up)) { speed = 200; }
        if (Keyboard::isKeyPressed(Keyboard::Down)) { speed = -200; }
        if (Keyboard::isKeyPressed(Keyboard::Tab)) { speed *= 3; }
        if (Keyboard::isKeyPressed(Keyboard::W)) { H += 100; }
        if (Keyboard::isKeyPressed(Keyboard::S)) { H -= 100; }
        // won't let the player go below road
        if(H < 1500){
            H = 1500;
        }
        // if player is off the road
        if(playerX >= 1 || playerX <= -1){
            speed *= 0.5;
        }

        pos += speed;
        while (pos >= N * segL) { pos -= N * segL; }
        while (pos < 0) { pos += N * segL; }

        app.clear(Color(105, 205, 4));
        app.draw(sBackground);
        int startPos = pos / segL;
        int camH = lines[startPos].y + H;
        if (speed > 0) { sBackground.move(-lines[startPos].curve * 2, 0); }
        if (speed < 0) { sBackground.move(lines[startPos].curve * 2, 0); }

        int maxy = height;
        float x = 0, dx = 0;

        if(playerX == l1 && startPos == 492){
            bolts++;
        }
        cout << startPos << " ";
        ///////draw road////////
        for (int n = startPos; n < startPos + 300; n++) {

            Line &l = lines[n % N];
            l.project(playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0));
            x += dx;
            dx += l.curve;

            l.clip = maxy;
            if (l.Y >= maxy) { continue; }
            maxy = l.Y;

            Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
            Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
            Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

            Line p = lines[(n - 1) % N]; //previous line

            drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
            drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
            drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);


        }

        if(startPos == 1599){
            lap++;
        }

        ////////draw objects////////
        for (int n = startPos + 300; n > startPos; n--) {
            lines[n % N].drawSprite(app);
        }
        timertext.setString("Timer: " + to_string(time));
        timertext.setFillColor(sf::Color::Black);
        timertext.setCharacterSize(22);
        timertext.setPosition(880, 30);
        laptext.setString("Lap: " + to_string(lap));
        laptext.setFillColor(sf::Color::Black);
        laptext.setCharacterSize(22);
        laptext.setPosition(880,60);
        bolttext.setString("Bolts: " + to_string(bolts));
        bolttext.setFillColor(sf::Color::Black);
        bolttext.setCharacterSize(22);
        bolttext.setPosition(880,90);
        app.draw(timertext);
        app.draw(laptext);
        app.draw(bolttext);
        app.draw(circle);
        app.display();
    }

    return 0;
}





