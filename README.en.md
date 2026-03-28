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
            <h1><a href="https://somenmi.github.io/aopfyflmby/"><b>aopfyflmby</b> (music player)</a></h1>
            <p><strong>An objective player for your favorite local music by Yalkee</strong></p>
         </td>
     </tr>
</table>

<div align="center">

[![Version](https://shields.io/badge/version-1.0.0-pink.svg)](https://github.com/somenmi/aopfyflmby/releases)
[![License](https://shields.io/badge/license-MIT-pink.svg)](LICENSE)
![Windows](https://shields.io/badge/Windows-7/11-pink.svg)
[![Info](https://shields.io/badge/Info-HTML-pink.svg)](https://somenmi.github.io/aopfyflmby/)

</div>

---

### 💭 How I came to create this program

About 12–13 years ago, I stumbled upon a music player that ran exclusively from the system tray — no extra windows, just an icon and a convenient context menu. It was simple, lightweight, and did exactly what it needed to: play music without any distractions.

Years passed, the program was lost, and the internet grew so much that finding it again became practically impossible.

As I delved deeper into IT, I decided to recreate that very player. Especially since 5–6 years ago, I had gathered an impressive music archive — everything I’ve collected over my life. But when I tried existing solutions (AIMP, Winamp, and others), I kept running into the same issue: they were bulky, overloaded with features I didn’t need.

The result is what you see on this page. Simple, convenient, and in the tray.

Thanks for stopping by! c:

---

## 🎼 About

**aopfyflmby** (abbr. from: <u>An objective player for your favorite local music by Yalkee</u>) - is a minimalist music player that runs from the system tray. No extra windows - just an icon in the tray and a context menu. Load a music folder and control playback via hotkeys or the context menu.

## 💥 Features

- 🎵 Supports MP3, WAV, FLAC, M4A, OGG, MP4 (audio)
- 🌐 Three interface languages: Russian, English, 中文
- 📁 Load entire music folders
- 📋 Playlists (save/load/edit)
- 🔀 Shuffle playback
- 🔁 Loop playlist
- 🔊 Volume control
- 🖱️ Control from system tray
- 💾 Auto-save session
- 🚀 Lightweight and fast

# Versions

### v0.1.0
    × Load folder via dialog
    × Play/Pause
    × Next/Previous track
    × Shuffle
    × Loop playlist
    × Increase/Decrease volume
    × Exit program
    × Right-click menu on tray icon
    × Icons: "logo_music.ico" (stop) and "pause.ico" (playback)
    × System tray notifications (WinAPI)

### v0.2.0
    × Added playlist (dropdown menu with tracks, play/pause icon)
    × Improved menu structure - added double separators between button groups

### v0.3.0
    × New "Settings" button with submenu
    × Three languages support: Russian, English, 中文
    × Playlist management:
        ↪︎ Save current track list to file
        ↪︎ Load saved playlists
        ↪︎ Edit (rename/delete) via dialog
        ↪︎ Manual playlist editing in any text editor
    × Performance optimization:
        ↪︎ Asynchronous settings saving
        ↪︎ Track information caching

### v1.0.0 - Release
    × Complete menu redesign - improved readability and usability
    × Added "About" item in Settings (links to GitHub Pages)
    × Hotkeys for tray control:
        ↪︎ "Shift + LMB" on icon → next track
        ↪︎ "Ctrl + LMB" on icon → previous track
    × Reworked shuffle logic:
        ↪︎ Shuffle now creates a random playback order without changing the original list
        ↪︎ Next/Previous navigation follows this order, not random
    × Three tray icon states:
        ↪︎ "warning.ico" - no tracks
        ↪︎ "logo_music.ico" - tracks available, playback stopped
        ↪︎ "pause.ico" - playback in progress

## 🛠 Usage

1. **Run the program** - icon appears in system tray (near clock), <u>it's best to pin it to the Taskbar</u>

        Recommended! (if you need dark theme interface)
        
        Install "WindHawk" and enable "Dark mode context menus"
        A very nice addition if you use Windows dark theme.

2. **Right-click** on the icon → **"Load folder"** and select your music folder
3. Control playback via tray menu:
   - Play/Pause
   - Next/Previous track
   - Volume control
   - Shuffle
   - Loop
4. **Playlist** - shows all tracks from the loaded folder
5. **Playlists** - save current track list and load them later
6. **Settings** → **Language** - choose interface language

---

## 💾 Data Storage

**Program automatically saves:**
- Last loaded folder
- Current playlist
- Playback position
- Volume, shuffle, loop settings

**Storage paths:**
- Portable version: `data\` in program folder
- Installed version: `%APPDATA%\aopfyflmby\`

<u>Playlists are stored in `data\playlists\` in `.pl` format (plain text file).</u>

## 🖼️ Screenshots

| Menu (Russian) | Menu (English) | Menu (Chinese) |
|-------------|------------------------|-----------|
| ![Menu RU](https://github.com/somenmi/images/raw/main/aopfyflmby/demo_ru.png) | ![Menu EN](https://github.com/somenmi/images/raw/main/aopfyflmby/demo_en.png) | ![Menu ZH](https://github.com/somenmi/images/raw/main/aopfyflmby/demo_cn.png) |

## 🔧 System Requirements

- Windows 7 / 8 / 10 / 11 (32 or 64 bit)
- 20 MB free RAM
- [BASS audio library](https://www.un4seen.com/) (included in distribution)

## 📦 Building from Source

1. Install [Visual Studio 2022-2026](https://visualstudio.microsoft.com/) with "Desktop development with C++" component
2. Open the project in Visual Studio and build the Release version
3. To create installer, install [Inno Setup](https://jrsoftware.org/isinfo.php) and run `installer\aopfyflmby.iss`

## ✨ Acknowledgments

- [BASS audio library](https://www.un4seen.com/) - powerful audio library
- [Inno Setup](https://jrsoftware.org/isinfo.php) - installer creation tool

---

<div align="center">

**© 2026 Yalkee (somenmi)** - [MIT License](LICENSE)

</div>