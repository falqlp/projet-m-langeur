char getNewInput(char c, char oldChar) {
  if(c != oldChar){
    oldChar = c;
    return c;
  }
  return "";
}


bool isDigit(char c) {
  return c >= '0' && c <= '9';
}