bool standby_loop(bool on,int duration){
  if(on){
   int timer = millis();
   while(millis() - timer < duration){
      //run sleep code here.
      //Maybe send radio transmissions/ log data   
   }
   return false;
  }else{
    return false;
  }
}
