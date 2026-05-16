#include "raylib.h"

// مصفوفة اللعبة: 0 يعني فارغ، 1 يعني X، و 2 يعني O
int board[3][3] = {0}; 
int player = 1; // 1 = X, 2 = O
int gameResult = -1; // -1 = مستمرة، 0 = تعادل، 1 = فوز X، 2 = فوز O

// دالة التحقق من الفوز
void checkWin() {
    // فحص الصفوف والأعمدة
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) { gameResult = board[i][0]; return; }
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) { gameResult = board[0][i]; return; }
    }
    // فحص الأقطار
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) { gameResult = board[0][0]; return; }
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) { gameResult = board[0][2]; return; }

    // فحص التعادل
    int draw = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) draw = 0;
        }
    }
    if (draw) gameResult = 0;
}

int main() {
    // أبعاد الشاشة الافتراضية للكمبيوتر (سيتم ملاءمتها للهاتف تلقائياً لاحقاً)
    const int screenWidth = 450;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Tic-Tac-Toe Mobile");
    SetTargetFPS(60);

    // حساب حجم وموقع المربع ليكون في المنتصف وضخم جداً
    int cellSize = 100;
    int startX = (screenWidth - (cellSize * 3)) / 2;
    int startY = (screenHeight - (cellSize * 3)) / 2;

    while (!WindowShouldClose()) {
        // إدارة اللمس (Touch) أو ضغط الفأرة
        if (gameResult == -1 && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetTouchPointCount() > 0)) {
            Vector2 touchPos = (GetTouchPointCount() > 0) ? GetTouchPosition(0) : GetMousePosition();
            
            // معرفة أي مربع تم لمسه
            int col = (touchPos.x - startX) / cellSize;
            int row = (touchPos.y - startY) / cellSize;

            if (col >= 0 && col < 3 && row >= 0 && row < 3 && board[row][col] == 0) {
                board[row][col] = player;
                checkWin();
                player = (player == 1) ? 2 : 1;
            }
        }
        
        // إعادة تشغيل اللعبة عند لمس الشاشة بعد انتهاء اللعبة
        if (gameResult != -1 && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetTouchPointCount() > 0)) {
            for(int i=0; i<3; i++) for(int j=0; j<3; j++) board[i][j] = 0;
            player = 1;
            gameResult = -1;
        }

        // الرسم والتصميم (صندوقي، ناعم، مريح للعين، وفي المنتصف تماماً)
        BeginDrawing();
        ClearBackground(BLACK); // خلفية سوداء هادئة بدون أي نشاز دائم

        // عنوان اللعبة في الأعلى بحجم كبير
        DrawText("TIC - TAC - TOE", screenWidth/2 - MeasureText("TIC - TAC - TOE", 30)/2, startY - 100, 30, WHITE);

        // رسم شبكة الخطوط الصندوقية المتصلة بدقة وهندسة
        for (int i = 0; i <= 3; i++) {
            DrawLineEx((Vector2){startX, startY + i*cellSize}, (Vector2){startX + 3*cellSize, startY + i*cellSize}, 3, GRAY);
            DrawLineEx((Vector2){startX + i*cellSize, startY}, (Vector2){startX + i*cellSize, startY + 3*cellSize}, 3, GRAY);
        }

        // رسم الـ X والـ O بداخل المربعات بحجم كبير جداً وواضح
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = startX + j * cellSize + cellSize/2;
                int y = startY + i * cellSize + cellSize/2;
                if (board[i][j] == 1) {
                    DrawText("X", x - MeasureText("X", 50)/2, y - 25, 50, RED);
                } else if (board[i][j] == 2) {
                    DrawText("O", x - MeasureText("O", 50)/2, y - 25, 50, BLUE);
                }
            }
        }

        // طباعة النتيجة أو دور من الحالي أسفل اللوحة
        if (gameResult == -1) {
            char turnText[20];
            int size = 20;
            if (player == 1) DrawText("PLAYER: X (RED)", screenWidth/2 - MeasureText("PLAYER: X (RED)", size)/2, startY + 3*cellSize + 50, size, RED);
            else DrawText("PLAYER: O (BLUE)", screenWidth/2 - MeasureText("PLAYER: O (BLUE)", size)/2, startY + 3*cellSize + 50, size, BLUE);
        } else {
            int size = 25;
            if (gameResult == 0) DrawText("==> GAME DRAW! <==", screenWidth/2 - MeasureText("==> GAME DRAW! <==", size)/2, startY + 3*cellSize + 50, size, ORANGE);
            else if (gameResult == 1) DrawText("==> PLAYER X WINS! <==", screenWidth/2 - MeasureText("==> PLAYER X WINS! <==", size)/2, startY + 3*cellSize + 50, size, GREEN);
            else DrawText("==> PLAYER O WINS! <==", screenWidth/2 - MeasureText("==> PLAYER O WINS! <==", size)/2, startY + 3*cellSize + 50, size, GREEN);
            
            DrawText("Touch anywhere to restart", screenWidth/2 - MeasureText("Touch anywhere to restart", 15)/2, startY + 3*cellSize + 100, 15, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
