void calibrate_imu(){
  long current_time = millis();

  int t = 5000;
  
  while(abs(millis()-current_time)<t){
    motorR.drive(255);
    motorL.drive(-255);
  }

  while(abs(millis()-current_time)<t){
    motorR.drive(-255);
    motorL.drive(255);
  }
      
  
}

