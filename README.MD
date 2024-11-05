# IoT Projesi - ESP32 ve DHT22 ile Sıcaklık ve Nem Ölçümü

Bu proje, ESP32 mikrodenetleyici, DHT22 sıcaklık ve nem sensörü, I2C özellikli 16x2 LCD ekran ve bir LED kullanılarak gerçekleştirilmiş bir Nesnelerin İnterneti (IoT) uygulamasıdır. Proje, çevresel koşulları ölçüp görüntülemek, ölçüm sonuçlarını Arduino Cloud'a göndermek ve LED'i yüksek sıcaklık durumlarında bir uyarı olarak kullanmak için tasarlanmıştır.

## Kullanılan Bileşenler
- **ESP32**: Dahili Wi-Fi ve Bluetooth özelliklerine sahip, çift çekirdekli bir mikrodenetleyici. IoT uygulamaları için idealdir.
- **DHT22 Sensörü**: Yüksek hassasiyetle sıcaklık ve nem ölçümü yapabilen bir sensör. 
- **I2C 16x2 LCD Ekran**: Sıcaklık, nem bilgileri ve cloud'dan gelen mesajları göstermek için kullanılır.
- **LED ve Direnç**: Yüksek sıcaklık durumlarında kullanıcıyı uyarmak için kullanılan bir LED. Direnç, LED'in aşırı akıma karşı korunmasını sağlar.
- **Arduino Cloud**: Sensör verilerinin izlenmesi ve LED'in uzaktan kontrol edilmesi için kullanılan bir bulut platformu.

## Proje Fonksiyonları
1. **Sıcaklık ve Nem Ölçümü**: DHT22 sensörü, çevresel sıcaklık ve nem değerlerini ölçer ve bu verileri ESP32'ye gönderir.
2. **Veri Görselleştirme**: I2C özellikli 16x2 LCD ekran, sıcaklık ve nem değerlerini, ayrıca cloud'dan gelen mesajları 2 saniyelik aralıklarla görüntüler.
3. **LED Uyarı Sistemi**: Belirlenen sıcaklık eşik değerini aştığında LED yanar. LED ayrıca Arduino Cloud üzerinden de kontrol edilebilir.
4. **Cloud Entegrasyonu**: Sıcaklık ve nem verileri, Arduino Cloud'a aktarılır ve LED'in uzaktan kontrolü sağlanır.

## Devre Bağlantıları
- **DHT22 Sensörü**:
  - VCC: 3.3V'a bağlanır
  - DATA: ESP32'nin bir dijital GPIO pinine bağlanır (10k pull-up direnç kullanılarak)
  - GND: GND'ye bağlanır
- **I2C 16x2 LCD**:
  - SCL: ESP32'nin GPIO 22 pinine bağlanır
  - SDA: ESP32'nin GPIO 21 pinine bağlanır
  - VCC: 3.3V'a bağlanır
  - GND: GND'ye bağlanır
- **LED ve Direnç**:
  - LED'in Anodu: ESP32'nin bir GPIO pinine, 1kΩ direnç üzerinden bağlanır
  - LED'in Katodu: GND'ye bağlanır

## Kurulum Talimatları
1. Bu depoyu klonlayın ve Arduino IDE'yi açın.
2. Gerekli kütüphanelerin kurulu olduğundan emin olun:
   - `LiquidCrystal I2C`
   - `ArduinoIoTCloud`
   - `DHT sensor library`
3. **Arduino Cloud Ayarları**:
   - Arduino Cloud üzerinde yeni bir hesap oluşturun.
   - Yeni bir "thing" tanımlayın ve aşağıdaki değişkenleri oluşturun:
     - `sicaklik`: Sıcaklık sensörü (°C), Sadece Okuma (Read Only)
     - `nem`: Bağıl nem, Sadece Okuma (Read Only)
     - `mesaj`: Karakter dizisi, Okuma & Yazma (Read & Write)
     - `led`: Boolean, Okuma & Yazma (Read & Write)
   - ESP32 cihazınızı tanımlayın ve ağ ayarlarını yapılandırın.
4. **thingProperties.h Dosyasını Düzenleyin**:
   - `DEVICE_LOGIN_NAME` ve `DEVICE_KEY` değerlerini Arduino Cloud'dan aldığınız bilgilerle değiştirin.
5. **Wi-Fi Ayarları**:
   - Wi-Fi ağı adı: `Wokwi-GUEST`
   - Şifre: Boş bırakın
6. Kodu ESP32'ye yükleyin ve simülasyonu başlatın. Wokwi simülasyonu için [buraya tıklayın](https://wokwi.com/projects/395867568432937985).

## Simülasyon
Projenizi Wokwi platformu üzerinde simüle edebilirsiniz: [Wokwi Simülasyonu](https://wokwi.com/projects/395867568432937985)

## Detaylı Açıklamalar
- **ESP32**: ESP32'nin yüksek performansı, Wi-Fi ve Bluetooth desteği, düşük güç tüketimi ve esnek pin konfigürasyonu bu projede kullanılmasını sağlamıştır.
- **DHT22 Sensörü**: Geniş sıcaklık ve nem ölçüm aralığı, düşük güç tüketimi ve yüksek hassasiyeti nedeniyle tercih edilmiştir.
- **I2C LCD Ekran**: Daha az pin kullanımı sayesinde devreyi basitleştirir ve verimli veri görüntüleme sağlar.
- **LED Uyarı Sistemi**: Sıcaklık belirli bir eşiği aştığında kullanıcıyı uyarır ve cloud üzerinden kontrol edilebilir.
- **Round Robin Zamanlayıcı**: Sistemde kesme (interrupt) olmadığı varsayıldığı için ölçüm verileri LCD ekranda 2 saniyelik aralıklarla round robin tekniği kullanılarak gösterilir.

## Örnek Senaryolar
1. **Senaryo 1**: Nem düşük ve sıcaklık çok düşük olduğunda LCD ekranda şu şekilde görüntülenir: 
HUMIDITY 49.00 - LOW 
TEMPERATURE -40.00 - VERY LOW
2. **Senaryo 2**: Cloud'dan gelen bir mesaj varsa, mesaj da sıcaklık ve nem bilgilerinin ardından görüntülenir.
3. **Senaryo 3**: Yüksek sıcaklık durumunda LED yanar ve cloud üzerinden kontrol edilse bile sıcaklık eşik değerinin altına düşene kadar yanmaya devam eder.

## Arduino Cloud Dashboard
1. Arduino Cloud Dashboard'da dört adet widget oluşturun:
- `sicaklik`, `nem`, `mesaj`, ve `led` değişkenleri için.
2. Bu widgetlar aracılığıyla sensör verilerini izleyebilir ve LED'i kontrol edebilirsiniz.

## Notlar
- Cloud'a bağlanma süresi birkaç dakika sürebilir. Lütfen sabırlı olun.
- Kodlarda her satır için açıklayıcı yorumlar eklenmiştir, böylece kolayca anlaşılabilir.
- ESP32 ve diğer bileşenlerle ilgili referanslar ve daha fazla bilgi README dosyasının sonunda verilmiştir.

## Kaynaklar
- [Arduino Cloud](https://cloud.arduino.cc/)
- [Wokwi Platformu](https://wokwi.com)


