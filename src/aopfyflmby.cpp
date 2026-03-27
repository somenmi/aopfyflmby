#include "framework.h"
#include "targetver.h"
#include "resource.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <map>
#include <shlobj.h>

#include "bass.h"

#pragma comment(lib, "bass.lib")
#pragma comment(lib, "Shell32.lib")

#define WM_TRAYICON (WM_USER + 1)
#define TIMER_CHECK_PLAYBACK 1
#define CHECK_INTERVAL 100
#define WM_SAVE_SESSION (WM_USER + 2)
#define WM_HIDE_NOTIFICATION (WM_USER + 3)

// ===== НАСТРОЙКА ЯЗЫКА ПО УМОЛЧАНИЮ =====
// LANG_RU; LANG_EN; LANG_ZH
// ========================================
#define DEFAULT_LANGUAGE LANG_ZH
// ========================================

// Поддерживаемые форматы
const std::vector<std::wstring> SUPPORTED_FORMATS = {
    L".mp3", L".wav", L".flac", L".m4a", L".ogg"
};

// Языки
enum Language { LANG_RU, LANG_EN, LANG_ZH };

// Кэшированная информация о треке
struct CachedTrack {
    std::wstring filepath;
    std::wstring displayName;
    std::wstring extension;
};

// Структура для информации о треке (ID3)
struct TrackInfo {
    std::wstring artist;
    std::wstring title;
    std::wstring extension;
};

// Структура для перевода
struct Translation {
    std::wstring loadFolder;
    std::wstring playPause;
    std::wstring next;
    std::wstring prev;
    std::wstring playlist;
    std::wstring playlists;
    std::wstring savePlaylist;
    std::wstring openPlaylist;
    std::wstring shuffle;
    std::wstring loop;
    std::wstring volumeUp;
    std::wstring volumeDown;
    std::wstring settings;
    std::wstring language;
    std::wstring russian;
    std::wstring english;
    std::wstring chinese;
    std::wstring exit;
    std::wstring noTracks;
    std::wstring loadFolderFirst;
    std::wstring errorBass;
    std::wstring alreadyRunning;
    std::wstring tracksLoaded;
    std::wstring tracks;
    std::wstring noMusic;
    std::wstring endOfPlaylist;
    std::wstring shuffleOn;
    std::wstring shuffleOff;
    std::wstring loopOn;
    std::wstring loopOff;
    std::wstring errorPlayback;
    std::wstring pauseText;
    std::wstring playingText;
    std::wstring aopfyflmby;
    std::wstring playlistEmpty;
    std::wstring enterPlaylistName;
    std::wstring folderPath;
    std::wstring save;
    std::wstring cancel;
    std::wstring managePlaylists;
    std::wstring playlistName;
    std::wstring edit;
    std::wstring deleteText;
    std::wstring loadText;
    std::wstring playlistSaved;
    std::wstring playlistLoaded;
    std::wstring playlistDeleted;
    std::wstring playlistRenamed;
    std::wstring enterName;
    std::wstring loading;
    std::wstring about;
};

Translation ruTexts = {
    L"Загрузить папку", L"Воспроизвести/Пауза", L"＞＞ Следующий", L"＜＜ Предыдущий",
    L"Список воспроизведения", L"Плейлисты", L"Сохранить плейлист", L"Открыть плейлист",
    L"Перемешать", L"Повтор", L"➕  Громкость", L"➖  Громкость",
    L"Настройки", L"Язык", L"🇷🇺 Русский", L"🇬🇧 English", L"🇨🇳 中文",
    L"Выход", L"Нет треков", L"Сначала загрузите папку с музыкой",
    L"Не удалось инициализировать BASS\nУбедитесь, что bass.dll находится в папке с программой",
    L"Программа уже запущена!", L"Загружено ", L" треков", L"В папке нет поддерживаемых аудиофайлов",
    L"Конец плейлиста", L"Перемешивание ВКЛ", L"Перемешивание ВЫКЛ",
    L"Повтор плейлиста ВКЛ", L"Повтор плейлиста ВЫКЛ", L"Ошибка воспроизведения файла",
    L"Пауза", L"Воспроизведение", L"aopfyflmby - музыкальный плеер", L"Загрузите папку",
    L"Введите название плейлиста:", L"Папка с музыкой:", L"Сохранить", L"Отмена",
    L"Управление плейлистами", L"Название:", L"Изменить", L"Удалить", L"Загрузить",
    L"Плейлист сохранен!", L"Плейлист загружен!", L"Плейлист удален!", L"Плейлист переименован!",
    L"Введите новое название:", L"Загрузка...", L"О приложении"
};

Translation enTexts = {
    L"Load folder", L"Play/Pause", L"＞＞ Next", L"＜＜ Previous",
    L"Playlist", L"Playlists", L"Save playlist", L"Open playlist",
    L"Shuffle", L"Loop", L"➕  Volume", L"➖  Volume",
    L"Settings", L"Language", L"🇷🇺 Russian", L"🇬🇧 English", L"🇨🇳 中文",
    L"Exit", L"No tracks", L"Please load a music folder first",
    L"Failed to initialize BASS\nMake sure bass.dll is in the program folder",
    L"Program is already running!", L"Loaded ", L" tracks", L"No supported audio files in folder",
    L"End of playlist", L"Shuffle ON", L"Shuffle OFF",
    L"Loop ON", L"Loop OFF", L"Error playing file",
    L"Paused", L"Playing", L"aopfyflmby - music player", L"Load a folder",
    L"Enter playlist name:", L"Music folder:", L"Save", L"Cancel",
    L"Manage playlists", L"Name:", L"Edit", L"Delete", L"Load",
    L"Playlist saved!", L"Playlist loaded!", L"Playlist deleted!", L"Playlist renamed!",
    L"Enter new name:", L"Loading...", L"About"
};

Translation zhTexts = {
    L"加载文件夹", L"播放/暂停", L"＞＞ 下一首", L"＜＜ 上一首",
    L"播放列表", L"播放列表", L"保存播放列表", L"打开播放列表",
    L"随机播放", L"循环播放", L"➕  音量", L"➖  音量",
    L"设置", L"语言", L"🇷🇺 俄语", L"🇬🇧 英语", L"🇨🇳 中文",
    L"退出", L"没有歌曲", L"请先加载音乐文件夹",
    L"无法初始化BASS\n请确保bass.dll在程序文件夹中",
    L"程序已经在运行！", L"已加载 ", L" 首歌曲", L"文件夹中没有支持的音频文件",
    L"播放列表结束", L"随机播放 开", L"随机播放 关",
    L"循环播放 开", L"循环播放 关", L"播放文件错误",
    L"已暂停", L"播放中", L"aopfyflmby - 音乐播放器", L"加载文件夹",
    L"输入播放列表名称:", L"音乐文件夹:", L"保存", L"取消",
    L"管理播放列表", L"名称:", L"编辑", L"删除", L"加载",
    L"播放列表已保存!", L"播放列表已加载!", L"播放列表已删除!", L"播放列表已重命名!",
    L"输入新名称:", L"加载中...", L"关于"
};

