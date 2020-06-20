
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;




int main() {
    RenderWindow window(VideoMode(512,512),"Animation",Style::Close | Style::Resize);
    RectangleShape player(Vector2f(100.0f,100.0f));
    Texture playerTexture;
    playerTexture.loadFromFile("images/player.png");

    return 0;
}
