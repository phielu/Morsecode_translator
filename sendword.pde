import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

String word = "";

void setup() {
  size(600,200);
  //fullScreen();
  myRemoteLocation = new NetAddress("127.0.0.1", 2345);
  oscP5 = new OscP5(this, 12000);
  
  textAlign(CENTER);
  textSize(64);
  fill(255);
}


void draw() {
  background(#3A919F);
  text(word, width/2, height/2);
}


void keyPressed() {
  if(key != CODED && key != RETURN && key != ENTER && key != BACKSPACE && key != TAB && key != DELETE) {
    word += key;
  }
  if((key == ENTER || key == RETURN) && word != "") {
    OscMessage myMessage = new OscMessage("/word");
    myMessage.add(word);
    oscP5.send(myMessage, myRemoteLocation);
    word = "";
  }
}
