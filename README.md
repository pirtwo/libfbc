# libfbc (Framebuffer Canvas)

This library offers a canvas facade for linux framebuffer and makes drawing more convenient.

## usage

```
#include "libfbc/canvas.h"

int main(int argc, char **argv)
{
    auto *c = new fbc::Canvas();
    c->init("/dev/fb0");

    auto red = c->create_color(0xff, 0, 0);
    auto green = c->create_color(0, 0xff, 0);

    c->clear(0xffffff);
    for (int y = 0; y < c->get_height(); i++)
    {
        for (int x = 0; x < c->get_width(); j++)
        {
            c->plot_pixel(x, y, y % 10 == 0 ? red : green);
        }
    }

    delete c;

    return EXIT_SUCCESS;
}
```

## build

```
$: ~/libfbc/make
```
