# Match3Game 文档索引

欢迎查阅 Match3Game 的完整文档！本文档集提供了项目的全面介绍、架构设计和 API 参考。

## 📚 文档目录

### 1. [项目文档](./PROJECT_DOCUMENTATION.md) ⭐ 推荐首先阅读
**完整的项目说明文档**

包含内容：
- 🎯 项目概述与核心特性
- 🛠️ 技术栈与项目结构
- 🏗️ 系统架构设计
- 📦 核心模块详解
- 🎮 游戏流程说明
- 🎨 类图与架构图（文本版）
- ⚙️ 关键算法解析
- 🚀 构建与运行指南
- 📝 代码规范
- 🔧 扩展性设计

**适合人群**: 所有开发者、项目维护者、新手入门

---

### 2. [架构图集](./ARCHITECTURE_DIAGRAMS.md) 📊
**可视化架构与流程图文档**

包含 Mermaid 图表：
- 🏛️ 系统架构图（分层架构、模块依赖）
- 🔗 类关系图（继承、组合、依赖）
- 🎯 游戏流程图（主循环、场景切换、消除循环）
- 🔄 状态机图（GameBoard 状态、交换操作）
- 📈 序列图（玩家交互、消除连锁、场景管理）
- 💾 数据流图（状态数据、匹配检测、动画系统、事件处理）
- 🧩 组件交互图

**适合人群**: 架构师、需要快速理解系统设计的开发者

---

### 3. [API 参考](./API_REFERENCE.md) 📖
**完整的 API 接口文档**

包含模块：
- **核心模块 (Core)**
  - Scene - 场景基类
  - SceneManager - 场景管理器
  - GameLogic - 游戏核心逻辑
  
- **UI 模块 (UI)**
  - GameBoard - 游戏棋盘
  - MainMenu - 主菜单
  - SettingsScene - 设置界面
  - Button - 按钮基类
  
- **工具模块 (Utils)**
  - ColorManager - 颜色管理
  - GameConfig - 配置管理
  - KeyboardMonitor - 键盘监听
  - RoundedRectangle - 圆角矩形

**适合人群**: 正在编写代码的开发者、需要查阅具体 API 的人员

---

## 🚀 快速开始

### 第一次接触项目？

1. **阅读顺序建议**:
   ```
   项目文档（概述+特性） 
   → 架构图集（系统架构图+游戏流程图）
   → 项目文档（核心模块+关键算法）
   → API 参考（按需查阅）
   ```

