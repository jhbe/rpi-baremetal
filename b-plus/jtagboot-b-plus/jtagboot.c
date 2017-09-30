#include "../common-b-plus/gpio.h"

#define TCK_GPIO    13
#define TMS_GPIO    12
#define TDI_GPIO    26
#define TDO_GPIO     5
#define TRST_GPIO   22

int main(void) {
	volatile int i, dummy;

	//
	// Set the GPIO pins associated with JTAG to ALT4 or 5.
	//
	gpio_set_alt(TCK_GPIO, 5); // TCK
	gpio_set_alt(TMS_GPIO, 5); // TMS
	gpio_set_alt(TDI_GPIO, 4); // TDI
	gpio_set_alt(TDO_GPIO, 5); // TDO
	gpio_set_alt(TRST_GPIO, 4); // TRST

	//
	// Clear the pull up/downs from the four JTAG signals we use.
	//
	gpio_set_pullupdown(TCK_GPIO, GPIO_MODE_NONE);
	gpio_set_pullupdown(TMS_GPIO, GPIO_MODE_NONE);
	gpio_set_pullupdown(TDI_GPIO, GPIO_MODE_NONE);
	gpio_set_pullupdown(TDO_GPIO, GPIO_MODE_NONE);

	//
	// Provide a pull-up to keep TRST out of RESET.
	//
	gpio_set_pullupdown(TRST_GPIO, GPIO_MODE_UP);

	while(1);
}
