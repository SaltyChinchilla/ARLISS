void splashStartup(int wait){
  tft.begin(HX8357D);
  tft.setRotation(1);
  tft.fillScreen(HX8357_BLACK);
  tft.setCursor(cx + 20,cy);
  tft.setTextSize(3);
  tft.println("Welcome");
  delay(1000);
  testFilledRoundRects();
  tft.setCursor(cx,cy);
  tft.println("APPLESEED");
  tft.setCursor(tft.width()-90,tft.height()-20);
  tft.setTextSize(1);
  tft.setTextColor(tft.color565(100,100,100));
  tft.println("AIAA 2018, OSU");
  delay(wait);
  tft.fillScreen(HX8357_BLACK);
}

void backSetup(){
  
  tft.fillRect(0,0,tft.width(),25,tft.color565(100,100,100));
  tft.setCursor(5,5);
  tft.setTextSize(2);
  tft.setTextColor(HX8357_WHITE);
  tft.print("APPLESEED NAV");
  tft.setCursor(tft.width() - 100,5);
  tft.print("Bat: ");

  //IMU GPS readout
  tft.setCursor(5,30);
  tft.print("Heading: ");
  tft.setCursor(5,50);
  tft.println("Location: ");
  tft.setCursor(5,70);
  tft.println("Calibration: ");
  tft.setCursor(tft.width() - 150,30);
  tft.println("GPS Fix: ");
  tft.setCursor(tft.width() - 150, 50);
  tft.println("RX: ");
  tft.setCursor(tft.width() - 150,70);
  tft.print("TX: ");

  //RX console
  tft.fillRect(tft.width()/2,tft.height()/2,240,160,tft.color565(100,100,100));
  tft.fillRect(tft.width()/2 + 5,tft.height()/2+10,230,145,HX8357_WHITE);
  
}
void dispData(float data,int x, int y,int sig){
    tft.setCursor(x,y);
    //tft.fillScreen(HX8357_BLACK);
    tft.fillRect(x,y,100,20,HX8357_BLACK);
    tft.println(data,sig);
}

void testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 ,
                cy = tft.height() / 2 ;

  tft.fillScreen(HX8357_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=8) {
    i2 = i / 2 - 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 100, 100));
  }
}
void testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 + 10,
                cy = tft.height() / 2 + 10;

  tft.fillScreen(HX8357_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()) - 20; i>25; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i-20, i-20, i/8, tft.color565(i/2, 0, 0));
  }
  int x = 260;
  int y = 20;
  tft.fillTriangle(0+x,0+y,50+x,-25+y,12+x,-15+y,tft.color565(0,150,0));
}

