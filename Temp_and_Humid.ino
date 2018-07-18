void THsetup(){
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
}

float getHumidity(){
  return htu.readHumidity(); 
}

float getTemp(){
  return htu.readTemperature();
}

