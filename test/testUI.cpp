#include <bits/stdc++.h>
using namespace std;

void printSpace(int length) {
    cout << string(length, ' ');
}

void printLine(int length) {
    for(int i=0;i<length;i++) cout << "═";
}

void printTitle() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl;

    printSpace(30);
    cout << " ___ __  __                                    " << endl;
    printSpace(30);
    cout << "|_ _|  \\/  |                                   " << endl;
    printSpace(30);
    cout << " | || |\\/| |                                   " << endl;
    printSpace(30);
    cout << " | || |  | |                                   " << endl;
    printSpace(30);
    cout << "|___|_|  |_|_          _                _      " << endl;
    printSpace(30);
    cout << "   / \\  / ___|__ _  __| | ___ _ __ ___ (_) ___ " << endl;
    printSpace(30);
    cout << "  / _ \\| |   / _` |/ _` |/ _ \\ '_ ` _ \\| |/ __|" << endl;
    printSpace(30);
    cout << " / ___ \\ |__| (_| | (_| |  __/ | | | | | | (__ " << endl;
    printSpace(30);
    cout << "/_/   \\_\\____\\__,_|\\__,_|\\___|_| |_| |_|_|\\___|" << endl;
    printSpace(30);
    cout << "\\ \\      / / \\   _ __ _ __(_) ___  _ __        " << endl;
    printSpace(30);
    cout << " \\ \\ /\\ / / _ \\ | '__| '__| |/ _ \\| '__|       " << endl;
    printSpace(30);
    cout << "  \\ V  V / ___ \\| |  | |  | | (_) | |          " << endl;
    printSpace(30);
    cout << "   \\_/\\_/_/   \\_\\_|  |_|  |_|\\___/|_|          " << endl;
    cout << endl;
    /*
    printSpace(45);
    
    */
    printSpace(30);
    printLine(20+14+25);

    cout<<endl;
    printSpace(30+20+18);
    cout << "按 “ENTER” 進入下一頁" <<endl;

    cout<<endl;

}

void printPreface() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;

    printSpace(50);
    cout << "----- 前言 -----"<< endl;
    cout << endl;
    printSpace(30);
    cout << "本遊戲由資管一的喻慈恩、黃靖媛、林妤娟、邱浚祐製作" << endl;
    printSpace(30);
    cout << "內容取材自我們的生活經驗" << endl;
    printSpace(30);
    cout << "如與你有任何雷同，純屬巧合" << endl;
    printSpace(30);
    cout << "希望大家玩得愉快！" << endl;
    cout << endl;
    printSpace(30);
    cout << "2024.12" << endl;
    cout<<endl<<endl<<endl;
    
    printSpace(30);
    printLine(20+14+25);

    cout<<endl;
    printSpace(30+20+18);
    cout << "按 “ENTER” 進入下一頁" <<endl;

    cout<<endl;
}

void printSummary() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;
    
    printSpace(50);
    cout << "----- 前情提要 -----"<<endl;
    cout << endl;
    
    printSpace(30);
    cout <<"你是臺大資管的大一菜鳥，帶著滿腔熱血與一絲忐忑"<<endl;
    printSpace(30);
    cout <<"踏入這座名為「大學」的迷宮"<<endl;
    printSpace(30);
    cout <<"這裡充滿了未知的挑戰與無窮的可能性——"<<endl;
    printSpace(30);
    cout <<"從初次見面的同學到眼花繚亂的選課系統"<<endl;
    printSpace(30);
    cout <<"從期待已久的社團活動到令人頭痛的GPA壓力"<<endl;
    cout<<endl;
    printSpace(30);
    cout <<"然而，大學生活並非如想像般地一帆風順……"<<endl;
    printSpace(30);
    cout <<"「命運」猶如一道無形的力量，冷不防地將你推向天堂或是深淵"<<endl;
    printSpace(30);
    cout <<"而「機會」的天秤兩端總是令人難以取捨，你能否抓住它們？"<<endl;
    printSpace(30);
    cout <<"作為一名新手冒險者，你準備好踏上這段喜淚交織的大學旅程了嗎？"<<endl;

    cout<<endl;
    printSpace(30);
    printLine(20+14+25);

    cout<<endl;
    printSpace(30+20+18);
    cout << "按 “ENTER” 進入下一頁" <<endl;

}

void printInstruction() {
    printSpace(30);
    printLine(20+14+25);
    cout<<endl<<endl;
    
    printSpace(50);
    cout << "----- 操作說明 -----"<<endl;
    cout << endl;

    printSpace(30);
    cout << "◆ 在迷宮裡，請以【WASD】控制角色移動以探索地圖" << endl;
    cout<<endl;
    printSpace(30);
    cout << "◆ 遇上選擇時，請按【Y/N】以進行互動" << endl;
    cout<<endl;
    printSpace(30);
    cout << "◆ 攻擊時，請按【1、2、3】以選擇技能" << endl;
    cout<<endl<<endl;
    printSpace(30);
    printLine(20+14+25);
    
    cout<<endl;
    printSpace(30+20+18);
    cout << "按 “ENTER” 進入下一頁" <<endl;
}

void printGameStart() {
    cout<<endl<<endl<<endl<<endl;
    printSpace(50);
    string s = "那麼，讓我們開始吧！";
    for(int i=0; i<s.length(); i++) {
        cout << s[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(50));
    }

}

int main() {
    system("chcp 65001");
    system("cls");
    printTitle();
    printPreface();
    printSummary();
    printInstruction();
    printGameStart();
    return 0;
}