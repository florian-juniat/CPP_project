/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** audio
*/

#include "portaudio.h"

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

class MyPortaudioClass
{

    int myMemberCallback(const void *input, void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags);

    static int myPaCallback(
    const void *input, void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData )
    {
    return ((MyPortaudioClass*)userData)
        ->myMemberCallback(input, output, frameCount, timeInfo, statusFlags);
    }

};

#endif /* !AUDIO_HPP_ */
