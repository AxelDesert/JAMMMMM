/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Display
*/

#ifndef JAMMMMM_DISPLAY_HPP
#define JAMMMMM_DISPLAY_HPP
#include "SFML/Window.hpp"
#include "soundType.hpp"
#include "Obstaculo.hpp"
#include "SoundManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class Display {
public:
    enum estadoJuego {
        INICIO,
        EN_CURSO,
        GAME_OVER
    };

    Display();
    sf::Sprite configuarAssetJugador();
    sf::Sprite configuarPapelPintadoDia();
    void moverPapelPintado(sf::Clock &tiempo, float &map);
    void animarPlayer(sf::Clock &tiempo, int &actual, bool &res);
    void buclejuego();
    void secuso(sf::Event event);
    void actualizarObstaculos();
    void actualizarVelocidad();
    estadoJuego verificarColisionJugador();
    void mostrarMenuGameOver();
    void monstrarSantos(int posX, int posY, int size);
    void monstrarMejorSantos(int posX, int posY, int size);
    void configuarPapelPintadoNoche();

private:
    float _tiempoDeActualizacion;
    float _santos; // score actuel
    float _highScore; // meilleur score obtenu
    float _velocidadBase; // vitesse de base du jeu
    float _tiempoEntreObstaculos;
    float _velocidadY = 0.0f;
    float _gravedad = 900.0f;
    float _salto = -350.0f;
    sf::RenderWindow _ventana;
    sf::Sprite _jugador;
    sf::Sprite _papelpintadodia;
    sf::Sprite _papelpintadodia2;
    sf::Sprite _papelpintadonoche;
    sf::Vector2f _postionPlayer;
    sf::Texture _texturePlayer;
    sf::Texture _textureBackground;
    sf::Texture _textureBackgroundN;
    sf::Vector2i _offsetPlayer;
    float _frameTime;
    std::vector<Obstaculo> _obstaculos;
    sf::Texture _textureObstaculo;
    float _tiempoUltimoObstaculo = 0;
    estadoJuego _estadoJuego = INICIO;
    SoundManager _soundManager;
    sf::View _vueOriginale;
    sf::Text _textsantos;
    sf::Text _mejorscore;
    sf::Font _font;
};


#endif //JAMMMMM_DISPLAY_HPP