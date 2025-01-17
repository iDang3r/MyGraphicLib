#include "Engine_SFML.hpp"

int Engine_SFML::init()
{
    main_window_.setFramerateLimit(144);
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Andale Mono.ttf")) {
        dump(DUMP_INFO, "Font not open");
        exit(1);
    }
    dump(DUMP_INFO, "init");
    ws("INIT");
    return 0;
}

int Engine_SFML::terminate()
{
    ws("TERM");
    return 0;
}

int Engine_SFML::is_run()
{
    return main_window_.isOpen();
}

void Engine_SFML::before_rendering() 
{
    // if (!Event::hover_disable) {
    //     Event::push(Event_t(Event::CLICK, 0.89375, 0.8352));
    //     Event::push(Event_t(Event::RELEASE, 0.89375, 0.8352));
    // }

    sf::Event event;
    while (main_window_.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed: {
                main_window_.close();
                break;
            }

            case sf::Event::Resized: {
                window_width  = event.size.width;
                window_height = event.size.height;
                window_w_to_h = (double)window_width / window_height;
                angle_circle_y = angle_circle_x * window_w_to_h;

                sf::View view(sf::FloatRect(0.f, 0.f, window_width, window_height));

                // activate it
                main_window_.setView(view);

                ws("RESIZED");
                ww(window_width);
                ww(window_height);
            }

            case sf::Event::MouseMoved: {
                // if (event.mouseButton.x > window_width || event.mouseButton.y > window_height) {
                //     break;
                // }

                // std::cout << "the mouse moved" << std::endl;
                // std::cout << "mouse x: " << event.mouseMove.x << std::endl;
                // std::cout << "mouse y: " << event.mouseMove.y << std::endl;

                Point point((double)event.mouseMove.x / window_width, 1 - (double)event.mouseMove.y / window_height);
                Event_t new_event(Event::HOVERED, point.x, point.y);
                Event::push(new_event);

                new_event.id = Event::UNHOVERED;
                Event::push(new_event);

                new_event.id = Event::MOUSE_MOVE;
                Event::push(new_event);

                break;
            }
            
            case sf::Event::MouseButtonPressed: {
                
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // std::cout << "the left button was pressed" << std::endl;
                    // std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    // std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    Point point((double)event.mouseButton.x / window_width, 1 - (double)event.mouseButton.y / window_height);
                    Event_t new_event(Event::CLICK, point.x, point.y);

                    // ww(point);

                    Event::push(new_event);
                }

                break;
            }

            case sf::Event::MouseButtonReleased: {
                
                if (event.mouseButton.button == sf::Mouse::Left) {

                    Point point((double)event.mouseButton.x / window_width, 1 - (double)event.mouseButton.y / window_height);
                    Event_t new_event(Event::RELEASE, point.x, point.y);

                    Event::push(new_event);
                }

                break;
            }


            case sf::Event::KeyPressed: {

                if (event.key.code == sf::Keyboard::Up) {
                    Event::push(Event_t(Event::BUTTON_UP));
                }

                if (event.key.code == sf::Keyboard::Down) {
                    Event::push(Event_t(Event::BUTTON_DOWN));
                }

                if (event.key.code == sf::Keyboard::Left) {
                    Event::push(Event_t(Event::BUTTON_LEFT));
                }

                if (event.key.code == sf::Keyboard::Right) {
                    Event::push(Event_t(Event::BUTTON_RIGHT));
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    Event::push(Event_t(Event::BUTTON_ENTER));
                }

                if (event.key.code == sf::Keyboard::Escape) {
                    Event::push(Event_t(Event::BUTTON_ESCAPE));
                }

                if (event.key.code == sf::Keyboard::BackSpace) {
                    Event::push(Event_t(Event::BUTTON_BACKSPACE));
                }

                break;
            }

            case sf::Event::TextEntered: {

                if (event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    if (c < 32) { // including ASCII backspace and other rubbish
                        break;
                    }
                    Event::push(Event_t(Event::BUTTON_LETTER, c));
                    // std::cout << "ASCII character typed: " << c << std::endl;
                }

                break;
            }

            default: {
                // Not got sf::Events
            }
            

        }
        
    }
    main_window_.clear(sf(COLORS::main_background));
}

