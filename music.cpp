#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<time.h>
#include <windows.h> // 包含Windows API
#include <mmsystem.h> // 包含多媒体函数
#pragma comment(lib, "winmm.lib")

extern int GameEnd;

// 设置结构体
typedef struct {
	float volume;        // 音量设置
	float animationSpeed; // 动画速度
	int bgmIndex;        // 当前背景音乐索引
	const char** bgmList; // 背景音乐列表
	int bgmCount;        // 背景音乐数量
} Settings;

// 初始化设置
void initSettings(Settings* settings) {
	settings->volume = 0.5f; // 默认音量为50%
	settings->animationSpeed = 1.0f; // 默认动画速度为1.0
	settings->bgmIndex = 0; // 默认背景音乐索引
}

// 设置背景音乐列表
void setBgmList(Settings* settings, const char** list, int count) {
	settings->bgmList = list;
	settings->bgmCount = count;
}

// 停止当前播放的音乐
void stopMusic() {
	mciSendString("stop bgm", NULL, 0, NULL);
	mciSendString("close bgm", NULL, 0, NULL);
}

// 播放音乐的函数
void playMusic(const char* filename) {
	stopMusic();
	char command[256];
	sprintf(command, "open \"%s\" alias bgm", filename);
	DWORD result = mciSendString(command, NULL, 0, NULL);
	if (result != 0) {
		printf("Failed to open music file: %s\n", filename);
		char errorText[256];
		mciGetErrorString(result, errorText, sizeof(errorText));
		printf("MCI Error: %s\n", errorText);
		return;
	}
	mciSendString("play bgm repeat", NULL, 0, NULL);
}

// 切换背景音乐
void switchBgm(Settings* settings) {
	if (settings->bgmCount > 1) {
		settings->bgmIndex = (settings->bgmIndex + 1) % settings->bgmCount;
		playMusic(settings->bgmList[settings->bgmIndex]); // 播放新的BGM
	}
	else {
		printf("No BGM available to switch.\n");
	}
}

// 调整音量
void adjustVolume(Settings* settings, float newVolume) {
	if (newVolume >= 0.0f && newVolume <= 1.0f) {
		settings->volume = newVolume;
		// 更新全局音量设置
	}
	else {
		printf("Invalid volume level. Please enter a value between 0.0 and 1.0.\n");
	}
}

// 设置动画速度
void setAnimationSpeed(Settings* settings, float speed) {
	if (speed > 0.0f) {
		settings->animationSpeed = speed;
	}
	else {
		printf("Invalid animation speed. Please enter a positive value.\n");
	}
}

int Music() {
	Settings settings;
	const char* bgmFiles[] = { "Music\\1.mp3", "Music\\2.mp3", "Music\\3.mp3", "Music\\4.mp3" }; // 使用相对路径

	initSettings(&settings);
	setBgmList(&settings, bgmFiles, sizeof(bgmFiles) / sizeof(bgmFiles[0])); // 设置背景音乐列表

	adjustVolume(&settings, 0.7f); // 调整音量为70%

	setAnimationSpeed(&settings, 0.8f); // 设置动画速度为0.8

	srand((unsigned int)time(NULL)); // 初始化随机数种子

	// 随机播放背景音乐
	do {
		switchBgm(&settings); // 切换到下一首BGM
		// 等待音乐播放结束
		while (mciSendString("status bgm mode", NULL, 0, NULL) == 0) {
			Sleep(100); // 每100毫秒检查一次
			if (GameEnd) goto end;// 如果检测到游戏结束，跳出循环，关闭音乐
		}
	} while (mciSendString("status bgm mode", NULL, 0, NULL) != 0); // 检查是否还有音乐在播放
	end:
	stopMusic(); // 停止音乐
	return 0;
}