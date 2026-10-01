#include <iostream>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image_write.h"
using namespace std;
int main() { 
string input_path = "input/image.png";
string output_path = "output/task2_output.png";
int width, height, channels;

// Resmi yükleme
unsigned char *img = stbi_load(input_path.c_str(), &width, &height, &channels, 0);

if (img == nullptr) {
    cout << "Resim yüklenirken hata oluştu\n";
    return -1;
}

cout << "Resim başarıyla yüklendi. Boyutlar: " << width << "x" << height << " ve Kanal sayısı: " << channels << "\n";
// Pikseller üzerinde döngü ile dolaşma ve aritmetik işlem uygulama
for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
        // Her pikselin başlangıç indeksini bulma
        int index = (y * width + x) * channels;

        // Her kanal (R, G, B) için işlemi uygulama ve sınırları kontrol etme (0-255)
        for (int c = 0; c < channels; c++) {
            if (c == 3) continue; // Eğer alfa kanalı (şeffaflık) varsa değiştirme
            
            float val = img[index + c] * 0.75f + 20.0f;
            
            // Değerin 0 ile 255 arasında kalmasını sağlama
            if (val > 255.0f) val = 255.0f;
            if (val < 0.0f) val = 0.0f;
            
            img[index + c] = (unsigned char)val;
        }
    }
}

// İşlenmiş resmi kaydetme
stbi_write_png(output_path.c_str(), width, height, channels, img, width * channels);

// İşlem sonrasında stbi_write_png kullanarak kaydedin

// Belleği serbest bırakma
stbi_image_free(img);

return 0;
}