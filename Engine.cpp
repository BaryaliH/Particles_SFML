#include "Engine.h"
#include <iostream>

Engine::Engine()
{
    VideoMode vm = VideoMode::getDesktopMode();

    m_Window.create(vm, "Elegant Particles", Style::Default);
}

void Engine::run()
{
    Clock clock;

    cout << "Starting Particle unit tests..." << endl;

    Particle p(m_Window, 4, {(int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2});

    p.unitTests();

    cout << "Unit tests complete. Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();

        update(dtAsSeconds);

        draw();
    }
}

void Engine::input()
{
    Event event;

    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            m_Window.close();
        }

        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                m_Window.close();
            }
        }

        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                // Create multiple particles on click
                for (int i = 0; i < 8; i++)
                {
                    int numPoints = rand() % 30 + 20;

                    m_particles.push_back(Particle(m_Window,numPoints,{event.mouseButton.x,event.mouseButton.y}));
                }
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    vector<Particle>::iterator it = m_particles.begin();

    while (it != m_particles.end())
    {
        if (it->getTTL() > 0.0f)
        {
            it->update(dtAsSeconds);

            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for (auto& p : m_particles)
    {
        m_Window.draw(p);
    }

    m_Window.display();
}