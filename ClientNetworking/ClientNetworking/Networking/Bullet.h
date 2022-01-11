#pragma once
class Bullet
{
private:
	sf::Sprite shot;
	sf::Texture bulletTextureSheet;

public:
	Bullet();

	void initTexture();
	void initSprite();

	//sf::Vector2f getGunPosition();
	//sf::Vector2f getGunWidthHeight();

	void moveFiredBullet();

	sf::Vector2f getBulletPosition();
	sf::Vector2f getBulletWidthHeight();

	void setFirstBulletPotition(sf::Vector2f coor, sf::Vector2f dir);
	void setScale(sf::Vector2f scale);

	void update();
	void render(sf::RenderTarget& target);
};

