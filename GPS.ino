void GPSsetup(){
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's
  GPS.begin(9600);
  //Turn on the RMC(recomeneded Minimum) and GCA (fix data)
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  //Set the GPS refresh 1Hz should be fine
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  //check for antenna
  GPS.sendCommand(PGCMD_ANTENNA);
  //wait for everythin
  delay(1000);
  Serial1.println(PMTK_Q_RELEASE);
  
}

float GPSloop(){
  char c = GPS.read();
  if (GPSECHO)
    if (c) Serial.print(c);
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())){}; // this also sets the newNMEAreceived() flag to false
      // we can fail to parse a sentence in which case we should just wait for another
  }
    float loc = DMStoDD(GPS.latitude);
    Serial.println(DMStoDD(GPS.latitude));
    return loc;
      // 8==D~~~
}

float getGPSBearing(float lat1,float lon1,float lat2,float lon2){
  //Convert to radians
  lat1 = lat1 * pi / 180.0;
  lat2 = lat2 * pi / 180.0;
  lon1 = lon1 * pi / 180.0;
  lon2 = lon2 * pi / 180.0;
  
  float y = sin(lon1-lon2) * cos(lat2);
  float x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon1 - lon2);

  float bearing = atan2(y,x);
  //convert back to degrees
  bearing = bearing * 180.0 / pi;
  return bearing;  
}
// Returns the Distance between 2 gps points
float getGPSDistance(float lat1,float lon1,float lat2,float lon2){
  float earthRadiusMeters = 6378100;
  //Convert to radians
  lat1 = lat1 * pi / 180.0;
  lat2 = lat2 * pi / 180.0;
  lon1 = lon1 * pi / 180.0;
  lon2 = lon2 * pi / 180.0;

  float dlat = lat2 - lat1;
  float dlon = lon2 - lon1;

  float a = sin(dlat/2) * sin(dlat/2) +
            sin(dlon/2) * sin(dlon/2) * cos(lat1) * cos(lat2);
  float c = 2 * atan2(sqrt(a),sqrt(1-a));

  float distanceMeters = c * earthRadiusMeters;
  return distanceMeters;  
}

float DMStoDD(float dms){

  float d = int(dms / 100);
  float m = (dms - (d * 100));
  //float sLon = int((dmsLon - (10*dLon) - (mLon)) * 100);
  
  float DD = d + (m/60);
  //Serial.println(DDlat);
  return DD;
  
}
