#include "main.h"
using namespace std;

class S51Servo {
    private: uint slice;
    private: uint channel;
    public: int currentMillis;
    public: float minMillis;
    public: float maxMillis;
    public: float minAngle;
    public: float maxAngle;
    public: float angleMultiplier;
    public: S51Servo(int pwm_pin, float leastAngle = 0.f, float largestAngle = 180.f, float floorMillis = 250.f, float cielMillis = 1275.f) {

        minAngle = leastAngle;
        maxAngle = largestAngle;
        minMillis = floorMillis;
        maxMillis = cielMillis;
        currentMillis = floorMillis;

        gpio_set_function(pwm_pin, GPIO_FUNC_PWM);  /// Set the pin number sent to be PWM
        slice = pwm_gpio_to_slice_num(pwm_pin);
        channel = pwm_gpio_to_channel(pwm_pin);

        pwm_set_clkdiv(slice, 256.0f);  /// Setting the divider to slow down the clock
        pwm_set_wrap(slice, 9804);      /// setting the Wrap time to 9764 (20 ms)
        pwm_set_enabled(slice, true);

        pwm_set_chan_level(slice, channel, currentMillis); /// Setting the duty period (0.6 ms)
    }
    public: void setServoAngleByMill(int mill) {
        if(mill >= minMillis && mill <= maxMillis) pwm_set_chan_level(slice, channel, mill);
        currentMillis = mill;
    }
    public: void setupAngleServoUpdateByAngle() {
        try {

            if(maxAngle - minAngle == 0) throw '0 value denominator detected';

            angleMultiplier = (maxMillis - minMillis)/(maxAngle - minAngle);

        } catch (string message) {
            cout << "Could not set up angle multiplier to set Servo by Angle" << '\n';
            cout << message << '\n';
        }
    }
    public: void setServoAngleByAngle(float angle) {
        try {
            
        if(angle < minAngle || angle > maxAngle || !angleMultiplier) throw "Out of range angle requested";

        currentMillis = (angleMultiplier * angle) + minMillis;

        pwm_set_chan_level(slice, channel, currentMillis);

        } catch (string message) {
            cout << message << '\n';
        }
    }
};
