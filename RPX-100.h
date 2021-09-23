/******************************************************************************
 * C++ source of RPX-100S
 *
 * File:   RPX-100.h
 * Author: Bernhard Isemann
 *
 * Created on 19 Sep 2021, 12:37
 * Updated on 19 Sep 2021, 17:00
 * Version 1.00
 *****************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sstream>
#include <syslog.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <math.h>
#include <complex.h>
#include <time.h>
#include <chrono>
#include <cstring>
#include <bitset>
#include "ini.h"
#include "log.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include "lime/LimeSuite.h"
#include <chrono>
#include <math.h>
#include "alsa/asoundlib.h"
#include "liquid/liquid.h"

// LimeSDR
#define INPUT_BUFFER_SIZE 8192
#define NUM_SAMPLES INPUT_BUFFER_SIZE/4
float sampleRate = 1e6f;
float resampleRate = 48e3f;
float bandwidth = 100e3f;
int modulation = 0;
float centerFrequency = 99.9e6;
float normalizedGain = 0;

// FM Demodulator
float fmDeviation = 75e3f;

// LP Filter Definition
#define CUTOFF_HZ 100000.0f

// Radio Frontend - Define GPIO settings for CM4 hat module
uint8_t setRX = 0x04;     //all other bit = 0 --> 6m
uint8_t setTXwoBP = 0x0B; //all other bit = 0 --> direct path without BP
uint8_t setTX6m = 0x08;   //all other bit = 0 --> 6m with BP
uint8_t setTX2m = 0x09;   //all other bit = 0 --> 2m with BP
uint8_t setTX70cm = 0x0A; //all other bit = 0 --> 70cm with BP