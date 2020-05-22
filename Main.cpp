#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "include/Vec3.h"
#include "include/Ray.h"


void RaytraceImage(int dimX, int dimY, sf::Uint8 *arrPtr) {

    std::cout << "P3\n" << dimX << " " << dimY << "\n255\n";
    for (int j = dimY-1; j >= 0; j--) {
        for (int i = 0; i < dimX; i++) {

            vec3 col(float(i) / float(dimX), float(j) / float(dimY), 0.2);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";

            int idx = ((dimX * j) + i) * 4;

            *(arrPtr + idx) = sf::Uint8(ir);
            *(arrPtr + idx + 1) = sf::Uint8(ig);
            *(arrPtr + idx + 2) = sf::Uint8(ib);
            *(arrPtr + idx + 3) = sf::Uint8(255);
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
    
    
    sf::RenderWindow window(sf::VideoMode(nx, ny), "test");
    window.setFramerateLimit(30);
    sf::Texture texture;
    texture.create(nx, ny);
    sf::Sprite sprite(texture);

    RaytraceImage(nx, ny, pxlPtr);

    texture.update(pxlPtr);

    //std::cout << " vec3(1,1,1) + vec3(-1, -0.5, 23) = " << 


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
