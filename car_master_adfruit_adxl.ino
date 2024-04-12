#include<SoftwareSerial.h>
SoftwareSerial ss(2, 3);
const int xpin = A0; // x-axis of the accelerometer
const int ypin = A1; // y-axis
const int zpin = A2; // z-axis
//Transmitter program

// Define sensitivity thresholds (adjust these based on calibration)
const int xThreshold = 5; // Minimum change for X to be considered movement
const int yThreshold = 5; // Minimum change for Y to be considered movement
const int zThreshold = 7; // Minimum change for Z to be considered movement


void setup()
{
  Serial.begin(38400);
  ss.begin(38400);


}
char dir;
void loop()
{
    int x = analogRead(xpin); //read from xpin
    delay(1); //
    int y = analogRead(ypin); //read from ypin
    delay(1);
    int z = analogRead(zpin); //read from zpin
  
    float zero_G = 512.0; //ADC is 0~1023 the zero g output equal to Vs/2
    float scale = 102.3; //ADXL335330 Sensitivity is 330mv/g
    //330 * 1024/3.3/1000
    float x_g = ((float)x - 331.5) / 65 * 9.8;
    float y_g = ((float)y - 329.5) / 68.5 * 9.8;
    float z_g = ((float)z - 340) / 68 * 9.8;
    Serial.print(x_g); //print x value on serial monitor
    Serial.print("\t");
    Serial.print(y_g); //print y value on serial monitor
    Serial.print("\t");
    Serial.print(z_g); //print z value on serial monitor
    Serial.print("\n");
      dir = 'S';
  
    // Check for movement in each dir based on thresholds
    if (abs(x_g) > xThreshold) {
      dir = (x_g > 0) ? 'R': 'L'; // Determine right or left based on sign of X
    } else if (abs(y_g) > yThreshold) {
      dir = (y_g > 0) ? 'F' : 'B'; // Determine forward or backward based on sign of Y
    } else if (abs(z_g) > zThreshold) {
      // Handle tilting (optional)
      // ... (Add tilting detection logic if needed)
    }
  
    // Print the detected dir
    Serial.print("direction: ");
    Serial.println(dir);
    ss.print(dir);
delay(300);
}