// Глобальные переменные
NOTIFYICONDATAW nid = { 0 };
HMENU hMenu = NULL;
HMENU hPlaylistMenu = NULL;
HMENU hSettingsMenu = NULL;
HMENU hLanguageMenu = NULL;
HMENU hPlaylistsMenu = NULL;
HWND hWnd = NULL;
HSTREAM stream = 0;
bool isPlaying = false;
std::vector<CachedTrack> playlistCache;
std::vector<std::wstring> playlistPaths;
int currentTrack = -1;
float volume = 0.5f;
bool shuffle = false;
bool loopPlaylist = false;
std::mt19937 rng((unsigned int)time(nullptr));
HANDLE hMutex = NULL;
Language currentLang = LANG_RU;
Translation* texts = &ruTexts;
std::wstring currentFolder;
bool sessionDirty = false;
UINT_PTR saveTimer = 0;
UINT_PTR hideNotifyTimer = 0;

// Флаги для защиты от повторного открытия диалогов
bool isSavePlaylistDialogOpen = false;
bool isOpenPlaylistDialogOpen = false;
bool isFolderDialogOpen = false;

// Для корректного shuffle
std::vector<std::wstring> originalPlaylistPaths;
std::vector<int> shuffleOrder;
int shuffleIndex = -1;

// Объявления функций
void PlayCurrent();
void ShowNotification(const std::wstring& message);
std::wstring OpenFolderDialog();
void NextTrack();
void PrevTrack();
void ToggleShuffle();
void ToggleLoop();
void VolumeUp();
void VolumeDown();
void UpdateTrayIcon(bool playing);
void LoadFolder(const std::wstring& folder);
void UpdatePlaylistMenu();
void UpdateMainMenu();
std::wstring GetDisplayName(const std::wstring& filepath);
void SaveSessionAsync();
void SaveSessionInternal();
void LoadSession();
void SaveSettings();
void LoadSettings();
std::wstring GetDataPath();
std::wstring GetPlaylistsPath();
void SavePlaylist(const std::wstring& name);
void LoadPlaylist(const std::wstring& name);
std::vector<std::wstring> GetPlaylistsList();
INT_PTR CALLBACK SavePlaylistDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK OpenPlaylistDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
void ReadTrackInfo(const std::wstring& filepath, CachedTrack& cached);
TrackInfo GetID3v1Info(const std::wstring& filepath);

// Получение пути к папке data
std::wstring GetDataPath() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);

    // Проверяем, запущена ли программа из Program Files
    if (wcsstr(exePath, L"Program Files") != NULL) {
        // Установленная версия — используем AppData\Roaming
        wchar_t appData[MAX_PATH];
        SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appData);
        std::wstring path = appData;
        path += L"\\aopfyflmby\\";
        CreateDirectoryW(path.c_str(), NULL);
        return path;
    }

    // Портативная версия — сохраняем в папке с программой
    std::wstring path = exePath;
    size_t pos = path.find_last_of(L"\\/");
    if (pos != std::wstring::npos) {
        path = path.substr(0, pos + 1);
    }
    path += L"data\\";
    CreateDirectoryW(path.c_str(), NULL);
    return path;
}

// Получение пути к папке playlists
std::wstring GetPlaylistsPath() {
    std::wstring path = GetDataPath() + L"playlists\\";
    CreateDirectoryW(path.c_str(), NULL);
    return path;
}

// Callback для установки иконки в диалоге выбора папки
int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if (uMsg == BFFM_INITIALIZED) {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));
        SendMessage(GetParent(hwnd), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(GetParent(hwnd), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }
    return 0;
}

// Чтение ID3v1 тега
TrackInfo GetID3v1Info(const std::wstring& filepath) {
    TrackInfo info;
    info.artist = L"";
    info.title = L"";

    FILE* file = NULL;
    _wfopen_s(&file, filepath.c_str(), L"rb");
    if (!file) return info;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    if (fileSize >= 128) {
        fseek(file, fileSize - 128, SEEK_SET);
        char tag[4] = { 0 };
        fread(tag, 1, 3, file);

        if (strcmp(tag, "TAG") == 0) {
            char title[31] = { 0 };
            fread(title, 1, 30, file);
            char artist[31] = { 0 };
            fread(artist, 1, 30, file);

            std::string titleStr(title);
            std::string artistStr(artist);

            titleStr.erase(std::find(titleStr.begin(), titleStr.end(), '\0'), titleStr.end());
            artistStr.erase(std::find(artistStr.begin(), artistStr.end(), '\0'), artistStr.end());

            while (!titleStr.empty() && titleStr.back() == ' ') titleStr.pop_back();
            while (!artistStr.empty() && artistStr.back() == ' ') artistStr.pop_back();

            if (!titleStr.empty()) {
                int len = MultiByteToWideChar(CP_ACP, 0, titleStr.c_str(), -1, NULL, 0);
                if (len > 0) {
                    wchar_t* wstr = new wchar_t[len];
                    MultiByteToWideChar(CP_ACP, 0, titleStr.c_str(), -1, wstr, len);
                    info.title = wstr;
                    delete[] wstr;
                }
            }
            if (!artistStr.empty()) {
                int len = MultiByteToWideChar(CP_ACP, 0, artistStr.c_str(), -1, NULL, 0);
                if (len > 0) {
                    wchar_t* wstr = new wchar_t[len];
                    MultiByteToWideChar(CP_ACP, 0, artistStr.c_str(), -1, wstr, len);
                    info.artist = wstr;
                    delete[] wstr;
                }
            }
        }
    }
    fclose(file);
    return info;
}

// Чтение информации о треке и кэширование
void ReadTrackInfo(const std::wstring& filepath, CachedTrack& cached) {
    cached.filepath = filepath;

    size_t dotPos = filepath.find_last_of(L'.');
    if (dotPos != std::wstring::npos) {
        cached.extension = filepath.substr(dotPos);
        for (auto& c : cached.extension) c = towlower(c);
    }

    std::wstring artist, title;
    if (cached.extension == L".mp3") {
        TrackInfo info = GetID3v1Info(filepath);
        title = info.title;
        artist = info.artist;
    }

    if (!artist.empty() && !title.empty()) {
        cached.displayName = artist + L" - " + title + L" [" + cached.extension + L"]";
    }
    else if (!title.empty()) {
        cached.displayName = title + L" [" + cached.extension + L"]";
    }
    else {
        size_t pos = filepath.find_last_of(L"\\/");
        if (pos != std::wstring::npos) {
            cached.displayName = filepath.substr(pos + 1);
        }
        else {
            cached.displayName = filepath;
        }
    }

    if (cached.displayName.length() > 60) {
        cached.displayName = cached.displayName.substr(0, 57) + L"...";
    }
}

// Получение отображаемого имени из кэша
std::wstring GetDisplayName(const std::wstring& filepath) {
    for (const auto& track : playlistCache) {
        if (track.filepath == filepath) {
            return track.displayName;
        }
    }
    return filepath;
}

