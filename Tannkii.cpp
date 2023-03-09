
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
public:
    Bullet(sf::Vector2f position, sf::Vector2f direction) {
        shape.setSize(sf::Vector2f(10.f, 10.f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position.x,
            position.y);
        xDirection = direction.x;
        yDirection = direction.y;
    }


    void move() {
        shape.move(xDirection, yDirection);
    }
    bool isOnScreen(const sf::RenderWindow& window, const sf::Shape& shape) {
        sf::FloatRect spriteBounds = shape.getGlobalBounds();
        sf::FloatRect screenBounds(0.f, 0.f, window.getSize().x, window.getSize().y);
        return spriteBounds.intersects(screenBounds);
    }
    sf::RectangleShape shape;
private:
    float xDirection;
    float yDirection;
};

class Enemy {
public:
    Enemy(sf::Texture& texture, sf::Vector2f position) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(2.f, 2.f);
        sprite.setOrigin(sprite.getGlobalBounds().width / 4, sprite.getGlobalBounds().height / 4);
        moveInterval = rand() % 2 + 1;



        if (di == 0) {
            direction.x = rand() % 2 == 0 ? -1.f : 1.f;

        }
        else if (di == 1) {
            direction.y = rand() % 2 == 0 ? -1.f : 1.f;

        }
        else if (di == 2) {
            direction.y = rand() % 2 == 0 ? -1.f : 1.f;
            direction.x = rand() % 2 == 0 ? -1.f : 1.f;


        }
    }

    void const move(int n) {
        di = rand() % 3;
        if (di == 0) {

            if (sprite.getPosition().x < sprite.getGlobalBounds().width / 2 || sprite.getPosition().x > 780 - sprite.getGlobalBounds().width / 2) {
                if (timer.getElapsedTime().asSeconds() >= 0.8f) {

                    direction.x *= -1.f;
                    timer.restart();
                }
            }
        }
        else if (di == 1) {

            if (sprite.getPosition().y < sprite.getGlobalBounds().height / 2 || sprite.getPosition().y > 780 - sprite.getGlobalBounds().height / 2) {
                if (timer.getElapsedTime().asSeconds() >= 0.8f) {

                    direction.y *= -1.f;
                    timer.restart();
                }
            }
        }
        else {
            if (sprite.getPosition().x < sprite.getGlobalBounds().width / 2 || sprite.getPosition().x > 780 - sprite.getGlobalBounds().width / 2) {
                if (timer.getElapsedTime().asSeconds() >= 0.8f) {

                    direction.x *= -1.f;
                    timer.restart();
                }
            }
            if (sprite.getPosition().y < sprite.getGlobalBounds().height / 2 || sprite.getPosition().y > 780 - sprite.getGlobalBounds().height / 2) {
                if (timer.getElapsedTime().asSeconds() >= 0.8f) {

                    direction.y *= -1.f;
                    timer.restart();
                }
            }
        }
        if (n == 0) {
            direction.x *= 0; direction.y *= 0;
        }


        sprite.move(direction.x * speed, direction.y * speed);
        float angle = atan2(direction.x, -direction.y) * 180.f / 3.14159265f;
        sprite.setRotation(angle);

    }

    bool isOnScreen(const sf::RenderWindow& window, const sf::Sprite& sprite) {
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        sf::FloatRect screenBounds(0.f, 0.f, window.getSize().x - 10, window.getSize().y - 10);
        return spriteBounds.intersects(screenBounds);
    }
    sf::Clock timer;
    sf::Sprite sprite;
    sf::Vector2f direction;

private:
    int di = rand() % 3;
    float speed = 2.f;
    float moveInterval;
};

