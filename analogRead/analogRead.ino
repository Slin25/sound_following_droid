#define mic1 A1
#define mic2 A2
#define power 8
#define left 11
#define right 10
// mic1 - left
// mic2 - right

int ambientLevel;

// setting initial ambient value 
int collectAmbient() {
  float initAmbient = 0;

  // collect 250 ambient values then take average
  for (int i = 0; i < 250; i++) {
    int test = analogRead(mic1);
    initAmbient += test;
  }
  return (int)((initAmbient * 1.0)/250.0);
}
void moveForward() {
  // both right and left wheel same speed, turn on motors
  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
  digitalWrite(power, HIGH);
  delay(1000);
  // turn off motors
  digitalWrite(power, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
}
void turnLeft() {
  // pin 11-connected to left wheel, right wheel is faster 
  digitalWrite(left, LOW);
  digitalWrite(right, HIGH);
  // turn motor on
  digitalWrite(power, HIGH);
  delay(1000);
  digitalWrite(power, LOW);
  moveForward();
}

void turnRight() {
  // pin 10-connected to right wheel, left wheel is faster 
  digitalWrite(right, LOW);
  digitalWrite(left, HIGH);
  // turn motor on
  digitalWrite(power, HIGH);
  delay(1000);
  digitalWrite(power, LOW);
  moveForward();
}

void isClap(double mic1, double mic2) {
  // above the threshold then it's considered a clap
  if (mic1 > 10 || mic2 > 10) {
    if (mic1 > mic2) {
      turnLeft();
    } else if (mic2 > mic1) {
      turnRight();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  
  // rate to read the data coming in
  Serial.begin(9600);
  // read the stable voltage level
  ambientLevel = collectAmbient();
  Serial.println(ambientLevel);
  Serial.println(ambientLevel);
  // initialize output pins to control motors
  pinMode(power, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  digitalWrite(power, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // turn everything off
  digitalWrite(power, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  
  // read in the values from microphone 
  double mic1Data = analogRead(mic1) - ambientLevel;
  double mic2Data = analogRead(mic2) - ambientLevel;
  
  // making all the voltages positive
  if (mic1Data < 0) {
    mic1Data = -1 * mic1Data;
  }
  if (mic2Data < 0) {
    mic2Data = -1 * mic2Data;
  }
  isClap(mic1Data, mic2Data);
  // show the graph of the mics
  //Serial.println(mic1Data-mic2Data);
}
