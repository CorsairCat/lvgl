/**
 * @file lv_canvas.h
 *
 */

#ifndef LV_CANVAS_H
#define LV_CANVAS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if LV_USE_CANVAS != 0

#include "../image/lv_image.h"
#include "../../draw/lv_draw_image.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_canvas_class;

/*Data of canvas*/
typedef struct {
    lv_image_t img;
    lv_image_dsc_t dsc;
    const void * buf_unaligned;
} lv_canvas_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a canvas object
 * @param parent     pointer to an object, it will be the parent of the new canvas
 * @return           pointer to the created canvas
 */
lv_obj_t * lv_canvas_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a buffer for the canvas.
 * @param buf a buffer where the content of the canvas will be.
 * The required size is (lv_image_color_format_get_px_size(cf) * w) / 8 * h)
 * It can be allocated with `lv_malloc()` or
 * it can be statically allocated array (e.g. static lv_color_t buf[100*50]) or
 * it can be an address in RAM or external SRAM
 * @param canvas pointer to a canvas object
 * @param w width of the canvas
 * @param h height of the canvas
 * @param cf color format. `LV_IMAGE_CF_...`
 */
void lv_canvas_set_buffer(lv_obj_t * canvas, void * buf, int32_t w, int32_t h, lv_color_format_t cf);

void lv_canvas_set_px(lv_obj_t * obj, int32_t x, int32_t y, lv_color_t color, lv_opa_t opa);

/**
 * Set the palette color of a canvas with index format. Valid only for `LV_IMAGE_CF_INDEXED1/2/4/8`
 * @param canvas pointer to canvas object
 * @param id the palette color to set:
 *   - for `LV_IMAGE_CF_INDEXED1`: 0..1
 *   - for `LV_IMAGE_CF_INDEXED2`: 0..3
 *   - for `LV_IMAGE_CF_INDEXED4`: 0..15
 *   - for `LV_IMAGE_CF_INDEXED8`: 0..255
 * @param c the color to set
 */
void lv_canvas_set_palette(lv_obj_t * canvas, uint8_t id, lv_color32_t c);

/*=====================
 * Getter functions
 *====================*/

lv_color32_t lv_canvas_get_px(lv_obj_t * obj, int32_t x, int32_t y);

/**
 * Get the image of the canvas as a pointer to an `lv_image_dsc_t` variable.
 * @param canvas pointer to a canvas object
 * @return pointer to the image descriptor.
 */
lv_image_dsc_t * lv_canvas_get_image(lv_obj_t * canvas);

/**
 * Return the pointer for the buffer.
 * It's recommended to use this function instead of the buffer form the
 * return value of lv_canvas_get_image() as is can be aligned
 * @param canvas    pointer to a canvas object
 * @return          pointer to the buffer
 */
const void * lv_canvas_get_buf(lv_obj_t * canvas);

/*=====================
 * Other functions
 *====================*/

/**
 * Copy a buffer to the canvas
 * @param canvas pointer to a canvas object
 * @param to_copy buffer to copy. The color format has to match with the canvas's buffer color
 * format
 * @param x left side of the destination position
 * @param y top side of the destination position
 * @param w width of the buffer to copy
 * @param h height of the buffer to copy
 */
void lv_canvas_copy_buf(lv_obj_t * canvas, const void * to_copy, int32_t x, int32_t y, int32_t w,
                        int32_t h);
/**
 * Fill the canvas with color
 * @param canvas pointer to a canvas
 * @param color the background color
 * @param opa the desired opacity
 */
void lv_canvas_fill_bg(lv_obj_t * obj, lv_color_t color, lv_opa_t opa);

void lv_canvas_init_layer(lv_obj_t * canvas, lv_layer_t * layer);

void lv_canvas_finish_layer(lv_obj_t * canvas, lv_layer_t * layer);

/**********************
 *      MACROS
 **********************/

#define LV_CANVAS_BUF_SIZE(w, h, bpp, stride) (((((w * bpp + 7) >> 3) + stride - 1) & ~(stride - 1)) * h + LV_DRAW_BUF_ALIGN)

#endif /*LV_USE_CANVAS*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_CANVAS_H*/
