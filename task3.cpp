#include <iostream> 
#include <vector>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h" 
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image_write.h"
using namespace std;
void processHistogramCUDA(unsigned char* img, int width, int height, int channels, int* histogram) { 
    int totalPixels = width * height;
for (int i = 0; i < totalPixels; ++i) {
    int index = i * channels;
    unsigned char brightness = img[index];
    histogram[brightness]++;
}
}
int main() { 
    string input_path = "input/image.png";
int width, height, channels;
unsigned char* img = stbi_load(input_path.c_str(), &width, &height, &channels, 0);
if (img == nullptr) {
    cout << "Resim okunamadı!\n";
    return 1;
}

cout << "Resim yüklendi: " << width << "x" << height << "\n";

vector<int> histogram(256, 0);
processHistogramCUDA(img, width, height, channels, histogram.data());

cout << "Histogram hesaplandı.\n";
cout << "Parlaklık 2 olan piksel sayısı: " << histogram[2] << "\n";

stbi_image_free(img);
return 0;
}