//	main.cpp
#include "MIDIPlayer.h"
#include <iostream>
#include <thread>

using namespace std;

vector<string> get_all_files(const string &path) {
    vector<string> files;
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    hFind = FindFirstFile(path.c_str(), &findData); //������һ���ļ�������������������������򷵻�TRUE
    if (hFind == INVALID_HANDLE_VALUE) {
        return files;
    }
    do {
        // ����"."��".."�������
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)   //strcmp �Ƚ��ַ�����ͬ�򷵻�0
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
        const char *menu[] = {"1 --- ����midi�ļ�",
                              "2 --- ѡ�񲥷�ģʽ",
                              "3 --- �Ƿ���ʾmidi����",
                              "0 --- �˳�",
                              "��ѡ�� "};
        for (auto &i: menu) {
            std::cout << i << std::endl;
        }

        std::cin >> choice;
        switch (choice) {
            case 1:
                // ����midi�ļ� ��ʼ
                midi_files = get_all_files("../midi/*.mid");
                std::cout << "��ѡ��һ��midi�ļ���" << std::endl;
                for (int i = 0; i < midi_files.size(); ++i) {
                    std::cout << i << " : " << midi_files[i] << std::endl;
                }
                int index;
                std::cin >> index;
                static const char *type_str[2] = {"������", "������"};
                std::cout << " ���ڲ��ŵ��ǣ�" << midi_files[index]
                          << " ����ģʽ��" << type_str[midiPlayer.play_type]
                          << " �Ƿ���ʾmidi���ݣ�" << (midiPlayer.show_msg ? "��" : "��") << std::endl;
                midiPlayer.play(("../midi/" + midi_files[index]).c_str());
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
                // ����midi�ļ� ����
            case 2:
                // ����ѡ�� ��ʼ
                std::cout << "1 --- �����첥��" << std::endl;
                std::cout << "2 --- �����첥��" << std::endl;
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
                // ����ѡ�� ����
            case 3:
                // �Ƿ���ʾ��Ϣ ��ʼ
                std::cout << "1 --- ��ʾmidi����" << std::endl;
                std::cout << "2 --- ����ʾmidi����" << std::endl;
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
                // �Ƿ���ʾ��Ϣ ����
            default:
                // �˳�
                goto end;
        }

    }
    end:
    std::cout << "Bye!" << endl;
}