// Показать уведомление
void ShowNotification(const std::wstring& message) {
    if (!hWnd) return;

    if (hideNotifyTimer) {
        KillTimer(hWnd, WM_HIDE_NOTIFICATION);
        hideNotifyTimer = 0;
    }

    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;
    wcscpy_s(nid.szInfo, message.c_str());
    wcscpy_s(nid.szInfoTitle, texts->aopfyflmby.c_str());
    Shell_NotifyIconW(NIM_MODIFY, &nid);

    hideNotifyTimer = SetTimer(hWnd, WM_HIDE_NOTIFICATION, 3000, NULL);
}

// Скрыть уведомление
void HideNotification() {
    if (hideNotifyTimer) {
        KillTimer(hWnd, WM_HIDE_NOTIFICATION);
        hideNotifyTimer = 0;
    }
    nid.szInfo[0] = 0;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    Shell_NotifyIconW(NIM_MODIFY, &nid);
}

// Сохранение сессии
void SaveSessionAsync() {
    sessionDirty = true;
    if (saveTimer) KillTimer(hWnd, saveTimer);
    saveTimer = SetTimer(hWnd, WM_SAVE_SESSION, 2000, NULL);
}

void SaveSessionInternal() {
    if (!sessionDirty) return;
    sessionDirty = false;

    std::wstring dataPath = GetDataPath();
    std::wstring filePath = dataPath + L"session.dat";

    FILE* file = NULL;
    _wfopen_s(&file, filePath.c_str(), L"wb");
    if (!file) return;

    size_t len = currentFolder.length();
    fwrite(&len, sizeof(len), 1, file);
    fwrite(currentFolder.c_str(), sizeof(wchar_t), len, file);

    fwrite(&currentTrack, sizeof(currentTrack), 1, file);
    fwrite(&volume, sizeof(volume), 1, file);
    fwrite(&shuffle, sizeof(shuffle), 1, file);
    fwrite(&loopPlaylist, sizeof(loopPlaylist), 1, file);

    size_t playlistSize = playlistPaths.size();
    fwrite(&playlistSize, sizeof(playlistSize), 1, file);

    for (size_t i = 0; i < playlistSize; i++) {
        len = playlistPaths[i].length();
        fwrite(&len, sizeof(len), 1, file);
        fwrite(playlistPaths[i].c_str(), sizeof(wchar_t), len, file);
    }

    size_t shuffleOrderSize = shuffleOrder.size();
    fwrite(&shuffleOrderSize, sizeof(shuffleOrderSize), 1, file);
    for (size_t i = 0; i < shuffleOrderSize; i++) {
        fwrite(&shuffleOrder[i], sizeof(shuffleOrder[i]), 1, file);
    }
    fwrite(&shuffleIndex, sizeof(shuffleIndex), 1, file);

    fclose(file);
}

// Загрузка сессии
void LoadSession() {
    std::wstring dataPath = GetDataPath();
    std::wstring filePath = dataPath + L"session.dat";

    FILE* file = NULL;
    _wfopen_s(&file, filePath.c_str(), L"rb");
    if (!file) return;

    size_t len = 0;
    fread(&len, sizeof(len), 1, file);
    if (len > 0 && len < MAX_PATH) {
        wchar_t* folder = new wchar_t[len + 1];
        fread(folder, sizeof(wchar_t), len, file);
        folder[len] = L'\0';
        currentFolder = folder;
        delete[] folder;

        fread(&currentTrack, sizeof(currentTrack), 1, file);
        fread(&volume, sizeof(volume), 1, file);
        fread(&shuffle, sizeof(shuffle), 1, file);
        fread(&loopPlaylist, sizeof(loopPlaylist), 1, file);

        size_t playlistSize = 0;
        fread(&playlistSize, sizeof(playlistSize), 1, file);

        if (playlistSize > 0 && playlistSize < 10000) {
            playlistPaths.clear();
            playlistCache.clear();
            for (size_t i = 0; i < playlistSize; i++) {
                size_t strLen = 0;
                fread(&strLen, sizeof(strLen), 1, file);
                if (strLen > 0 && strLen < MAX_PATH) {
                    wchar_t* track = new wchar_t[strLen + 1];
                    fread(track, sizeof(wchar_t), strLen, file);
                    track[strLen] = L'\0';
                    playlistPaths.push_back(track);
                    delete[] track;
                }
            }

            for (const auto& path : playlistPaths) {
                CachedTrack cached;
                ReadTrackInfo(path, cached);
                playlistCache.push_back(cached);
            }
        }

        size_t shuffleOrderSize = 0;
        fread(&shuffleOrderSize, sizeof(shuffleOrderSize), 1, file);
        if (shuffleOrderSize > 0 && shuffleOrderSize < 10000) {
            shuffleOrder.resize(shuffleOrderSize);
            for (size_t i = 0; i < shuffleOrderSize; i++) {
                fread(&shuffleOrder[i], sizeof(shuffleOrder[i]), 1, file);
            }
            fread(&shuffleIndex, sizeof(shuffleIndex), 1, file);
        }
        else {
            shuffleOrder.clear();
            shuffleIndex = -1;
        }

        originalPlaylistPaths = playlistPaths;
    }
    fclose(file);
}

// Загрузка папки (синхронная, без потоков)
void LoadFolder(const std::wstring& folder) {
    if (folder.empty()) return;

    playlistPaths.clear();
    playlistCache.clear();

    std::wstring searchPath = folder + L"\\*";
    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::wstring filename = findData.cFileName;
                size_t dotPos = filename.find_last_of(L'.');
                if (dotPos != std::wstring::npos) {
                    std::wstring ext = filename.substr(dotPos);
                    for (auto& c : ext) c = towlower(c);

                    for (const auto& fmt : SUPPORTED_FORMATS) {
                        if (ext == fmt) {
                            std::wstring fullPath = folder + L"\\" + filename;
                            playlistPaths.push_back(fullPath);
                            CachedTrack cached;
                            ReadTrackInfo(fullPath, cached);
                            playlistCache.push_back(cached);
                            break;
                        }
                    }
                }
            }
        } while (FindNextFileW(hFind, &findData));
        FindClose(hFind);
    }

    if (!playlistPaths.empty()) {
        currentFolder = folder;

        originalPlaylistPaths = playlistPaths;

        if (shuffle) {
            shuffleOrder.clear();
            for (size_t i = 0; i < playlistPaths.size(); i++) {
                shuffleOrder.push_back((int)i);
            }
            std::shuffle(shuffleOrder.begin(), shuffleOrder.end(), rng);
            shuffleIndex = 0;
            currentTrack = shuffleOrder[shuffleIndex];

            std::vector<std::wstring> newPaths;
            std::vector<CachedTrack> newCache;
            for (int idx : shuffleOrder) {
                newPaths.push_back(playlistPaths[idx]);
                newCache.push_back(playlistCache[idx]);
            }
            playlistPaths = newPaths;
            playlistCache = newCache;
        }
        else {
            currentTrack = 0;
        }

        UpdatePlaylistMenu();
        PlayCurrent();
        ShowNotification(texts->tracksLoaded + std::to_wstring(playlistPaths.size()) + texts->tracks);
    }
    else {
        ShowNotification(texts->noMusic);
    }

    SaveSessionAsync();
}

