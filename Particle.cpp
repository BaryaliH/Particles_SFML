#include "Particle.h"
#include <iostream>

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    m_ttl = TTL;

    m_numPoints = numPoints;

    m_radiansPerSec = ((float)rand() / RAND_MAX) * PI;

    m_cartesianPlane.setCenter(0, 0);

    m_cartesianPlane.setSize(target.getSize().x, (-1.0f) * target.getSize().y);

    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    // Random horizontal speed
    m_vx = rand() % 401 + 150;

    if (rand() % 2)
    {
        m_vx *= -1;
    }

    // Initial upward speed
    m_vy = -(rand() % 401 + 150);

    // Colors
    m_color1 = Color::White;

    m_color2 = Color(rand() % 256, rand() % 256, rand() % 256);

    float theta = ((float)rand() / RAND_MAX) * PI / 2.0f;

    float dTheta = 2 * PI / (numPoints - 1);

    for (int j = 0; j < numPoints; j++)
    {
        // Random radius for shape
        float r = rand() % 100 + 50;

        float dx = r * cos(theta);

        float dy = r * sin(theta);

        m_A(0, j) = m_centerCoordinate.x + dx;

        m_A(1, j) = m_centerCoordinate.y + dy;

        theta += dTheta;
    }
}

void Particle::draw(RenderTarget& target, RenderStates states) const
{
    VertexArray lines(TriangleFan, m_numPoints + 1);

    Vector2f center = (Vector2f)target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane);

    lines[0].position = center;

    lines[0].color = m_color1;

    for (int j = 1; j <= m_numPoints; j++)
    {
        Vector2f point(m_A(0, j - 1), m_A(1, j - 1));

        lines[j].position = (Vector2f)target.mapCoordsToPixel(point, m_cartesianPlane);

        lines[j].color = m_color2;
    }

    target.draw(lines);
}

void Particle::update(float dt)
{
    m_ttl -= dt;

    rotate(dt * m_radiansPerSec);

    scale(SCALE);

    float dx = m_vx * dt;

    // Gravity
    m_vy += G * dt;

    float dy = m_vy * dt;

    // Smooth fading effect
    if (m_color2.r > 5) m_color2.r -= 2;
    if (m_color2.g > 5) m_color2.g -= 2;
    if (m_color2.b > 5) m_color2.b -= 2;

    translate(dx, dy);
}

void Particle::translate(double xShift, double yShift)
{
    TranslationMatrix T(xShift, yShift, m_numPoints);

    m_A = T + m_A;

    m_centerCoordinate.x += xShift;

    m_centerCoordinate.y += yShift;
}

void Particle::rotate(double theta)
{
    Vector2f temp = m_centerCoordinate;

    // Move shape to origin
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

    RotationMatrix R(theta);

    m_A = R * m_A;

    // Move shape back
    translate(temp.x, temp.y);
}

void Particle::scale(double c)
{
    Vector2f temp = m_centerCoordinate;

    // Move shape to origin
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

    ScalingMatrix S(c);

    m_A = S * m_A;

    // Move shape back
    translate(temp.x, temp.y);
}

bool Particle::almostEqual(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    cout << "Particle unit tests complete." << endl;
}