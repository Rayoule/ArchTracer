#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "include/Vec3.h"
#include "include/ARay.h"
#include "include/ASphere.h"
#include "include/AHitableList.h"
#include "include/ACamera.h"


vec3 Color(const ARay& r, AHitable *world) {

    SHitRecord rec;
    if(world->Hit(r, 0.0, MAXFLOAT, rec)){
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }else {

        // Background Color
        vec3 unit_direction = unit_vector(r.direction());
        float f = 0.5*(unit_direction.y() + 1.0);
        return (1.0-f)*vec3(1.0, 1.0, 1.0) + f*vec3(0.5, 0.7, 1.0);
    }
}


void RaytraceImage(int nx, int ny, sf::Uint8 *arrPtr) {

    
}

int main() {

    // Setup Variables
    unsigned int nx = 800;
    unsigned int ny = 400;
    int ns = 100;
    int pxlNumber = ny * nx * 4;
    sf::Uint8 pixels[pxlNumber];
    sf::Uint8 *pxlPtr;
    pxlPtr = pixels;
    
    // Creates Texture to display
    sf::RenderWindow window(sf::VideoMode(nx, ny), "test");
    window.setFramerateLimit(30);
    sf::Texture texture;
    texture.create(nx, ny);
    sf::Sprite sprite(texture);

    // Camera
    ACamera cam;

    // START Raytrace Image -------
    AHitable *list[2];
    list[0] = new ASphere(vec3(0,0,-1), 0.5);
    list[1] = new ASphere(vec3(0,-100.5,-1), 100);
    AHitable *world = new AHitableList(list, 2);

    for (int j = 0; j < ny; j++) {

        for (int i = 0; i < nx; i++) {

            vec3 col(0,0,0);

            for(int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = 1.0 - (float(j + drand48()) / float(ny));
                
                ARay r = cam.GetRay(u,v);
                vec3 p = r.point_at_parameter(2.0);
                col += Color(r, world);
            }

            col /= float(ns);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);


            int idx = ((nx * j) + i) * 4;
            *(pxlPtr + idx) = sf::Uint8(ir);
            *(pxlPtr + idx + 1) = sf::Uint8(ig);
            *(pxlPtr + idx + 2) = sf::Uint8(ib);
            *(pxlPtr + idx + 3) = sf::Uint8(255);
        }
    }
    // END Raytrace Image -----------

    texture.update(pxlPtr);

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
