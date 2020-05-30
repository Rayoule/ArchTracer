#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "include/GeneralHeader.h"
#include "include/ASphere.h"
#include "include/AHitableList.h"
#include "include/ACamera.h"
#include "include/AAntiAliasing.h"
#include "include/AMaterial.h"



vec3 RayColor(const ARay& r, const AHitable& world, int depth) {
    SHitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3(0,0,0);

    if (world.Hit(r, 0.001, infinity, rec)) {
        ARay scattered;
        vec3 attenuation;
        if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, world, depth-1);
        return vec3(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}


void RaytraceImage(int nx, int ny, sf::Uint8 *arrPtr) {

    
}

int main() {

    // Setup Variables
    const int nx = 400;
    const int ny = 200;
    const int max_depth = 50;
    int samples_per_pixels = 50;
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
    // AntiAliasing
    AAntiAliasing AA;

    // Defines the world
    AHitableList world;

    world.add(make_shared<ASphere>(
        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.7, 0.3, 0.3))));

    world.add(make_shared<ASphere>(
        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));

    world.add(make_shared<ASphere>(vec3(1,0,-1), 0.5, make_shared<AMetal>(vec3(0.8,0.6,0.2), 0.0)));
    world.add(make_shared<ASphere>(vec3(-1,0,-1), 0.5, make_shared<AMetal>(vec3(0.8,0.8,0.8), 0.0)));


    for (int j = 0; j < ny; j++) {

        for (int i = 0; i < nx; i++) {

            vec3 col(0,0,0);

            for(int s = 0; s < samples_per_pixels; s++) {

                float u = (float(i) + random_float()) / float(nx);
                float v = 1.0 - ((float(j) + random_float()) / float(ny));
                
                ARay r = cam.GetRay(u,v);
                vec3 p = r.at(2.0);
                col += RayColor(r, world, max_depth);
            }

            col /= float(samples_per_pixels);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

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
