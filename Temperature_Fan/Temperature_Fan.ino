int ButtonPressed = 0;
// Minimum temp to activate the fan
int BaselineTemp = 72;
// The number of temp samples (1/sec) to average
int SampleRate = 20;
int currentSample = 0;
// Sensor readings
int SensorVal = 0;
float Voltage = 0;
// Temperature of all kinds!
float Temperature = 0;
float avgTemp = 0;
float Celsius = 0;
float Farenheit = 0;

void setup()
{
  // Set pins
  pinMode(A0, INPUT);
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  // Count samples
  currentSample++;
  // Measure the temp 5 times over 5 seconds
  SensorVal = analogRead(A0);
  // Convert pin input to Voltage
  Voltage = (SensorVal/1024.0) * 5.0;
  Serial.println(analogRead(A0));
  // Convert Voltage to ºC
  Celsius =  (Voltage - 0.5) * 100;
  // Convert ºC to ºF
  Farenheit = ((Celsius * 9) / 5 + 32);
  
  // Display
  Serial.print("Sample ");
  Serial.print(currentSample);
  Serial.print(" is ");
  Serial.print(Farenheit);
  Serial.println("ºF");
  
  // Add this sample to the average
  avgTemp += Farenheit;
  if (currentSample == SampleRate){
    // Average the temperatures
    avgTemp = avgTemp/SampleRate;
    Temperature = avgTemp;
    // Print Temp
    Serial.print("The temperature is currently: ");
    Serial.print(Temperature);
    Serial.println("ºF");
    // Reset to start again fresh
    avgTemp = 0;
    currentSample = 0;
  }
  
  // Check if button is pressed
  ButtonPressed = digitalRead(2);
  if (ButtonPressed == HIGH) {
    // Yes? Fan On.
    digitalWrite(9, HIGH);
  } else {
    // No? No fan... unless?
    digitalWrite(9, LOW);
    // If the button is off, check the temperature
    if (Temperature > BaselineTemp) {
      // If temp is > baseline, turn on fan and blue LED
      digitalWrite(9, HIGH);
      digitalWrite(5, HIGH);
    } else {
      // If temp is < baseline, turn off fan and LED
      digitalWrite(9, LOW);
      digitalWrite(5, LOW);
    }
  }
  delay(1000); // 1 Second delay for sampling
}
