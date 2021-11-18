#ifndef FBC_ERRORS_H_INCLUDE
#define FBC_ERRORS_H_INCLUDE

#include <stdint.h>
#include <exception>

namespace fbc
{
    enum ErrorCode : int32_t
    {
        SUCCESS = 0,
        ERR_OPEN_FB,
        ERR_OPEN_TTY,
        ERR_IOTCL_FB,
        ERR_MMAP_FB,
        ERR_FB_UNSUPPORTED_VIDEO_MODE,
        ERR_FB_UNSUPPORTED_COLOR_MODE
    };

    class Exception : public std::exception
    {
    protected:
        int32_t _code;

    public:
        Exception(int32_t code)
        {
            _code = code;
        }

        virtual int32_t error_code() const
        {
            return _code;
        }
    };
} // namespace fbc

#endif