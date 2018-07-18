void SDsetup(){
   
   if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    //return " ";
   }
}

String fileSetup(String filename){
  int x = 1;
  if(SD.exists(filename)){
    while (SD.exists(filename)) {
        x = x+1;
        String var = String(x);
        if(!SD.exists(filename + var)){
          filename = filename + var;
        }
    }
    return filename;
  }else{
    return filename;
  }
  
}

//void SDstorageloop(){
//  long t = millis();
//  float temp =  htu.readTemperature();
//  float humid = htu.readHumidity();
////  char c = GPS.read();
//  
////  float lat = GPS.latitude();
////  float longitude = GPS.longitude();
//  String datastring = String(t)+String(",")+ String(temp) + String(",") + String(humid);
//  File dataFile = SD.open(filename, FILE_WRITE);
//  if (dataFile) {
//    dataFile.println(datastring);
//    dataFile.close();
//    // print to the serial port too:
//    Serial.println(datastring);
//  }
//}
float decimalSpace = 100000.0;
void write_to_SD(float data,String filename){
  File dataFile = SD.open(filename, FILE_WRITE);
  String datastring = String(data  * decimalSpace);
  if (dataFile) {
    dataFile.println(datastring);
    dataFile.close();
  }
  Serial.println("wrote " + String(data) + " to " + filename);
}

float read_from_SD(int index, String filename){
  File dataFile = SD.open(filename);
  int count = 0;
  float data[1000] = {};

  if (dataFile){
    while (dataFile.available()){
      String line = dataFile.readStringUntil('\n');
      data[count] = line.toFloat();
      count++; 
    }
    dataFile.close();
  }
  if(index == -1){
    return data[count] / decimalSpace;
  }else{
    return data[index] / decimalSpace;
  }
}


