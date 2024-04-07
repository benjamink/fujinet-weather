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

char *ipLocationUrl = "https://ipconfig.io/json";

char url_buffer[256];
char result[1024];
uint8_t err = 0;
char *url;
uint16_t conn_bw;
uint8_t connected;
uint8_t conn_err;
uint8_t trans_type = OPEN_TRANS_CRLF;

char *location;

void debug() {}

int main(void)
{
  setup();
  get_location();
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

void handle_err(char *reason)
{
  if (err)
  {
    printf("Error: %d (d: %d) %s\n", err, fn_device_error, reason);
    cgetc();
    exit(1);
  }
}

void open(char *u)
{
  url = u;
  err = network_open(url, OPEN_MODE_HTTP_GET, OPEN_TRANS_NONE);
  handle_err("open");
}

void close()
{
  err = network_close(url);
  handle_err("close");
}

void open_and_parse_json(char *u)
{
  url = u;
  open(url);

  err = network_json_parse(url);
  handle_err("parse");
}

char *json_query(char *path)
{
  int count = 0;
  count = network_json_query(url, path, result);
  if (count < 0)
  {
    err = -count;
    handle_err("query");
  }

  printf("Querying URL: %s for path %s\n", url, path);
  printf("Result of path %s is %s\n", path, result);

  return result;
}

void get_location()
{
  open_and_parse_json(ipLocationUrl);
  printf("Your zip code is: %s\n", json_query("zip"));
  close();
}