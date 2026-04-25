#include <unity.h>
#include "roi_math.h"

void test_roi_origin() {
    uint8_t mock_data[100];
    ImageBuffer img = {
        .width = 10,
        .height = 10,
        .bytes_per_pixel = 1,
        .data = mock_data
    };

    uint8_t* ptr = get_pixel_ptr(&img, 0, 0);
    TEST_ASSERT_EQUAL_PTR(mock_data, ptr);
}

void test_roi_offset_rgb565() {
    uint8_t mock_data[640 * 480 * 2];
    ImageBuffer img = {
        .width = 640,
        .height = 480,
        .bytes_per_pixel = 2, // RGB565
        .data = mock_data
    };

    uint16_t target_x = 100;
    uint16_t target_y = 50;
    
    // Expected: base + (y * width + x) * bpp
    uint8_t* expected_ptr = mock_data + (50 * 640 + 100) * 2;
    uint8_t* actual_ptr = get_pixel_ptr(&img, target_x, target_y);
    
    TEST_ASSERT_EQUAL_PTR(expected_ptr, actual_ptr);
}

void test_roi_boundary() {
    uint8_t mock_data[100];
    ImageBuffer img = {
        .width = 10,
        .height = 10,
        .bytes_per_pixel = 1,
        .data = mock_data
    };

    uint8_t* ptr = get_pixel_ptr(&img, 9, 9);
    uint8_t* expected_ptr = mock_data + 99;
    
    TEST_ASSERT_EQUAL_PTR(expected_ptr, ptr);
}

void setup() {
    delay(2000); // Wait for serial monitor
    UNITY_BEGIN();
    RUN_TEST(test_roi_origin);
    RUN_TEST(test_roi_offset_rgb565);
    RUN_TEST(test_roi_boundary);
    UNITY_END();
}

void loop() {
    // Nothing to do
}
