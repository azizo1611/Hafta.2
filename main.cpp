#define STB_IMAGE_IMPLEMENTATION
 #include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image_write.h"
#include <iostream> 
#include <chrono>
using namespace std;
int main() {
     int width, height, channels; 
     unsigned char* img = stbi_load("image.png", &width, &height, &channels, 3);
if (img == nullptr) {
    cout << "Error: Could not load image!" << endl;
    return -1;
}

cout << "Image loaded successfully! Width: " << width << ", Height: " << height << endl;

auto start = chrono::high_resolution_clock::now();

for (int i = 0; i < width * height * 3; i++) {
    img[i] = (img[i] / 4) * 4;
}

auto end = chrono::high_resolution_clock::now();
cout << "Processing time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n";

stbi_write_png("output/result_task1.png", width, height, 3, img, width * 3);

stbi_image_free(img);
cout << "Task 1 completed successfully!" << endl;

return 0;
}