#pragma once

class Image_container {
private:
public:

    sf::Image img_;
    // const char* name;

    Image_container()
    {}

    Image_container(const char* source) 
    {
        if (!img_.loadFromFile(source)) {
            dump(DUMP_INFO, "error: image load from source");
            ww(source);
            abort();
        }
        // name = source;
    }

    bool load(const char* source)
    {
        return img_.loadFromFile(source);
    }

    void get_pixel_array(Pixel* &ptr, int &width_px, int &height_px)
    {
        sf::Vector2u ret = img_.getSize();
        width_px  = ret.x;
        height_px = ret.y;

        ptr = (Pixel*)new char[4 * width_px * height_px];
        memcpy(ptr, img_.getPixelsPtr(), 4 * width_px * height_px);
    }



};