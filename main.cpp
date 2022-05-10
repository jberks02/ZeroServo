/*
 * Blink for Raspberry Pi Pico
 *
 * @version     1.0.0
 * @author     Justin Berkshire
 * @copyright   2022
 * @licence     MIT
 *
 */
#include "main.h"
#include "./servo51.cpp"
using namespace std;

int main()
{
    const uint LED = PICO_DEFAULT_LED_PIN;

    gpio_init(LED);

    gpio_set_dir(LED, GPIO_OUT);

    gpio_put(LED, 1);

    stdio_init_all();

    S51Servo zeroedServo(0);

   while(true) {

       zeroedServo.setServoAngleByAngle(0);

       sleep_ms(1000);

   }

    return 0;
}
