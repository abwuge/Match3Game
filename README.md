# Match3Game

一个基于 SFML 3.0 开发的现代化三消益智游戏，采用 C++17 标准实现。

## 项目简介

Match3Game 是一款经典的三消类游戏，玩家通过拖拽或点击交换相邻的彩色方块，使三个或更多相同颜色的方块连成一线即可消除。游戏具有流畅的动画效果和完善的场景管理系统。

### 核心特性

- ✅ **流畅动画** - 平滑的交换、下落、消除动画
- ✅ **直观交互** - 支持鼠标拖拽和点击操作
- ✅ **自动消除** - 智能检测并自动消除匹配方块
- ✅ **重力系统** - 方块自动下落填充空位
- ✅ **场景管理** - 主菜单、游戏场景、设置界面
- ✅ **可配置参数** - 灵活的网格大小和颜色配置
- ✅ **圆角美化** - 现代化的圆角矩形渲染
- ✅ **快捷键支持** - 完整的键盘操作支持

### 技术栈

- **语言**: C++17
- **图形库**: SFML 3.0.2
- **构建工具**: CMake 3.28+
- **编译器**: MinGW (GCC/G++)

### 项目结构

```
Match3Game/
├── include/          # 头文件
│   ├── core/        # 核心系统（场景管理、游戏逻辑）
│   ├── ui/          # UI组件（按钮、游戏板、菜单）
│   └── utils/       # 工具类（配置、颜色管理、圆角矩形）
├── src/             # 源文件
│   ├── main.cpp     # 程序入口
│   ├── core/
│   ├── ui/
│   └── utils/
├── docs/            # 项目文档
└── build/           # 构建输出目录
```

## 开发环境搭建

### 前置要求

1. **CMake** 3.28 或更高版本
   - 下载地址: https://cmake.org/download/
   
2. **MinGW** (推荐 MinGW-w64)
   - 下载地址: https://www.mingw-w64.org/
   - 确保 `gcc`、`g++` 和 `mingw32-make` 在系统 PATH 中

3. **Git** (用于克隆项目和下载依赖)
   - 下载地址: https://git-scm.com/downloads

4. **Visual Studio Code** (推荐)
   - 安装 C/C++ 扩展
   - 安装 CMake Tools 扩展

### 环境配置步骤

#### Windows 环境

1. **克隆项目**
   ```powershell
   git clone <repository-url>
   cd Match3Game
   ```

2. **配置 CMake**
   ```powershell
   cmake -S . -B build -G "MinGW Makefiles"
   ```

3. **构建项目**
   
   Debug 版本（推荐开发时使用）:
   ```powershell
   cmake --build build --config Debug -- -j
   ```
   
   Release 版本（性能优化）:
   ```powershell
   cmake --build build --config Release -- -j
   ```

4. **运行程序**
   ```powershell
   .\build\bin\Match3Game.exe
   ```

#### Linux 环境

1. **安装依赖**
   ```bash
   sudo apt update
   sudo apt install build-essential cmake git \
       libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
       libfreetype-dev libflac-dev libvorbis-dev \
       libgl1-mesa-dev libegl1-mesa-dev
   ```

2. **构建和运行**
   ```bash
   git clone https://github.com/abwuge/Match3Game.git
   cd Match3Game
   cmake -B build
   cmake --build build
   ./build/bin/Match3Game
   ```

### 使用 VS Code

1. 打开项目文件夹
2. CMake 扩展会自动检测配置
3. 使用底部状态栏的按钮：
   - **Configure** - 配置 CMake
   - **Build** - 构建项目
   - **Run** - 运行程序

或使用预配置的任务：
- `Ctrl+Shift+P` → `Tasks: Run Task`
- 选择 `Build Debug` 或 `Build Release`

## 使用说明

### 游戏操作

- **鼠标拖拽**: 按住方块并拖动到相邻位置
- **鼠标点击**: 点击两个相邻方块进行交换
- **ESC 键**: 返回主菜单或退出游戏
- **空格键**: 暂停/继续游戏（开发中）

### 游戏规则

1. 交换相邻的方块使得三个或更多相同颜色连成直线
2. 匹配的方块会被消除
3. 上方的方块会自动下落填充空位
4. 如果交换后无法形成匹配，方块会自动恢复原位

### 配置参数

可在 `include/utils/GameConfig.h` 中修改游戏参数：

- `GRID_SIZE`: 游戏网格大小（默认 8×8）
- `NUM_COLORS`: 方块颜色数量（默认 6 种）
- `TILE_SIZE`: 方块尺寸
- `ANIMATION_SPEED`: 动画速度

## 项目文档

详细的技术文档请查看 `docs` 目录：

- **[完整项目文档](docs/PROJECT_DOCUMENTATION.md)** - 详细的系统架构和模块说明
- **[架构图集](docs/ARCHITECTURE_DIAGRAMS.md)** - 系统架构图、类图、流程图
- **[API 参考](docs/API_REFERENCE.md)** - 完整的 API 文档

## 构建选项

### 更改构建类型

Debug 模式（包含调试符号）:
```powershell
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

Release 模式（性能优化）:
```powershell
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

### 清理构建

```powershell
Remove-Item -Recurse -Force build
cmake -S . -B build -G "MinGW Makefiles"
```

## 依赖管理

项目使用 CMake 的 **FetchContent** 自动管理依赖：

- SFML 3.0.2 会在首次构建时自动下载和编译
- 无需手动安装 SFML
- 确保网络连接正常

### 升级 SFML 版本

修改 `CMakeLists.txt` 中的 `GIT_TAG`:
```cmake
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2  # 修改此处版本号
    ...
)
```

## 故障排除

### 常见问题

**Q: CMake 找不到编译器**  
A: 确保 MinGW 的 `bin` 目录在系统 PATH 中，运行 `gcc --version` 验证。

**Q: 构建时网络错误**  
A: SFML 下载需要网络连接，可使用代理或手动下载。

**Q: 运行时找不到 DLL**  
A: Debug 模式下所需的 DLL 会自动复制到 `build/bin` 目录。

**Q: 编译错误 C++17 特性**  
A: 确保编译器支持 C++17，GCC 7+ 或 MSVC 2017+。

## 开发计划

- [ ] 添加分数系统
- [ ] 实现关卡系统
- [ ] 添加音效和背景音乐
- [ ] 特殊方块和道具
- [ ] 存档系统
- [ ] 游戏设置界面完善

## 贡献指南

欢迎贡献代码或提出建议！请遵循：

1. Fork 本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 相关资源

- [SFML 官方文档](https://www.sfml-dev.org/documentation/3.0.0/)
- [CMake 官方教程](https://cmake.org/cmake/help/latest/guide/tutorial/)
- [C++17 特性参考](https://en.cppreference.com/w/cpp/17)

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
