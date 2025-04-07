/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** Obstaculo
*/

#include "Obstaculo.hpp"

#include "Obstaculo.hpp"

Obstaculo::Obstaculo(const sf::Texture& textura, float x, float y)
{
    _sprite.setTexture(textura);
    _sprite.setScale(1.f, 1.f);
    _sprite.setPosition(x, y);
}

//void Obstaculo::actualizar()
//{
//    _sprite.move(-_velocidad, 0.f);
//}

void Obstaculo::dibujar(sf::RenderWindow& ventana) const
{
    ventana.draw(_sprite);
}

bool Obstaculo::estaFueraDePantalla() const
{
    return obtenerPosicion().x + obtenerLimites().width < 0;
}

const sf::FloatRect Obstaculo::obtenerLimites() const
{
    return _sprite.getGlobalBounds();
}

sf::Vector2f Obstaculo::obtenerPosicion() const {
    return _sprite.getPosition();
}

void Obstaculo::establecerPosicion(const sf::Vector2f& posicion) {
    _sprite.setPosition(posicion);
}
