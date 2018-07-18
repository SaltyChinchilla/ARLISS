//This should run from apogee until landing
//needs to be tracking gps points as fall

bool Falling_loop(bool on){
  float release_setpoint = 0;
  if(on){
    //Record current gps point to a falling gps log
    // clalculate current heading from last two gps points. 

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

