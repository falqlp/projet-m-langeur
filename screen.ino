void display(LiquidCrystal_74HC595 lcd, boolean editMode){
  if(editMode){
    displayEditMode();
  } else{
    lcd.begin(20, 2);
    lcd.setCursor(0, 0);
    lcd.print("A,B,C,D,E:Launch");
    lcd.setCursor(0, 1);
    lcd.print("F: Edit");
  }
}

void displayEditMode(){
    lcd.begin(20, 2);
    lcd.setCursor(0, 0);
    lcd.print("A,B,C,D,E:Edit");
    lcd.setCursor(0, 1);
    lcd.print("F: Back");
}

void displayEditModeSelectedProgram(String value){
    lcd.begin(20, 2);
    lcd.setCursor(0, 0);
    lcd.print("Enter:RR,GG,BB");
    lcd.setCursor(0, 1);
    lcd.print(formatStringWithCommas(value));
}

String formatStringWithCommas(String str) {
  String formattedStr = "";
  int len = str.length();
  
  // Parcourir la chaîne de la fin vers le début
  for (int i = 0; i < len; i++) {
    formattedStr += str[i];
    // Ajouter une virgule tous les deux caractères sauf après le dernier caractère
    if ((i % 2 == 1) && (i != len - 1)) {
      formattedStr += ',';
    }
  }

  return formattedStr;
}