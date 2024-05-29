void turnOnMotor(Adafruit_DCMotor *motor){
  motor->run(FORWARD);
  motor->setSpeed(150);
  Serial.println("motor turned on");
}

void turnOffMotor(Adafruit_DCMotor *motor){
  motor->run(RELEASE);
  Serial.println("motor turned off");
}