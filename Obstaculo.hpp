/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Obstaculo
*/

#ifndef OBSTACULO_HPP
#define OBSTACULO_HPP

#pragma once
#include <SFML/Graphics.hpp>

class Obstaculo {
public:
    Obstaculo(const sf::Texture& textura, float x, float y);

    //void actualizar();
    void dibujar(sf::RenderWindow& ventana) const;
    bool estaFueraDePantalla() const;
    const sf::FloatRect obtenerLimites() const;
    sf::Vector2f obtenerPosicion() const;
    void establecerPosicion(const sf::Vector2f& posicion);

private:
    sf::Sprite _sprite;
    float _velocidad;
    std::pair<float, float> position;
};



#endif //OBSTACULO_HPP
