/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Display
*/


#include "Display.hpp"
#define SI if
#define MINETRAS while

Display::Display() : _ventana(sf::VideoMode(1000, 470), "Mi_phoenix") {
    _papelpintadodia = configuarPapelPintadoDia();
    _papelpintadodia2 = configuarPapelPintadoDia();
    _papelpintadodia2 .setPosition(_papelpintadodia.getGlobalBounds().width, 0);
    _jugador = configuarAssetJugador();
    _frameTime = 0.15f;
}

void Display::moverPapelPintado(sf::Clock &tiempo, float &map)
{
    if (tiempo.getElapsedTime().asSeconds() > 0.008f) {
        map -= 1;
        _papelpintadodia.setPosition(map, 0);
        _papelpintadodia2.setPosition(map + _papelpintadodia.getGlobalBounds().width, 0);
        if (map <= -_papelpintadodia.getGlobalBounds().width) {
            map = 0;
        }
        tiempo.restart();
    }
}

void Display::animarPlayer(sf::Clock &tiempo, int &actual)
{
    const int numeroFrames = 4;

    if (tiempo.getElapsedTime().asSeconds() > _frameTime) {
        actual = (actual + 1) % numeroFrames;
        _jugador.setTextureRect(sf::IntRect((actual  * _offsetPlayer.x), _offsetPlayer.y, 32, 32));
        tiempo.restart();
    }
}

void Display::buclejuego()
{
    sf::Clock tiempo;
    sf::Clock tiempoBack;
    sf::Clock test;
    int currentFrame = 0;
    float map = 0;

    MINETRAS (_ventana.isOpen()) {
        sf::Event event;
        MINETRAS (_ventana.pollEvent(event)) {
            SI (event.type == sf::Event::Closed) {
                _ventana.close();
            }
            SI (event.type == sf::Event::KeyPressed) {
                SI (event.key.code == sf::Keyboard::Up) {
                    _offsetPlayer.y = 32;
                    _offsetPlayer.x = 32 ;
                    _jugador.setTextureRect(sf::IntRect(_offsetPlayer.x,_offsetPlayer.y,32,32));
                    _postionPlayer.y -= 20;
                    _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                }
                SI (event.key.code == sf::Keyboard::Down) {
                    _offsetPlayer.y = 0;
                    _offsetPlayer.x = 32;
                    _jugador.setTextureRect(sf::IntRect(_offsetPlayer.x,_offsetPlayer.y,32,32));
                }
            }
        }
        animarPlayer(tiempo, currentFrame);
        moverPapelPintado(tiempoBack, map);
        _ventana.draw(_papelpintadodia);
        _ventana.draw(_papelpintadodia2);
        _ventana.draw(_jugador);
        _ventana.display();
        _ventana.clear();
    }
}


sf::Sprite Display::configuarAssetJugador()
{
    if (!_texturePlayer.loadFromFile("assets/Phoenix.png"))
        std::cout << "no d'asset" << std::endl;
    sf::Sprite play(_texturePlayer);
    _offsetPlayer = {32,0};
    _postionPlayer = {50, 100};
    play.setTextureRect(sf::IntRect(_offsetPlayer.x,_offsetPlayer.y,32,32));
    play.setPosition(_postionPlayer.x, _postionPlayer.y);
    play.setScale({2, 2});
    return play;
}

sf::Sprite Display::configuarPapelPintadoDia() {
    if (!_textureBackground.loadFromFile("assets/diamapa2.png"))
        std::cout << "pas d'asset" << std::endl;
    sf::Sprite back(_textureBackground);
    back.setPosition({0, 0});
    back.setScale({1.5, 1.5});
    return back;
}