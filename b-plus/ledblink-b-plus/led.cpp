#include "../common-b-plus/gpio.h"
#include "led.h"

CLed::CLed(int gpioNumber) {
	m_gpioNumber = gpioNumber;
	gpio_set_output(m_gpioNumber);
}

CLed::~CLed() {
	m_gpioNumber = -1;
}

void CLed::Set(void) {
	gpio_set(m_gpioNumber);
}

void CLed::Clear(void) {
	gpio_clear(m_gpioNumber);
}
