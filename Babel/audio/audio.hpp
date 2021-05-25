/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"
#include <string.h>
#include </usr/include/opus/opus.h>

#define FRAMES_PER_BUFFER 480
#define RATE 48000
#define CHANNELS 2

#define PACKET_MAX 3840
#define FRAME_MAX 5760

typedef std::vector<float*> RECORDED;

class Audio
{
    public:
        Audio(void);
        ~Audio();
        RECORDED _recData;
        unsigned char *_encoded;
        float* _decodedData;
        PaStream *_stream;
        PaError _err;
        int Initialize(std::string clientName);
        void Terminate(std::string clientName);
        int			startStream();
		int			stopStream(void);
		bool 		play(RECORDED);
		RECORDED	record(void);
        void		cleanRecord(void);
        unsigned char* encode();
        float* decode(unsigned char *encoded);
};


#endif /* !AUDIO_HPP_ */