2. **动手实践**:
   - 按照[项目文档 - 构建与运行](./PROJECT_DOCUMENTATION.md#构建与运行)章节编译项目
   - 运行游戏，体验功能
   - 查看[架构图集 - 游戏流程图](./ARCHITECTURE_DIAGRAMS.md#游戏流程图)理解运行逻辑

3. **开始开发**:
   - 参考[项目文档 - 扩展性设计](./PROJECT_DOCUMENTATION.md#扩展性设计)了解如何扩展
   - 使用[API 参考](./API_REFERENCE.md)查阅具体接口
   - 遵循[项目文档 - 代码规范](./PROJECT_DOCUMENTATION.md#代码规范)

---

## 📋 文档结构对比

| 文档 | 侧重点 | 详细程度 | 可视化 | 代码示例 |
|------|--------|----------|--------|----------|
| 项目文档 | 全面概述 | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐ |
| 架构图集 | 可视化设计 | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐ |
| API 参考 | 接口细节 | ⭐⭐⭐⭐⭐ | ⭐ | ⭐⭐⭐⭐⭐ |

---

## 🎯 按需查找

### 我想了解...

#### "整个项目是什么？"
→ [项目文档 - 项目概述](./PROJECT_DOCUMENTATION.md#项目概述)

#### "如何编译运行？"
→ [项目文档 - 构建与运行](./PROJECT_DOCUMENTATION.md#构建与运行)

#### "系统是怎么设计的？"
→ [架构图集 - 系统架构图](./ARCHITECTURE_DIAGRAMS.md#系统架构图)  
→ [项目文档 - 系统架构](./PROJECT_DOCUMENTATION.md#系统架构)

#### "游戏是怎么运行的？"
→ [架构图集 - 游戏流程图](./ARCHITECTURE_DIAGRAMS.md#游戏流程图)  
→ [项目文档 - 游戏流程](./PROJECT_DOCUMENTATION.md#游戏流程)

#### "类之间的关系是什么？"
→ [架构图集 - 类关系图](./ARCHITECTURE_DIAGRAMS.md#类关系图)  
→ [项目文档 - 类图与架构图](./PROJECT_DOCUMENTATION.md#类图与架构图)

#### "如何使用某个类？"
→ [API 参考](./API_REFERENCE.md) (查找对应模块)

#### "匹配算法是怎么实现的？"
→ [项目文档 - 关键算法](./PROJECT_DOCUMENTATION.md#关键算法)

#### "如何添加新功能？"
→ [项目文档 - 扩展性设计](./PROJECT_DOCUMENTATION.md#扩展性设计)  
→ [API 参考 - 使用示例](./API_REFERENCE.md#使用示例)

#### "场景是如何切换的？"
→ [架构图集 - 序列图 - 场景管理序列](./ARCHITECTURE_DIAGRAMS.md#场景管理序列)  
→ [API 参考 - SceneManager](./API_REFERENCE.md#scenemanager)

#### "状态机是怎么工作的？"
→ [架构图集 - 状态机图](./ARCHITECTURE_DIAGRAMS.md#状态机图)  
→ [API 参考 - GameBoard](./API_REFERENCE.md#gameboard)

#### "数据是如何流动的？"
→ [架构图集 - 数据流图](./ARCHITECTURE_DIAGRAMS.md#数据流图)

---

## 🔍 关键概念索引

### 设计模式
- **场景管理模式**: [项目文档](./PROJECT_DOCUMENTATION.md#系统架构) | [API - Scene](./API_REFERENCE.md#scene)
- **单例模式**: [API - GameConfig](./API_REFERENCE.md#gameconfig)
- **观察者模式**: [API - KeyboardMonitor](./API_REFERENCE.md#keyboardmonitor)

### 核心系统
- **场景系统**: [架构图 - 场景管理序列](./ARCHITECTURE_DIAGRAMS.md#场景管理序列)
- **动画系统**: [项目文档 - 关键算法](./PROJECT_DOCUMENTATION.md#3-动画插值算法) | [架构图 - 动画系统数据流](./ARCHITECTURE_DIAGRAMS.md#动画系统数据流)
- **匹配系统**: [项目文档 - 匹配检测算法](./PROJECT_DOCUMENTATION.md#1-匹配检测算法) | [架构图 - 匹配检测数据流](./ARCHITECTURE_DIAGRAMS.md#匹配检测数据流)
- **状态机**: [架构图 - GameBoard 状态机](./ARCHITECTURE_DIAGRAMS.md#gameboard-状态机)

### 关键类
- **SceneManager**: [API](./API_REFERENCE.md#scenemanager) | [架构图](./ARCHITECTURE_DIAGRAMS.md#scenemanager-类详细结构)
- **GameLogic**: [API](./API_REFERENCE.md#gamelogic) | [架构图](./ARCHITECTURE_DIAGRAMS.md#gamelogic-类详细结构)
- **GameBoard**: [API](./API_REFERENCE.md#gameboard) | [架构图](./ARCHITECTURE_DIAGRAMS.md#gameboard-状态机)

---

## 📝 代码示例速查

### 创建简单游戏
→ [API 参考 - 使用示例](./API_REFERENCE.md#使用示例)

### 自定义场景
→ [API 参考 - 自定义场景](./API_REFERENCE.md#自定义场景)

### 场景切换
```cpp
sceneManager.pushScene("game");   // 压入新场景
sceneManager.popScene();          // 返回上一场景
sceneManager.changeScene("menu"); // 直接切换场景
```

### 设置回调
```cpp
keyboardMonitor.setCallback(GlobalKey::Backspace, [&]() {
    sceneManager.popScene();
});
```

### 颜色管理
```cpp
sf::Color color = ColorManager::getColor(colorIndex);
```

### 游戏配置
```cpp
GameConfig& config = GameConfig::getInstance();
config.setNumColors(6);
config.setGridSize(sf::Vector2i(8, 8));
```

---

## 🛠️ 开发工具

### VS Code 任务
项目已配置以下任务（`Ctrl+Shift+B`）:
- **CMake Configure** - 配置项目
- **Build Debug** - 编译调试版本 ⭐ 默认
- **Build Release** - 编译发布版本

### 调试配置
使用 VS Code C++ 调试器，配置文件已设置：
- 断点调试
- 变量监视
- 调用栈查看

---

## 📚 学习路径

### 初级开发者
1. ✅ 阅读[项目文档 - 项目概述](./PROJECT_DOCUMENTATION.md#项目概述)
2. ✅ 查看[架构图集 - 系统架构图](./ARCHITECTURE_DIAGRAMS.md#系统架构图)
3. ✅ 按照[构建与运行](./PROJECT_DOCUMENTATION.md#构建与运行)编译项目
4. ✅ 运行并体验游戏
5. ✅ 阅读[项目文档 - 核心模块](./PROJECT_DOCUMENTATION.md#核心模块)
6. ✅ 参考[API 参考](./API_REFERENCE.md)编写简单示例

### 中级开发者
1. ✅ 深入理解[架构图集 - 游戏流程图](./ARCHITECTURE_DIAGRAMS.md#游戏流程图)
2. ✅ 学习[项目文档 - 关键算法](./PROJECT_DOCUMENTATION.md#关键算法)
3. ✅ 研究[架构图集 - 序列图](./ARCHITECTURE_DIAGRAMS.md#序列图)
4. ✅ 阅读源代码并对照 API 文档
5. ✅ 实现自定义场景或功能

### 高级开发者
1. ✅ 分析[架构图集 - 数据流图](./ARCHITECTURE_DIAGRAMS.md#数据流图)
2. ✅ 优化算法和性能
3. ✅ 扩展核心功能（如关卡系统、特殊道具）
4. ✅ 重构代码架构
5. ✅ 贡献到开源项目

---

## 🤝 贡献文档

如果发现文档错误或需要补充，欢迎提交 PR：

1. Fork 项目
2. 修改 `docs/` 目录下的 Markdown 文件
3. 提交 Pull Request

### 文档编写规范
- 所有文档使用 Markdown 格式
- 图表使用 Mermaid 语法
- 代码示例使用 C++ 语法高亮
- 保持格式一致性

---

## 📞 获取帮助

- **GitHub Issues**: [提交问题](https://github.com/abwuge/Match3Game/issues)
- **Discussions**: [参与讨论](https://github.com/abwuge/Match3Game/discussions)
- **Email**: 联系项目维护者

---

## 📄 许可证

本项目遵循 MIT 许可证，详见 [LICENSE.md](../LICENSE.md)

---

## ⭐ 相关资源

### 外部文档
- [SFML 官方文档](https://www.sfml-dev.org/documentation/3.0.0/)
- [CMake 文档](https://cmake.org/documentation/)
- [C++17 参考](https://en.cppreference.com/w/cpp/17)

### 学习资源
- [三消游戏设计原理](https://en.wikipedia.org/wiki/Tile-matching_video_game)
- [游戏状态机模式](https://gameprogrammingpatterns.com/state.html)
- [SFML 教程](https://www.sfml-dev.org/tutorials/3.0/)

---

**文档集版本**: 1.0  
**最后更新**: 2025-11-24  
**维护者**: abwuge

---

## 🎉 感谢使用 Match3Game！

希望这些文档能帮助你快速上手并深入理解项目。祝开发愉快！
