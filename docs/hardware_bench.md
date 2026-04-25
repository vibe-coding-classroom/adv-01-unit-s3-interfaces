# ESP32-S3 Hardware Interface Benchmark Report

## 1. Environment Configuration
- **Board:** ESP32-S3 DevKitC-1
- **PSRAM Type:** Octal SPI (OPI)
- **Clock Frequency:** 240 MHz
- **Build Flags:** `-DBOARD_HAS_PSRAM`, `-mfix-esp32-psram-cache-issue`

## 2. Memory Stress Test (Task 1)
| Memory Type | Write Time (us) | Read Time (us) | Allocation Method |
|-------------|-----------------|----------------|-------------------|
| Internal SRAM | | | `MALLOC_CAP_INTERNAL` |
| External PSRAM | | | `MALLOC_CAP_SPIRAM` |

**Analysis:**
- How much slower is the PSRAM compared to SRAM?
- Why do we use PSRAM for image buffers instead of internal SRAM?

## 3. ROI Pointer Math (Task 2)
- **Logic Explanation:** Describe how you calculated the memory address for a pixel `(x, y)` in a linear buffer.
- **Alignment:** Did you encounter any issues with 4-byte or 8-byte alignment when accessing memory?

## 4. Signal Integrity (Task 3)
- **PSRAM Frequency:** 80 MHz / 40 MHz
- **Observation:** Describe any noise or glitches observed in sensor data or image streams when PSRAM is under high load.
- **Evidence:** [Insert screenshot or data log here]

## 5. Conclusion
- What are the physical boundaries of the ESP32-S3 that you discovered in this lab?
