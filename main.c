#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

/* 1000 msec = 1 sec */
#define LED0_DELAY 100
#define LED1_DELAY 200
#define LED2_DELAY 300
#define LED3_DELAY 500

#define MY_STACK_SIZE 500

typedef struct _lednode 
{
	const char *label;
	int pin;
	int flags;
}led_t;

/* Get LED binding info from device tree */
#define LED0_NODE DT_ALIAS(led0)
led_t led0 = {
	.label = DT_GPIO_LABEL(LED0_NODE, gpios),
	.pin = DT_GPIO_PIN(LED0_NODE, gpios),
	.flags = DT_GPIO_FLAGS(LED0_NODE, gpios)
};

#define LED1_NODE DT_ALIAS(led1)
led_t led1 = {
	.label = DT_GPIO_LABEL(LED1_NODE, gpios),
	.pin = DT_GPIO_PIN(LED1_NODE, gpios),
	.flags = DT_GPIO_FLAGS(LED1_NODE, gpios)
};

#define LED2_NODE DT_ALIAS(led2)
led_t led2 = {
	.label = DT_GPIO_LABEL(LED2_NODE, gpios),
	.pin = DT_GPIO_PIN(LED2_NODE, gpios),
	.flags = DT_GPIO_FLAGS(LED2_NODE, gpios)
};

#define LED3_NODE DT_ALIAS(led3)
led_t led3 = {
	.label = DT_GPIO_LABEL(LED3_NODE, gpios),
	.pin = DT_GPIO_PIN(LED3_NODE, gpios),
	.flags = DT_GPIO_FLAGS(LED3_NODE, gpios)
};

void blinky_task(led_t *led, int delay_ms)
{
	const struct device *led_dev = device_get_binding(led->label);

	gpio_pin_configure(led_dev, led->pin, GPIO_OUTPUT_ACTIVE | led->flags);

	while (true) {
		gpio_pin_toggle(led_dev, led->pin);
		k_msleep(delay_ms);
	}
}

K_THREAD_DEFINE(blinky_id0, MY_STACK_SIZE, blinky_task, &led0, LED0_DELAY, NULL, 1, 0, 0);
K_THREAD_DEFINE(blinky_id1, MY_STACK_SIZE, blinky_task, &led1, LED1_DELAY, NULL, 2, 0, 0);
K_THREAD_DEFINE(blinky_id2, MY_STACK_SIZE, blinky_task, &led2, LED2_DELAY, NULL, 3, 0, 0);
K_THREAD_DEFINE(blinky_id3, MY_STACK_SIZE, blinky_task, &led3, LED3_DELAY, NULL, 4, 0, 0);
