#include <QTRSensors.h>


#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             255  // emitter is controlled by digital pin 2
#define SPEED 255
// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {
  0, 1, 2, 3, 4, 5
},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int MOTOR2_PIN1 = 3;
int MOTOR2_PIN2 = 5;
int MOTOR1_PIN1 = 6;
int MOTOR1_PIN2 = 9;
int calSpeed = 165;
void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);

  delay(500);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}


void loop()
{
  int s0 = 0;
  int s1 = 0;
  int s2 = 0;
  int s3 = 0;
  int s4 = 0;
  int s5 = 0;

  s0 = analogRead(0);//Signal pin 1 on the board
  s1 = analogRead(1);//Signal pin 2 on the board
  s2 = analogRead(2);//Signal pin 3 on the board
  s3 = analogRead(3);//Signal pin 4 on the board
  s4 = analogRead(4);//Signal pin 5 on the board
  s5 = analogRead(5);//Signal pin 6 on the board

  Serial.print(" ");
  Serial.print(s0);
  Serial.print(" ");
  Serial.print(s1);
  Serial.print(" ");
  Serial.print(s2);
  Serial.print(" ");
  Serial.print(s3);
  Serial.print(" ");
  Serial.print(s4);
  Serial.print(" ");
  Serial.print(s5);
  Serial.print(" ");
  Serial.println();

  //analogWrite(MOTOR1_PIN1, 0);
  //analogWrite(MOTOR2_PIN2, 0);

  //delay(1);

  if ((s0 < 100) && (s1 < 100) && (s2 < 100) && (s3 < 100) && (s4 < 100) && (s5 < 100))
  { analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR2_PIN2, 0);


  }
  else if ((s2 > 100) && (s3 > 100))
  {
    analogWrite(MOTOR1_PIN1, 80);
    analogWrite(MOTOR2_PIN2, 80);
  }


  else if (s4 < 100)
  {
    if (s5 < 100) {
      analogWrite(MOTOR1_PIN1, 200);
      analogWrite(MOTOR2_PIN2, 20);
    }
    else
    {
      analogWrite(MOTOR1_PIN1, 255);
      analogWrite(MOTOR2_PIN2, 100);
    }
  }


  else if (s1 < 100)
  {

    if (s0 < 100) {
      analogWrite(MOTOR1_PIN1, 20);
      analogWrite(MOTOR2_PIN2, 255);
    }
    else {
      analogWrite(MOTOR1_PIN1, 100);
      analogWrite(MOTOR2_PIN2, 255);
    }
  }
}


