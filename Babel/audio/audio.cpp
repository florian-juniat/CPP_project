/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** audio
*/

#include "audio.hpp"

Audio::Audio(void)
{
  this->Initialize("Franky");
  std::cout << "Audio initialized" << std::endl;
}

Audio::~Audio(void)
{
  this->Terminate("coucou");
}

int Audio::Initialize(std::string clientName)
{
  if (Pa_Initialize())
    return (0);
  return (1);
}

void Audio::Terminate(std::string clientName)
{
  Pa_Terminate();
  std::cout << "Audio terminated" << std::endl;
}

int Audio::startStream()
{
  PaStreamParameters outputParams;
  PaStreamParameters inputParams;

  Pa_OpenDefaultStream(&this->_stream, 2, 2, paFloat32, 48000, 960, NULL, NULL);
  Pa_StartStream(this->_stream);
  return (0);
}

RECORDED Audio::record(void)
{
  RECORDED buffer(FRAMES_PER_BUFFER);
  if ((this->_err = Pa_IsStreamActive(this->_stream)) != 1)
	{
		std::cerr << "Error: Can't run the stream: Stream inactive." << std::endl;
		return {0};
	}
  Pa_ReadStream(this->_stream, buffer.data(), FRAMES_PER_BUFFER / 2);
  return buffer;
}

bool Audio::play(RECORDED audio)
{
  if (Pa_IsStreamActive(this->_stream) != 1)
    return false;
  Pa_WriteStream(this->_stream, audio.data(), 960 / 2);
}

void	Audio::cleanRecord(void)
{
	this->_recData = {0};
}

unsigned char* Audio::encode()
{
  int frame_sizeee;
  frame_sizeee = 40000;
  int err_op;
  opus_int32 rate;
  OpusEncoder *encoder;
  OpusDecoder *decoder;

  encoder = opus_encoder_create(24000, 2, OPUS_APPLICATION_VOIP,
  &err_op);
  decoder = opus_decoder_create(24000, 2, &err_op);
  opus_encoder_ctl(encoder, OPUS_GET_BANDWIDTH(&rate));
  unsigned char *compressed_buffer;
  int ret;
  
  compressed_buffer = new (unsigned char[rate]);
  ret = opus_encode_float(encoder, this->_recData[0], frame_sizeee, compressed_buffer, rate);

  std::string ss(reinterpret_cast<char *>(compressed_buffer));
  unsigned char *comp = (unsigned char*)malloc(40000); // error is here 
  strcpy((char *)comp, ss.c_str());
  return comp;
}

float* Audio::decode(unsigned char *encoded)
{
  PaStreamParameters inputParameters, outputParameters;
  int frame_sizeee = 40000;
  opus_int32 rate2;
  OpusDecoder *decoder;
  int err_op;
  PaError err = paNoError;
  float *framee;
  PaStream *stream;

  decoder = opus_decoder_create(24000, 2, &err_op);
  framee = new (float[frame_sizeee * 2]);
  opus_packet_get_nb_channels(encoded);
  int ret = opus_decode_float(decoder, encoded, rate2, framee, frame_sizeee, 0);
  return framee;
}