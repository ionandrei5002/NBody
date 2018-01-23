#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <random>
#include <math.h>

static float G = 6.673e-11;
int nb = 1024;
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
    for(int i = 0; i < nb; i++) {
        Particles->cx[i] = 800 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->cy[i] = 800 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->vx[i] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->vy[i] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->fx[i] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->fy[i] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }
    for(int i = 0; i < nb; i++) {
        Particles->mass[i] = 10e15 * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }

    Particles->cx[0] = 500.f;
    Particles->cy[0] = 400.f;
    Particles->vx[0] = .0f;
    Particles->vy[0] = .0f;
    Particles->fx[0] = .0f;
    Particles->fy[0] = .0f;
    Particles->mass[0] = 10e18;
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
    for(int i = 0; i < nb; i++) {
        Particles->vx[i] += dt * Particles->fx[i] / Particles->mass[i];
    }
    for(int i = 0; i < nb; i++) {
        Particles->vy[i] += dt * Particles->fy[i] / Particles->mass[i];
    }
    for(int i = 0; i < nb; i++) {
        Particles->cx[i] += dt * Particles->vx[i];
    }
    for(int i = 0; i < nb; i++) {
        Particles->cy[i] += dt * Particles->vy[i];
    }
}

void resetForces(int nb) {
    for(int i = 0; i < nb; i++) {
        Particles->fx[i] = 0.0f;
    }
    for(int i = 0; i < nb; i++) {
        Particles->fy[i] = 0.0f;
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

void setPosition(sf::CircleShape shapes[], int nb) {
    for(int i = 0; i < nb; i++) {
        shapes[i].setPosition(Particles->cx[i], Particles->cy[i]);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
    initParticles(nb);
    sf::CircleShape* shapes = new sf::CircleShape[nb];
    for(int i = 0; i < nb; i++) {
        shapes[i] = sf::CircleShape(1.f);
        shapes[i].setFillColor(sf::Color::Red);
    }

    shapes[0].setRadius(10.f);
    shapes[0].setFillColor(sf::Color::Blue);

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

        window.clear(sf::Color(255,255,255));

        for(int i = 0; i < 1024; i++) {
            window.draw(shapes[i]);
        }
        window.draw(text);

        window.display();
    }

    return 0;
}
