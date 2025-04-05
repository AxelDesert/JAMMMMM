/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Display
*/


#include "Display.hpp"
#define SI if
#define MIENTRAS while

Display::Display() : _ventana(sf::VideoMode(1000, 470), "Mi_phoenix") {
    _papelpintadodia = configuarPapelPintadoDia();
    _papelpintadodia2 = configuarPapelPintadoDia();
    _papelpintadodia2 .setPosition(_papelpintadodia.getGlobalBounds().width, 0);
    _jugador = configuarAssetJugador();
    _frameTime = 0.15f;
    SI (!_textureObstaculo.loadFromFile("assets/littleWater.png"))
        std::cout << "no d'asset" << std::endl;
}

void Display::moverPapelPintado(sf::Clock &tiempo, float &mapa)
{
    SI (tiempo.getElapsedTime().asSeconds() > 0.008f) {
        mapa -= 1;
        _papelpintadodia.setPosition(mapa, 0);
        _papelpintadodia2.setPosition(mapa + _papelpintadodia.getGlobalBounds().width, 0);
        SI (mapa <= -_papelpintadodia.getGlobalBounds().width) {
            mapa = 0;
        }

        for (auto& obs : _obstaculos) {
            sf::Vector2f position = obs.obtenerPosicion();
            position.x -= 1;
            obs.establecerPosicion(position);
        }

        _obstaculos.erase(std::remove_if(_obstaculos.begin(), _obstaculos.end(),
            [](const Obstaculo& obs) {
                return obs.estaFueraDePantalla();
            }), _obstaculos.end());
        tiempo.restart();
    }
}

void Display::animarPlayer(sf::Clock &tiempo, int &actual)
{
    const int numeroFrames = 4;

    SI (tiempo.getElapsedTime().asSeconds() > _frameTime) {
        actual = (actual + 1) % numeroFrames;
        _jugador.setTextureRect(sf::IntRect((actual  * _offsetPlayer.x), _offsetPlayer.y, 32, 32));
        tiempo.restart();
    }
}

void Display::buclejuego() {
    sf::Clock tiempo;
    sf::Clock tiempoBack;
    sf::Clock test;
    sf::Clock relojObstaculos;
    sf::Clock temporizadorMenu;
    int currentFrame = 0;
    float mapa = 0;
    sf::Event event;

    while (_ventana.isOpen()) {
        while (_ventana.pollEvent(event)) {
            this->secuso(event);
        }

        if (_estadoJuego == EN_CURSO) {
            temporizadorMenu.restart();
            animarPlayer(tiempo, currentFrame);
            moverPapelPintado(tiempoBack, mapa);

            _tiempoUltimoObstaculo += relojObstaculos.restart().asSeconds();
            if (_tiempoUltimoObstaculo >= 2.0f) {
                float y = rand() % _ventana.getSize().y;
                _obstaculos.emplace_back(_textureObstaculo, _ventana.getSize().x, y);
                _tiempoUltimoObstaculo = 0;
            }

            if (verificarColisionJugador() == GAME_OVER) {
                _estadoJuego = GAME_OVER;
                temporizadorMenu.restart();
            }

            _ventana.draw(_papelpintadodia);
            _ventana.draw(_papelpintadodia2);
            _ventana.draw(_jugador);
            for (const auto& obs : _obstaculos)
                obs.dibujar(_ventana);
            _ventana.display();
            _ventana.clear();
        } else if (_estadoJuego == GAME_OVER || _estadoJuego == INICIO) {
            if (temporizadorMenu.getElapsedTime().asSeconds() >= 10.0f) {
                _estadoJuego = EN_CURSO;
                _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                _obstaculos.clear();
                temporizadorMenu.restart();
            } else {
                mostrarMenuGameOver();
            }
        }
    }
}


void Display::secuso(sf::Event event)
{
    SI (event.type == sf::Event::Closed) {
            _ventana.close();
    }
    SI (event.type == sf::Event::KeyPressed) {
        SI (event.key.code == sf::Keyboard::Up) {
            SI (_postionPlayer.y - 20 >= 0) {
                _offsetPlayer.y = 0;
                _offsetPlayer.x = 32;
                _postionPlayer.y -= 20;
                _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                //_jugador.setTextureRect(sf::IntRect(_offsetPlayer.x,_offsetPlayer.y,32,32));
            }
        }
        SI (event.key.code == sf::Keyboard::Down) {
            SI (_postionPlayer.y + 20 <= _ventana.getSize().y - 32) {
                _offsetPlayer.y = 0;
                _offsetPlayer.x = 32;
                _postionPlayer.y += 20;
                _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                //_jugador.setTextureRect(sf::IntRect(_offsetPlayer.x,_offsetPlayer.y,32,32));
            }
        }
    }
}

Display::estadoJuego Display::verificarColisionJugador()
{
    for (const auto& obs : _obstaculos) {
        SI (_jugador.getGlobalBounds().intersects(obs.obtenerLimites())) {
            return GAME_OVER;
        }
    }
    return EN_CURSO;
}

sf::Sprite Display::configuarAssetJugador()
{
    SI (!_texturePlayer.loadFromFile("assets/Phoenix.png"))
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
    SI (!_textureBackground.loadFromFile("assets/diamapa2.png"))
        std::cout << "pas d'asset" << std::endl;
    sf::Sprite back(_textureBackground);
    back.setPosition({0, 0});
    back.setScale({1.5, 1.5});
    return back;
}