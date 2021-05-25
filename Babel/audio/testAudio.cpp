/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** testAudio
*/

#include "audio.hpp"

int main()
{
    Audio test = Audio();
    test.Initialize("Franky");
    test.startStream();
    for (auto start = std::chrono::steady_clock::now(), now = start; now < start + std::chrono::seconds{60}; now = std::chrono::steady_clock::now()) {
        test._recData = test.record(); 
        test._encoded = test.encode();
        test._recData[0] = test.decode(test._encoded);
        test.play(test._recData);
        test.cleanRecord();
    }
    return (0);
}