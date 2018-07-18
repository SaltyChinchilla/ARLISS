//int waypoints[15] = {180,180,180,270,0,0,0,270,180,180,180,270,0,0,0};
int waypoints[15] ={225,225,225,315,45,45,45,315,225,225,225,315,45,45,45};
int waypointsback[15] = {225,225,225,135,45,45,45,135,225,225,225,135,45,45,45};

int len = 15;

bool make_hmap(){
  int dist = 2000;
  
  for(int i = 0; i < len; i++){
    //Take data here
    write_to_SD(getHumidity(),humidlog);
    write_to_SD(GPSloop(1),latlog);
    write_to_SD(GPSloop(0),lonlog);
    Serial.println("Driving");
    drive_time(dist,waypoints[i]);
    Serial.print("logging");
    delay(2000);
    
  }
  //return false to turn off mapping switch
  return false;
}

int*  process_hmap(){
  float hmap[1000] = {};
  // get data from SD
  for(int i = 0;  i <= len; i++){
    hmap[i] = read_from_SD(i,humidlog);
  }

  //find min and max
  float minimum = 1000;
  float maximum = 0;
  for(int i = 0; i < sizeof(hmap)/sizeof(hmap[0]); i++){
    if(hmap[i] > 0){
      if(hmap[i] < minimum){
        minimum = hmap[i]; 
      }if(hmap[i] > maximum){
        maximum = hmap[i];
      }
    }
  }

  //Set seeding setpoints
  float humid_setpoint = (minimum + maximum)/ 2.0; //Takes upper 50%

  //Find all values above setpoint, add them to list
  int POI[1000] = {};
  int index = 0;
  for(int i = 0; i < sizeof(hmap)/sizeof(hmap[0]); i++){
    if(hmap[i] >= humid_setpoint){
      POI[index] = i;
      index = index + 1;
    } 
  }
  return POI;
}

bool seed(int* points){
  
  for(int i = 0; i < sizeof(points)/sizeof(points[0]); i++){
    float lat = read_from_SD(points[i],latlog);
    float lon = read_from_SD(points[i],lonlog);
    while(!drive_to_waypoint(lat,lon)){
   
      
    }
    
  }
  dispense_seed(2000);
  return false;
  
}

bool seed2(int* points){
  Serial.println("Seeding 2");
  //Serial.println(points[0]);
  int dist = 2000;
  for(int i = 0; i < len; i++){
    drive_time(dist,waypointsback[i]);
    Serial.println(i);
    delay(1000);
    for(int j = 0; j < 2; j++){
      Serial.println(j);
      Serial.println(points[j]);
      if(len - i == points[j]){
        Serial.println("yes");
        dispense_seed(5000);
      }
    
    }
  }
  return false;
  
}

void dispense_seed(float t){
  float current_time = millis();
  while(abs(millis()-current_time)<t){
    seedServo.write(0);
  }
  seedServo.writeMicroseconds(1450);
}




