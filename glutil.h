#define GLUTIL_H

#include <vector>
#include<windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include<mmsystem.h>
#include <string>
#include <string.h>
#include<windows.h>
#include <cmath>

#pragma comment(lib, "winmm.lib")

using namespace std;

void PlayMusicFromPosition(const std::string& path, int startPositionMillis){
    std::string command;
    // Open the audio file
    command = "open \"" + path + "\" type mpegvideo alias myAudio";
    mciSendStringA(command.c_str(), NULL, 0, NULL);
    // Set the playback position
    command = "seek myAudio to " + std::to_string(startPositionMillis);
    mciSendStringA(command.c_str(), NULL, 0, NULL);
    // Play the audio file from the specified position
    command = "play myAudio";
    mciSendStringA(command.c_str(), NULL, 0, NULL);
}

