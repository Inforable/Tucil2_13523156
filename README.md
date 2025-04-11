# Tucil2 (Kompresi Gambar dengan Metode QuadTree)

Program ini merupakan implementasi algoritma Divide and Conquer untuk melakukan kompresi gambar dengan metode QuadTree. Gambar akan dikompresi berdasarkan keseragaman warna dalam blok dan sejauh apa blok dapat dibagi dengan batasan ukuran blok minimum. Terdapat empat metode pengukuran error, yaitu Variance, Mean Absolute Deviation (MAD), Max Pixel Difference, dan Entropy

## Persyaratan
- **Compiler C++ (minimal versi C++17)**
- **Library FreeImage https://freeimage.sourceforge.io**

## Setup
1. Lakukan Clone Repository
    ```bash
    git clone https://github.com/Inforable/Tucil2_13523156.git
    cd Tucil2_13523156

2. Instalasi
- **Linux (Ubuntu)**
    ```bash
    sudo apt install libfreeimage-dev

    Atau

    make install

- **Windows: Depedenci sudah tersedia di src/library**

## Kompilasi
- **Windows**
    ```bash
    g++ src/main.cpp src/Image.cpp src/InputHandler.cpp src/QuadTree.cpp src/QuadNode.cpp src/ErrorCalculation.cpp -Isrc/header -Lsrc/library -lFreeImage -std=c++17 -o bin/win_compressor.exe

- **Linux**
    ```bash
    make build

## Cara Menjalankan Program
- **Windows**
    ```bash
    .\bin\win_compressor

- **Linux**
    ```bash
    .\bin\linux_compressor

## Author
**13523156 - Hasri Fayadh Muqaffa**