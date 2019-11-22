#define mic1 A1
#define mic2 A2

int ambientLevel;

// setting initial ambient value 
int collectAmbient() {
  int initAmbient = 0;
  // delay for 1 sec (1000 milli sec)
  delay(1000);

  // collect 1000 ambient values thent take average
  for (int i = 0; i < 1000; i++) {
    initAmbient += analogRead(mic1);
  }
  return (initAmbient/1000);
}

void turnLeft() {
  
}

void turnRight() {
  
}

int isClap(double mic1, double mic2) {

}

void setup() {
  // put your setup code here, to run once:
  
  // rate to read the data coming in
  Serial.begin(9600);

  ambientLevel = collectAmbient();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  double mic1Data = analogRead(mic1) - ambientLevel;
  double mic2Data = analogRead(mic2) - ambientLevel;

  if (mic1Data < 0) {
    mic1Data = -1 * mic1Data;
  }
  if (mic2Data < 0) {
    mic2Data = -1 * mic2Data;
  }
  // show the graph of the mics
  Serial.println(analogRead(mic1));
}
