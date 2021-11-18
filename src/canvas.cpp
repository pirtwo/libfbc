#include "libfbc/canvas.h"
#include "libfbc/errors.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

using namespace fbc;

Canvas::Canvas()
{
    _fb_fd = -1;
    _fb = nullptr;
}

Canvas::~Canvas()
{
    if (_fb != nullptr)
        munmap(_fb, _fb_size_bytes);

    if (_fb_fd != -1)
        close(_fb_fd);
}

int Canvas::init(const char *fb_dev)
{
    try
    {
        fb_var_screeninfo fb_vsi;
        fb_fix_screeninfo fb_fsi;

        _fb_fd = open(fb_dev, O_RDWR);
        if (_fb_fd < 0)
            throw Exception(ErrorCode::ERR_OPEN_FB);

        if (ioctl(_fb_fd, FBIOGET_VSCREENINFO, &fb_vsi) < 0)
            throw Exception(ErrorCode::ERR_IOTCL_FB);
        if (ioctl(_fb_fd, FBIOGET_FSCREENINFO, &fb_fsi) < 0)
            throw Exception(ErrorCode::ERR_IOTCL_FB);
        if (fb_vsi.bits_per_pixel != 32)
            throw Exception(ErrorCode::ERR_FB_UNSUPPORTED_VIDEO_MODE);
        if (fb_vsi.red.msb_right | fb_vsi.green.msb_right | fb_vsi.blue.msb_right)
            throw Exception(ErrorCode::ERR_FB_UNSUPPORTED_COLOR_MODE);

        _fb_xres = fb_vsi.xres;
        _fb_yres = fb_vsi.yres;
        _fb_xoffset = fb_vsi.xoffset;
        _fb_yoffset = fb_vsi.yoffset;
        _r_pos = fb_vsi.red.offset;
        _g_pos = fb_vsi.green.offset;
        _b_pos = fb_vsi.blue.offset;
        _r_mask = ((1 << fb_vsi.red.length) - 1) << _r_pos;
        _g_mask = ((1 << fb_vsi.green.length) - 1) << _g_pos;
        _b_mask = ((1 << fb_vsi.blue.length) - 1) << _b_pos;
        _fb_size_bytes = _fb_yres * fb_fsi.line_length;
        _fb_size_pixel = _fb_xres * _fb_yres;

        _fb = (uint32_t *)mmap(
            nullptr, _fb_size_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, _fb_fd, 0);
        if (_fb == MAP_FAILED)
            throw Exception(ErrorCode::ERR_MMAP_FB);

        return 0;
    }
    catch (const Exception &e)
    {
        release();
        return e.error_code();
    }
}

int Canvas::get_width()
{
    return _fb_xres;
}

int Canvas::get_height()
{
    return _fb_yres;
}

void Canvas::plot_pixel(int x, int y, uint32_t color)
{
    x += _fb_xoffset;
    y += _fb_yoffset;

    if (x < 0 || x > _fb_xres || y < 0 || y > _fb_yres)
        return;

    _fb[y * _fb_xres + x] = color;
}

void Canvas::clear(uint32_t color)
{
    for (size_t i = 0; i < _fb_size_pixel; i++)
    {
        _fb[i] = color;
    }
}

uint32_t Canvas::create_color(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r << _r_pos) & _r_mask) |
           ((g << _g_pos) & _g_mask) |
           ((b << _b_pos) & _b_mask);
}

void Canvas::release()
{
    if (_fb != nullptr)
        munmap(_fb, _fb_size_bytes);

    if (_fb_fd != -1)
        close(_fb_fd);

    _fb_fd = -1;
    _fb = nullptr;
}
