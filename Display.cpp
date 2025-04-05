/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Display
*/


#include "Display.hpp"
#define SI if
#define MIENTRAS while
#include <math.h>

Display::Display() : _ventana(sf::VideoMode(1000, 470), "Mi_phoenix") {
    _papelpintadodia = configuarPapelPintadoDia();
    _papelpintadodia2 = configuarPapelPintadoDia();
    _papelpintadodia2.setPosition(_papelpintadodia.getGlobalBounds().width, 0);
    _jugador = configuarAssetJugador();
    _frameTime = 0.15f;
    _santos = 0;             // Score actuel
    _highScore = 0;          // Meilleur score
    _velocidadBase = 0.2f;   // Vitesse de base
    _tiempoDeActualizacion = 0.002f;  // Temps entre chaque mise à jour (remplace _goncalves)
    SI (!_textureObstaculo.loadFromFile("assets/littleWater.png"))
        std::cout << "no d'asset" << std::endl;
    _vueOriginale = _ventana.getDefaultView();
}

void Display::moverPapelPintado(sf::Clock &tiempo, float &mapa)
{
    SI (tiempo.getElapsedTime().asSeconds() > _tiempoDeActualizacion) {
        mapa -= _velocidadBase;
        _papelpintadodia.setPosition(mapa, 0);
        _papelpintadodia2.setPosition(mapa + _papelpintadodia.getGlobalBounds().width, 0);
        SI (mapa <= -_papelpintadodia.getGlobalBounds().width) {
            mapa = 0;
        }

        for (auto& obs : _obstaculos) {
            sf::Vector2f position = obs.obtenerPosicion();
            position.x -= _velocidadBase;
            obs.establecerPosicion(position);
        }

        _obstaculos.erase(std::remove_if(_obstaculos.begin(), _obstaculos.end(),
                                         [](const Obstaculo& obs) {
                                             return obs.estaFueraDePantalla();
                                         }), _obstaculos.end());
        tiempo.restart();
    }
}

void Display::animarPlayer(sf::Clock &tiempo, int &actual, bool &res)
{
    const int numeroFrames = 5;
    const int zoomFrames = 10;
    static int frameCount = 0;

    SI (tiempo.getElapsedTime().asSeconds() > _frameTime) {
        actual = (actual + 1) % numeroFrames;
        SI (res) {
            _jugador.setTextureRect(sf::IntRect((actual * _offsetPlayer.x), 64, 32, 32));
            frameCount++;
            sf::View zoomView = _vueOriginale;
            zoomView.setSize(_vueOriginale.getSize().x / 1.5f, _vueOriginale.getSize().y / 1.5f); // zoom x1.5
            zoomView.setCenter(_jugador.getPosition());
            _ventana.setView(zoomView);
            SI (frameCount >= zoomFrames) {
                res = false;
                _jugador.setTextureRect(sf::IntRect((actual * _offsetPlayer.x), 0, 32, 32));
                frameCount = 0;
                _ventana.setView(_vueOriginale);
            }
        } else {
            _jugador.setTextureRect(sf::IntRect((actual * _offsetPlayer.x), 0, 32, 32));
            _ventana.setView(_vueOriginale);
        }

        tiempo.restart();
    }
}


void Display::actualizarVelocidad()
{
    _velocidadBase = 1.0f + (_santos / 4000.0f) * 0.2f;

    SI (_velocidadBase > 3.0f) {
        _velocidadBase = 3.0f;
    }

    _tiempoEntreObstaculos = 1.0f;
}

void Display::buclejuego() {
    sf::Clock tiempo;
    sf::Clock tiempoBack;
    sf::Clock flap;
    sf::Clock relojObstaculos;
    sf::Clock temporizadorMenu;
    sf::Clock introTimer;
    int currentFrame = 0;
    float mapa = 0;
    bool res = false;
    sf::Event event;

    MIENTRAS (_ventana.isOpen()) {
        MIENTRAS (_ventana.pollEvent(event)) {
            this->secuso(event);
        }

        SI (_estadoJuego == EN_CURSO) {
            _santos += 0.2f * _velocidadBase;

            SI (_santos > _highScore) {
                _highScore = _santos;
            }
            actualizarVelocidad();

            temporizadorMenu.restart();
            animarPlayer(tiempo, currentFrame, res);
            moverPapelPintado(tiempoBack, mapa);
            float dt = flap.restart().asSeconds();

            _velocidadY += _gravedad * dt;
            _postionPlayer.y += _velocidadY * dt;
            float angle = std::min(std::max((_velocidadY / 400.f) * 360.f, -30.f), 360.f);
            _jugador.setRotation(angle);
            SI (_postionPlayer.y < 0) {
                _postionPlayer.y = 0;
                _velocidadY = 0;
            }
            SI (_postionPlayer.y > _ventana.getSize().y - 64) {
                _postionPlayer.y = _ventana.getSize().y - 64;
                _velocidadY = 0;
            }
            _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
            _tiempoUltimoObstaculo += relojObstaculos.restart().asSeconds();
            SI (_tiempoUltimoObstaculo >= _tiempoEntreObstaculos) {
                float y = rand() % (_ventana.getSize().y - 100);
                _obstaculos.emplace_back(_textureObstaculo, _ventana.getSize().x, y);
                _tiempoUltimoObstaculo = 0;
            }
            SI (verificarColisionJugador() == GAME_OVER) {
                _soundManager.playSound(MUERTE);
                _estadoJuego = GAME_OVER;
                temporizadorMenu.restart();
            }
            _ventana.draw(_papelpintadodia);
            _ventana.draw(_papelpintadodia2);
            _ventana.draw(_jugador);
            for (const auto& obs : _obstaculos) {
                obs.dibujar(_ventana);
            }
            _ventana.display();
            _ventana.clear();
        } else SI (_estadoJuego == GAME_OVER || _estadoJuego == INICIO) {
            SI (temporizadorMenu.getElapsedTime().asSeconds() >= 15.0f) {
                SI (_estadoJuego != INICIO) {
                    res = true;
                    introTimer.restart();
                    _soundManager.playSound(RES);
                _estadoJuego = EN_CURSO;
                _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                _obstaculos.clear();
                _santos = 0;
                _velocidadBase = 1.0f;
                _tiempoEntreObstaculos = 1.0f;
                temporizadorMenu.restart();
                }
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
        SI (event.key.code == sf::Keyboard::Space) {
            _soundManager.playSound(SALTAR);
            SI (_postionPlayer.y - 20 >= 0) {
                _offsetPlayer.y = 0;
                _offsetPlayer.x = 32;
                _velocidadY = _salto;
                _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
            }
        }
    }
}

Display::estadoJuego Display::verificarColisionJugador()
{
    for (const auto& obs : _obstaculos) {
        sf::FloatRect hitboxJu =  {_jugador.getGlobalBounds().left + 25, _jugador.getGlobalBounds().top + 25, _jugador.getGlobalBounds().width - 50 , _jugador.getGlobalBounds().height - 50};
        sf::FloatRect hitbox = {obs.obtenerLimites().left + 10, obs.obtenerLimites().top + 10, obs.obtenerLimites().width - 15, obs.obtenerLimites().height - 15};
        SI (hitboxJu.intersects(hitbox)) {
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
    play.setOrigin(16, 16);
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