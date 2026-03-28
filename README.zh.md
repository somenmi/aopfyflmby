<div align="center">
  <h6>Выберите язык / Select language / 选择语言</h3>
  <p>
    <a href="README.md"><img src="https://img.shields.io/badge/Русский-RU-skyblue" alt="Русский"></a>
    <a href="README.en.md"><img src="https://img.shields.io/badge/English-GB-skyblue" alt="English"></a>
    <a href="README.zh.md"><img src="https://img.shields.io/badge/中文-CN-skyblue" alt="中文"></a>
  </p>
</div>

---

<table border="20" align="center">
     <tr>
         <td>
            <img src="https://github.com/somenmi/images/raw/main/aopfyflmby/logo.png" width="120" height="120">
         </td>
        <td align="center">
            <h1><a href="https://somenmi.github.io/aopfyflmby/"><b>aopfyflmby</b> (音乐播放器)</a></h1>
            <p><strong>An objective player for your favorite local music by Yalkee</strong></p>
         </td>
     </tr>
</table>

<div align="center">

[![版本](https://shields.io/badge/version-1.0.0-pink.svg)](https://github.com/somenmi/aopfyflmby/releases)
[![许可证](https://shields.io/badge/license-MIT-pink.svg)](LICENSE)
![Windows](https://shields.io/badge/Windows-7/11-pink.svg)
[![信息](https://shields.io/badge/Info-HTML-pink.svg)](https://somenmi.github.io/aopfyflmby/)

</div>

---

## 💭 我如何想到创建这个程序

大约 12-13 年前，我偶然发现了一个完全运行在系统托盘中的音乐播放器——没有多余的窗口，只有一个图标和一个方便的右键菜单。它简单、轻巧，只做一件事：播放音乐，没有任何干扰。

时光流逝，这个程序早已消失，而互联网变得如此庞大，几乎不可能再找到它。

随着我对 IT 的深入了解，我决定重制那个播放器。尤其是在 5-6 年前，我收集了一个庞大的音乐档案——那是我一生积累的所有音乐。但当我尝试现有的播放器（如 AIMP、Winamp 等）时，总是遇到同样的问题：它们太臃肿，功能太多，根本用不上。

结果就是你现在看到的这个页面。简单、方便，就在托盘里。

感谢你的光临！😊

---

## 🎼 关于播放器

**aopfyflmby** (缩写是：<u>An objective player for your favorite local music by Yalkee</u>) 是一个极简音乐播放器，运行在系统托盘中。没有多余的窗口——只有托盘图标和上下文菜单。加载音乐文件夹，通过快捷键或上下文菜单控制播放。

## 💥 特点

- 🎵 支持 MP3, WAV, FLAC, M4A, OGG, MP4 (音频)
- 🌐 三种界面语言：俄语、英语、中文
- 📁 加载整个音乐文件夹
- 📋 播放列表（保存/加载/编辑）
- 🔀 随机播放
- 🔁 循环播放
- 🔊 音量控制
- 🖱️ 从系统托盘控制
- 💾 自动保存会话
- 🚀 轻量快速

# 版本历史

### v0.1.0
    × 通过对话框加载文件夹
    × 播放/暂停
    × 下一首/上一首
    × 随机播放
    × 循环播放
    × 增加/减少音量
    × 退出程序
    × 右键点击托盘图标打开菜单
    × 图标："logo_music.ico"（停止）和 "pause.ico"（播放）
    × 系统托盘通知（WinAPI）

### v0.2.0
    × 添加播放列表（下拉菜单显示曲目，播放/暂停图标）
    × 改进菜单结构 - 按钮组之间添加双分隔线

### v0.3.0
    × 新增"设置"按钮及子菜单
    × 支持三种语言：俄语、英语、中文
    × 播放列表管理：
        ↪︎ 保存当前曲目列表到文件
        ↪︎ 加载已保存的播放列表
        ↪︎ 通过对话框编辑（重命名/删除）
        ↪︎ 可在任何文本编辑器中手动编辑播放列表
    × 性能优化：
        ↪︎ 异步保存设置
        ↪︎ 曲目信息缓存

### v1.0.0 - 正式版
    × 完全重新设计菜单 - 提高可读性和易用性
    × 设置中添加"关于"选项（链接到 GitHub Pages）
    × 托盘控制快捷键：
        ↪︎ "Shift + 左键" 点击图标 → 下一首
        ↪︎ "Ctrl + 左键" 点击图标 → 上一首
    × 重新设计随机播放逻辑：
        ↪︎ 随机播放创建随机播放顺序，不改变原始列表
        ↪︎ 上一首/下一首按此顺序导航，而非随机
    × 三种托盘图标状态：
        ↪︎ "warning.ico" - 无曲目
        ↪︎ "logo_music.ico" - 有曲目，播放停止
        ↪︎ "pause.ico" - 正在播放

## 🛠 使用方法

1. **运行程序** - 图标出现在系统托盘中（时钟附近），<u>最好将其固定到任务栏</u>

        推荐！（如果你需要深色主题界面）
        
        安装 "WindHawk" 并启用 "Dark mode context menus"
        如果你使用 Windows 深色主题，这是一个非常好的工具。

2. **右键点击** 图标 → **"加载文件夹"** 并选择你的音乐文件夹
3. 通过托盘菜单控制播放：
   - 播放/暂停
   - 下一首/上一首
   - 音量控制
   - 随机播放
   - 循环播放
4. **播放列表** - 显示已加载文件夹中的所有曲目
5. **播放列表管理** - 保存当前曲目列表并可稍后加载
6. **设置** → **语言** - 选择界面语言

---

## 💾 数据存储

**程序自动保存：**
- 最后加载的文件夹
- 当前播放列表
- 播放位置
- 音量、随机播放、循环播放设置

**存储路径：**
- 便携版：程序文件夹中的 `data\`
- 安装版：`%APPDATA%\aopfyflmby\`

<u>播放列表以 `.pl` 格式存储在 `data\playlists\` 中（纯文本文件）。</u>

## 🖼️ 截图

| 菜单 (俄语) | 菜单 (英语) | 菜单 (中文) |
|-------------|------------------------|-----------|
| ![俄语菜单](https://github.com/somenmi/images/raw/main/aopfyflmby/demo_ru.png) | ![英语菜单](https://github.com/somenmi/images/raw/main/aopfyflmby/demo_en.png) | ![中文菜单](https://github.com/somenmi/images/raw/main/aopfyflmby/demo_cn.png) |

## 🔧 系统要求

- Windows 7 / 8 / 10 / 11（32 或 64 位）
- 20 MB 空闲内存
- [BASS 音频库](https://www.un4seen.com/)（已包含在发行包中）

## 📦 从源代码构建

1. 安装 [Visual Studio 2022-2026](https://visualstudio.microsoft.com/) 并选择"使用 C++ 的桌面开发"组件
2. 在 Visual Studio 中打开项目，构建 Release 版本
3. 要创建安装程序，安装 [Inno Setup](https://jrsoftware.org/isinfo.php) 并运行 `installer\aopfyflmby.iss`

## 📝 许可证

本项目采用 MIT 许可证分发。详见 [LICENSE](LICENSE) 文件。

## ✨ 致谢

- [BASS 音频库](https://www.un4seen.com/) - 强大的音频库
- [Inno Setup](https://jrsoftware.org/isinfo.php) - 安装程序创建工具

---

<div align="center">

**© 2026 Yalkee (somenmi)** - [MIT 许可证](LICENSE)

</div>