// Сохранение настроек
void SaveSettings() {
    std::wstring filePath = GetDataPath() + L"settings.dat";

    FILE* file = NULL;
    _wfopen_s(&file, filePath.c_str(), L"wb");
    if (!file) return;

    int lang = (int)currentLang;
    fwrite(&lang, sizeof(lang), 1, file);
    fclose(file);
}

// Загрузка настроек
void LoadSettings() {
    std::wstring filePath = GetDataPath() + L"settings.dat";

    FILE* file = NULL;
    _wfopen_s(&file, filePath.c_str(), L"rb");
    if (!file) {
        currentLang = DEFAULT_LANGUAGE;
        switch (currentLang) {
        case LANG_RU: texts = &ruTexts; break;
        case LANG_EN: texts = &enTexts; break;
        case LANG_ZH: texts = &zhTexts; break;
        }
        return;
    }

    int lang = 0;
    fread(&lang, sizeof(lang), 1, file);

    currentLang = static_cast<Language>(lang);
    switch (currentLang) {
    case LANG_RU: texts = &ruTexts; break;
    case LANG_EN: texts = &enTexts; break;
    case LANG_ZH: texts = &zhTexts; break;
    default: texts = &ruTexts; break;
    }
    fclose(file);
}

// Сохранение плейлиста
void SavePlaylist(const std::wstring& name) {
    if (playlistPaths.empty()) return;

    std::wstring filePath = GetPlaylistsPath() + name + L".pl";
    FILE* file = NULL;
    _wfopen_s(&file, filePath.c_str(), L"w, ccs=UTF-8");
    if (!file) return;

    fwprintf(file, L"[Folder]\n%s\n\n", currentFolder.c_str());
    fwprintf(file, L"[Tracks]\n");
    for (const auto& track : playlistPaths) {
        fwprintf(file, L"%s\n", track.c_str());
    }
    fclose(file);

    ShowNotification(texts->playlistSaved);
}

// Загрузка плейлиста
void LoadPlaylist(const std::wstring& name) {
    std::wstring filePath = GetPlaylistsPath() + name + L".pl";
    FILE* file = NULL;
    _wfopen_s(&file, filePath.c_str(), L"r, ccs=UTF-8");
    if (!file) return;

    std::vector<std::wstring> newPaths;
    std::wstring newFolder;
    bool inTracks = false;
    wchar_t line[MAX_PATH * 2];

    while (fgetws(line, MAX_PATH * 2, file)) {
        std::wstring str(line);
        str.erase(std::remove(str.begin(), str.end(), L'\n'), str.end());
        str.erase(std::remove(str.begin(), str.end(), L'\r'), str.end());

        if (str == L"[Folder]") continue;
        else if (str == L"[Tracks]") { inTracks = true; continue; }
        else if (str.empty()) continue;

        if (!inTracks && newFolder.empty()) newFolder = str;
        else if (inTracks && !str.empty()) {
            DWORD attrs = GetFileAttributesW(str.c_str());
            if (attrs != INVALID_FILE_ATTRIBUTES) newPaths.push_back(str);
        }
    }
    fclose(file);

    if (!newPaths.empty()) {
        playlistPaths = newPaths;
        playlistCache.clear();
        for (const auto& path : playlistPaths) {
            CachedTrack cached;
            ReadTrackInfo(path, cached);
            playlistCache.push_back(cached);
        }
        currentFolder = newFolder;

        originalPlaylistPaths = playlistPaths;

        if (shuffle) {
            shuffleOrder.clear();
            for (size_t i = 0; i < playlistPaths.size(); i++) {
                shuffleOrder.push_back((int)i);
            }
            std::shuffle(shuffleOrder.begin(), shuffleOrder.end(), rng);
            shuffleIndex = 0;
            currentTrack = shuffleOrder[shuffleIndex];

            std::vector<std::wstring> newPaths;
            std::vector<CachedTrack> newCache;
            for (int idx : shuffleOrder) {
                newPaths.push_back(playlistPaths[idx]);
                newCache.push_back(playlistCache[idx]);
            }
            playlistPaths = newPaths;
            playlistCache = newCache;
        }
        else {
            currentTrack = 0;
        }

        if (stream) {
            BASS_StreamFree(stream);
            stream = 0;
        }

        UpdatePlaylistMenu();
        PlayCurrent();
        ShowNotification(texts->playlistLoaded + L" (" + std::to_wstring(playlistPaths.size()) + L" " + texts->tracks + L")");
        SaveSessionAsync();
    }
    else {
        ShowNotification(texts->noMusic);
    }
}

// Получение списка плейлистов
std::vector<std::wstring> GetPlaylistsList() {
    std::vector<std::wstring> playlists;
    std::wstring searchPath = GetPlaylistsPath() + L"*.pl";
    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::wstring filename = findData.cFileName;
            size_t dotPos = filename.find_last_of(L'.');
            if (dotPos != std::wstring::npos) playlists.push_back(filename.substr(0, dotPos));
        } while (FindNextFileW(hFind, &findData));
        FindClose(hFind);
    }
    std::sort(playlists.begin(), playlists.end());
    return playlists;
}

// Диалог сохранения плейлиста
INT_PTR CALLBACK SavePlaylistDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));
        SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

        SetWindowTextW(hDlg, texts->savePlaylist.c_str());
        SetDlgItemTextW(hDlg, IDC_PLAYLIST_NAME, L"");
        SetDlgItemTextW(hDlg, IDC_FOLDER_PATH, currentFolder.c_str());

        HWND hStaticTitle = GetDlgItem(hDlg, 1009);
        if (hStaticTitle) SetWindowTextW(hStaticTitle, texts->enterPlaylistName.c_str());

        HWND hStaticFolder = GetDlgItem(hDlg, 1010);
        if (hStaticFolder) SetWindowTextW(hStaticFolder, texts->folderPath.c_str());

        SetDlgItemTextW(hDlg, IDOK, texts->save.c_str());
        SetDlgItemTextW(hDlg, IDCANCEL, texts->cancel.c_str());
    }
    return TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            wchar_t name[256];
            GetDlgItemTextW(hDlg, IDC_PLAYLIST_NAME, name, 256);
            std::wstring playlistName(name);

            if (!playlistName.empty()) {
                std::wstring invalidChars = L"\\/:*?\"<>|";
                for (wchar_t c : invalidChars) {
                    playlistName.erase(std::remove(playlistName.begin(), playlistName.end(), c), playlistName.end());
                }
                if (!playlistName.empty()) {
                    EndDialog(hDlg, IDOK);
                    SavePlaylist(playlistName);
                }
            }
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
        }
        break;

    case WM_DESTROY:
        isSavePlaylistDialogOpen = false;
        if (hMenu) EnableMenuItem(hMenu, ID_TRAY_SAVE_PLAYLIST, MF_ENABLED);
        break;
    }
    return FALSE;
}

