#include "graphics.h"
#include <string.h>
// inline-функции.
#include "graphics_inlines.h"

// ютф8!

err_t graphics_init(graphics_t* graphics, uint8_t* data, graphics_size_t width, graphics_size_t height, graphics_format_t format)
{
    if(data == NULL) return E_NULL_POINTER;

    graphics->data = data;
    graphics->width = width;
    graphics->height = height;
    graphics->format = format;

    return E_NO_ERROR;
}

size_t graphics_data_size(const graphics_t* graphics)
{
    size_t size = graphics->width * graphics->height;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
#endif
#if defined(USE_GRAPHICS_FORMAT_BW_1_V) || defined(USE_GRAPHICS_FORMAT_BW_1_H)
            size >>= 3;
            break;
#endif

#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
#endif
#if defined(USE_GRAPHICS_FORMAT_GRAY_2_V) || defined(USE_GRAPHICS_FORMAT_GRAY_2_H)\
                                          || defined(USE_GRAPHICS_FORMAT_GRAY_2_VFD)
            size >>= 2;
            break;
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
#endif
#if defined(USE_GRAPHICS_FORMAT_RGB_121_V) || defined(USE_GRAPHICS_FORMAT_RGB_121_H)
            size >>= 1;
            break;
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            break;
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            size <<= 1;
            break;
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            size = (size << 1) + size;
            break;
#endif
    }

    return size;
}

void graphics_clear(graphics_t* graphics)
{
    if(graphics->data == NULL) return;

    memset(graphics->data, 0x0, graphics_data_size(graphics));
}

void graphics_fill(graphics_t* graphics, uint8_t mask)
{
    if(graphics->data == NULL) return;

    memset(graphics->data, mask, graphics_data_size(graphics));
}

bool graphics_get_pixel_pos(const graphics_t* graphics, graphics_pos_t x, graphics_pos_t y, graphics_size_t* byte, graphics_size_t* bit)
{
    if(x < 0 || y < 0) return false;
    if(x >= graphics->width || y >= graphics->height) return false;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
            graphics_bw_1_v_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
            graphics_bw_1_h_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
            graphics_gray_2_v_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
            graphics_gray_2_h_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
            graphics_gray_2_vfd_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
            graphics_rgb_121_v_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
            graphics_rgb_121_h_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            graphics_rgb_332_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            graphics_rgb_565_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            graphics_rgb_8_get_pixel_pos(graphics, x, y, byte, bit);
            break;
#endif
    }
    return true;
}

graphics_color_t graphics_get_pixel(const graphics_t* graphics, graphics_pos_t x, graphics_pos_t y)
{
    if(x < 0 || y < 0) return 0;
    if(x >= graphics->width || y >= graphics->height) return 0;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
            return graphics_bw_1_v_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
            return graphics_bw_1_h_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
            return graphics_gray_2_v_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
            return graphics_gray_2_h_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
            return graphics_gray_2_vfd_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
            return graphics_rgb_121_v_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
            return graphics_rgb_121_h_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            return graphics_rgb_332_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            return graphics_rgb_565_get_pixel(graphics, x, y);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            return graphics_rgb_8_get_pixel(graphics, x, y);
#endif
    }

    return 0;
}

bool graphics_set_pixel(graphics_t* graphics, graphics_pos_t x, graphics_pos_t y, graphics_color_t color)
{
    if(x < 0 || y < 0) return false;
    if(x >= graphics->width || y >= graphics->height) return false;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
            graphics_bw_1_v_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
            graphics_bw_1_h_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
            graphics_gray_2_v_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
            graphics_gray_2_h_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
            graphics_gray_2_vfd_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
            graphics_rgb_121_v_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
            graphics_rgb_121_h_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            graphics_rgb_332_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            graphics_rgb_565_set_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            graphics_rgb_8_set_pixel(graphics, x, y, color);
            break;
#endif
    }
    return true;
}

bool graphics_or_pixel(graphics_t* graphics, graphics_pos_t x, graphics_pos_t y, graphics_color_t color)
{
    if(x < 0 || y < 0) return false;
    if(x >= graphics->width || y >= graphics->height) return false;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
            graphics_bw_1_v_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
            graphics_bw_1_h_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
            graphics_gray_2_v_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
            graphics_gray_2_h_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
            graphics_gray_2_vfd_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
            graphics_rgb_121_v_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
            graphics_rgb_121_h_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            graphics_rgb_332_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            graphics_rgb_565_or_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            graphics_rgb_8_or_pixel(graphics, x, y, color);
            break;
#endif
    }
    return true;
}

