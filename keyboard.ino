char getNewInput(char c, char oldChar) {
  if(c != oldChar){
    oldChar = c;
    return c;
  }
  return "";
}