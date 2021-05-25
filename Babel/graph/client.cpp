
#include "mainwindow.h"
#include <QApplication>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <QDebug>

#include <string>
#include <thread>
#include <vector>
#include <boost/array.hpp>


using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using boost::asio::ip::udp;


using std::endl;




#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"
#define SAMPLE_RATE       (44100)
#define FRAMES_PER_BUFFER   (512)
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


int discuss()
{
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream = NULL;
    PaError err;
    const PaDeviceInfo *inputInfo;
    const PaDeviceInfo* outputInfo;
    char *sampleBlock = NULL;
    int i;
    int numBytes;
    int numChannels;

    err = Pa_Initialize();
    if (err != paNoError)
        goto error2;

    inputParameters.device = Pa_GetDefaultInputDevice();
    inputInfo = Pa_GetDeviceInfo(inputParameters.device);

    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputInfo = Pa_GetDeviceInfo(outputParameters.device);

    numChannels = inputInfo->maxInputChannels < outputInfo->maxOutputChannels
        ? inputInfo->maxInputChannels : outputInfo->maxOutputChannels;

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
    if (err != paNoError)
        goto error2;

    numBytes = FRAMES_PER_BUFFER * numChannels * SAMPLE_SIZE;
    sampleBlock = (char *) malloc(numBytes);
    if (sampleBlock == NULL)
        goto error1;
    memset(sampleBlock, SAMPLE_SILENCE, numBytes);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        goto error1;

    fflush(stdout);

    printf("test : %d\n", numBytes);
    numBytes = 1000;

    for (i = 0; i < (NUM_SECONDS*SAMPLE_RATE)/FRAMES_PER_BUFFER; ++i ) {
        err = Pa_ReadStream(stream, sampleBlock, FRAMES_PER_BUFFER);

        char *test = (char *)malloc(sizeof(char) * numBytes * 100);
        for (int j = 0; j < numBytes * 100; j++)
            test[j] = 'a';
        try {
            std::cout << "Try to send something" << std::endl;
            boost::asio::io_service io_send;
            udp::endpoint send_end(boost::asio::ip::address::from_string("127.0.0.1"),
                    7175);
            udp::socket sock(io_send);
            sock.open(udp::v4());
            sock.send_to(boost::asio::buffer(test, numBytes), send_end);
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        try {
            std::cout << "Try to recv something" << std::endl;
            boost::asio::io_service io_service;
            udp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 7175);
            udp::socket socket(io_service);
            socket.open(udp::v4());
            socket.bind(end);

            udp::endpoint sender;
            size_t len = socket.receive_from(boost::asio::buffer(sampleBlock, numBytes), sender);
        } catch (std::exception& e)
        {
        }
        std::cout << "End recv" << std::endl;
        err = Pa_WriteStream(stream, sampleBlock, FRAMES_PER_BUFFER);
    }
    fflush(stdout);
    err = Pa_StopStream(stream);
    if (err != paNoError)
        goto error1;
    free(sampleBlock);
    Pa_Terminate();
    return (0);

xrun:
    fflush(stdout);
    if (stream) {
        Pa_AbortStream(stream);
        Pa_CloseStream(stream);
    }
    free(sampleBlock);
    Pa_Terminate();
    return (84);
error1:
    free(sampleBlock);
error2:
    if (stream) {
        Pa_AbortStream(stream);
        Pa_CloseStream(stream);
    }
    Pa_Terminate();
    return (-1);
}

