#include <Arduino.h>

// Use RTC_DATA_ATTR to store data in RTC memory

RTC_DATA_ATTR int bootCount = 0; // Store boot count in RTC memory to keep it after deep sleep


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Hello World");

    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch(wakeup_reason){
        case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
        case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
        case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
        case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
        default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
    }
    bootCount++;


    /*
        Deep sleep
        All exemple from
    */
    Serial.println("Going to sleep now");
    Serial.flush(); // Wait for the serial buffer to empty
    esp_sleep_enable_timer_wakeup(1000000);
    esp_deep_sleep_start();

    // Touch wakeup
    // esp_sleep_enable_touchpad_wakeup();
    // esp_deep_sleep_start();

    // Timer wakeup
    // esp_sleep_enable_timer_wakeup(1000000);
    // esp_deep_sleep_start();

    // External wakeup
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0);
    // esp_deep_sleep_start();

    // Multiple wakeup
    // esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);
    // esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
    // esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ALL_LOW);
    // esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
    // esp_deep_sleep_start();

    // ULP coprocessor wakeup
    // esp_sleep_enable_ulp_wakeup();
    // esp_deep_sleep_start();
    


}

void loop() {}