class Player {
public:
    Player(sf::Texture& texture, sf::Vector2f position) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(2.f, 2.f);
        sprite.setOrigin(sprite.getGlobalBounds().width / 4, sprite.getGlobalBounds().height / 4);
    }
    void move(sf::Vector2f direction) {
        sprite.move(direction);
    }
    sf::Sprite sprite;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "TaNks");
    window.setFramerateLimit(60);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("..\\assets1\\player1.png");
    Player player(playerTexture, sf::Vector2f(400, 600));

    float playerSpeed = 3;

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("..\\assets1\\enemy1.png");

    std::vector<Enemy> enemies;

    std::vector<Bullet> bullets;

    //æèçíè
    int lives = 3;
    sf::Font font;
    font.loadFromFile("..\\assets1\\arial.ttf");
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    if (lives > 0) { livesText.setString("Lives: " + std::to_string(lives)); }
    else { livesText.setString("You lose"); }
    livesText.setPosition(10.f, 10.f);

    //î÷êè
    int score = 0;
    sf::Font font1;
    font1.loadFromFile("..\\assets1\\arial.ttf");
    sf::Text scoreText;
    scoreText.setFont(font1);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(window.getSize().x - scoreText.getGlobalBounds().width - 30.f, 10.f);

    int maxEnemies = 5;

    float speed = 5.0f;

    srand(time(NULL));

    sf::Vector2f dir;
    sf::Clock timer;

    while (window.isOpen())
    {
        if (lives > 0)
        {
            livesText.setString("Lives: " + std::to_string(lives));
            scoreText.setString("Score: " + std::to_string(score));
        }
        else { livesText.setString("You lose"); }

        window.draw(livesText);
        window.draw(scoreText);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // ñòðåëüáà
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (bullets.size() < 3) { // äîáàâëÿåì îãðàíè÷åíèå íà ñêîðîñòü ñòðåëüáû
                    if (dir != sf::Vector2f(0, 0)) {
                        bullets.emplace_back(player.sprite.getPosition(), dir);
                    }
                }
            }
        }

        // äâèæåíèÿ âðàãîâ
        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].move(2);
            if (lives <= 0) { enemies[i].move(0); break; }
            if (!enemies[i].isOnScreen(window, enemies[i].sprite)) { enemies.erase(enemies.begin() + i); }

        }

        //âðàãè
        if (rand() % 1 < 1 && enemies.size() < maxEnemies)
        {
            sf::Vector2f enemyPosition(rand() % window.getSize().x, rand() % window.getSize().y);
            enemies.emplace_back(enemyTexture, enemyPosition);
        }

        // Îáðàáîòêà äâèæåíèÿ èãðîêà è íàïðàâëåíèÿ
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (player.sprite.getPosition().y >= 40) {
                player.move(speed * sf::Vector2f(0, -1));
            }
            dir = sf::Vector2f(0, -10);
            player.sprite.setRotation(0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (player.sprite.getPosition().y >= 760) {
                player.move(speed * sf::Vector2f(0, -1));
            }
            player.move(speed * sf::Vector2f(0, 1));
            dir = sf::Vector2f(0, 10);
            player.sprite.setRotation(180.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (player.sprite.getPosition().x >= 40) {
                player.move(speed * sf::Vector2f(-1, 0));
            }
            dir = sf::Vector2f(-10, 0);
            player.sprite.setRotation(270.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (player.sprite.getPosition().x <= 760) {
                player.move(speed * sf::Vector2f(1, 0));
            }
            dir = sf::Vector2f(10, 0);
            player.sprite.setRotation(90.f);
        }

        // Îáðàáîòêà äâèæåíèÿ ïóëü è ïîïàäàíèé
        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].move();

            if (bullets[i].shape.getPosition().y < 0 || !bullets[i].isOnScreen(window, bullets[i].shape))
            {
                bullets.erase(bullets.begin() + i);
                i--;
            }
            else
            {
                for (size_t j = 0; j < enemies.size(); j++)
                {
                    if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].sprite.getGlobalBounds()))
                    {
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        score += 10;
                        break;
                    }

                }
            }
        }
        for (auto& enemy : enemies) {// ñòîëêíîâåíèå âðàãà è èãðîêà
            if (enemy.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {

                if (timer.getElapsedTime().asSeconds() >= 2.f) {//3 ñåêóíäû èíâèçà

                    if (player.sprite.getPosition().x < enemy.sprite.getPosition().x) {
                        enemy.direction.x = std::abs(enemy.direction.x);
                    }
                    else {
                        enemy.direction.x = -std::abs(enemy.direction.x);
                    }

                    if (player.sprite.getPosition().y < enemy.sprite.getPosition().y) {
                        enemy.direction.y = std::abs(enemy.direction.y);
                    }
                    else {
                        enemy.direction.y = -std::abs(enemy.direction.y);
                    }

                    if (lives > 0) {
                        lives--;
                    }

                    timer.restart();
                }
            }
        }


        // Îòðèñîâêà îáúåêòîâ
        window.clear(sf::Color::Color(204, 177, 100));
        window.draw(player.sprite);
        window.draw(livesText);
        window.draw(scoreText);

        for (auto& enemy : enemies)
        {
            window.draw(enemy.sprite);
        }
        for (auto& bullet : bullets)
        {
            window.draw(bullet.shape);
        }
        window.display();
    }

    return 0;
}
