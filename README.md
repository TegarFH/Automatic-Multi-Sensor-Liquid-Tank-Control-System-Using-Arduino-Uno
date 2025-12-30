Automatic Multi-Sensor Liquid Tank Control System
Tinkercad : https://www.tinkercad.com/things/eKNvZsVfHvv-automatic-multi-sensor-liquid-tank-control-system
Arduino Uno – Instrumentation & Automation Project

Deskripsi

Proyek ini merupakan perancangan dan simulasi sistem pengendalian cairan otomatis berbasis Arduino Uno yang menggunakan multi-sensor untuk memonitor dan mengontrol level, suhu, dan tekanan pada sebuah tangki. Sistem bekerja secara close loop dengan prioritas keselamatan dan divisualisasikan melalui LCD 16×2.

Proyek dikembangkan sebagai bagian dari mata kuliah Pengantar Instrumentasi dan Automasi.
Rangkaian

<img width="936" height="767" alt="Screenshot 2025-12-30 195223" src="https://github.com/user-attachments/assets/35bc3348-cee8-43e3-bb39-5a97d3517aaf" />


Fitur Utama
-Kontrol level cairan otomatis menggunakan sensor ultrasonic
-Monitoring suhu menggunakan TMP36
-Simulasi tekanan menggunakan potensiometer

Pengendalian aktuator:
-Pompa DC (level control)
-Servo motor sebagai control valve (pressure control)
-LED & buzzer sebagai alarm keselamatan
-Tampilan data real-time pada LCD 16×2
-Penanganan kesalahan sensor (fail-safe)
-Dilengkapi Diagram Blok Sistem dan Diagram P&ID (ISA Standard)

Komponen yang Digunakan(Hardware)
-Arduino Uno R3
-Sensor Suhu TMP36
-Ultrasonic Sensor HC-SR04
-Potensiometer (simulasi pressure sensor)
-Motor DC + Transistor + Dioda
-Servo Motor
-LED Merah & Buzzer
-LCD 16×2
-Kabel jumper & catu daya
-Software
-Tinkercad Circuits
-Arduino IDE

Logika Kerja Sistem
-Level Control
-Level rendah → Pompa ON
-Level cukup/tinggi → Pompa OFF
-Temperature Protection
-Suhu > 40°C → Alarm ON
-Pressure Protection
-Tekanan > 80% → Valve OPEN & Alarm ON
-Sensor Error
-Sistem masuk mode aman (motor OFF, alarm OFF, display error)
-Diagram Sistem
-Diagram Blok Sistem Kontrol
-Diagram P&ID Sistem Pengendalian Cairan Otomatis Multi-Sensor
-(Sensor: TT, LT, PT | Aktuator: Pump, Control Valve, Alarm)

Diagram Blok

![Diagram Blok UAS](https://github.com/user-attachments/assets/ccf2eb33-5ed7-447c-85a0-e060ba9f3383)

Jenis Sistem Kendali
-Close Loop Control System
-Menggunakan feedback sensor untuk koreksi otomatis
-Dilengkapi prioritas keselamatan (safety first)

P&Id Diagram

![P Id Uas PIA](https://github.com/user-attachments/assets/7515cefc-3207-44f7-b605-6116c9dbbf9b)

Tujuan Pembelajaran
-Memahami hubungan sensor – controller – actuator
-Mampu merancang sistem otomasi sederhana
-Memahami fungsi dan simbol P&ID
-Menerapkan konsep keselamatan pada sistem industri

Author
Tegar Fariz Habibi
Program Studi Rekayasa Instrumentasi dan Automasi
Institut Teknologi Sumatera
2025
