Viewed adv-01-unit-s3-interfaces.html:1-407

針對 **`adv-01-unit-s3-interfaces` (ESP32-S3 感測器介面與 PSRAM)** 單元，這是一個深入探討「硬體資源調度」與「底層記憶體管理」的課程，是實施邊緣 AI 運算的物理基礎。

以下是在 **GitHub Classroom** 部署其作業 (Assignments) 的具體建議：

### 1. 範本倉庫 (Template Repo) 配置建議
進階硬體單元的範本應模擬一個「小型作業系統」的環境，建議包含：
*   **📂 `platformio.ini`**：預置關鍵的編譯選項，如 `-DBOARD_HAS_PSRAM`，並正確設定 `memory_type`（如 `qio_opi`），確保學員能直接調用 PSRAM。
*   **📂 `src/mem_lab.cpp`**：提供一個測試框架，內含精確到微秒 ($\mu s$) 的計時器，用於測量 SRAM 與 PSRAM 的效能差異。
*   **📂 `src/roi_processor.h`**：定義影像處理結構體，將「指針運算 (Pointer Math)」邏輯留給學員補完。
*   **📂 `docs/hardware_report.md`**：預置結構化的實驗報告，用於紀錄不同時鐘頻率下的訊號表現。

---

### 2. 作業任務部署細節

#### 任務 1：PSRAM 初始化與壓力測試 (Memory Stress Test)
*   **目標**：理解 ESP32-S3 的記憶體分層架構，掌握特殊分配指令。
*   **Classroom 部署建議**：
    *   **關鍵代碼檢核**：
        ```cpp
        // 學生需實作：使用正確的 Capability 標籤申請 PSRAM
        uint8_t* buf = (uint8_t*) heap_caps_malloc(1024*1024, MALLOC_CAP_SPIRAM);
        ```
    *   **數據提交**：學員需在 `hardware_report.md` 中填入百萬次單次 1MB 的寫入時間。導師核閱其數據是否展現出「SRAM 快、PSRAM 慢」的物理特徵。

#### 任務 2：影像緩衝區管理 - ROI 提取 (Pointer Arithmetic Lab)
*   **目標**：在不複製數據的情況下，利用指針偏移技術存取影像特定區域。
*   **Classroom 部署建議**：
    *   **驗證方式**：學員需實作一個函數，計算給定 $(x, y)$ 座標後，在寬度為 640 的 RGB565 Buffer 中的指針地址。
    *   **Autograding**：撰寫一個模擬單元測試，提供一組 mock 的 Buffer 並檢核學員提取的 ROI 數值是否與預期一致。這能強化學生對「步幅 (Stride)」與「像素格式」的理解。

#### 任務 3：感測器與 PSRAM 聯動除錯 (Signal Integrity Lab)
*   **目標**：觀察高速匯流排競爭對類比訊號（影像雜訊）的影響。
*   **Classroom 部署建議**：
    *   **證據提交**：學員需將 PSRAM 設定在 80MHz (Octal SPI) 下產生的影像雜訊截圖上傳。
    *   **分析任務**：在報告中描述當 PSRAM 全速讀寫時，I2C 感測器（如陀螺儀）是否出現數據丟失或延遲現象。這能培養學員對「硬體系統級除錯」的直覺。

---

### 3. 進階硬體單元導師點評標準 (Advanced Benchmarks)
此單元的價值在於 **「對硬體物理邊界的認知」**：
*   [ ] **內存安全意識**：學員在申請大容量 Buffer 前是否檢查了 `heap_caps_get_free_size`？
*   [ ] **指針嚴謹度**：ROI 計算是否考慮了邊界對齊（Alignment）與越界檢查？
*   [ ] **資源權衡能力**：是否能解釋為什麼在某些場景下需要手動調降 PSRAM 頻率以獲得更乾淨的影像？

### 📁 推薦範本結構 (GitHub Classroom Template)：
```text
.
├── platformio.ini         # 核心硬體配置 (啟用 PSRAM 支援)
├── src/
│   ├── memory_benchmark.cpp # 壓測腳本
│   └── roi_math.h         # 指針運算邏輯實作位元
├── docs/
│   └── hardware_bench.md  # 實驗報告 (含 SRAM/PSRAM 對比數據)
└── README.md              # 系統架構心得：從 MCU 到小型電腦
```

透過這種部署方式，學生能從「單純寫程式」跨越到「**操控硬體靈魂**」的層次，這對於未來開發無人機、工業相機等複雜系統是不可或缺的深度練習。_
