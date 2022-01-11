#include "preHeads.h"
#include "Collision.h"

Collision::Collision(sf::RectangleShape& body)
    :body(body)
{
}

void Collision::move(float dx, float dy)
{
    body.move(dx, dy);
}

sf::Vector2f Collision::getPosition()
{
    return body.getPosition();
}

sf::Vector2f Collision::getHalfSize()
{
    return body.getSize() / 2.f;
}

bool Collision::CheckCollision(Collision other, float push)
{
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = this->getPosition();
    sf::Vector2f thisHalfSize = this->getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.f && intersectY < 0.f)
    {
        push = std::min(std::max(push, 0.f), 1.f);

        if (intersectX > intersectY)
        {
            if (deltaX > 0.f)
            {
                this->move(intersectX * (1.f - push), 0.f);
                other.move(-intersectX * push, 0.f);
            }
            else
            {
                this->move(-intersectX * (1.f - push), 0.f);
                other.move(intersectX * push, 0.f);
            }
        }
        else
        {
            if (deltaY > 0.f)
            {
                this->move(0.f, intersectY * (1.f - push));
                other.move(0.f, -intersectY * push);
            }
            else
            {
                this->move(0.f, -intersectY * (1.f - push));
                other.move(0.f, intersectY * push);
            }
        }
        return true;
    }
    return false;
}
