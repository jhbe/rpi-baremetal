#include "../common-b-plus/delay.h"
#include "led.h"

#define LED_GPIO 35  // Red power LED. The green one is 47, but could not get that to work. Don't know why.

int main(void) {
	CLed led(LED_GPIO);

	while (1) {
		led.Set();
		delayms(200);

		led.Clear();
		delayms(200);
	}
}
