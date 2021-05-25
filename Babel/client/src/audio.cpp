/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** cds
*/


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <thread>

using boost::asio::ip::udp;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"
#define SAMPLE_RATE       (48000)
#define FRAMES_PER_BUFFER   (516)
#define NUM_SECONDS          (10)
#define DITHER_FLAG           (0)

#if 1
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE (4)
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 0
#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SIZE (2)
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt24
#define SAMPLE_SIZE (3)
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif


void send_audio(PaError err, bool *stop, PaStream *stream, int numBytes,
std::string ip, int port_send, int port_recv)
{
    boost::asio::io_service io_send;
    udp::endpoint send_end(boost::asio::ip::address::from_string(ip),
    port_send);
    udp::endpoint send_end_me(boost::asio::ip::address::from_string("127.0.0.1"),
    port_recv);
    udp::socket sock(io_send);
    sock.open(udp::v4());
    char *sampleBlock = (char *) malloc(numBytes);


    memset(sampleBlock, SAMPLE_SILENCE, numBytes);
    numBytes = 2000;
    while (!(*stop)) {
        err = Pa_ReadStream(stream, sampleBlock, FRAMES_PER_BUFFER);
        try {
            sock.send_to(boost::asio::buffer(sampleBlock, numBytes), send_end);
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    sock.send_to(boost::asio::buffer("stop", 4), send_end);
    sock.send_to(boost::asio::buffer("stop", 4), send_end_me);
}

void recv_audio(PaError err, bool *stop, PaStream *stream2, int numBytes,
std::string ip, int port_recv)
{
    boost::asio::io_service io_service;
    udp::endpoint end(boost::asio::ip::address::from_string("0.0.0.0"), port_recv);
    udp::socket socket(io_service);
    socket.open(udp::v4());
    socket.bind(end);
    char *sampleBlock = (char *) malloc(numBytes);


    memset(sampleBlock, SAMPLE_SILENCE, numBytes);
    numBytes = 2000;
    while (!(*stop)) {
        try {
            size_t len = socket.receive_from(boost::asio::buffer(sampleBlock, numBytes), end);
        } catch (std::exception& e)
        {
        }
        if (sampleBlock[0] == 's' && sampleBlock[1] == 't')
            *stop = true;
        err = Pa_WriteStream(stream2, sampleBlock, FRAMES_PER_BUFFER);
    }
}


int call(std::string name, std::string ip, int port_send, int port_recv, bool *stop)
{
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream = NULL;
    PaStream *stream2 = NULL;
    PaError err;
    const PaDeviceInfo *inputInfo;
    const PaDeviceInfo* outputInfo;
    char *sampleBlock = NULL;
    int i;
    int numBytes;
    int numChannels;

    err = Pa_Initialize();


    inputParameters.device = Pa_GetDefaultInputDevice();
    inputInfo = Pa_GetDeviceInfo(inputParameters.device);

    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputInfo = Pa_GetDeviceInfo(outputParameters.device);

    numChannels = 1;//inputInfo->maxInputChannels < outputInfo->maxOutputChannels
        //? inputInfo->maxInputChannels : outputInfo->maxOutputChannels;

    inputParameters.channelCount = numChannels;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = inputInfo->defaultHighInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.channelCount = numChannels;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = outputInfo->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, SAMPLE_RATE,
            FRAMES_PER_BUFFER, paClipOff, NULL, NULL);

    err = Pa_OpenStream(&stream2, &inputParameters, &outputParameters, SAMPLE_RATE,
            FRAMES_PER_BUFFER, paClipOff, NULL, NULL);

    numBytes = FRAMES_PER_BUFFER * numChannels * SAMPLE_SIZE;
    sampleBlock = (char *) malloc(numBytes);


    memset(sampleBlock, SAMPLE_SILENCE, numBytes);
    err = Pa_StartStream(stream);
    err = Pa_StartStream(stream2);

    fflush(stdout);


    std::thread recvv(recv_audio, err, stop, stream2, numBytes, "0.0.0.0", port_recv);
    std::thread sendd(send_audio, err, stop, stream, numBytes, ip, port_send, port_recv);

    recvv.join();
    sendd.join();

    std::cout << "End Peer to Peer" << std::endl;
    *stop = false;

    fflush(stdout);
    err = Pa_StopStream(stream);
    err = Pa_StopStream(stream2);

    free(sampleBlock);
    Pa_Terminate();
    return (0);
}
