# ESP8266 Remote Relay via HTTP JSON

## Deskripsi
Project ini menggunakan ESP8266 (NodeMCU 1.0) untuk mengontrol 4 relay berdasarkan status dari server lewat HTTP GET dan JSON. Cocok untuk smart home sederhana, seperti mengontrol lampu dari server web.

ESP akan:
- Terhubung ke WiFi
- Mengambil status relay dari server (lampu1–lampu4) setiap 5 detik
- Mengubah output relay sesuai data JSON

## Fitur
- Kontrol 4 relay via ESP8266 (NodeMCU 1.0)
- Update status otomatis tiap 5 detik
- Mendukung JSON dari server
- Reconnect WiFi otomatis jika putus

## Hardware yang dibutuhkan
- ESP8266 (NodeMCU 1.0)
- 4 channel relay module (5V atau sesuai spesifikasi)
- Kabel jumper
- Breadboard (opsional)
- Sumber daya ESP8266

## Wiring / Skema Rangkaian

Tabel koneksi ESP8266 ke relay:
| Relay | ESP8266 Pin | VCC | GND |
|-------|------------|-----|-----|
| Relay 1 | D1 | 5V | GND |
| Relay 2 | D2 | 5V | GND |
| Relay 3 | D3 | 5V | GND |
| Relay 4 | D4 | 5V | GND |

Diagram ASCII sederhana:
```
           +5V
            |
           [Relay VCC]
            |
           -----
ESP8266 D1 |---> IN1
ESP8266 D2 |---> IN2
ESP8266 D3 |---> IN3
ESP8266 D4 |---> IN4
            |
           GND
            |
          ESP8266 GND
```

Catatan:
- Pastikan GND ESP8266 terhubung ke GND relay module.
- Relay module 5V bisa digunakan untuk mengontrol lampu 220V dengan aman jika modul mendukung. Jangan sambungkan lampu AC langsung ke ESP!

## Library yang dibutuhkan
1. ESP8266WiFi (sudah termasuk ESP8266 Board Package)
2. ESP8266HTTPClient (sudah termasuk ESP8266 Board Package)
3. ArduinoJson (versi 6.x)
   - [Link library ArduinoJson](https://arduinojson.org/)

## Installasi Board ESP8266 di Arduino IDE
1. Buka File → Preferences
2. Tambahkan URL ini ke `Additional Board Manager URLs`:
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Buka Tools → Board → Board Manager → Cari `ESP8266` → Install
4. Pilih board: **NodeMCU 1.0 (ESP-12E Module)**

## Upload Sketch
1. Hubungkan ESP8266 (NodeMCU 1.0) ke komputer via USB
2. Pilih board & port di Arduino IDE
3. Upload sketch
4. Buka Serial Monitor untuk melihat log WiFi & JSON

## Konfigurasi
Ubah di awal kode:
```cpp
const char* ssid = "IOT";         // Nama WiFi
const char* password = "1234567890"; // Password WiFi
const char* serverName = "http://smkssyaum.my.id:8080/iotlampu/get_status.php?api=json"; // URL server JSON
```

## Catatan
- Pastikan server JSON bisa diakses dari jaringan WiFi ESP
- Relay harus menggunakan daya sesuai spesifikasi (hindari langsung pakai 220V tanpa modul relay aman)
- `client.setInsecure();` digunakan untuk bypass SSL jika pakai HTTPS self-signed

