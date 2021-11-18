#include "libfbc/canvas.h"

int main(int argc, char **argv)
{
    auto *c = new fbc::Canvas();
    c->init("/dev/fb0");

    auto red = c->create_color(0xff, 0, 0);
    auto green = c->create_color(0, 0xff, 0);

    c->clear(0xffffff);
    for (int i = 0; i < c->get_height(); i++)
    {
        for (int j = 0; j < c->get_width(); j++)
        {
            c->plot_pixel(j, i, i % 10 == 0 ? red : green);
        }
    }

    delete c;

    return EXIT_SUCCESS;
}