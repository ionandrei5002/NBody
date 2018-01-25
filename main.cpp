#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <random>
#include <math.h>

static float G = 6.673e-11;
int nb = 2048;
struct particles {
    float* cx;
    float* cy;
    float* vx;
    float* vy;
    float* fx;
    float* fy;
    float* mass;
    particles(int nb) {
       cx = new float[nb];
       cy = new float[nb];
       vx = new float[nb];
       vy = new float[nb];
       fx = new float[nb];
       fy = new float[nb];
       mass = new float[nb];
    }
}* Particles = new particles(nb);

void initParticles(int nb) {
    std::srand(std::time(NULL));
    for(int i = 0; i < nb/2; i++) {
        Particles->cx[i] = 1000 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb/2; i++) {
        Particles->cy[i] = 800 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = nb/2; i < nb; i++) {
        Particles->cx[i] = 600 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = nb/2; i < nb; i++) {
        Particles->cy[i] = 400 + 200 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->vx[i] = 0 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->vy[i] = 0 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->fx[i] = 0 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->fy[i] = 0 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->mass[i] = 10e13f * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }

    Particles->cx[0] = 500.f;
    Particles->cy[0] = 400.f;
    Particles->vx[0] = .0f;
    Particles->vy[0] = .0f;
    Particles->fx[0] = .0f;
    Particles->fy[0] = .0f;
    Particles->mass[0] = 10e18;
    Particles->mass[1] = 10e17;
    Particles->mass[2] = 10e17;
    Particles->mass[3] = 10e17;
}

void printParticles(int nb) {
    std::cout << "============================================DEBUG============================================" << std::endl;
    for(int i = 0; i < nb; i++) {
        std::cout << Particles->cx[i] << " " << Particles->cx[i]
                     << " " << Particles->vx[i] << " " << Particles->vx[i]
                        << " " << Particles->fx[i] << " " << Particles->fx[i]
                           << " " << Particles->mass[i]
                              << std::endl;
    }
    std::cout << "============================================DEBUG============================================" << std::endl;
}

void update(float dt, int nb) {
    for(int i = 0; i < nb; i+=4) {
        Particles->vx[i] += dt * Particles->fx[i] / Particles->mass[i];
        Particles->vx[i+1] += dt * Particles->fx[i+1] / Particles->mass[i+1];
        Particles->vx[i+2] += dt * Particles->fx[i+2] / Particles->mass[i+2];
        Particles->vx[i+3] += dt * Particles->fx[i+3] / Particles->mass[i+3];
    }
    for(int i = 0; i < nb; i+=4) {
        Particles->vy[i] += dt * Particles->fy[i] / Particles->mass[i];
        Particles->vy[i+1] += dt * Particles->fy[i+1] / Particles->mass[i+1];
        Particles->vy[i+2] += dt * Particles->fy[i+2] / Particles->mass[i+2];
        Particles->vy[i+3] += dt * Particles->fy[i+3] / Particles->mass[i+3];
    }
    for(int i = 0; i < nb; i+=4) {
        Particles->cx[i] += dt * Particles->vx[i];
        Particles->cx[i+1] += dt * Particles->vx[i+1];
        Particles->cx[i+2] += dt * Particles->vx[i+2];
        Particles->cx[i+3] += dt * Particles->vx[i+3];
    }
    for(int i = 0; i < nb; i+=4) {
        Particles->cy[i] += dt * Particles->vy[i];
        Particles->cy[i+1] += dt * Particles->vy[i+1];
        Particles->cy[i+2] += dt * Particles->vy[i+2];
        Particles->cy[i+3] += dt * Particles->vy[i+3];
    }
}

void resetForces(int nb) {
    for(int i = 0; i < nb; i+=4) {
        Particles->fx[i] = 0.0f;
        Particles->fx[i+1] = 0.0f;
        Particles->fx[i+2] = 0.0f;
        Particles->fx[i+3] = 0.0f;
    }
    for(int i = 0; i < nb; i+=4) {
        Particles->fy[i] = 0.0f;
        Particles->fy[i+1] = 0.0f;
        Particles->fy[i+2] = 0.0f;
        Particles->fy[i+3] = 0.0f;
    }
}

void addForces(int i, int j) {
    float eps = 3e4;
    float dx = Particles->cx[j] - Particles->cx[i];
    float dy = Particles->cy[j] - Particles->cy[i];
    float dist = std::sqrt(dx*dx + dy*dy);
    float F = (G * Particles->mass[i] * Particles->mass[j]) / (dist * dist + eps*eps);
    Particles->fx[i] += F * dx/dist;
    Particles->fy[i] += F * dy/dist;
}

void setPosition(sf::CircleShape* shapes, int nb) {
    for(int i = 0; i < nb; i+=4) {
        shapes[i].setPosition(Particles->cx[i], Particles->cy[i]);
        shapes[i+1].setPosition(Particles->cx[i+1], Particles->cy[i+1]);
        shapes[i+2].setPosition(Particles->cx[i+2], Particles->cy[i+2]);
        shapes[i+3].setPosition(Particles->cx[i+3], Particles->cy[i+3]);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "NBody Simulation");
    initParticles(nb);
    sf::CircleShape* shapes = new sf::CircleShape[nb];
    for(int i = 0; i < nb; i++) {
        int red = (int) floor(Particles->mass[i]*254/(Particles->mass[i]*1e20));
        int blue = (int) floor(Particles->mass[i]*254/(Particles->mass[i]*1e20));
        shapes[i] = sf::CircleShape(2.f);
        shapes[i].setFillColor(sf::Color(red, 255, blue));
    }

    shapes[0].setRadius(10.f);
    shapes[0].setFillColor(sf::Color::Blue);
    shapes[1].setRadius(10.f);
    shapes[1].setFillColor(sf::Color::Red);
    shapes[2].setRadius(10.f);
    shapes[2].setFillColor(sf::Color::Black);
    shapes[3].setRadius(10.f);
    shapes[3].setFillColor(sf::Color::Cyan);

    sf::Clock _clock;

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMono.ttf")) {

    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        resetForces(nb);
        for(int i = 0; i < nb; i++) {
            for(int j = 0; j < nb; j++) {
                if (i != j)
                    addForces(i, j);
            }
        }
        update(.1f, nb);
        setPosition(shapes, nb);

        float ElapsedTime = _clock.getElapsedTime().asMicroseconds();
        _clock.restart();
        float fps = 1.f / (ElapsedTime / 1000000);

        sf::String str(std::to_string(fps));
        sf::Text text;
        text.setFont(font);
        text.setColor(sf::Color::Black);
        text.setString(str);
        text.setCharacterSize(25);

        window.clear(sf::Color::White);

        for(int i = 0; i < nb; i+=4) {
            window.draw(shapes[i]);
            window.draw(shapes[i+1]);
            window.draw(shapes[i+2]);
            window.draw(shapes[i+3]);
        }
        window.draw(text);

        window.display();
    }

    return 0;
}
