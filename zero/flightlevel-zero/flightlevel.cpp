#include <stdio.h>
#include "../../b-plus/common-b-plus/delay.h"
#include "../../b-plus/common-b-plus/uart.h"
#include "led.h"
#include "mpu6050.h"

#define LED_GPIO 47  // Green ACT LED on Pi Zero.

int main(void) {
  uart_init();
  printf("Starting...\n");
  
  mpu6050_init();
          
  CLed led(LED_GPIO);

  while (1) {
    float gx, gy, gz, ax, ay, az;
    mpu6050_read(gx, gy, gz, ax, ay, az);
    printf("GX:%08f  GY:%08f  GZ:%08f  AX:%08f  AY:%08f  AZ%08f\n", gx, gy, gz, ax, ay, az);
    
    led.Set();
    delayms(100);

    led.Clear();
    delayms(100);
  }
}
