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
#include <string.h>
#include <sys/_intsup.h>

#include "ui.h"
#include <pico/time.h>
#include <stdbool.h>
#include <stdio.h>

#define TELEGRAM_MAX_NUM_CHARS                                                 \
  (40 * 3) + 6 // 40 fields, three chars each (%XX), 6 for safety

enum user_action { UPDATE_TELEGRAM, VIEW_DATA, INVALID = -1 };

void print_main_menu(void) {
  printf("Choose what you would like to do:\n");
  printf(" 1: update the telegram format\n");
  printf(" 2: view live data\n");
}

int collect_user_action(void) {
  char selected = stdio_getchar();

  switch (selected) {
  case '1':
    return UPDATE_TELEGRAM;
  case '2':
    return VIEW_DATA;
  }

  return INVALID;
}

void update_telegram_format(void) {
  printf("You are now changing the telegram, this should not be done lightly. "
         "If you are unsure what you are doing, you shouldn't be here\n");
  printf("Please enter the string you want me to save, character at a time. "
         "When you are done, press the exclamation mark (!). To cancel at any "
         "stage, enter the at symbol (@)\n\n>");
  char telegram[TELEGRAM_MAX_NUM_CHARS];
  memset(telegram, 0, TELEGRAM_MAX_NUM_CHARS);

  int i = 0;
  while (true) {
    char c = stdio_getchar();
    printf("%c", c);
    if (c == '!') {
      break;
    } else if (c == '@') {
      printf("Cancelled!\n\n");
      return;
    }
    telegram[i++] = c;
  }
  telegram[i] = '\0';
  printf("\nYou are trying to set the telegram to:\n  %s\n", telegram);
  printf("Continue? [y/n]: ");
  char response = stdio_getchar();
  if (response == 'y') {
    // uart_puts(uart0, telegram);
    printf("Saved!\n\n");
  } else {
    printf("Aborted!\n\n");
  }
}

void show_data(void) { printf("Here is the data:\n(todo)\n\n"); }

void start_user_interface(void) {
  int count = 0;

  while (true) {
    print_main_menu();
    int action = collect_user_action(); // stalls here by design
    switch (action) {
    case UPDATE_TELEGRAM:
      update_telegram_format();
      break;
    case VIEW_DATA:
      show_data();
      break;
    case INVALID:
      break;
    }
  }
}
