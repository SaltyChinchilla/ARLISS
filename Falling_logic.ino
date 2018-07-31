//This should run from apogee until landing
//needs to be tracking gps points as fall
float alt = 0;
float oldalt = 0;
bool pastApogee = false;
bool Falling_loop(bool on){
  float release_setpoint = 0;
  if(on){
    //Record current gps point to a falling gps log
    // clalculate current heading from last two gps points. 
    write_to_SD(GPSloop(1),latlog);
    write_to_SD(GPSloop(0),lonlog);
    write_to_SD(GPSloop(2),Altlog);
    alt = GPSloop(2);
    if(alt < oldalt){
      pastApogee = true;
    }else if(alt > oldalt){
      pastApogee = false;
    }
    oldalt = alt;
    
    //Check from landing jolt
    if(IMULoop(1) > release_setpoint){
      //relese shoot pin
      Release_pin();
      return false;
    }else{
      return true;      
    }
  }else{
    return false;
  }
  
}

bool Release_pin(){
  int timer = millis();
  while(millis() - timer < 2000){
      motorR.drive(255);
  }
  motorR.drive(0);
  return true;
}

