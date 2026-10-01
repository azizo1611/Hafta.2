#include <iostream> 
#include <vector> 
#include <cmath> 
#include <cstdlib> 
#include <ctime>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h" 
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image_write.h"
using namespace std;
struct RGB {
    float r, g, b;
};
int main() {
     string input_path = "input/image.png"; 
    int width, height, channels;
// Resmi yükleme (3 kanal RGB olarak)
unsigned char* img = stbi_load(input_path.c_str(), &width, &height, &channels, 3);
if (img == nullptr) {
    cout << "Resim okunamadı\n";
    return 1;
}

cout << "Resim yüklendi: " << width << "x" << height << "\n";

int totalPixels = width * height;
int k = 8; // Küme sayısı (K-Means küme değeri: 4, 8 veya 16 yapılabilir)

// Rastgele başlangıç merkezleri (Centroids) seçimi
srand(time(0));
vector<RGB> centroids(k);
for (int i = 0; i < k; ++i) {
    int idx = rand() % totalPixels;
    centroids[i] = { (float)img[idx * 3], (float)img[idx * 3 + 1], (float)img[idx * 3 + 2] };
}

vector<int> assignments(totalPixels);
int iterations = 10; // Algoritmanın tekrar (iterasyon) sayısı

for (int iter = 0; iter < iterations; ++iter) {
    // Adım 1: Her pikseli kendisine en yakın renk merkezine atama
    for (int i = 0; i < totalPixels; ++i) {
        float r = img[i * 3];
        float g = img[i * 3 + 1];
        float b = img[i * 3 + 2];

        int best_cluster = 0;
        float min_dist = -1;

        for (int j = 0; j < k; ++j) {
            float dist = pow(r - centroids[j].r, 2) + pow(g - centroids[j].g, 2) + pow(b - centroids[j].b, 2);
            if (min_dist == -1 || dist < min_dist) {
                min_dist = dist;
                best_cluster = j;
            }
        }
        assignments[i] = best_cluster;
    }

    // Adım 2: Renk merkezlerini (Centroids) güncelleme
    vector<RGB> sum(k, {0, 0, 0});
    vector<int> count(k, 0);

    for (int i = 0; i < totalPixels; ++i) {
        int cluster = assignments[i];
        sum[cluster].r += img[i * 3];
        sum[cluster].g += img[i * 3 + 1];
        sum[cluster].b += img[i * 3 + 2];
        count[cluster]++;
    }

    for (int j = 0; j < k; ++j) {
        if (count[j] > 0) {
            centroids[j].r = sum[j].r / count[j];
            centroids[j].g = sum[j].g / count[j];
            centroids[j].b = sum[j].b / count[j];
        }
    }
}

// Yeni küme renklerini kullanarak resmi yeniden oluşturma
vector<unsigned char> output_img(totalPixels * 3);
for (int i = 0; i < totalPixels; ++i) {
    int cluster = assignments[i];
    output_img[i * 3]     = (unsigned char)centroids[cluster].r;
    output_img[i * 3 + 1] = (unsigned char)centroids[cluster].g;
    output_img[i * 3 + 2] = (unsigned char)centroids[cluster].b;
}

// İşlenen sonucu output klasörüne kaydetme
stbi_write_png("output/task3_output.png", width, height, 3, output_img.data(), width * 3);
cout << "K-Means uygulandı ve resim kaydedildi!\n";

// Belleği temizleme
stbi_image_free(img);
return 0;
}