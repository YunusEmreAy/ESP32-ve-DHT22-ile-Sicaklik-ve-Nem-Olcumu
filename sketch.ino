#include "thingProperties.h" // Bu kütüphane, Arduino Bulut hizmetine bağlanmak için gerekli olan özellikleri ve fonksiyonları içerir.
#include "DHT.h" // Bu kütüphane DHT sensörü kullanabilmemizi sağlar.
#include <LiquidCrystal_I2C.h> // I2C arayüzü üzerinden çalışan LCD ekran için kütüphane.


DHT dht(0, DHT22); // DHT sensörünü pin 0'a ve DHT22 tipine bağla.
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2); // 0x27 adresinde 16x2 LCD ekranını başlat.

void setup() {
  Serial.begin(9600); // Seri iletişimi başlat, hızı 9600 baud/s olarak ayarla.
  delay(1000); // 1 saniye bekle.

  pinMode(12, OUTPUT); // 12. pine bağlı bir çıkış olarak tanımla.

  LCD.init(); // LCD ekranını başlat.
  LCD.backlight(); // LCD ekranının arka ışığını aç.
  LCD.setCursor(0, 0); // Cursor'u LCD ekranın 0.satir - 0.stun 'una tasir.

  initProperties(); // Arduino Bulut özelliklerini başlat.
  ArduinoCloud.begin(ArduinoIoTPreferredConnection); // Arduino Bulut bağlantısını başlat, öncelikli bağlantı yöntemini kullan.
  setDebugMessageLevel(2); // Hata ayıklama mesaj seviyesini ayarla (2: Tüm mesajlar).
  ArduinoCloud.printDebugInfo(); // Debug bilgilerini Arduino Bulut üzerinde yazdır.

}

void loop() {
  ArduinoCloud.update(); // Arduino Cloud güncellemelerini kontrol et.
  dhtVeriOkuma(); // DHT sensöründen veri okuma işlemini gerçekleştir.
  LCD_Write(); // LCD ekranına, veri yazma islemlerini gercekelstir.
}

void dhtVeriOkuma(){ // Sicaklik ve nem degerlerini okur.
  sicaklik = dht.readTemperature(); // Sıcaklık değerini oku.
  nem = dht.readHumidity(); // Nem değerini oku.
  Serial.println("Humidity: "+String(nem)+"% || Temperature: "+String(sicaklik)+"°C"); // Sıcaklık ve Nem değerlerini terminale yazdırır.
}

void onMesajChange()  {  // Cloud ekranında "mesaj" girdisi oldugu zaman bu fonksiyon otomatik calisir (tetiklenir/cagrilir).
  LCD.clear(); // LCD ekrani temizle.
  mesaj.trim(); // Mesaj boşluklu geldiği icin, mesajin basinda gelen bosluklar temizlenir. 
  LCD.setCursor(0, 0); // Cursor'u LCD ekranın 0.satir - 0.stun 'una tasir.
  LCD.print(mesaj); // LCD ekrana "mesaj"i basar
  delay(2000); // 2 saniye bekleme saglar.
}


void LCD_Write(){ // LCD ekrana yazi yazilmak istendigi zaman (sicaklik/nem) bu fonksiyon "loop()" icerisinde cagrilir.

  LCD.clear(); // LCD ekrani temizle

  if(nem<=50) // nem degeri 50'ye esit ya da 50'nin altindaysa if sartine girilir.
  {
    LCD.setCursor(4, 0); // Cursor'u LCD ekranın 0.satir - 4.stun 'una tasir.
    LCD.print("HUMIDITY"); // LCD ekranina "HUMIDITY" yazilir.
    LCD.setCursor(3, 1); // Cursor'u LCD ekranın 1.satir - 3.stun 'una tasir.
    LCD.print(String(nem) + "-LOW"); // LCD ekranina {nem}+"-LOW" yazilir.
  }
  else // nem degeri ilgili sarti saglamadigi durumda else durumuna girilir.
  {
    LCD.setCursor(4, 0); // Cursor'u LCD ekranın 0.satir - 4.stun 'una tasir.
    LCD.print("HUMIDITY"); // LCD ekranina "HUMIDITY" yazilir.
    LCD.setCursor(3, 1); // Cursor'u LCD ekranın 1.satir - 3.stun 'una tasir.
    LCD.print(String(nem) + "-HIGH"); // LCD ekranina {nem}+"-HIGH" yazilir.
  }

  delay(2000); // 2 saniye bekleme saglar.
  LCD.clear(); // LCD ekrani temizle

  if(sicaklik<0) // sicaklik degeri 0'in altindaysa if sartine girilir.
  {
    LCD.setCursor(2, 0); // Cursor'u LCD ekranın 0.satir - 2.stun 'una tasir.
    LCD.print("TEMPERATURE"); // LCD ekranina "TEMPERATURE" yazilir.
    LCD.setCursor(0, 1); // Cursor'u LCD ekranın 1.satir - 0.stun 'una tasir.
    LCD.print(String(sicaklik) + "-VERY LOW"); // LCD ekranina {sicaklik}+"-VERY LOW" yazilir.
  }
  else if(sicaklik<=25) // sicaklik degeri 25'e esit ya da 25'in altindaysa else if sartine girilir.
  {
    LCD.setCursor(2, 0); // Cursor'u LCD ekranın 0.satir - 2.stun 'una tasir.
    LCD.print("TEMPERATURE"); // LCD ekranina "TEMPERATURE" yazilir.
    LCD.setCursor(3, 1); // Cursor'u LCD ekranın 1.satir - 3.stun 'una tasir.
    LCD.print(String(sicaklik) + "-NORMAL"); // LCD ekranina {sicaklik}+"-NORMAL" yazilir.
  }
  else // sicaklik degeri ilgili sarti saglamadigi durumda else durumuna girilir.
  {
    LCD.setCursor(2, 0); // Cursor'u LCD ekranın 0.satir - 2.stun 'una tasir.
    LCD.print("TEMPERATURE"); // LCD ekranina "TEMPERATURE" yazilir.
    LCD.setCursor(3, 1); // Cursor'u LCD ekranın 1.satir - 3.stun 'una tasir.
    LCD.print(String(sicaklik) + "-HIGH"); // LCD ekranina {sicaklik}+"-HIGH" yazilir.
    led = 1; // sicaklik degeri "HIGH" oldugu icin led = 1 olmalidir, led yanmalidir. "led = 1" durum gucellemesi yapilir.
    digitalWrite(12, HIGH); // led yanar.
  }

  delay(2000); // 2 saniye bekleme saglar.

}


void onLedChange()  { // Cloud ekranında led durumu degistirildiginde bu fonksiyon otomatik calisir (tetiklenir/cagrilir)
  if (led == 1) // led'in 1'e esit oldugu durumlarda if sartina girilir.
  {
    digitalWrite(12, HIGH); // led yanar.
  }
  else if (led == 0 && (sicaklik<=25))  // led'in 0'e esit oldugu ve sicaklik degeri 25'e esit ya da 25'in altinda oldugu durumlarda else if durumuna girilir.
  {
    digitalWrite(12, LOW); // led soner.
  }
  else // led'in 0'e esit oldugu ancak sicaklik degerinin 25'den buyuk oldugu durumlarda else durumuna girilir.
  {
    led = 1; // cloud'dan led = 0 yapilmistir ancak sicaklik degeri 25'in uzerinde oldugu icin led kapatilamamistir. cloud'da led kapali gözüküyor ancak led gercekte yaniyor. Bu durumun önüne gecebilmek icin led durumu cloud'da 'yaniyor' olarak guncellernir. 
  }

}