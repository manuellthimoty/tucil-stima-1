# N-Queens Solver dengan Visualisasi Real-Time

## Penjelasan Program

Program ini adalah **solver untuk masalah N-Queens** dengan antarmuka web interaktif yang menampilkan visualisasi real-time proses pencarian solusi. Program menggunakan dua algoritma:

1. **Naive Backtracking** - Brute force sederhana, cocok untuk N kecil
2. **Optimized Backtracking** - Dengan constraint checking lebih efisien

Fitur utama:
- Grid dengan region berwarna (input grid dengan huruf A-Z)
- Real-time visualization menggunakan Server-Sent Events (SSE)
- Statistik iterasi dan waktu eksekusi
- Slider untuk mengatur frekuensi output progress
- Upload file atau input manual

---

## 🔧 Requirements & Instalasi

### Software Requirements:
- **Node.js** >= 14.0 (untuk server)
- **C++ Compiler** (MinGW/GCC untuk Windows, g++ untuk Linux/Mac)
- **Modern Browser** (Chrome, Firefox, Safari, Edge)

### Dependencies:
```bash
# Instalasi Node.js dependencies
cd src
npm install
```
# Cara Mengkompilasi
Masuk ke root Project

### Compile naive algorithm
```bash
g++ src/cpp/naive.cpp -o bin/naive
```

### Compile optimized algorithm
```bash
g++ src/cpp/optimized.cpp -o bin/optimize
```
# Cara Menjalankan
### Masuk ke src
```bash
node server.js
```
### Buka Browser dan akses
```bash
cd src
http://localhost:3000
```

# Menjalankan Solver

Ada beberapa hal yang bisa Anda lakukan disini 
### Input
Anda bisa memilih apakah mau input via uploading file atau langsung type di text area.
### Slider
Anda bisa memilih frekuensi iterasi Live Update.
### Toggle Optimization
Anda bisa memilih apakah Anda ingin mempercepat algoritma atau tidak.
