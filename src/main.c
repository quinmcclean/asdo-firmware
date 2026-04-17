#include "ui.h"
#include <hardware/gpio.h>
#include <hardware/uart.h>
#include <pico/assert.h>
#include <pico/cyw43_arch.h>
#include <pico/error.h>
#include <pico/multicore.h>
#include <pico/stdio.h>
#include <pico/stdio_uart.h>
#include <pico/stdio_usb.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/_intsup.h>

#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART0_BAUD_RATE 19200

void gpio_pin_setup(void) {
  stdio_uart_init_full(uart0, UART0_BAUD_RATE, UART0_TX_PIN, UART0_RX_PIN);
}

void pico_init_led(void) {
#ifdef CYW43_WL_GPIO_LED_PIN
  cyw43_arch_init();
#endif
}

void pico_set_led(bool led_on) {
#if defined(CYW43_WL_GPIO_LED_PIN)
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main(int argc, char *argv[]) {
  stdio_usb_init();
  gpio_pin_setup();
  pico_init_led();
  multicore_launch_core1(start_user_interface);
  int count = 0;

  while (true) {
    printf("Hello, world! (%d)\n", count++);
    pico_set_led(true);
    sleep_ms(500);
    pico_set_led(false);
    sleep_ms(500);
  }
}
