#include "raylib.h"

int board[3][3] = {0}; 
int player = 1; 
int gameResult = -1; 

void checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) { gameResult = board[i][0]; return; }
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) { gameResult = board[0][i]; return; }
    }
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) { gameResult = board[0][0]; return; }
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) { gameResult = board[0][2]; return; }

    int draw = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) draw = 0;
        }
    }
    if (draw) gameResult = 0;
}

int main() {
    // إعدادات تناسب شاشات الهواتف تلقائياً
    const int screenWidth = 450;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Tic-Tac-Toe");
    SetTargetFPS(60);

    int cellSize = 110;
    int startX = (screenWidth - (cellSize * 3)) / 2;
    int startY = (screenHeight - (cellSize * 3)) / 2;

    while (!WindowShouldClose()) {
        // فحص اللمس على شاشة الهاتف
        if (gameResult == -1 && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetTouchPointCount() > 0)) {
            Vector2 touchPos = (GetTouchPointCount() > 0) ? GetTouchPosition(0) : GetMousePosition();
            
            int col = (touchPos.x - startX) / cellSize;
            int row = (touchPos.y - startY) / cellSize;

            if (col >= 0 && col < 3 && row >= 0 && row < 3 && board[row][col] == 0) {
                board[row][col] = player;
                checkWin();
                player = (player == 1) ? 2 : 1;
            }
        }
        
        if (gameResult != -1 && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetTouchPointCount() > 0)) {
            for(int i=0; i<3; i++) for(int j=0; j<3; j++) board[i][j] = 0;
            player = 1;
            gameResult = -1;
        }

        BeginDrawing();
        ClearBackground(BLACK); 

        DrawText("TIC - TAC - TOE", screenWidth/2 - MeasureText("TIC - TAC - TOE", 32)/2, startY - 100, 32, WHITE);

        // رسم الشبكة
        for (int i = 0; i <= 3; i++) {
            DrawLineEx((Vector2){startX, startY + i*cellSize}, (Vector2){startX + 3*cellSize, startY + i*cellSize}, 4, LIGHTGRAY);
            DrawLineEx((Vector2){startX + i*cellSize, startY}, (Vector2){startX + i*cellSize, startY + 3*cellSize}, 4, LIGHTGRAY);
        }

        // رسم العناصر
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = startX + j * cellSize + cellSize/2;
                int y = startY + i * cellSize + cellSize/2;
                if (board[i][j] == 1) {
                    DrawText("X", x - MeasureText("X", 60)/2, y - 30, 60, RED);
                } else if (board[i][j] == 2) {
                    DrawText("O", x - MeasureText("O", 60)/2, y - 30, 60, BLUE);
                }
            }
        }

        if (gameResult == -1) {
            if (player == 1) DrawText("PLAYER: X", screenWidth/2 - MeasureText("PLAYER: X", 24)/2, startY + 3*cellSize + 60, 24, RED);
            else DrawText("PLAYER: O", screenWidth/2 - MeasureText("PLAYER: O", 24)/2, startY + 3*cellSize + 60, 24, BLUE);
        } else {
            if (gameResult == 0) DrawText("DRAW!", screenWidth/2 - MeasureText("DRAW!", 26)/2, startY + 3*cellSize + 60, 26, ORANGE);
            else if (gameResult == 1) DrawText("PLAYER X WINS!", screenWidth/2 - MeasureText("PLAYER X WINS!", 26)/2, startY + 3*cellSize + 60, 26, GREEN);
            else DrawText("PLAYER O WINS!", screenWidth/2 - MeasureText("PLAYER O WINS!", 26)/2, startY + 3*cellSize + 60, 26, GREEN);
            
            DrawText("Touch to restart", screenWidth/2 - MeasureText("Touch to restart", 18)/2, startY + 3*cellSize + 110, 18, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
