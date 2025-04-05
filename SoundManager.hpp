/*
** EPITECH PROJECT, 2025
** JAMMMMM
** File description:
** SoundManager
*/

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP
#include <SFML/Audio.hpp>
#include <map>
#include "soundType.hpp"

class SoundManager {
public:
    SoundManager();
    void playSound(soundType sound);
private:
    std::map<soundType, sf::Sound> _sons;
    std::map<soundType, sf::SoundBuffer> _buffers;
};

#endif //SOUNDMANAGER_HPP
