void THsetup() {
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  htu.begin();
}

float getHumidity() {
  float Humid = htu.readHumidity();
  return Humid;
}

float getTemp() {
  float Temp = htu.readTemperature();
  return Temp;
}

