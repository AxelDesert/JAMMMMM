/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** SoundManager
*/

#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager()
{
    if (!_buffers[SALTAR].loadFromFile("assets/songs/phoenixSaut.ogg"))
        std::cerr << "Erreur chargement sound SALTAR\n";
    if (!_buffers[RES].loadFromFile("assets/songs/resurrection.ogg"))
        std::cerr << "Erreur chargement sound RES\n";
    if (!_buffers[BOTON].loadFromFile("assets/songs/clicBouton.ogg"))
        std::cerr << "Erreur chargement sound BOTON\n";
    if (!_buffers[MUERTE].loadFromFile("assets/songs/mort.ogg"))
        std::cerr << "Erreur chargement sound MUERTE\n";
    for (auto& pair : _buffers) {
        _sons[pair.first].setBuffer(pair.second);
    }
}

void SoundManager::playSound(soundType sound)
{
    auto it = _sons.find(sound);
    if (it != _sons.end()) {
        it->second.play();
    }
}