// Диалог открытия плейлиста
INT_PTR CALLBACK OpenPlaylistDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    static std::vector<std::wstring> playlists;
    static int selectedIndex = -1;

    switch (message) {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));
        SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

        SetWindowTextW(hDlg, texts->openPlaylist.c_str());
        SetDlgItemTextW(hDlg, IDC_PLAYLIST_EDIT, texts->edit.c_str());
        SetDlgItemTextW(hDlg, IDC_PLAYLIST_DELETE, texts->deleteText.c_str());
        SetDlgItemTextW(hDlg, IDOK, texts->loadText.c_str());
        SetDlgItemTextW(hDlg, IDCANCEL, texts->cancel.c_str());

        playlists = GetPlaylistsList();
        selectedIndex = -1;
        HWND hList = GetDlgItem(hDlg, IDC_PLAYLIST_LIST);

        if (hList) {
            SendMessageW(hList, LB_RESETCONTENT, 0, 0);
            for (size_t i = 0; i < playlists.size(); i++) {
                SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)playlists[i].c_str());
            }
            if (!playlists.empty()) {
                SendMessageW(hList, LB_SETCURSEL, 0, 0);
                selectedIndex = 0;
            }
        }

        EnableWindow(GetDlgItem(hDlg, IDOK), !playlists.empty());
        EnableWindow(GetDlgItem(hDlg, IDC_PLAYLIST_EDIT), !playlists.empty());
        EnableWindow(GetDlgItem(hDlg, IDC_PLAYLIST_DELETE), !playlists.empty());
    }
    return TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_PLAYLIST_LIST && HIWORD(wParam) == LBN_SELCHANGE) {
            selectedIndex = (int)SendMessageW(GetDlgItem(hDlg, IDC_PLAYLIST_LIST), LB_GETCURSEL, 0, 0);
        }
        else if (LOWORD(wParam) == IDC_PLAYLIST_EDIT && selectedIndex >= 0 && selectedIndex < (int)playlists.size()) {
            wchar_t newName[256];
            wcscpy_s(newName, playlists[selectedIndex].c_str());

            INT_PTR result = DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_RENAME_PLAYLIST), hDlg,
                [](HWND hDlg2, UINT msg, WPARAM wp, LPARAM lp) -> INT_PTR {
                    static wchar_t* namePtr;
                    if (msg == WM_INITDIALOG) {
                        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));
                        SendMessage(hDlg2, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                        SendMessage(hDlg2, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                        namePtr = (wchar_t*)lp;
                        SetWindowTextW(hDlg2, texts->edit.c_str());
                        SetDlgItemTextW(hDlg2, IDC_PLAYLIST_NAME, namePtr);
                        SetDlgItemTextW(hDlg2, IDOK, texts->save.c_str());
                        SetDlgItemTextW(hDlg2, IDCANCEL, texts->cancel.c_str());
                        HWND hStatic = GetDlgItem(hDlg2, 1009);
                        if (hStatic) SetWindowTextW(hStatic, texts->enterName.c_str());
                        return TRUE;
                    }
                    else if (msg == WM_COMMAND && LOWORD(wp) == IDOK) {
                        wchar_t newNameBuf[256];
                        GetDlgItemTextW(hDlg2, IDC_PLAYLIST_NAME, newNameBuf, 256);
                        wcscpy_s(namePtr, 256, newNameBuf);
                        EndDialog(hDlg2, IDOK);
                        return TRUE;
                    }
                    else if (msg == WM_COMMAND && LOWORD(wp) == IDCANCEL) {
                        EndDialog(hDlg2, IDCANCEL);
                        return TRUE;
                    }
                    return FALSE;
                }, (LPARAM)newName);

            if (result == IDOK) {
                std::wstring oldPath = GetPlaylistsPath() + playlists[selectedIndex] + L".pl";
                std::wstring newPath = GetPlaylistsPath() + newName + L".pl";
                if (MoveFileW(oldPath.c_str(), newPath.c_str())) {
                    playlists[selectedIndex] = newName;
                    HWND hList = GetDlgItem(hDlg, IDC_PLAYLIST_LIST);
                    SendMessageW(hList, LB_DELETESTRING, selectedIndex, 0);
                    SendMessageW(hList, LB_INSERTSTRING, selectedIndex, (LPARAM)newName);
                    SendMessageW(hList, LB_SETCURSEL, selectedIndex, 0);
                    ShowNotification(texts->playlistRenamed);
                }
            }
        }
        else if (LOWORD(wParam) == IDC_PLAYLIST_DELETE && selectedIndex >= 0 && selectedIndex < (int)playlists.size()) {
            std::wstring filePath = GetPlaylistsPath() + playlists[selectedIndex] + L".pl";
            if (DeleteFileW(filePath.c_str())) {
                HWND hList = GetDlgItem(hDlg, IDC_PLAYLIST_LIST);
                SendMessageW(hList, LB_DELETESTRING, selectedIndex, 0);
                playlists.erase(playlists.begin() + selectedIndex);
                selectedIndex = -1;
                if (!playlists.empty()) {
                    SendMessageW(hList, LB_SETCURSEL, 0, 0);
                    selectedIndex = 0;
                }
                EnableWindow(GetDlgItem(hDlg, IDOK), !playlists.empty());
                EnableWindow(GetDlgItem(hDlg, IDC_PLAYLIST_EDIT), !playlists.empty());
                EnableWindow(GetDlgItem(hDlg, IDC_PLAYLIST_DELETE), !playlists.empty());
                ShowNotification(texts->playlistDeleted);
            }
        }
        else if (LOWORD(wParam) == IDOK && selectedIndex >= 0 && selectedIndex < (int)playlists.size()) {
            LoadPlaylist(playlists[selectedIndex]);
            EndDialog(hDlg, IDOK);
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
        }
        break;

    case WM_DESTROY:
        isOpenPlaylistDialogOpen = false;
        if (hMenu) EnableMenuItem(hMenu, ID_TRAY_OPEN_PLAYLIST, MF_ENABLED);
        break;
    }
    return FALSE;
}

// Диалог выбора папки
std::wstring OpenFolderDialog() {
    if (isFolderDialogOpen) return L"";
    isFolderDialogOpen = true;

    BROWSEINFOW bi = { 0 };
    bi.hwndOwner = hWnd;
    bi.lpszTitle = texts->loadFolder.c_str();
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseCallbackProc;

    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
    std::wstring result;

    if (pidl != NULL) {
        wchar_t path[MAX_PATH];
        if (SHGetPathFromIDListW(pidl, path)) {
            result = path;
        }
        CoTaskMemFree(pidl);
    }

    isFolderDialogOpen = false;
    if (hMenu) EnableMenuItem(hMenu, ID_TRAY_LOADFOLDER, MF_ENABLED);
    return result;
}

