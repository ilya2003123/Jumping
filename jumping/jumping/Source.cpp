#include <SFML/Graphics.hpp>
#include <time.h>

struct point
{
	int x, y;
};

int main()
{
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(400, 533), "Jump!");
	window.setFramerateLimit(60);

	sf::Texture w;
	w.loadFromFile("Paint/background.png");
	sf::Sprite win(w);

	sf::Texture m;
	m.loadFromFile("Paint/man.png");
	sf::Sprite man(m);
	man.setTextureRect(sf::IntRect(540, 0, 90, 140));
	man.setScale(0.5, 0.5);

	int x = 100, y = 100, px = 0, py = 1;
	float dx = 0, dy = 0, frame = 6;

	sf::Texture p;
	p.loadFromFile("Paint/platform.png");
	sf::Sprite platform(p);

	point pt[10];
	for (int i = 0; i < 10; i++)
	{
		pt[i].x = rand() % 400;
		pt[i].y = rand() % 533;
	}

	sf::Texture go;
	go.loadFromFile("Paint/gameover.png");
	sf::Sprite gameover(go);
	gameover.setPosition(0, 150);
	bool Game = true;

	sf::Texture s;
	s.loadFromFile("Paint/score.png");
	sf::Sprite score[5];
	int fs[5];
	for (int i = 0; i < 5; i++)
	{
		score[i].setTexture(s);
		score[i].setTextureRect(sf::IntRect(0, 0, 30, 47));
		score[i].setPosition(35 * i, 0);
		fs[i] = 0;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Game)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				x += 3;

				px = 0;
				py = 1;

				man.setTextureRect(sf::IntRect(540, 0, 90, 140));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				x -= 3;

				px = 90;
				py = -1;

				man.setTextureRect(sf::IntRect(540 + 90, 0, -90, 140));
			}

			dy += 0.2;
			y += dy;
			if (y > 510)
				Game = false;

			if (x < -40)
				x = 400;
			if (x > 400)
				x = -40;

			for (int i = 0; i < 10; i++)
				if ((x + 40 > pt[i].x) && (x + 5 < pt[i].x + 68)
					&& (y + 70 > pt[i].y) && (y + 70 < pt[i].y + 14)
					&& (dy > 0))
				{
					dy -= 20;

					frame = 0;
				}

			if (y < 100)
				for (int i = 0; i < 10; i++)
				{
					y = 100;

					pt[i].y = pt[i].y - dy;
					if (pt[i].y > 533)
					{
						pt[i].y = 0;
						pt[i].x = rand() % 400;

						fs[4]++;
						if (fs[4] > 9) 
						{
							fs[4] -= 10;

							fs[3]++;
							if (fs[3] > 9) 
							{
								fs[3] -= 10;

								fs[2]++;
								if (fs[2] > 9) 
								{
									fs[2] -= 10;

									fs[1]++;
									if (fs[1] > 9) 
									{
										fs[1] -= 10;

										fs[0]++;
										if (fs[0] > 9)
											fs[0] -= 10;
										score[0].setTextureRect(sf::IntRect(30 * fs[0], 0, 30, 47));
									}
									score[1].setTextureRect(sf::IntRect(30 * fs[1], 0, 30, 47));
								}
								score[2].setTextureRect(sf::IntRect(30 * fs[2], 0, 30, 47));
							}
							score[3].setTextureRect(sf::IntRect(30 * fs[3], 0, 30, 47));
						}
						score[4].setTextureRect(sf::IntRect(30 * fs[4], 0, 30, 47));
					}
				}

			if (frame < 6) 
			{
				frame += 0.2;
				man.setTextureRect(sf::IntRect(90 * int(frame) + px, 0, 90 * py, 140));
			}
		}

		man.setPosition(x, y);

		window.clear(sf::Color::White);
		window.draw(win);
		window.draw(man);

		for (int i = 0; i < 10; i++) 
		{
			platform.setPosition(pt[i].x, pt[i].y);

			window.draw(platform);
		}

		if (!Game)
			window.draw(gameover);

		for (int i = 0; i < 5; i++)
			window.draw(score[i]);

		window.display();
	}

	return 0;
}