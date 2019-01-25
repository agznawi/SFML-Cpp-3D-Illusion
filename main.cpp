#include <SFML/Graphics.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
		"Moon, Earth, Sun, Spaghetti Way!");

	// Load background
	sf::Texture spaceTexture;
	spaceTexture.loadFromFile("stars.png");
	sf::Sprite background(spaceTexture);
	float textureWidth = spaceTexture.getSize().x;
	float textureHeight = spaceTexture.getSize().y;
	background.setScale(WIDTH / textureWidth, HEIGHT / textureHeight);

	// Load Sun
	sf::Texture sunTexture;
	sunTexture.loadFromFile("sun2.png");
	sf::Sprite sun(sunTexture);
	sun.setOrigin(sunTexture.getSize().x / 2, sunTexture.getSize().y / 2);
	sun.setScale(0.4f, 0.4f);
	sun.setPosition(WIDTH / 2, HEIGHT / 2);

	// Load Earth
	sf::Texture earthTexture;
	earthTexture.loadFromFile("earth3.png");
	sf::Sprite earth(earthTexture);
	earth.setOrigin(earthTexture.getSize().x / 2, earthTexture.getSize().y / 2);
	earth.setScale(0.1f, 0.1f);

	// Load Moon
	sf::Texture moonTexture;
	moonTexture.loadFromFile("moon1.png");
	sf::Sprite moon(moonTexture);
	moon.setOrigin(moonTexture.getSize().x / 2, moonTexture.getSize().y / 2);
	moon.setScale(0.01f, 0.01f);

	float earthAngle = 3.0f;
	float moonAngle = 3.0f;

	while (window.isOpen())
	{
    // ----- Event handling -----
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

    // ----- Update -----
		// Update angles of Earth and moon
		earthAngle += 0.001f;
		moonAngle += 0.004f;
		// Update Earth position
		sf::Vector2f earthDelta(300 * cos(earthAngle), 50 * sin(earthAngle));
		earth.setPosition(sun.getPosition() + earthDelta);
		// Update Moon position
		float moonDistance = earth.getScale().x*500;
		sf::Vector2f moonDelta(moonDistance * cos(moonAngle), moonDistance * sin(moonAngle));
		moon.setPosition(earth.getPosition() + moonDelta);
		// Update Earth and moon sizes
		float fractionDown = 0.9995f;
		float fractionUp = 1.0005f;
		if (earth.getPosition().x > sun.getPosition().x)
		{
			earth.scale(fractionUp, fractionUp);
			moon.scale(fractionUp, fractionUp);
		}
		else if (earth.getPosition().x < sun.getPosition().x)
		{
			earth.scale(fractionDown, fractionDown);
			moon.scale(fractionDown, fractionDown);
		}
    
    // ----- Draw -----
		window.clear();
		window.draw(background);
		if (earth.getPosition().y > sun.getPosition().y) // earth is close to view
		{
			window.draw(sun);
			window.draw(earth);
			window.draw(moon);
		}
		else
		{
			window.draw(earth);
			window.draw(moon);
			window.draw(sun);
		}
		window.display();
	}
}
