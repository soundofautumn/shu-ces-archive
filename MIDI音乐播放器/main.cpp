//	main.cpp
#include "MIDIPlayer.h"
#include <iostream>
#include <thread>

using namespace std;

vector<string> get_all_files(const string &path) {
    vector<string> files;
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    hFind = FindFirstFile(path.c_str(), &findData); //搜索第一个文件，创建并返回搜索句柄，有则返回TRUE
    if (hFind == INVALID_HANDLE_VALUE) {
        return files;
    }
    do {
        // 忽略"."和".."两个结果
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)   //strcmp 比较字符，相同则返回0
            continue;
        files.emplace_back(findData.cFileName);
    } while (FindNextFile(hFind, &findData));
    return files;
}

int main() {
    int choice;
    MIDIPlayer midiPlayer;
    vector<string> midi_files;
    while (true) {
        // main loop begin
        const char *menu[] = {"1 --- 播放midi文件",
                              "2 --- 选择播放模式",
                              "3 --- 是否显示midi内容",
                              "0 --- 退出",
                              "请选择： "};
        for (auto &i: menu) {
            std::cout << i << std::endl;
        }

        std::cin >> choice;
        switch (choice) {
            case 1:
                // 播放midi文件 开始
                midi_files = get_all_files("../midi/*.mid");
                std::cout << "请选择一个midi文件：" << std::endl;
                for (int i = 0; i < midi_files.size(); ++i) {
                    std::cout << i << " : " << midi_files[i] << std::endl;
                }
                int index;
                std::cin >> index;
                static const char *type_str[2] = {"单音轨", "多音轨"};
                std::cout << " 现在播放的是：" << midi_files[index]
                          << " 播放模式：" << type_str[midiPlayer.play_type]
                          << " 是否显示midi内容：" << (midiPlayer.show_msg ? "是" : "否") << std::endl;
                midiPlayer.play(("../midi/" + midi_files[index]).c_str());
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
                // 播放midi文件 结束
            case 2:
                // 音轨选择 开始
                std::cout << "1 --- 单音轨播放" << std::endl;
                std::cout << "2 --- 多音轨播放" << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        midiPlayer.play_type = MIDIPlayer::SINGLE_TRACK;
                        break;
                    case 2:
                        midiPlayer.play_type = MIDIPlayer::MULTI_TRACK;
                        break;
                    default:
                        break;
                }
                break;
                // 音轨选择 结束
            case 3:
                // 是否显示消息 开始
                std::cout << "1 --- 显示midi内容" << std::endl;
                std::cout << "2 --- 不显示midi内容" << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        midiPlayer.show_msg = true;
                        break;
                    case 2:
                        midiPlayer.show_msg = false;
                        break;
                    default:
                        break;
                }
                break;
                // 是否显示消息 结束
            default:
                // 退出
                goto end;
        }

    }
    end:
    std::cout << "Bye!" << endl;
}
