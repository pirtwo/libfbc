#ifndef FBC_CANVAS_H_INCLUDE
#define FBC_CANVAS_H_INCLUDE

#include <stdlib.h>
#include <stdint.h>

namespace fbc
{
    class Canvas
    {
    protected:
        int _fb_fd;
        uint32_t *_fb;

        int _fb_xres;
        int _fb_yres;
        int _fb_xoffset;
        int _fb_yoffset;
        size_t _fb_size_bytes;
        size_t _fb_size_pixel;

        uint8_t _r_pos;
        uint8_t _g_pos;
        uint8_t _b_pos;
        uint32_t _r_mask;
        uint32_t _g_mask;
        uint32_t _b_mask;

    public:
        Canvas();

        ~Canvas();

        /**
         * initializes the canvas with provided framebuffer device.
         * 
         * @param[in] fb_dev framebuffer device name, default is /dev/fb0
         * 
         * @return returns 0 in case of success or fbc::ErrorCode in case of failure.
         */
        int init(const char *fb_dev = "/dev/fb0");

        /**
         * returns canvas width in pixel.
         * 
         * @return canvas width
         */
        int get_width();

        /**
         * returns canvas height in pixel.
         * 
         * @return canvas height
         */
        int get_height();

        /**
         * paints pixel in position (x, y) with provided color.
         * 
         * @param[in] x x coordinate of pixel
         * @param[in] y y coordinate of pixel
         * @param[in] color paint color
         */
        void plot_pixel(int x, int y, uint32_t color);

        /**
         * clears the canvas with provided color.
         * 
         * @param[in] color paint color
         */
        void clear(uint32_t color);

        /**
         * creates 32bit RGB color.
         * 
         * @param[in] r 8bit red channel
         * @param[in] g 8bit green channel
         * @param[in] b 8bit blue channel
         * 
         * @return 32bit RGB color
         */
        uint32_t create_color(uint8_t r, uint8_t g, uint8_t b);

        /**
         * release canvas resources.
         */
        void release();
    };

} // namespace fbc

#endif