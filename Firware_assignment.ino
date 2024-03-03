  #include <TimerOne.h>
  
  const int analogPin = A0;                           // Analog pin connected to the LM35
  const float ref_Voltage = 5.0;                      // Reference voltage of Arduino (5V)
  const float voltage_perCel = ref_Voltage / 1024.0;  // LM35 sensitivity = 10 mV per degree celsius
  
  void setup() {
    pinMode(analogPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
  // Initialize Timer1 with 1 millisecond interval
    Timer1.initialize(1000);                          // 1000 microseconds = 1 millisecond
  // Attach the ISR function to Timer1
    Timer1.attachInterrupt(blinkLED, 250000);         // Default: 250 milliseconds = 250000 microseconds
    Serial.begin(9600);
  }
  
  void loop() {
    int rawValue = analogRead(analogPin);             // Read raw analog value
    float voltage = rawValue * voltage_perCel;        // Convert raw value to voltage
    float temperature = voltage * 1000.0;             // LM35 outputs 10 mV per degree Celsius
    Serial.print("In Degree C =\t");
    Serial.print(temperature);
    Serial.print("\n");
    if(temperature < 30)
    {
      // Update the blinking interval to 250 milliseconds
      Timer1.setPeriod(250000);                       // 250 milliseconds = 250000 microseconds
    }
    else{
      // Update the blinking interval to 500 milliseconds
      Timer1.setPeriod(500000);                       // 500 milliseconds = 500000 microseconds
    }
  }

  void blinkLED() {
  static bool state = false;
  digitalWrite(LED_BUILTIN, state);
  state = !state;
  }
