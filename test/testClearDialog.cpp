#include <iostream>
#include <string>
#include <vector>

// 繪製地圖和對話框
void drawUI() {
    // 地圖部分
    std::cout << "═══════════════════  遊戲畫面  ══════════════════\n";
    std::cout << "........c..............c...cB...\n";
    std::cout << "c.......C....d...........B......\n";
    std::cout << "........D.......................\n";
    std::cout << ".......c....D.............C.....\n";

    // 對話框部分
    std::cout << "╠═════════════════════════════════════════╣\n";
    std::cout << "║ >                                      ║\n";
    std::cout << "║                                        ║\n";
    std::cout << "║                                        ║\n";
    std::cout << "║                                        ║\n";
    std::cout << "╚═════════════════════════════════════════╝\n";
    std::cout << "WASD探索地圖          Y/N決定選項          ENTER進入下一頁\n";
}

// 更新對話框內容
void updateDialog(const std::vector<std::string>& dialogLines) {
    int dialogStartRow = 6; // 對話框內容起始列（第6行）
    
    // 覆蓋對話框內容
    for (int i = 0; i < 4; ++i) {
        // 將光標移動到對話框對應的行
        std::cout << "\033[" << (dialogStartRow + i) << ";4H"; // 4H 將光標移到第4列
        if (i < dialogLines.size()) {
            std::cout << dialogLines[i]; // 輸出對應行
        } else {
            std::cout << "                                        "; // 清空多餘的行
        }
    }
    std::cout.flush();
}

int main() {
    drawUI(); // 畫出初始畫面
    
    // 模擬對話框更新
    std::vector<std::string> dialog1 = {
        "冒險開始了！",
        "你遇到了一隻怪物。",
        "請選擇你的動作。",
        ""
    };
    updateDialog(dialog1); // 更新對話框內容

    

    std::vector<std::string> dialog2 = {
        "怪物被擊敗了！",
        "你獲得了經驗值。",
        "",
        ""
    };
    updateDialog(dialog2); // 再次更新對話框內容

    return 0;
}