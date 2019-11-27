#define mic1 A1
#define mic2 A2
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
  
}
void turnLeft() {
  // pin 5-connected to left wheel, right wheel is faster 
  digitalWrite(5, LOW);
  moveForward();
}

void turnRight() {
  // pin 6-connected to right wheel, left wheel is faster 
  digitalWrite(6, LOW);
  moveForward();
}

void isClap(double mic1, double mic2) {
  // above the threshold then it's considered a clap
  if (mic1 > (ambientLevel * 3) || mic2 > (ambientLevel*3)) {
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
  double mic1Data = analogRead(mic1) - ambientLevel;
  double mic2Data = analogRead(mic2) - ambientLevel;
  
  // making all the voltages positive
  if (mic1Data < 0) {
    mic1Data = -1 * mic1Data;
  }
  if (mic2Data < 0) {
    mic2Data = -1 * mic2Data;
  }
  // show the graph of the mics
  Serial.println(analogRead(mic1));
}
