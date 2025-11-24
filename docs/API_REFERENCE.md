# Match3Game API 参考文档

本文档详细描述了项目中所有公共类和接口的 API。

## 目录
- [核心模块 (Core)](#核心模块-core)
  - [Scene](#scene)
  - [SceneManager](#scenemanager)
  - [GameLogic](#gamelogic)
- [UI 模块 (UI)](#ui-模块-ui)
  - [GameBoard](#gameboard)
  - [MainMenu](#mainmenu)
  - [SettingsScene](#settingsscene)
  - [Button](#button)
- [工具模块 (Utils)](#工具模块-utils)
  - [ColorManager](#colormanager)
  - [GameConfig](#gameconfig)
  - [KeyboardMonitor](#keyboardmonitor)
  - [RoundedRectangle](#roundedrectangle)

---

## 核心模块 (Core)

### Scene

**文件**: `include/core/Scene.h`

抽象基类，所有游戏场景必须继承此类。

#### 类定义

```cpp
class Scene {
public:
    virtual ~Scene() = default;
    
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime) {}
    virtual void render(sf::RenderWindow& window) = 0;
    
    void setSceneManager(SceneManager* manager);

protected:
    SceneManager* sceneManager = nullptr;
};
```

#### 方法说明

##### `virtual void onEnter()`
- **用途**: 场景进入时调用
- **调用时机**: `SceneManager::pushScene()` 或 `changeScene()` 时
- **默认实现**: 空函数
- **用途示例**: 初始化场景资源、重置状态

```cpp
void GameBoard::onEnter() override {
    initializeGame();
    startFallAnimation();
}
```

##### `virtual void onExit()`
- **用途**: 场景退出时调用
- **调用时机**: `SceneManager::popScene()` 或 `changeScene()` 时
- **默认实现**: 空函数
- **用途示例**: 清理资源、保存状态

##### `virtual void handleEvent(const sf::Event& event) = 0`
- **用途**: 处理输入事件（纯虚函数，必须实现）
- **参数**: `event` - SFML 事件对象
- **事件类型**: 
  - `sf::Event::MouseButtonPressed`
  - `sf::Event::MouseMoved`
  - `sf::Event::KeyPressed`
  - 等等

```cpp
void MainMenu::handleEvent(const sf::Event& event) override {
    startButton.handleEvent(event);
    settingsButton.handleEvent(event);
}
```

##### `virtual void update(float deltaTime)`
- **用途**: 更新场景逻辑
- **参数**: `deltaTime` - 自上一帧经过的时间（秒）
- **默认实现**: 空函数
- **用途示例**: 更新动画、物理模拟

##### `virtual void render(sf::RenderWindow& window) = 0`
- **用途**: 渲染场景（纯虚函数，必须实现）
- **参数**: `window` - SFML 渲染窗口引用

```cpp
void GameBoard::render(sf::RenderWindow& window) override {
    drawGrid(window);
    for (auto& row : shapes) {
        for (auto& shape : row) {
            window.draw(shape);
        }
    }
}
```

##### `void setSceneManager(SceneManager* manager)`
- **用途**: 设置场景管理器指针
- **参数**: `manager` - SceneManager 实例指针
- **注意**: 由 SceneManager 自动调用，用户无需手动调用

---

### SceneManager

**文件**: `include/core/SceneManager.h`

管理所有场景的生命周期和切换。

#### 类定义

```cpp
class SceneManager {
public:
    SceneManager(sf::RenderWindow& window);
    
    void registerScene(const std::string& name, std::unique_ptr<Scene> scene);
    void pushScene(const std::string& name);
    void popScene();
    void changeScene(const std::string& name);
    
    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render();
    
    bool hasActiveScene() const;

private:
    sf::RenderWindow& window;
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    std::stack<std::string> sceneStack;
    
    Scene* getCurrentScene();
};
```

#### 方法说明

##### `SceneManager(sf::RenderWindow& window)`
- **用途**: 构造场景管理器
- **参数**: `window` - 渲染窗口的引用

```cpp
sf::RenderWindow window({800, 600}, "Game");
SceneManager sceneManager(window);
```

##### `void registerScene(const std::string& name, std::unique_ptr<Scene> scene)`
- **用途**: 注册一个场景
- **参数**:
  - `name` - 场景名称（唯一标识符）
  - `scene` - 场景对象的唯一指针
- **注意**: 必须在 `pushScene` 前调用

```cpp
sceneManager.registerScene("menu", 
    std::make_unique<MainMenu>(800.0f, 600.0f));
sceneManager.registerScene("game", 
    std::make_unique<GameBoard>(800.0f));
```

##### `void pushScene(const std::string& name)`
- **用途**: 将场景压入栈顶（成为当前活动场景）
- **参数**: `name` - 场景名称
- **效果**:
  1. 调用新场景的 `setSceneManager()`
  2. 调用新场景的 `onEnter()`
  3. 新场景成为活动场景

```cpp
sceneManager.pushScene("menu");  // 显示主菜单
sceneManager.pushScene("game");  // 进入游戏，菜单保留在栈中
```

##### `void popScene()`
- **用途**: 弹出当前场景，返回上一个场景
- **效果**:
  1. 调用当前场景的 `onExit()`
  2. 从栈中移除当前场景
  3. 栈顶下一个场景成为活动场景
- **注意**: 如果栈为空，不执行任何操作

```cpp
sceneManager.popScene();  // 从游戏返回主菜单
```

##### `void changeScene(const std::string& name)`
- **用途**: 切换到指定场景（清空栈并压入新场景）
- **参数**: `name` - 场景名称
- **效果**:
  1. 调用当前场景的 `onExit()`
  2. 清空场景栈
  3. 压入新场景
  4. 调用新场景的 `onEnter()`

```cpp
sceneManager.changeScene("game");  // 直接切换到游戏，不保留历史
```

##### `void handleEvent(const sf::Event& event)`
- **用途**: 将事件传递给当前活动场景
- **参数**: `event` - SFML 事件对象

```cpp
while (const auto event = window.pollEvent()) {
    sceneManager.handleEvent(event.value());
}
```

##### `void render()`
- **用途**: 渲染当前活动场景
- **注意**: 内部调用当前场景的 `render(window)`

```cpp
window.clear();
sceneManager.render();
window.display();
```

##### `bool hasActiveScene() const`
- **用途**: 检查是否有活动场景
- **返回**: `true` 如果场景栈非空

---

### GameLogic

**文件**: `include/core/GameLogic.h`

处理游戏的核心逻辑，包括网格状态、匹配检测、重力等。

#### 数据结构

```cpp
struct Tile {
    int colorIndex;      // 颜色索引 (0-7)
    bool isEmpty;        // 是否为空
};

struct Match {
    std::vector<sf::Vector2i> positions;  // 匹配的方块位置列表
};
```

#### 类定义

```cpp
class GameLogic {
public:
    GameLogic(int width, int height, int numColors);
    
    void initialize();
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getColorIndex(int row, int col) const;
    bool isEmpty(int row, int col) const;
    const std::vector<int>& getAvailableColors() const;
    
    std::vector<Match> findMatches();
    void clearMatches(const std::vector<Match>& matches);
    std::vector<sf::Vector2i> applyGravity();
    void fillEmptySpaces();
    void swapTiles(int row1, int col1, int row2, int col2);

private:
    int width;
    int height;
    int numColors;
    std::vector<std::vector<Tile>> grid;
    std::vector<int> availableColorIndices;
    
    void findHorizontalMatches(std::vector<Match>& matches);
    void findVerticalMatches(std::vector<Match>& matches);
};
```

#### 方法说明

##### `GameLogic(int width, int height, int numColors)`
- **用途**: 构造游戏逻辑对象
- **参数**:
  - `width` - 网格宽度（列数）
  - `height` - 网格高度（行数）
  - `numColors` - 颜色种类数量
- **注意**: 从 `GameConfig` 读取颜色配置

```cpp
GameConfig& config = GameConfig::getInstance();
auto logic = std::make_shared<GameLogic>(8, 8, 6);
```

##### `void initialize()`
- **用途**: 初始化网格，随机填充方块
- **调用时机**: 游戏开始或重置时

```cpp
gameLogic->initialize();
```

##### `int getColorIndex(int row, int col) const`
- **用途**: 获取指定位置的颜色索引
- **参数**:
  - `row` - 行索引 (0 到 height-1)
  - `col` - 列索引 (0 到 width-1)
- **返回**: 颜色索引，如果位置无效返回 -1

```cpp
int color = gameLogic->getColorIndex(3, 4);
sf::Color rgbColor = ColorManager::getColor(color);
```

##### `bool isEmpty(int row, int col) const`
- **用途**: 检查指定位置是否为空
- **参数**: `row`, `col` - 位置坐标
- **返回**: `true` 如果为空或越界

##### `std::vector<Match> findMatches()`
- **用途**: 查找所有匹配（3个或以上连续相同颜色）
- **返回**: `Match` 对象的向量
- **算法**: 横向扫描 + 纵向扫描
- **时间复杂度**: O(width × height)

```cpp
auto matches = gameLogic->findMatches();
if (!matches.empty()) {
    // 发现匹配，进行消除
}
```

##### `void clearMatches(const std::vector<Match>& matches)`
- **用途**: 清除指定的匹配方块
- **参数**: `matches` - 匹配对象的向量
- **效果**: 将匹配位置标记为 `isEmpty = true`

```cpp
gameLogic->clearMatches(matches);
```

##### `std::vector<sf::Vector2i> applyGravity()`
- **用途**: 应用重力，使方块下落填补空位
- **返回**: 受影响的列的位置向量
- **算法**: 逐列从下往上扫描，非空方块下移

```cpp
auto affectedColumns = gameLogic->applyGravity();
// 对受影响的列播放下落动画
```

##### `void fillEmptySpaces()`
- **用途**: 用随机颜色填充所有空位
- **调用时机**: 重力应用后

```cpp
gameLogic->applyGravity();
gameLogic->fillEmptySpaces();
```

##### `void swapTiles(int row1, int col1, int row2, int col2)`
- **用途**: 交换两个方块的位置
- **参数**: 两个方块的行列坐标
- **注意**: 仅交换逻辑状态，不处理动画

```cpp
gameLogic->swapTiles(0, 0, 0, 1);  // 交换 (0,0) 和 (0,1)
```

---

## UI 模块 (UI)

### GameBoard

**文件**: `include/ui/GameBoard.h`

游戏主场景，显示棋盘并处理玩家交互。

#### 枚举

```cpp
enum class GameState {
    Idle,                  // 等待玩家输入
    Swapping,              // 交换动画中
    FallingInitial,        // 初始下落动画
    CheckingMatches,       // 检查匹配
    ClearingMatches,       // 消除动画
    FallingAfterClear      // 消除后下落
};
```

#### 类定义

```cpp
class GameBoard : public Scene {
public:
    GameBoard(float windowSize);
    
    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void render(sf::RenderWindow& window) override;

private:
    float windowSize;
    std::shared_ptr<GameLogic> gameLogic;
    std::vector<std::vector<RoundedRectangle>> shapes;
    GameState gameState;
    
    // 动画相关
    std::vector<std::vector<sf::Vector2f>> targetPositions;
    std::vector<std::vector<sf::Vector2f>> startPositions;
    sf::Clock animationClock;
    
    // 交互相关
    sf::Vector2i selectedTile;
    bool isDragging;
    sf::Vector2i dragStartTile;
    sf::Vector2f dragCurrentPos;
    
    void initializeGame();
    void initializeShapes();
    void updateAnimation();
    void checkAndClearMatches();
    void handleTileClick(int row, int col);
    void startSwapAnimation(const sf::Vector2i& tile1, const sf::Vector2i& tile2);
    void startFallAnimation(const std::vector<sf::Vector2i>& affectedTiles = {});
    void drawGrid(sf::RenderWindow& window);
    void drawSelectedHighlight(sf::RenderWindow& window);
    float getTileSize() const;
    float getPadding() const;
};
```

#### 方法说明

##### `GameBoard(float windowSize)`
- **用途**: 构造游戏棋盘场景
- **参数**: `windowSize` - 窗口尺寸（正方形）

```cpp
auto gameBoard = std::make_unique<GameBoard>(800.0f);
```

##### `void onEnter() override`
- **用途**: 初始化游戏并开始初始下落动画
- **效果**:
  1. 调用 `initializeGame()`
  2. 调用 `startFallAnimation()`

##### `void handleEvent(const sf::Event& event) override`
- **用途**: 处理鼠标交互
- **支持的交互**:
  - **点击**: 点击两个相邻方块进行交换
  - **拖拽**: 拖动方块到相邻位置进行交换
- **状态限制**: 仅在 `GameState::Idle` 时响应

##### `void render(sf::RenderWindow& window) override`
- **用途**: 渲染游戏棋盘
- **渲染内容**:
  1. 网格线
  2. 所有方块
  3. 拖拽反馈
  4. 选中高亮

##### `float getTileSize() const`
- **用途**: 计算单个方块的尺寸
- **返回**: 方块尺寸（像素）
- **计算公式**: `windowSize / gridWidth`

##### `float getPadding() const`
- **用途**: 计算方块之间的间距
- **返回**: 间距（像素）
- **计算公式**: `tileSize * 0.05`

---

### MainMenu

**文件**: `include/ui/MainMenu.h`

主菜单场景，显示游戏标题和操作按钮。

#### 类定义

```cpp
class MainMenu : public Scene {
public:
    MainMenu(float windowWidth, float windowHeight);
    
    void handleEvent(const sf::Event& event) override;
    void render(sf::RenderWindow& window) override;

private:
    StartButton startButton;
    SettingsButton settingsButton;
    float windowWidth;
    float windowHeight;
};
```

#### 方法说明

##### `MainMenu(float windowWidth, float windowHeight)`
- **用途**: 构造主菜单场景
- **参数**: 窗口的宽度和高度

```cpp
auto menu = std::make_unique<MainMenu>(800.0f, 600.0f);
```

##### `void handleEvent(const sf::Event& event) override`
- **用途**: 处理按钮点击事件
- **按钮**:
  - **Start**: 进入游戏场景
  - **Settings**: 进入设置场景

##### `void render(sf::RenderWindow& window) override`
- **用途**: 渲染菜单界面
- **渲染内容**: 标题、按钮

---

### SettingsScene

**文件**: `include/ui/SettingsScene.h`

设置场景，允许玩家配置游戏参数。

#### 类定义

```cpp
class SettingsScene : public Scene {
public:
    SettingsScene(float windowWidth, float windowHeight);
    
    void handleEvent(const sf::Event& event) override;
    void render(sf::RenderWindow& window) override;

private:
    float windowWidth;
    float windowHeight;
    std::vector<ColorButton> colorButtons;
    std::vector<GridSizeButton> gridSizeButtons;
};
```

#### 功能

- **颜色选择**: 勾选/取消勾选可用颜色
- **网格大小**: 选择 6x6, 8x8, 10x10 等
- **实时预览**: 修改立即生效

---

### Button

**文件**: `include/ui/Button.h`

抽象按钮基类，所有按钮继承此类。

#### 类定义

```cpp
class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, 
           const std::string& text);
    
    virtual void onClick() = 0;
    virtual void handleEvent(const sf::Event& event);
    virtual void render(sf::RenderWindow& window);

protected:
    RoundedRectangle shape;
    sf::Text label;
    bool isHovered;
};
```

#### 方法说明

##### `Button(position, size, text)`
- **用途**: 构造按钮
- **参数**:
  - `position` - 按钮位置
  - `size` - 按钮尺寸
  - `text` - 按钮文本

##### `virtual void onClick() = 0`
- **用途**: 点击回调（纯虚函数）
- **实现示例**:

```cpp
class StartButton : public Button {
    void onClick() override {
        sceneManager->pushScene("game");
    }
};
```

##### `void handleEvent(const sf::Event& event)`
- **用途**: 处理鼠标事件
- **功能**:
  - 悬停检测 (`MouseMoved`)
  - 点击检测 (`MouseButtonPressed`)

---

## 工具模块 (Utils)

### ColorManager

**文件**: `include/utils/ColorManager.h`

管理游戏中使用的颜色。

#### 类定义

```cpp
class ColorManager {
public:
    static sf::Color getColor(int colorIndex);
    static const std::vector<sf::Color>& getAllColors();
};
```

#### 方法说明

##### `static sf::Color getColor(int colorIndex)`
- **用途**: 根据索引获取颜色
- **参数**: `colorIndex` - 颜色索引 (0-7)
- **返回**: SFML Color 对象
- **注意**: 索引越界返回黑色

```cpp
sf::Color red = ColorManager::getColor(0);
sf::Color green = ColorManager::getColor(1);
```

##### `static const std::vector<sf::Color>& getAllColors()`
- **用途**: 获取所有预定义颜色
- **返回**: 颜色向量的常量引用

#### 预定义颜色

| 索引 | 颜色 | RGB 值 |
|------|------|--------|
| 0 | 红色 | (231, 76, 60) |
| 1 | 绿色 | (46, 204, 113) |
| 2 | 蓝色 | (52, 152, 219) |
| 3 | 黄色 | (241, 196, 15) |
| 4 | 紫色 | (155, 89, 182) |
| 5 | 橙色 | (230, 126, 34) |
| 6 | 青色 | (26, 188, 156) |
| 7 | 灰色 | (52, 73, 94) |

---

### GameConfig

**文件**: `include/utils/GameConfig.h`

单例类，管理全局游戏配置。

#### 类定义

```cpp
class GameConfig {
public:
    static GameConfig& getInstance();
    
    int getNumColors() const { return numColors; }
    void setNumColors(int n) { numColors = n; }
    
    sf::Vector2i getGridSize() const { return gridSize; }
    void setGridSize(const sf::Vector2i& size) { gridSize = size; }
    
    const std::vector<int>& getSelectedColorIndices() const;
    void setSelectedColorIndices(const std::vector<int>& indices);

private:
    GameConfig();  // 私有构造函数
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
    
    int numColors;
    sf::Vector2i gridSize;
    std::vector<int> selectedColorIndices;
};
```

#### 方法说明

##### `static GameConfig& getInstance()`
- **用途**: 获取单例实例
- **返回**: 唯一的 GameConfig 实例引用

```cpp
GameConfig& config = GameConfig::getInstance();
config.setNumColors(6);
```

##### `int getNumColors() const`
- **用途**: 获取当前使用的颜色数量
- **返回**: 颜色数量 (1-8)

##### `void setNumColors(int n)`
- **用途**: 设置颜色数量
- **参数**: `n` - 颜色数量
- **注意**: 需要同时更新 `selectedColorIndices`

##### `sf::Vector2i getGridSize() const`
- **用途**: 获取网格尺寸
- **返回**: Vector2i(width, height)

##### `void setGridSize(const sf::Vector2i& size)`
- **用途**: 设置网格尺寸
- **参数**: `size` - 新的网格尺寸
- **示例**:

```cpp
config.setGridSize(sf::Vector2i(10, 10));  // 10x10 网格
```

##### `const std::vector<int>& getSelectedColorIndices() const`
- **用途**: 获取当前选中的颜色索引列表
- **返回**: 索引向量的常量引用

##### `void setSelectedColorIndices(const std::vector<int>& indices)`
- **用途**: 设置选中的颜色索引
- **参数**: `indices` - 颜色索引列表
- **示例**:

```cpp
config.setSelectedColorIndices({0, 1, 2, 3, 4, 5});  // 使用前6种颜色
```

#### 默认配置

```cpp
numColors = 6
gridSize = (8, 8)
selectedColorIndices = {0, 1, 2, 3, 4, 5}
```

---

### KeyboardMonitor

**文件**: `include/utils/KeyboardMonitor.h`

监听全局键盘快捷键。

#### 枚举

```cpp
enum class GlobalKey {
    Backspace,
    Space,
    Enter
};
```

#### 类定义

```cpp
class KeyboardMonitor {
public:
    using KeyCallback = std::function<void()>;
    
    void handleEvent(const sf::Event& event);
    void setCallback(GlobalKey key, KeyCallback callback);
    void clearCallback(GlobalKey key);

private:
    std::unordered_map<GlobalKey, KeyCallback> callbacks;
    sf::Keyboard::Key toSFMLKey(GlobalKey key) const;
};
```

#### 方法说明

##### `void handleEvent(const sf::Event& event)`
- **用途**: 处理键盘事件
- **参数**: `event` - SFML 事件对象

```cpp
keyboardMonitor.handleEvent(event);
```

##### `void setCallback(GlobalKey key, KeyCallback callback)`
- **用途**: 设置键盘回调
- **参数**:
  - `key` - 全局按键
  - `callback` - 回调函数
- **示例**:

```cpp
keyboardMonitor.setCallback(GlobalKey::Backspace, [&]() {
    sceneManager.popScene();
});

keyboardMonitor.setCallback(GlobalKey::Space, [&]() {
    game.pause();
});
```

##### `void clearCallback(GlobalKey key)`
- **用途**: 清除键盘回调
- **参数**: `key` - 全局按键

---

### RoundedRectangle

**文件**: `include/utils/RoundedRectangle.h`

自定义圆角矩形形状，继承自 `sf::Drawable`。

#### 类定义

```cpp
class RoundedRectangle : public sf::Drawable, public sf::Transformable {
public:
    RoundedRectangle();
    RoundedRectangle(const sf::Vector2f& size, float cornerRadius);
    
    void setSize(const sf::Vector2f& size);
    void setCornerRadius(float radius);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    
    sf::Vector2f getSize() const { return size; }
    float getCornerRadius() const { return cornerRadius; }
    sf::FloatRect getGlobalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateGeometry();
    
    sf::Vector2f size;
    float cornerRadius;
    sf::Color fillColor;
    sf::Color outlineColor;
    float outlineThickness;
    sf::VertexArray vertices;
};
```

#### 方法说明

##### `RoundedRectangle(size, cornerRadius)`
- **用途**: 构造圆角矩形
- **参数**:
  - `size` - 矩形尺寸
  - `cornerRadius` - 圆角半径

```cpp
RoundedRectangle rect(sf::Vector2f(100, 100), 10.0f);
rect.setFillColor(sf::Color::Red);
rect.setPosition(50, 50);
window.draw(rect);
```

##### `void setSize(const sf::Vector2f& size)`
- **用途**: 设置矩形尺寸
- **参数**: `size` - 新尺寸

##### `void setCornerRadius(float radius)`
- **用途**: 设置圆角半径
- **参数**: `radius` - 圆角半径（像素）

##### `void setFillColor(const sf::Color& color)`
- **用途**: 设置填充颜色
- **参数**: `color` - SFML Color 对象

##### `void setOutlineColor(const sf::Color& color)`
- **用途**: 设置边框颜色
- **参数**: `color` - SFML Color 对象

##### `void setOutlineThickness(float thickness)`
- **用途**: 设置边框厚度
- **参数**: `thickness` - 厚度（像素）

##### `sf::FloatRect getGlobalBounds() const`
- **用途**: 获取全局边界框
- **返回**: FloatRect(left, top, width, height)
- **用途示例**: 碰撞检测、鼠标悬停检测

```cpp
sf::Vector2f mousePos = ...;
if (rect.getGlobalBounds().contains(mousePos)) {
    // 鼠标在矩形内
}
```

---

## 使用示例

### 创建一个简单的游戏

```cpp
#include <SFML/Graphics.hpp>
#include "core/SceneManager.h"
#include "ui/MainMenu.h"
#include "ui/GameBoard.h"
#include "utils/KeyboardMonitor.h"

int main() {
    // 创建窗口
    auto window = sf::RenderWindow(
        sf::VideoMode({800, 800}), 
        "Match 3 Game"
    );
    window.setFramerateLimit(144);
    
    // 创建场景管理器
    SceneManager sceneManager(window);
    KeyboardMonitor keyboardMonitor;
    
    // 注册场景
    sceneManager.registerScene("menu", 
        std::make_unique<MainMenu>(800.0f, 800.0f));
    sceneManager.registerScene("game", 
        std::make_unique<GameBoard>(800.0f));
    
    // 设置快捷键
    keyboardMonitor.setCallback(GlobalKey::Backspace, [&]() {
        sceneManager.popScene();
    });
    
    // 启动游戏
    sceneManager.pushScene("menu");
    
    // 主循环
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            keyboardMonitor.handleEvent(event.value());
            sceneManager.handleEvent(event.value());
        }
        
        window.clear(sf::Color(245, 245, 245));
        sceneManager.render();
        window.display();
    }
    
    return 0;
}
```

### 自定义场景

```cpp
#include "core/Scene.h"
#include "utils/RoundedRectangle.h"

class MyCustomScene : public Scene {
public:
    MyCustomScene() {
        // 初始化
    }
    
    void onEnter() override {
        // 场景进入时的初始化
        std::cout << "Entering custom scene" << std::endl;
    }
    
    void onExit() override {
        // 场景退出时的清理
        std::cout << "Exiting custom scene" << std::endl;
    }
    
    void handleEvent(const sf::Event& event) override {
        if (event.is<sf::Event::KeyPressed>()) {
            auto keyEvent = event.getIf<sf::Event::KeyPressed>();
            if (keyEvent->code == sf::Keyboard::Key::Escape) {
                sceneManager->popScene();
            }
        }
    }
    
    void render(sf::RenderWindow& window) override {
        // 渲染逻辑
        RoundedRectangle rect(sf::Vector2f(200, 100), 15.0f);
        rect.setPosition(300, 350);
        rect.setFillColor(sf::Color::Blue);
        window.draw(rect);
    }
};
```

---

## 性能注意事项

### 最佳实践

1. **避免频繁创建对象**: 重用 `RoundedRectangle` 等对象
2. **批量绘制**: 在一个渲染循环中绘制所有对象
3. **状态检查**: 仅在必要时更新动画
4. **事件过滤**: 在不同状态下忽略无关事件

### 示例

```cpp
// 好的做法 ✓
std::vector<RoundedRectangle> shapes(100);  // 预分配
for (auto& shape : shapes) {
    window.draw(shape);  // 批量绘制
}

// 不好的做法 ✗
for (int i = 0; i < 100; i++) {
    RoundedRectangle shape(...);  // 频繁创建
    window.draw(shape);
}
```

---

## 线程安全

⚠️ **警告**: 本项目不保证线程安全。所有类都应在主线程中使用。

SFML 的窗口和图形操作必须在主线程中执行。

---

## 版本兼容性

- **SFML 版本**: 3.0.2
- **C++ 标准**: C++17
- **CMake 版本**: 3.28+

---

## 常见问题

### Q: 如何添加新的全局按键？

A: 在 `KeyboardMonitor.h` 的 `GlobalKey` 枚举中添加新键，然后在 `toSFMLKey()` 方法中映射到 SFML 按键。

### Q: 如何自定义颜色？

A: 编辑 `ColorManager.cpp` 中的 `colors` 数组。

### Q: 场景之间如何传递数据？

A: 使用 `GameConfig` 单例类存储共享数据，或通过构造函数传递。

---

**文档版本**: 1.0  
**最后更新**: 2025-11-24
