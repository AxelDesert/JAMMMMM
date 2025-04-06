/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** menu
*/

#include "Display.hpp"

void Display::mostrarMenuGameOver() {
    sf::Event evento;
    sf::Texture texturaMenu;
    sf::Texture texturatitulo;
    sf::Texture texturamenu;
    if (!texturaMenu.loadFromFile("assets/buttons.png"))
        std::cout << "no d'asset" << std::endl;
    if (!texturatitulo.loadFromFile("assets/title.png"))
        std::cout << "no d'asset" << std::endl;
    if (!texturamenu.loadFromFile("assets/menu.png"))
        std::cout << "no d'asset" << std::endl;
    sf::Sprite continuar(texturaMenu);
    sf::Sprite salir(texturaMenu);
    sf::Sprite empezar(texturaMenu);
    sf::Vector2u ventanaSize = _ventana.getSize();
    salir.setTextureRect(sf::IntRect(1210, 620, 600, 200));
    continuar.setTextureRect(sf::IntRect(0, 620, 600, 200));
    empezar.setTextureRect(sf::IntRect(0, 0, 600, 200));
    float escalaBoton = (ventanaSize.x / 5.0f) / 600.0f;
    salir.setScale(0.2, 0.2);
    continuar.setScale(escalaBoton, escalaBoton);
    empezar.setScale(escalaBoton, escalaBoton);
    float anchoBoton = 600 * escalaBoton;
    float altoBoton = 200 * escalaBoton;
    salir.setPosition(ventanaSize.x - 130 , 20);
    continuar.setPosition((ventanaSize.x - anchoBoton) / 2, (ventanaSize.y - altoBoton) / 2);
    empezar.setPosition((ventanaSize.x - anchoBoton) / 2, (ventanaSize.y - altoBoton) / 2);
    _ventana.draw(_papelpintadodia);
    _ventana.draw(_papelpintadodia2);
    _ventana.draw(_jugador);
    for (const auto& obs : _obstaculos)
        obs.dibujar(_ventana);
    sf::Sprite titulo(texturatitulo);
    sf::Sprite menu(texturamenu);
    titulo.setScale(0.4, 0.4);
    titulo.setPosition(150, 80);
    menu.setPosition(0, 0);
    //sf::RectangleShape overlay(sf::Vector2f(ventanaSize.x, ventanaSize.y));
    //overlay.setFillColor(sf::Color(255, 217, 128));
    _ventana.draw(menu);
    _ventana.draw(titulo);
    monstrarMejorSantos(10, 10, 40);
    if (_estadoJuego == GAME_OVER) {
        monstrarSantos(390, 280, 50);
        _ventana.draw(_textsantos);
        _ventana.draw(continuar);
        _ventana.draw(salir);
        _ventana.draw(_mejorscore);
    }
    else if (_estadoJuego == INICIO) {
        _ventana.draw(empezar);
        _ventana.draw(salir);
        _ventana.draw(_mejorscore);
    }
    while (_ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            _ventana.close();
        }
        if (evento.type == sf::Event::MouseButtonReleased) {
            if (evento.mouseButton.button == sf::Mouse::Left) {
                if (_estadoJuego == GAME_OVER) {
                    if (continuar.getGlobalBounds().contains(evento.mouseButton.x, evento.mouseButton.y)) {
                        _estadoJuego = EN_CURSO;
                        _santos = 0;
                        _velocidadBase = 1.0f;
                        _tiempoDeActualizacion = 0.002f;
                        _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                        _obstaculos.clear();
                        _soundManager.playSound(BOTON);
                        return;
                    }
                    if (salir.getGlobalBounds().contains(evento.mouseButton.x, evento.mouseButton.y)) {
                        _soundManager.playSound(BOTON);
                        sf::sleep(sf::seconds(1));
                        _ventana.close();
                    }
                }
                else if (_estadoJuego == INICIO) {
                    if (empezar.getGlobalBounds().contains(evento.mouseButton.x, evento.mouseButton.y)) {
                        _estadoJuego = EN_CURSO;
                        _jugador.setPosition(_postionPlayer.x, _postionPlayer.y);
                        _obstaculos.clear();
                        _soundManager.playSound(BOTON);
                        return;
                    }
                    if (salir.getGlobalBounds().contains(evento.mouseButton.x, evento.mouseButton.y)) {
                        _soundManager.playSound(BOTON);
                        sf::sleep(sf::seconds(1));
                        _ventana.close();
                    }
                }
            }
        }
        if (evento.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, evento.size.width, evento.size.height);
            _ventana.setView(sf::View(visibleArea));
        }
    }
    _ventana.display();
}