// Обновление главного меню
void UpdateMainMenu() {
    if (!hMenu) return;

    while (GetMenuItemCount(hMenu) > 0) RemoveMenu(hMenu, 0, MF_BYPOSITION);

    hSettingsMenu = CreatePopupMenu();
    hLanguageMenu = CreatePopupMenu();

    AppendMenuW(hLanguageMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hLanguageMenu, MF_STRING, ID_TRAY_LANG_RU, texts->russian.c_str());
    AppendMenuW(hLanguageMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hLanguageMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hLanguageMenu, MF_STRING, ID_TRAY_LANG_EN, texts->english.c_str());
    AppendMenuW(hLanguageMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hLanguageMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hLanguageMenu, MF_STRING, ID_TRAY_LANG_ZH, texts->chinese.c_str());
    AppendMenuW(hLanguageMenu, MF_SEPARATOR, 0, NULL);

    AppendMenuW(hSettingsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hSettingsMenu, MF_POPUP, (UINT_PTR)hLanguageMenu, texts->language.c_str());
    AppendMenuW(hSettingsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hSettingsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hSettingsMenu, MF_STRING, ID_TRAY_ABOUT, texts->about.c_str());
    AppendMenuW(hSettingsMenu, MF_SEPARATOR, 0, NULL);

    hPlaylistsMenu = CreatePopupMenu();
    AppendMenuW(hPlaylistsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hPlaylistsMenu, MF_STRING, ID_TRAY_SAVE_PLAYLIST, texts->savePlaylist.c_str());
    AppendMenuW(hPlaylistsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hPlaylistsMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hPlaylistsMenu, MF_STRING, ID_TRAY_OPEN_PLAYLIST, texts->openPlaylist.c_str());
    AppendMenuW(hPlaylistsMenu, MF_SEPARATOR, 0, NULL);

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSettingsMenu, texts->settings.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hPlaylistsMenu, texts->playlists.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_LOADFOLDER, texts->loadFolder.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_PLAYPAUSE, texts->playPause.c_str());
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_NEXT, texts->next.c_str());
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_PREV, texts->prev.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);

    hPlaylistMenu = CreatePopupMenu();
    AppendMenuW(hPlaylistMenu, MF_GRAYED, 0, texts->playlistEmpty.c_str());
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hPlaylistMenu, texts->playlist.c_str());

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_SHUFFLE, texts->shuffle.c_str());
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_LOOP, texts->loop.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_VOLUMEUP, texts->volumeUp.c_str());
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_VOLUMEDOWN, texts->volumeDown.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ID_TRAY_EXIT, texts->exit.c_str());
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);

    UpdatePlaylistMenu();
}

// Обновление меню плейлиста
void UpdatePlaylistMenu() {
    if (!hPlaylistMenu) return;
    while (GetMenuItemCount(hPlaylistMenu) > 0) RemoveMenu(hPlaylistMenu, 0, MF_BYPOSITION);

    if (playlistPaths.empty()) {
        AppendMenuW(hPlaylistMenu, MF_GRAYED, 0, texts->noTracks.c_str());
    }
    else {
        for (size_t i = 0; i < playlistCache.size(); i++) {
            std::wstring displayName = playlistCache[i].displayName;
            if ((int)i == currentTrack && stream && BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING) {
                displayName = L"♪♪♪ ▶ " + displayName;
            }
            else if ((int)i == currentTrack) {
                displayName = L"⏸ " + displayName;
            }
            else {
                displayName = L"  " + displayName;
            }
            AppendMenuW(hPlaylistMenu, MF_STRING, 2000 + (int)i, displayName.c_str());
        }
    }
}

// Обновление иконки в трее
void UpdateTrayIcon(bool playing) {
    if (!hWnd) return;

    HICON hIcon = NULL;

    if (playlistPaths.empty()) {
        // Нет треков - показываем warning иконку
        hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_WARNING_ICON));
    }
    else if (playing) {
        // Идет воспроизведение - иконка паузы
        hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PAUSE));
    }
    else {
        // Есть треки, но воспроизведение на паузе/остановлено
        hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MINIMALPLAYER));
    }

    nid.hIcon = hIcon;
    nid.uFlags = NIF_ICON;
    Shell_NotifyIconW(NIM_MODIFY, &nid);
    wcscpy_s(nid.szTip, texts->aopfyflmby.c_str());
    Shell_NotifyIconW(NIM_MODIFY, &nid);
}

// Воспроизведение текущего трека
void PlayCurrent() {
    if (currentTrack < 0 || currentTrack >= (int)playlistPaths.size()) {
        if (stream) {
            BASS_StreamFree(stream);
            stream = 0;
        }
        isPlaying = false;
        UpdateTrayIcon(false);
        return;
    }

    if (stream) {
        BASS_StreamFree(stream);
        stream = 0;
    }

    stream = BASS_StreamCreateFile(FALSE, playlistPaths[currentTrack].c_str(), 0, 0, BASS_STREAM_AUTOFREE);
    if (stream) {
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
        BASS_ChannelPlay(stream, FALSE);
        isPlaying = true;
        UpdateTrayIcon(true);
        SetTimer(hWnd, TIMER_CHECK_PLAYBACK, CHECK_INTERVAL, NULL);

        std::wstring displayName = GetDisplayName(playlistPaths[currentTrack]);
        ShowNotification(L"♫ " + displayName);
    }
    else {
        ShowNotification(texts->errorPlayback);
        isPlaying = false;
        UpdateTrayIcon(false);
    }

    UpdatePlaylistMenu();
    SaveSessionAsync();
}

// Следующий трек
void NextTrack() {
    if (playlistPaths.empty()) return;

    if (shuffle) {
        // Перемешанный режим
        if (shuffleOrder.empty()) return;

        int nextIndex = shuffleIndex + 1;
        if (nextIndex >= (int)shuffleOrder.size()) {
            if (loopPlaylist) {
                nextIndex = 0;
            }
            else {
                if (stream) {
                    BASS_ChannelStop(stream);
                    BASS_StreamFree(stream);
                    stream = 0;
                }
                isPlaying = false;
                UpdateTrayIcon(false);
                KillTimer(hWnd, TIMER_CHECK_PLAYBACK);
                ShowNotification(texts->endOfPlaylist);
                UpdatePlaylistMenu();
                return;
            }
        }
        shuffleIndex = nextIndex;
        currentTrack = shuffleOrder[shuffleIndex];
    }
    else {
        // Обычный режим
        int nextTrack = currentTrack + 1;
        if (nextTrack >= (int)playlistPaths.size()) {
            if (loopPlaylist) {
                nextTrack = 0;
            }
            else {
                if (stream) {
                    BASS_ChannelStop(stream);
                    BASS_StreamFree(stream);
                    stream = 0;
                }
                isPlaying = false;
                UpdateTrayIcon(false);
                KillTimer(hWnd, TIMER_CHECK_PLAYBACK);
                ShowNotification(texts->endOfPlaylist);
                UpdatePlaylistMenu();
                return;
            }
        }
        currentTrack = nextTrack;
    }

    PlayCurrent();
}

