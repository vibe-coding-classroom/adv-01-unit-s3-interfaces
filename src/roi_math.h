#ifndef ROI_MATH_H
#define ROI_MATH_H

#include <stdint.h>

/**
 * @brief Pointer Arithmetic Lab: ROI Extraction
 * Students will implement the logic to calculate pointers for specific regions of interest.
 */

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t bytes_per_pixel; // e.g., 2 for RGB565, 3 for RGB888
    uint8_t* data;
} ImageBuffer;

/**
 * @brief Get the pointer to a specific pixel (x, y)
 * @param img Pointer to the image buffer structure
 * @param x X coordinate
 * @param y Y coordinate
 * @return Pointer to the pixel data
 */
inline uint8_t* get_pixel_ptr(ImageBuffer* img, uint16_t x, uint16_t y) {
    // TASK 2: Implement pointer arithmetic here
    // Hint: address = base_address + (y * width + x) * bytes_per_pixel
    return nullptr; // Placeholder
}

/**
 * @brief Extract a Region of Interest (ROI)
 * This doesn't copy data, just returns the starting pointer.
 */
typedef struct {
    uint8_t* start_ptr;
    uint16_t roi_width;
    uint16_t roi_height;
    uint16_t stride; // Distance between the start of one row and the start of the next
} ROI;

#endif // ROI_MATH_H
