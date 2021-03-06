// for Arduino/Genuino 101
#include <CurieTimerOne.h>

// for anode common 7 segment display
#define DIGIT_ON HIGH
#define DIGIT_OFF LOW
#define SEGMENT_ON HIGH
#define SEGMENT_OFF LOW

// 4 3 2 1
const int digitPins[] = {4, 3, 2, 8};
const int digitPinsLength = sizeof(digitPins) / sizeof(digitPins[0]);
// A B C D E F G DP
const int pinA = 6;
const int pinB = 5;
const int pinC = 12;
const int pinD = 10;
const int pinE = 9;
const int pinF = 7;
const int pinG = 13;
const int pinDP = 11;
const int segmentPins[] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};
const int segmentPinsLength = sizeof(segmentPins) / sizeof(segmentPins[0]);

const int digits[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00100111, // 7
    0b01111111, // 8
    0b01101111, // 9
};
const int dot = 0b10000000;

int numberTemp = 0;

void displayNumber(int n)
{
  for (int i = 0; i < segmentPinsLength; i++)
  {
    pinMode(segmentPins[i], digits[n] & (1 << i) ? SEGMENT_ON : SEGMENT_OFF);
  }
}

void updateDisplay()
{
  int n = numberTemp;
  for (int i = 0; i < digitPinsLength; i++)
  {
    digitalWrite(digitPins[i], DIGIT_ON);
    displayNumber(n % 10);
    delayMicroseconds(100);
    for (int j = 0; j < segmentPinsLength; j++)
    {
      digitalWrite(segmentPins[j], SEGMENT_OFF);
    }
    digitalWrite(digitPins[i], DIGIT_OFF);
    n /= 10;
  }
}

void setNumbers(int n)
{
  numberTemp = n;
}

void countUp()
{
  for (int i = 0; i < 10000; i++)
  {
    setNumbers(i);
    delay(50);
  }
}

void slot()
{
  setNumbers(random(10000));
  delay(50);
}

void setup()
{
  for (int i = 0; i < digitPinsLength; i++)
  {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], DIGIT_OFF);
  }
  for (int i = 0; i < segmentPinsLength; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], SEGMENT_OFF);
  }

  CurieTimerOne.start(1000, &updateDisplay);
}

void loop()
{
  countUp();
  // slot();
}
