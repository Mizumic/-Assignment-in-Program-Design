#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<string.h>
#include <bits/stdc++.h>
#include <graphics.h>
#include <mmsystem.h>
#include<windows.h>
using namespace std;
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
	PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
}
// 播放音乐的函数
void playMusic(const char* filename) {
	stopMusic(); // 停止当前播放的音乐
	PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // 播放新的BGM
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
	}
	else {
		printf("Invalid volume level.Please enter a value between 0.0 and 1.0.\n");
	}
}
// 设置动画速度
void setAnimationSpeed(Settings* settings, float speed) {
	if (speed > 0.0f) {
		settings->animationSpeed = speed;
	}
	else {
		printf("Invalid animation speed.Please enter a positive value.\n");
	}
}

//int main() {
//	Settings settings;
//	const char* bgmFiles[] = { "Music\1.mp3", "Music\2.mp3", "Music\3.mp3", "Music\4.mp3" }; // 背景音乐文件列表
//	initSettings(&settings);
//	setBgmList(&settings, bgmFiles, sizeof(bgmFiles) / sizeof(bgmFiles[0])); // 设置背景音乐列表
//
//	return 0;
//
//}
//
