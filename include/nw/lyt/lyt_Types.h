#ifndef NW_LYT_TYPES_H_
#define NW_LYT_TYPES_H_

#include <nw/types.h>

#include <nw/math/math_Types.h>

namespace nw { namespace lyt {

const int ResourceNameStrMax = 24;
// ...
const int UserDataStrMax = 8;
// ...
const int TexMapMax = 3;

enum TextColor
{
    TEXTCOLOR_TOP,
    TEXTCOLOR_BOTTOM,
    TEXTCOLOR_MAX,

    TextColor_Top = TEXTCOLOR_TOP,
    TextColor_Bottom = TEXTCOLOR_BOTTOM,
    TextColor_MaxTextColor = TEXTCOLOR_MAX,
};

struct Size
{
    Size()
        : width(0), height(0)
    {
    }

    Size(f32 aWidth, f32 aHeight)
        : width(aWidth), height(aHeight)
    {
    }

    Size(const Size& other)
        : width(other.width), height(other.height)
    {
    }

    static Size Create(float aWidth, float aHeight)
    {
        Size size;

        size.width = aWidth;
        size.height = aHeight;

        return size;
    }

    f32 width;
    f32 height;
};

} } // namespace nw::lyt

#endif // NW_LYT_TYPES_H_
