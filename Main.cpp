#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>


void RaytraceImage(int dimX, int dimY, int arrSize, sf::Uint8 *arrPtr) {

    std::cout << "P3\n" << dimX << " " << dimY << "\n255\n";
    for (int j = dimY-1; j >= 0; j--) {
        for (int i = 0; i < dimX; i++) {
            float r = float(i) / float(dimX);
            float g = float(j) / float(dimY);
            float b = 0.2;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            std::cout << ir << " " << ig << " " << ib << "\n";

            int idx = i * j * 4;
            /*(*arrPtr)[idx] = ir;
            (*arrPtr)[idx + 1] = ig;
            (*arrPtr)[idx + 2] = ib;
            (*arrPtr)[idx + 3] = 0;*/
            *(arrPtr + idx) = sf::Uint8(ir);
            *(arrPtr + idx + 1) = sf::Uint8(ig);
            *(arrPtr + idx + 2) = sf::Uint8(ib);
            *(arrPtr + idx + 3) = sf::Uint8(0);
        }
    }
}

int main() {

    unsigned int nx = 200;
    unsigned int ny = 100;
    int pxlNumber = ny * nx * 4;
    sf::Uint8 pixels[pxlNumber];
    sf::Uint8 *pxlPtr;
    pxlPtr = pixels;
    bool bIsFinished = false;

    RaytraceImage(nx, ny, pxlNumber, pxlPtr);


    sf::RenderWindow window(sf::VideoMode(nx, ny), "test");
    window.setFramerateLimit(30);
    sf::Texture texture;
    texture.create(nx, ny);
    sf::Sprite sprite(texture);

    texture.update(pxlPtr);

    for(int i = 0; i < pxlNumber; i++) {
        std::cout << " entry num. " << i << " is " << *(pxlPtr + i) << "\n";
    }

    for(int i = 0; i < pxlNumber; i++) {
        pixels[i] = int(255);
    }


    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    return 0;
}