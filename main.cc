#include <stdlib.h>
#include <iostream>
#include "portaudio.h"

// using namespace std;

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

static void checkErr(PaError err) {
    if (err != paNoError) {
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        exit(-1);
    }
}

static int patestCallBack(
    const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData
) {
    std::cout << "HERE" << std::endl;
    return 0;
}

int main() {
    PaError err;
    err = Pa_Initialize();
    checkErr(err);

    int numDevices = Pa_GetDeviceCount();
    std::cout << "Number of devices: " << numDevices << std::endl;

    if (numDevices < 0) { std::cout << "Error getting device count\n"; exit(EXIT_FAILURE); }
    if (numDevices == 0) { std::cout << "No audio devices found\n"; exit(EXIT_SUCCESS); }

    const PaDeviceInfo* deviceInfo;
    for (int i = 0; i < numDevices; i++) {
        deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << "Device " << i << " name: " << deviceInfo->name << std::endl;
        std::cout << "  maxInputChannels: " << deviceInfo->maxInputChannels << std::endl;
        std::cout << "  maxOutputChannels: " << deviceInfo->maxOutputChannels << std::endl;
    }
    // note, the speakers should be device #4, the mic should be #9
    int headset_speakers = 9; // input 
    int headset_mic = 4; // output

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    // input
    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.channelCount = 1;
    inputParameters.device = headset_speakers;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(headset_speakers)->defaultLowInputLatency;

    // output
    memset(&outputParameters, 0, sizeof(outputParameters));
    outputParameters.channelCount = 2;
    outputParameters.device = headset_speakers;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(headset_mic)->defaultLowInputLatency;

    std::cout << "AFTER OUTPUT 1" << std::endl;

    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paNoFlag,
        patestCallBack,
        NULL
    );
    std::cout << "AFTER CALLBACK 2" << std::endl;
    checkErr(err);
    std::cout << "AFTER CALLBACK 3" << std::endl;

    err = Pa_StartStream(stream);
    checkErr(err);

    Pa_Sleep(10 * 1000); // 10 seconds of audio capture

    err = Pa_StopStream(stream);
    checkErr(err);

    err = Pa_CloseStream(stream);
    checkErr(err);


    err = Pa_Terminate();
    checkErr(err);
    return 0;
}