//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;

int ledPin = D1;                // choose the pin for the LED
int inputPin = D2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
float micro = 1000000;
float temps_DeepSleep = (0)*60 + 3; // minutes + secondes

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);

  Serial.print("calibrating sensor ");
  /*for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }*/
}

void loop()
{
  val = digitalRead(inputPin);  // read input value
  Serial.println(val);
  if (val == HIGH) 
  { // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(60000);
    //Deep sleep 
    ESP.deepSleep(temps_DeepSleep*micro);

    if (pirState == LOW) 
    {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    delay(300);
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
