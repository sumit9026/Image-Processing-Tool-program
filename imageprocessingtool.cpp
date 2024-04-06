#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Image {
    int width;
    int height;
    vector<Pixel> pixels; 
};

Image readImage(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    Image image;
    file.read(reinterpret_cast<char*>(&image.width), sizeof(int));
    file.read(reinterpret_cast<char*>(&image.height), sizeof(int));
    image.pixels.resize(image.width * image.height);
    file.read(reinterpret_cast<char*>(image.pixels.data()), image.width * image.height * sizeof(Pixel));

    file.close();
    return image;
}

void writeImage(const char* filename, const Image& image) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening ile: " << filename << endl;
        exit(1);

    }
    file.write(reinterpret_cast<const char*>(&image.width), sizeof(int));
    file.write(reinterpret_cast<const char*>(&image.height), sizeof(int));
    file.write(reinterpret_cast<const char*>(image.pixels.data()), image.width * image.height * sizeof(Pixel));

    file.close();    
}

void displayMenu() {
    cout << "Image Processing Tool Menu" << endl;
    cout << "1. Load Image" << endl;
    cout << "2. Display Image" << endl;
    cout << "3. Save Image" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Image image;
    bool imageLoaded = false;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;


        switch (choice) {
            case 1: {

                const char* filename = "input_image.bin";
                image = readImage(filename);
                imageLoaded = true;
                cout << "Image loaded successfully." << endl;
                break;
            }
            case 2: {

                if (imageLoaded) {
                    for (int y = 0; y < image.height; ++y) {
                        for (int x = 0; x < image.width; ++x) {
                            Pixel& pixel = image.pixels[y * image.width + x];
                            cout << "(" << (int)pixel.red << ", " << (int)pixel.green << ", " << (int)pixel.blue << ") ";

                }
                cout << endl;
            }
        } else {
            cout << "No image loaded." << endl;
        }
        break;
    }
    case 3: {

        if (imageLoaded) {
                    const char* filename = "output_image.bin"; // Change this to your output image file
                    writeImage(filename, image);
                    cout << "Image saved successfully." << endl;
    } else {
        cout << "No image loaded." << endl;
    }
    break;

}
case 4: {
                // Exit
                cout << "Exiting program." << endl;
                exit(0);
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}