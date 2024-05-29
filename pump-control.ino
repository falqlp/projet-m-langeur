void turnOnMotor(Adafruit_DCMotor *motor){
  motor->run(FORWARD);
  motor->setSpeed(150);
}

void turnOffMotor(Adafruit_DCMotor *motor){
  motor->run(RELEASE);
}

void launchProg(int program[3], Adafruit_DCMotor *redPump, Adafruit_DCMotor *greenPump, Adafruit_DCMotor *bluePump) {
    double R, G, B;
    R = EEPROM.read(program[0]);
    G = EEPROM.read(program[1]);
    B = EEPROM.read(program[2]);

    double total = R + G + B;

    if (total > 0) {
        Serial.println("Open Red");
        turnOnMotor(redPump);
        if (R > 0) {
            delay(R * 10000 / total);
        }
        turnOffMotor(redPump);
        Serial.println("Close Red");

        Serial.println("Open Green");
        turnOnMotor(greenPump);
        if (G > 0) {
            delay(G * 10000 / total);
        }
        turnOffMotor(greenPump);
        Serial.println("Close Green");

        Serial.println("Open Blue");
        turnOnMotor(bluePump);
        if (B > 0) {
            delay(B * 10000 / total);
        }
        turnOffMotor(bluePump);
        Serial.println("Close Blue");
    } else {
        Serial.println("Total des valeurs est zéro, aucun délai appliqué.");
    }
}