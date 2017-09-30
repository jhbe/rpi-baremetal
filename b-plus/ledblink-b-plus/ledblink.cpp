#include "../common-b-plus/delay.h"
#include "led.h"

#define LED_GPIO 47

int main(void) {
	CLed led(LED_GPIO);

	while (1) {
		led.Set();
		delayms(200);

		led.Clear();
		delayms(200);
	}
}
