#include <stdio.h>
#include"../../b-plus/common-b-plus/uart.h"

int main(void) {
  uart_init();
  printf("Starting...\n\r");
  
  float x = 1.5;
  float y = x * 3.23;
  printf("X:%08f Y:%0.5f\n\r", x, y);
  
  while(1);
}
