import processing.serial.*;
Serial port;
void setup(){
  println("Available serial ports:");
  println(Serial.list());
  port = new Serial(this, Serial.list()[0], 115200);  // Open the port that the Arduino board is connected to, at 9600 baud
}
void draw(){
  background(192, 64, 0);
       line(150, 25, mouseX, mouseY);
  while (port.available() > 0){
    String in = port.readString();
    if(in != null){
      JSONObject j = parseJSONObject(in);
      
    }
  }
  
    int num;
    num = 0 ; // change string into Int
    println((num)); // write as a byte over serial
  
  //port.write(0xff); //write our marker
  delay(10);
}