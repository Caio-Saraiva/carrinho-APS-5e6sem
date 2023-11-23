/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 12
#define S1 11
#define S2 8
#define S3 6
#define sensorOut 13

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(A5, OUTPUT);

  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // redColor = map(redFrequency, 70, 120, 255,0);
  redColor = map(redFrequency, 22, 190, 255, 0);

  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = map(greenFrequency, 48, 190, 255, 0);

  // Printing the GREEN (G) value
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = map(blueFrequency, 48, 190, 255, 0);

  // Printing the BLUE (B) value
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);
  Serial.println();

  // Checks the current detected color and prints
  // a message in the serial monitor
  if (redColor > 0 || greenColor > 0 || blueColor > 0) {

    if (redColor > greenColor && redColor > blueColor && blueColor > greenColor && redColor > 0 && greenColor > 0 && blueColor > 0 && redColor >= 200) {
      Serial.println(" - RED detected!");
      digitalWrite(A5, LOW);
    }
    if (redColor > 0 && greenColor > 0 && blueColor > 0 && redColor >= 180 && greenColor >= 225 && blueColor >= 230 && redColor < 220) {
      Serial.println(" - GREEN detected!");
      digitalWrite(A5, HIGH);
    }
    if (redColor > 0 && greenColor > 0 && blueColor > 0 && redColor >= 265 && greenColor >= 300 && blueColor >= 270) {
      Serial.println("Yellow!");
      digitalWrite(A5, HIGH);
      delay(300);
      digitalWrite(A5, LOW);
    }

  }


  delay(500);
}