void Engine_SFML::after_rendering() 
{
    if (!frame_cx) {
        Framerate = 1.0 / clock.getElapsedTime().asSeconds();
    }
    clock.restart();
    frame_cx++;
    draw_text(Point(0.0, 0.95), 0.1, 0.05, ("FPS: " + std::to_string(Framerate)).c_str());
    // ww(Framerate);

    main_window_.display();
}

sf::Vector2f Engine_SFML::sf(Point point)
{
    return sf::Vector2f(window_width * point.x, window_height * (1 - point.y));
}

sf::Color Engine_SFML::sf(const Color &color)
{
    return sf::Color   (static_cast<uint8_t>(color.r * 255),
                        static_cast<uint8_t>(color.g * 255),
                        static_cast<uint8_t>(color.b * 255),
                        static_cast<uint8_t>(color.a * 255));
}

Point Engine_SFML::get_mouse_pos()
{
    sf::Vector2i ret = sf::Mouse::getPosition(main_window_);
    return Point((double)ret.x / window_width, 1 - (double)ret.y / window_height);
}

void Engine_SFML::draw_rectangle(Point start, double width, double height, const Color &color)
{
    start.y += height;

    sf::RectangleShape rect(sf::Vector2f(width * window_width, height * window_height));
    rect.setFillColor(sf(color));
    rect.setPosition(sf(start));
    main_window_.draw(rect);
}

void Engine_SFML::draw_square(Point start, double width, const Color &color) 
{   // MAYBE NOT WORKS
    dump(DUMP_INFO, "NOT CORRECT IMPLEMENTATION");
    abort();
    double height = width * window_w_to_h;
    draw_rectangle(start, width, height, color);
}

void Engine_SFML::draw_circle(Point start, double radius, const Color &color) 
{
    start.y += radius * window_w_to_h;
    start.x -= radius;
    sf::CircleShape circle(radius * window_width);
    circle.setPosition(sf(start));
    circle.setFillColor(sf(color));
    main_window_.draw(circle);
}

void Engine_SFML::draw_text(const Point &start_, double width, double height, const char* str, int font_size, int length)
{
    if (str == NULL) {
        return;
    }
    
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(font_size);
    text.setFillColor(sf::Color::Black);
    text.setPosition((start_.x + width / 2) * window_width - text.getLocalBounds().width / 2.0, (1 - (start_.y + height / 2)) * window_height - font_size * 0.6);
    main_window_.draw(text);
}

void Engine_SFML::draw_text_lefty(const Point &start_, double width, double height, const char* str, int font_size, int length)
{
    if (str == NULL) {
        return;
    }
    
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(font_size);
    text.setFillColor(sf::Color::Black);
    text.setPosition(start_.x * window_width, (1 - (start_.y + height / 2)) * window_height - font_size * 0.6);
    main_window_.draw(text);
}

void Engine_SFML::draw_image_by_pixel_array(Point start, double width, double height, const Pixel_array &pix_arr, Visible_part vis_part)
{
    start.y += height;
    int width_px  = width  * window_width;
    int height_px = height * window_height;

    if (vis_part.x + vis_part.width > pix_arr.width) {
        vis_part.width = pix_arr.width - vis_part.x;
    }

    if (vis_part.y + vis_part.height > pix_arr.height) {
        vis_part.height = pix_arr.height - vis_part.y;
    }

    sf::Texture texture;
    texture.create(pix_arr.width,  pix_arr.height);
    texture.update((const sf::Uint8*)pix_arr.start, pix_arr.width,  pix_arr.height, 0, 0);

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(vis_part.x, vis_part.y, vis_part.width, vis_part.height));

    double k = 0;
    if (sprite.getGlobalBounds().width / width > sprite.getGlobalBounds().height / height) {
        k = (double)width_px / sprite.getGlobalBounds().width;
    } else {
        k = (double)height_px / sprite.getGlobalBounds().height;
    }

    sprite.setPosition(sf(start));
    sprite.setScale(k, k);

    main_window_.draw(sprite);
}

sf::RenderWindow Engine_SFML::main_window_(sf::VideoMode(window_width, window_height), "by DED_32");
sf::Font         Engine_SFML::font;
sf::Clock        Engine_SFML::clock;
float            Engine_SFML::Framerate = 0.0f;
uint8_t          Engine_SFML::frame_cx = 0;