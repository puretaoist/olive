# Olive++ — 一个轻量级 C++ 软件光栅化图形库

> 从 Tsoding 的 [olive.c](https://github.com/tsoding/olive.c) 移植并扩展的 C++ 实现，用于学习和实验像素级图形绘制。

## 特性

- 纯 C++17，无外部依赖（如需 PNG 支持，可选用 `stb_image_write.h`）
- 基于 `std::vector` 的现代内存管理，无需手动 `malloc/free`
- 目前支持绘制基本图形：
  - 填充矩形（`olive_fill_rect`）
  - 直线（`olive_draw_line`，采用抗隙缝扫描算法）
  - 实心圆（`olive_fill_circle`）
  - 实心三角形（`olive_fill_triangle`，扫描线填充）
- 导出为 PPM 格式（纯文本/二进制），便于调试
- 可选支持 WebAssembly（需 Emscripten），可在浏览器中运行
- 与 VS Code 深度集成，一键构建运行（`Ctrl+Shift+B`）并支持调试（`F5`）

## 快速开始

### 环境要求

- C++17 编译器（GCC、Clang 或 MSVC）
- （可选）Emscripten SDK 用于 WASM 编译

### 构建与运行

1. 克隆仓库：
   ```bash
   git clone https://github.com/your-username/olivepp.git
   cd olivepp