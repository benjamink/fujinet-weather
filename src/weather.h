#ifndef WEATHER_H
#define WEATHER_H

#include <stdint.h>

char *create_url(char *method);
void handle_err(char *reason);

void setup();
void start_get();
void get_current();

#ifdef BUILD_APPLE2
extern uint8_t sp_network;
#endif

#endif