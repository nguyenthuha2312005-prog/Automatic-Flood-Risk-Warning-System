#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;  
const int ledPin = 8;     
const int buzzerPin = 9;  

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();        
  lcd.backlight();   
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // --- PHẦN XỬ LÝ NHIỄU: LẤY TRUNG BÌNH 10 LẦN ---
  long sum = 0;               // Biến lưu tổng các lần đo
  int sampleCount = 10;       // Số lần lấy mẫu

  for (int i = 0; i < sampleCount; i++) {
    sum += analogRead(sensorPin); 
    delay(10);                // Nghỉ ngắn giữa các lần đo để ổn định điện áp
  }
  
  int averageValue = sum / sampleCount; // Giá trị trung bình cuối cùng
  // ----------------------------------------------

  // Hiển thị lên LCD
  lcd.setCursor(0, 0);
  lcd.print("Gia tri: ");
  lcd.print(averageValue);
  lcd.print("    "); // Xóa số thừa

  if (averageValue > 500) {
    lcd.setCursor(0, 1);
    lcd.print("CANH BAO! CAO   ");
    digitalWrite(ledPin, HIGH);
    
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
  } 
  else {
    lcd.setCursor(0, 1);
    lcd.print("Trang thai: OK  ");
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
  
  delay(200); 
}
