/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Display
*/


#ifndef JAMMMMM_DISPLAY_HPP
#define JAMMMMM_DISPLAY_HPP
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


class Display {
    public:
        Display();
        sf::Sprite configuarAssetJugador();
        sf::Sprite configuarPapelPintadoDia();
        void moverPapelPintado(sf::Clock &tiempo, float &map);
        void animarPlayer(sf::Clock &tiempo, int &actual);
        void buclejuego();
    private:
        sf::RenderWindow _ventana;
        sf::Sprite _jugador;
        sf::Sprite _papelpintadodia;
        sf::Sprite _papelpintadodia2;
        sf::Sprite _papelpintadonoche;
        sf::Vector2f _postionPlayer;
        sf::Texture _texturePlayer;
        sf::Texture _textureBackground;
        sf::Vector2i _offsetPlayer;
        float _frameTime;
};


#endif //JAMMMMM_DISPLAY_HPP