// Предыдущий трек
void PrevTrack() {
    if (playlistPaths.empty()) return;

    if (shuffle) {
        // Перемешанный режим
        if (shuffleOrder.empty()) return;

        int prevIndex = shuffleIndex - 1;
        if (prevIndex < 0) {
            if (loopPlaylist) {
                prevIndex = (int)shuffleOrder.size() - 1;
            }
            else {
                prevIndex = 0;
            }
        }
        shuffleIndex = prevIndex;
        currentTrack = shuffleOrder[shuffleIndex];
    }
    else {
        // Обычный режим
        currentTrack = (currentTrack - 1 + (int)playlistPaths.size()) % (int)playlistPaths.size();
    }

    PlayCurrent();
}

// Перемешивание
void ToggleShuffle() {
    shuffle = !shuffle;
    ShowNotification(shuffle ? texts->shuffleOn : texts->shuffleOff);

    if (!originalPlaylistPaths.empty()) {
        if (shuffle) {
            shuffleOrder.clear();
            for (size_t i = 0; i < originalPlaylistPaths.size(); i++) {
                shuffleOrder.push_back((int)i);
            }
            std::shuffle(shuffleOrder.begin(), shuffleOrder.end(), rng);

            for (size_t i = 0; i < shuffleOrder.size(); i++) {
                if (shuffleOrder[i] == currentTrack) {
                    shuffleIndex = (int)i;
                    break;
                }
            }

            std::vector<std::wstring> newPaths;
            std::vector<CachedTrack> newCache;
            for (int idx : shuffleOrder) {
                newPaths.push_back(originalPlaylistPaths[idx]);
                // Важно!!! берем из originalPlaylistPaths, а не из текущего playlistCache
                CachedTrack cached;
                ReadTrackInfo(originalPlaylistPaths[idx], cached);
                newCache.push_back(cached);
            }
            playlistPaths = newPaths;
            playlistCache = newCache;

        }
        else {
            // Выключаем shuffle - возвращаемся к оригинальному порядку. Находим позицию текущего трека в оригинальном списке
            for (size_t i = 0; i < originalPlaylistPaths.size(); i++) {
                if (originalPlaylistPaths[i] == playlistPaths[currentTrack]) {
                    currentTrack = (int)i;
                    break;
                }
            }
            // Восстанавливаем оригинальный порядок
            playlistPaths = originalPlaylistPaths;
            playlistCache.clear();
            for (const auto& path : playlistPaths) {
                CachedTrack cached;
                ReadTrackInfo(path, cached);
                playlistCache.push_back(cached);
            }
        }
        UpdatePlaylistMenu();
    }
    SaveSessionAsync();
}

// Повтор
void ToggleLoop() {
    loopPlaylist = !loopPlaylist;
    ShowNotification(loopPlaylist ? texts->loopOn : texts->loopOff);
    SaveSessionAsync();
}

// Громкость
void VolumeUp() {
    volume = min(1.0f, volume + 0.1f);
    if (stream) BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
}

void VolumeDown() {
    volume = max(0.0f, volume - 0.1f);
    if (stream) BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
}

