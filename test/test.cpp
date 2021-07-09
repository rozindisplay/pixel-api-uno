#include "Arduino.h"
#include "unity.h"

void test_empty(void) {
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() {
    RUN_TEST(test_empty);
    delay(500);

	UNITY_END();
}
