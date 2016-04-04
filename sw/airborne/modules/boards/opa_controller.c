/*
 * Copyright (C) Freek van Tienen <freek.v.tienen@gmail.com>
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/boards/opa_controller.c"
 * @author Freek van Tienen <freek.v.tienen@gmail.com>
 * Controller for OPA board functionalities
 */

#include "modules/boards/opa_controller.h"
#include "generated/airframe.h"
#include "mcu_periph/gpio.h"
#include "led.h"

#define OFF_TIMER 20*3 // FIXME: make nicer
#define MIN_ARMING_TRIG 20*3 //FIXME: make nicer

/* Whether the autopilot arming LED is on */
static bool_t arming_led = FALSE;
extern bool_t autopilot_motors_on;

void opa_controller_init(void) {
  /* Setup E-Stop, Arming and On/Off button as input */
  gpio_setup_input(BTN_ESTOP, BTN_ESTOP_PIN);
  gpio_setup_input(BTN_ARMING, BTN_ARMING_PIN);
  gpio_setup_input(BTN_ON, BTN_ON_PIN);

  /* Enable Autopilot power */
  gpio_setup_output(AP_PWR, AP_PWR_PIN);
  AP_PWR_ON(AP_PWR, AP_PWR_PIN);

  /* Enable Main power (25V) */
  gpio_setup_output(MAIN_PWR, MAIN_PWR_PIN);
  MAIN_PWR_ON(MAIN_PWR, MAIN_PWR_PIN);

  /* Enable Balancer power */
  gpio_setup_output(BAL_PWR, BAL_PWR_PIN);
  BAL_PWR_ON(BAL_PWR, BAL_PWR_PIN);

#if defined ARMING_LED
  /* Disable the arming LED */
  LED_OFF(ARMING_LED);
#endif
}

void opa_controller_periodic(void) {
  static uint16_t off_cnt = 0;
  static uint16_t arming_cnt = 0;

  /* Check E-Stop and power off Main power if pressed */
  if(!gpio_get(BTN_ESTOP, BTN_ESTOP_PIN)) {
    MAIN_PWR_OFF(MAIN_PWR, MAIN_PWR_PIN);
  }

  /* Check On/Off button and disable if pressed for 3 seconds */
  if(!gpio_get(BTN_ON, BTN_ON_PIN)) {
    if(++off_cnt >= OFF_TIMER) {
      MCU_PWR_OFF(MCU_PWR, MCU_PWR_PIN);
    }
  }
  else off_cnt = 0;

  /* Check Arming button and set LED */
  if(arming_cnt >= MIN_ARMING_TRIG && !gpio_get(BTN_ARMING, BTN_ARMING_PIN)) {
    autopilot_motors_on = !autopilot_motors_on;
    arming_cnt = 0;
  }
  else arming_cnt++;

#if defined ARMING_LED
  /* Update Arming LED */
  if(arming_led && !autopilot_motors_on) LED_OFF(ARMING_LED);
  if(!arming_led && autopilot_motors_on) LED_ON(ARMING_LED);
  arming_led = autopilot_motors_on;
#endif
}