// Оконная процедура
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_TIMER:
        if (wParam == TIMER_CHECK_PLAYBACK) {
            if (stream && BASS_ChannelIsActive(stream) == BASS_ACTIVE_STOPPED && !playlistPaths.empty()) {
                NextTrack();
            }
        }
        else if (wParam == WM_SAVE_SESSION) {
            KillTimer(hwnd, WM_SAVE_SESSION);
            saveTimer = 0;
            SaveSessionInternal();
        }
        else if (wParam == WM_HIDE_NOTIFICATION) {
            KillTimer(hwnd, WM_HIDE_NOTIFICATION);
            hideNotifyTimer = 0;
            HideNotification();
        }
        break;

    case WM_TRAYICON:
        if (lParam == WM_RBUTTONDOWN) {
            POINT pt;
            GetCursorPos(&pt);

            if (hMenu) {
                MENUITEMINFOW miiShuffle = { 0 }; miiShuffle.cbSize = sizeof(MENUITEMINFOW); miiShuffle.fMask = MIIM_STRING;
                std::wstring shuffleText = shuffle ? L"✓   " + texts->shuffle : texts->shuffle;
                miiShuffle.dwTypeData = (LPWSTR)shuffleText.c_str();
                SetMenuItemInfoW(hMenu, ID_TRAY_SHUFFLE, FALSE, &miiShuffle);

                MENUITEMINFOW miiLoop = { 0 }; miiLoop.cbSize = sizeof(MENUITEMINFOW); miiLoop.fMask = MIIM_STRING;
                std::wstring loopText = loopPlaylist ? L"✓   " + texts->loop : texts->loop;
                miiLoop.dwTypeData = (LPWSTR)loopText.c_str();
                SetMenuItemInfoW(hMenu, ID_TRAY_LOOP, FALSE, &miiLoop);

                MENUITEMINFOW miiPlay = { 0 }; miiPlay.cbSize = sizeof(MENUITEMINFOW); miiPlay.fMask = MIIM_STRING;
                std::wstring playText = isPlaying ? texts->pauseText : texts->playPause;
                miiPlay.dwTypeData = (LPWSTR)playText.c_str();
                SetMenuItemInfoW(hMenu, ID_TRAY_PLAYPAUSE, FALSE, &miiPlay);

                MENUITEMINFOW miiLangRu = { 0 }; miiLangRu.cbSize = sizeof(MENUITEMINFOW); miiLangRu.fMask = MIIM_STRING;
                std::wstring ruText = currentLang == LANG_RU ? texts->russian + L" ✓" : texts->russian;
                miiLangRu.dwTypeData = (LPWSTR)ruText.c_str();
                SetMenuItemInfoW(hLanguageMenu, ID_TRAY_LANG_RU, FALSE, &miiLangRu);

                MENUITEMINFOW miiLangEn = { 0 }; miiLangEn.cbSize = sizeof(MENUITEMINFOW); miiLangEn.fMask = MIIM_STRING;
                std::wstring enText = currentLang == LANG_EN ? texts->english + L" ✓" : texts->english;
                miiLangEn.dwTypeData = (LPWSTR)enText.c_str();
                SetMenuItemInfoW(hLanguageMenu, ID_TRAY_LANG_EN, FALSE, &miiLangEn);

                MENUITEMINFOW miiLangZh = { 0 }; miiLangZh.cbSize = sizeof(MENUITEMINFOW); miiLangZh.fMask = MIIM_STRING;
                std::wstring zhText = currentLang == LANG_ZH ? texts->chinese + L" ✓" : texts->chinese;
                miiLangZh.dwTypeData = (LPWSTR)zhText.c_str();
                SetMenuItemInfoW(hLanguageMenu, ID_TRAY_LANG_ZH, FALSE, &miiLangZh);

                SetForegroundWindow(hwnd);

                HMONITOR monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
                MONITORINFO mi = { sizeof(mi) };
                GetMonitorInfoW(monitor, &mi);

                int screenBottom = mi.rcWork.bottom;
                if (pt.y > screenBottom - 8) {
                    pt.y = screenBottom - 8;
                }

                int screenRight = mi.rcWork.right;
                int menuX = screenRight - 10;

                TrackPopupMenuEx(hMenu, TPM_RIGHTBUTTON | TPM_RIGHTALIGN | TPM_TOPALIGN, menuX, pt.y, hwnd, NULL);
                PostMessage(hwnd, WM_NULL, 0, 0);
            }
        }
        else if (lParam == WM_LBUTTONUP) {
            if (GetKeyState(VK_SHIFT) & 0x8000) {
                // Shift + ЛКМ = следующий трек
                PostMessage(hwnd, WM_COMMAND, ID_TRAY_NEXT, 0);
            }
            else if (GetKeyState(VK_CONTROL) & 0x8000) {
                // Ctrl + ЛКМ = предыдущий трек
                PostMessage(hwnd, WM_COMMAND, ID_TRAY_PREV, 0);
            }
            else {
                // Обычный ЛКМ = пауза/воспроизведение
                PostMessage(hwnd, WM_COMMAND, ID_TRAY_PLAYPAUSE, 0);
            }
        }
        break;

    case WM_COMMAND:
    {
        int cmd = LOWORD(wParam);

        if (cmd >= 2000 && cmd < 2000 + 1000) {
            int trackIndex = cmd - 2000;
            if (trackIndex >= 0 && trackIndex < (int)playlistPaths.size()) {
                currentTrack = trackIndex;
                PlayCurrent();
            }
            break;
        }

        switch (cmd) {
        case ID_TRAY_EXIT:
            SaveSessionInternal();
            SaveSettings();
            DestroyWindow(hwnd);
            break;
        case ID_TRAY_SAVE_PLAYLIST:
            if (!playlistPaths.empty() && !isSavePlaylistDialogOpen) {
                isSavePlaylistDialogOpen = true;
                if (hMenu) EnableMenuItem(hMenu, ID_TRAY_SAVE_PLAYLIST, MF_GRAYED);
                DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SAVE_PLAYLIST), hWnd, SavePlaylistDialogProc);
            }
            else if (playlistPaths.empty()) {
                ShowNotification(texts->noTracks);
            }
            break;
        case ID_TRAY_OPEN_PLAYLIST:
            if (!isOpenPlaylistDialogOpen) {
                isOpenPlaylistDialogOpen = true;
                if (hMenu) EnableMenuItem(hMenu, ID_TRAY_OPEN_PLAYLIST, MF_GRAYED);
                DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_OPEN_PLAYLIST), hWnd, OpenPlaylistDialogProc);
            }
            break;
        case ID_TRAY_LANG_RU:
            currentLang = LANG_RU; texts = &ruTexts; UpdateMainMenu(); UpdateTrayIcon(isPlaying); SaveSettings(); break;
        case ID_TRAY_LANG_EN:
            currentLang = LANG_EN; texts = &enTexts; UpdateMainMenu(); UpdateTrayIcon(isPlaying); SaveSettings(); break;
        case ID_TRAY_LANG_ZH:
            currentLang = LANG_ZH; texts = &zhTexts; UpdateMainMenu(); UpdateTrayIcon(isPlaying); SaveSettings(); break;
        case ID_TRAY_LOADFOLDER:
            if (!isFolderDialogOpen) {
                if (hMenu) EnableMenuItem(hMenu, ID_TRAY_LOADFOLDER, MF_GRAYED);
                std::wstring folder = OpenFolderDialog();
                if (!folder.empty()) LoadFolder(folder);
                if (hMenu) EnableMenuItem(hMenu, ID_TRAY_LOADFOLDER, MF_ENABLED);
            }
            break;
        case ID_TRAY_PLAYPAUSE:
            if (playlistPaths.empty()) ShowNotification(texts->loadFolderFirst);
            else if (stream == 0 && currentTrack >= 0) PlayCurrent();
            else if (stream && BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING) {
                BASS_ChannelPause(stream);
                isPlaying = false;
                UpdateTrayIcon(false);
                UpdatePlaylistMenu();
            }
            else if (stream && BASS_ChannelIsActive(stream) == BASS_ACTIVE_PAUSED) {
                BASS_ChannelPlay(stream, FALSE);
                isPlaying = true;
                UpdateTrayIcon(true);
                UpdatePlaylistMenu();
            }
            else if (currentTrack >= 0) PlayCurrent();
            break;
        case ID_TRAY_NEXT: NextTrack(); break;
        case ID_TRAY_PREV: PrevTrack(); break;
        case ID_TRAY_SHUFFLE: ToggleShuffle(); break;
        case ID_TRAY_LOOP: ToggleLoop(); break;
        case ID_TRAY_VOLUMEUP: VolumeUp(); break;
        case ID_TRAY_VOLUMEDOWN: VolumeDown(); break;
        case ID_TRAY_ABOUT:
            ShellExecuteW(NULL, L"open", L"https://somenmi.github.io/aopfyflmby/", NULL, NULL, SW_SHOW);
            break;
        }
    }
    break;

    case WM_DESTROY:
        KillTimer(hWnd, TIMER_CHECK_PLAYBACK);
        if (saveTimer) KillTimer(hWnd, saveTimer);
        if (hideNotifyTimer) KillTimer(hWnd, hideNotifyTimer);
        if (stream) { BASS_StreamFree(stream); stream = 0; }
        BASS_Free();
        Shell_NotifyIconW(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

// Точка входа
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    hMutex = CreateMutexW(NULL, TRUE, L"aopfyflmby_Mutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxW(NULL, L"Программа уже запущена!", L"aopfyflmby", MB_OK | MB_ICONINFORMATION);
        return 0;
    }

    CoInitialize(NULL);

    LoadSettings();

    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        MessageBoxW(NULL, texts->errorBass.c_str(), L"Error", MB_ICONERROR);
        CoUninitialize();
        return 1;
    }

    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"aopfyflmbyClass";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    RegisterClassExW(&wc);

    hWnd = CreateWindowExW(0, L"aopfyflmbyClass", L"aopfyflmby", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        CoUninitialize();
        return 1;
    }

    nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hWnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    wcscpy_s(nid.szTip, texts->aopfyflmby.c_str());
    Shell_NotifyIconW(NIM_ADD, &nid);

    hMenu = CreatePopupMenu();
    UpdateMainMenu();
    LoadSession();

    // Обновляем иконку в трее в соответствии с текущим состоянием
    if (playlistPaths.empty()) {
        UpdateTrayIcon(false);  // пустой список -> warning иконка
    }
    else if (!playlistPaths.empty() && currentTrack >= 0 && currentTrack < (int)playlistPaths.size()) {
        PlayCurrent();  // PlayCurrent сам вызовет UpdateTrayIcon(true)
    }
    else {
        UpdateTrayIcon(false);  // есть треки, но нет воспроизведения -> иконка MINIMALPLAYER
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CoUninitialize();
    return 0;
}