bool graphics_xor_pixel(graphics_t* graphics, graphics_pos_t x, graphics_pos_t y, graphics_color_t color)
{
    if(x < 0 || y < 0) return false;
    if(x >= graphics->width || y >= graphics->height) return false;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
            graphics_bw_1_v_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
            graphics_bw_1_h_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
            graphics_gray_2_v_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
            graphics_gray_2_h_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
            graphics_gray_2_vfd_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
            graphics_rgb_121_v_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
            graphics_rgb_121_h_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            graphics_rgb_332_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            graphics_rgb_565_xor_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            graphics_rgb_8_xor_pixel(graphics, x, y, color);
            break;
#endif
    }
    return true;
}

bool graphics_and_pixel(graphics_t* graphics, graphics_pos_t x, graphics_pos_t y, graphics_color_t color)
{
    if(x < 0 || y < 0) return false;
    if(x >= graphics->width || y >= graphics->height) return false;

    switch(graphics->format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
            graphics_bw_1_v_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
            graphics_bw_1_h_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
            graphics_gray_2_v_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
            graphics_gray_2_h_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
            graphics_gray_2_vfd_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
            graphics_rgb_121_v_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
            graphics_rgb_121_h_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            graphics_rgb_332_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            graphics_rgb_565_and_pixel(graphics, x, y, color);
            break;
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            graphics_rgb_8_and_pixel(graphics, x, y, color);
            break;
#endif
    }
    return true;
}

graphics_color_t graphics_convert_color(graphics_format_t to_format, graphics_format_t from_format, graphics_color_t color)
{
    if(to_format == from_format) return color;

    switch(to_format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
#endif
#if defined(USE_GRAPHICS_FORMAT_BW_1_V) || defined(USE_GRAPHICS_FORMAT_BW_1_H)
            return graphics_bw_1_color_from(from_format, color);
#endif

#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
#endif
#if defined(USE_GRAPHICS_FORMAT_GRAY_2_V) || defined(USE_GRAPHICS_FORMAT_GRAY_2_H)\
                                          || defined(USE_GRAPHICS_FORMAT_GRAY_2_VFD)
            return graphics_gray_2_color_from(from_format, color);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
#endif
#if defined(USE_GRAPHICS_FORMAT_RGB_121_V) || defined(USE_GRAPHICS_FORMAT_RGB_121_H)
            return graphics_rgb_121_color_from(from_format, color);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            return graphics_rgb_332_color_from(from_format, color);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            return graphics_rgb_565_color_from(from_format, color);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            return graphics_rgb_8_color_from(from_format, color);
#endif
    }

    return 0;
}

graphics_color_t graphics_apply_mask(graphics_format_t color_format, graphics_color_t color, graphics_format_t mask_format, graphics_color_t mask)
{
    if(color == 0 || mask == 0) return 0;

    switch(color_format){
#ifdef USE_GRAPHICS_FORMAT_BW_1_V
        case GRAPHICS_FORMAT_BW_1_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_BW_1_H
        case GRAPHICS_FORMAT_BW_1_H:
#endif
#if defined(USE_GRAPHICS_FORMAT_BW_1_V) || defined(USE_GRAPHICS_FORMAT_BW_1_H)
            return graphics_bw_1_apply_mask(color, mask_format, mask);
#endif

#ifdef USE_GRAPHICS_FORMAT_GRAY_2_V
        case GRAPHICS_FORMAT_GRAY_2_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_H
        case GRAPHICS_FORMAT_GRAY_2_H:
#endif
#ifdef USE_GRAPHICS_FORMAT_GRAY_2_VFD
        case GRAPHICS_FORMAT_GRAY_2_VFD:
#endif
#if defined(USE_GRAPHICS_FORMAT_GRAY_2_V) || defined(USE_GRAPHICS_FORMAT_GRAY_2_H)\
                                          || defined(USE_GRAPHICS_FORMAT_GRAY_2_VFD)
            return graphics_gray_2_apply_mask(color, mask_format, mask);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_121_V
        case GRAPHICS_FORMAT_RGB_121_V:
#endif
#ifdef USE_GRAPHICS_FORMAT_RGB_121_H
        case GRAPHICS_FORMAT_RGB_121_H:
#endif
#if defined(USE_GRAPHICS_FORMAT_RGB_121_V) || defined(USE_GRAPHICS_FORMAT_RGB_121_H)
            return graphics_rgb_121_apply_mask(color, mask_format, mask);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_332
        case GRAPHICS_FORMAT_RGB_332:
            return graphics_rgb_332_apply_mask(color, mask_format, mask);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_565
        case GRAPHICS_FORMAT_RGB_565:
            return graphics_rgb_565_apply_mask(color, mask_format, mask);
#endif

#ifdef USE_GRAPHICS_FORMAT_RGB_8
        case GRAPHICS_FORMAT_RGB_8:
            return graphics_rgb_8_apply_mask(color, mask_format, mask);
#endif
    }

    return color;
}