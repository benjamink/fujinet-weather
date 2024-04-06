#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "fujinet-network.h"

#include "weather.h"

char *apiToken = "a2f6f4f587f6465a9af00744242403";
char *api = "n:https://api.weatherapi.com/v1/";

char url_buffer[256];
char result[1024];
uint8_t err = 0;
char *url;
uint16_t conn_bw;
uint8_t connected;
uint8_t conn_err;
uint8_t trans_type = OPEN_TRANS_CRLF;

char *location = "18976";

void debug() {}

int main(void)
{
  setup();
  start_get();

  printf("Press a key to exit.");
  cgetc();
  printf("\n");

  return 0;
}

void setup() {
  uint8_t init_r = 0;
  bzero(url_buffer, 128);
  bzero(result, 1024);
  gotox(8);
  init_r = network_init();
  printf("init: %d, derr: %d\n", init_r, fn_device_error);
#ifdef BUILD_APPLE2
  printf("nw: %d\n", sp_network);
#endif 
}

char *create_url(char *query) {
  sprintf(url_buffer, "%s?q=%s&key=%s%s", api, query, apiToken);
  return (char *)url_buffer;
}

void handle_err(char *reason)
{
  if (err)
  {
    printf("Error: %d (d: %d) %s\n", err, fn_device_error, reason);
    cgetc();
    exit(1);
  }
}

void start_get() {
  url = create_url(location);
  err = network_open(url, OPEN_MODE_HTTP_GET, trans_type);
  handle_err("open");

  err = network_json_parse(url);
  handle_err("parse");

  printf("URL: %s\n", url);
}
