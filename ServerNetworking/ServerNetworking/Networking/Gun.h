#pragma once
class Gun
{
private:
	sf::Sprite shoty;
	sf::Texture gunTextureSheet;

public:
	Gun();

	void initTexture();
	void initSprite();
	
	sf::Vector2f getGunPosition();
	sf::Vector2f getGunWidthHeight();

	void setGunPotition(sf::Vector2f coor, sf::Vector2f dir);

	void update();
	void render(sf::RenderTarget& target);
};

