#include <Arduino.h>

/**
 * @brief Memory Benchmark for ESP32-S3
 * This lab compares the performance of internal SRAM and external PSRAM.
 * Students will use this to understand the hardware physical boundaries.
 */

void run_benchmark(const char* label, uint8_t* buffer, size_t size) {
    if (!buffer) {
        Serial.printf("%s: Allocation Failed!\n", label);
        return;
    }

    uint32_t start_time = micros();
    
    // Perform a million write operations (or proportional to size)
    // Here we fill the buffer and read it back
    for (size_t i = 0; i < size; i++) {
        buffer[i] = (uint8_t)(i & 0xFF);
    }
    
    uint32_t write_time = micros() - start_time;
    
    start_time = micros();
    volatile uint8_t sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += buffer[i];
    }
    uint32_t read_time = micros() - start_time;

    Serial.printf("--- %s Benchmark ---\n", label);
    Serial.printf("Size: %d bytes\n", size);
    Serial.printf("Write Time: %u us\n", write_time);
    Serial.printf("Read Time: %u us\n", read_time);
    Serial.printf("----------------------\n\n");
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    Serial.println("ESP32-S3 Interface Lab: Memory Benchmarking");
    
    // 1. Check PSRAM Status
    if (psramInit()) {
        Serial.printf("PSRAM Initialized. Total size: %d bytes\n", ESP.getPsramSize());
    } else {
        Serial.println("PSRAM Initialization Failed! Check build flags.");
    }

    const size_t test_size = 1024 * 100; // 100KB test

    // 2. SRAM Allocation
    uint8_t* sram_buf = (uint8_t*) heap_caps_malloc(test_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    run_benchmark("Internal SRAM", sram_buf, test_size);
    heap_caps_free(sram_buf);

    // 3. PSRAM Allocation (Task 1)
    // Students: Use heap_caps_malloc with MALLOC_CAP_SPIRAM to allocate 1MB if possible
    uint8_t* psram_buf = (uint8_t*) heap_caps_malloc(test_size, MALLOC_CAP_SPIRAM);
    run_benchmark("External PSRAM", psram_buf, test_size);
    heap_caps_free(psram_buf);
}

void loop() {
    delay(1000);
}
