#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Shape.h"
#include "Elfmath.h"

#define WIDTH 40
#define HEIGHT 24



// ���� ������ ��ũ�� ���� ����
char screenBuffer[HEIGHT * (2 * WIDTH)];

// ȭ�� �ʱ�ȭ �Լ�
void Init() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH * 2; x++) {
            screenBuffer[y * WIDTH * 2 + x] = ' ';
        }
    }
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ȭ�� ��� �Լ�
void Draw() {
    system("cls");  // ȭ�� �����
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH * 2; x++) {
            putchar(screenBuffer[y * WIDTH * 2 + x]);
        }
        putchar('\n');
    }
}


void ShowInitialScreen() {
    Init();  // ȭ�� �ʱ�ȭ
    const char* message = "20201552 �ӵ���";  // ����� �ѱ� ���� �޽���
    int msgLen = strlen(message);  // �޽����� ���� ���� (����Ʈ ����)

    // �ѱ��� 2����Ʈ �����̹Ƿ� �߾� ��ġ ��� (���� ���� ����)
    int charCount = msgLen / 2;  // �ѱ��� 2����Ʈ, �� ���� �� ���
    int startX = (WIDTH - charCount) / 2;  // �߾� ��ġ ���
    int startY = HEIGHT / 2;

    // �޽����� ȭ�� ���ۿ� ���� (�ѱ� 2����Ʈ ó��)
    int bufferIndex = startY * WIDTH * 2 + startX * 2;
    for (int i = 0; i < msgLen; i += 2) {
        screenBuffer[bufferIndex] = message[i];         // ù ��° ����Ʈ
        screenBuffer[bufferIndex + 1] = message[i + 1]; // �� ��° ����Ʈ
        bufferIndex += 2;  // �� ���ڴ� 2ĭ(�ȼ�)�� �̵�
    }

    Draw();  // ȭ�� ���
}


// ���� ��� �Լ�


// ���� ���� üũ �Լ�


// ���� �׸��� �Լ�
void DrawShape() {
    Vector3D a1 = { 15, 10, 0 };
    Vector3D b1 = { 20, 17, 0 };
    Vector3D c1 = { 25, 10, 0 };

    // �簢�� ��ǥ
    Vector3D a2 = { 30, 10, 0 };
    Vector3D b2 = { 34, 10, 0 };
    Vector3D c2 = { 34, 14, 0 };
    Vector3D d2 = { 30, 14, 0 };

    // ���� �߽ɰ� ������
    Vector3D center = { 36, 12, 0 };
    float radius = 1.5;

    // ȭ�� ���ۿ� �ﰢ��, �簢��, �� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        int adjustedY = HEIGHT - 1 - y;
        for (int x = 0; x < WIDTH; x++) {
            Vector3D p = { x, adjustedY, 0 };
            if (isInsideTriangle(p, a1, b1, c1)) {
                screenBuffer[y * WIDTH * 2 + x * 2] = 'S';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'S';
            }
            else if (isInsideSquare(p, a2, b2, c2, d2)) {
                screenBuffer[y * WIDTH * 2 + x * 2] = 'E';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'E';
            }
            else if (isInsideCircle(p, center, radius)) {
                screenBuffer[y * WIDTH * 2 + x * 2] = 'M';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'M';
            }
        }
    }

    Draw();
}

void RotateTriangle(float elapsedTime) {
    // �ﰢ�� ������ �ʱ�ȭ (�ʱ� ��ǥ�� static���� ����)
    static Vector3D a1 = { 15, 10, 1 };
    static Vector3D b1 = { 20, 17, 1 };
    static Vector3D c1 = { 25, 10, 1 };

    // �ﰢ�� �߽� ���
    Vector3D center = {
        (a1.x + b1.x + c1.x) / 3.0f,
        (a1.y + b1.y + c1.y) / 3.0f,
        1
    };

    // ȸ�� ���� ��� (3�ʿ� 1����, �ݽð� ����)
    float theta = 120.0f * elapsedTime;  // �ʴ� 120�� ȸ��

    // ȸ�� ��� ����
    Matrix3x3 moveToOrigin = translation_matrix(-center.x, -center.y);
    Matrix3x3 rotation = rotation_matrix(theta);
    Matrix3x3 moveBack = translation_matrix(center.x, center.y);

    // ���� ��ȯ ��� ���
    Matrix3x3 transform = multiply_matrices(moveBack, multiply_matrices(rotation, moveToOrigin));

    // �� ���� ��ȯ ����
    a1 = multiply_matrix_vector(transform, a1);
    b1 = multiply_matrix_vector(transform, b1);
    c1 = multiply_matrix_vector(transform, c1);

    // ȭ�� ���ۿ� �ﰢ�� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        int adjustedY = HEIGHT - 1 - y;
        for (int x = 0; x < WIDTH; x++) {
            Vector3D p = { x, adjustedY, 1 };
            if (isInsideTriangle(p, a1, b1, c1)) {
                screenBuffer[y * WIDTH * 2 + x * 2] = 'S';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'S';
            }
        }
    }
}





// ���� ������ ������ �߽� ����
static Vector3D squareCenter;

void RotateSquare(float elapsedTime, Vector3D triangleCenter) {
    static Vector3D a2 = { 30, 10, 1 };
    static Vector3D b2 = { 34, 10, 1 };
    static Vector3D c2 = { 34, 14, 1 };
    static Vector3D d2 = { 30, 14, 1 };

    // �簢�� �߽� ���
    squareCenter = (Vector3D){
        (a2.x + b2.x + c2.x + d2.x) / 4.0f,
        (a2.y + b2.y + c2.y + d2.y) / 4.0f,
        1
    };

    // ���� ���� ��� (3�ʿ� 1����, �ð� ����)
    float orbitTheta = 120.0f * elapsedTime;
    Matrix3x3 orbitMoveToOrigin = translation_matrix(-triangleCenter.x, -triangleCenter.y);
    Matrix3x3 orbitRotation = rotation_matrix2(orbitTheta);  // �ð� ���� ȸ��
    Matrix3x3 orbitMoveBack = translation_matrix(triangleCenter.x, triangleCenter.y);
    Matrix3x3 orbitTransform = multiply_matrices(orbitMoveBack, multiply_matrices(orbitRotation, orbitMoveToOrigin));

    // ���� ���� ��� (2�ʿ� 1����, �ð� ����)
    float spinTheta = -180.0f * elapsedTime;
    Matrix3x3 spinMoveToOrigin = translation_matrix(-squareCenter.x, -squareCenter.y);
    Matrix3x3 spinRotation = rotation_matrix(spinTheta);  // �ð� ���� ����
    Matrix3x3 spinMoveBack = translation_matrix(squareCenter.x, squareCenter.y);
    Matrix3x3 spinTransform = multiply_matrices(spinMoveBack, multiply_matrices(spinRotation, spinMoveToOrigin));

    // ���� ��ȯ (���� + ����)
    Matrix3x3 finalTransform = multiply_matrices(orbitTransform, spinTransform);

    // �� �������� ���� ��ȯ ����
    a2 = multiply_matrix_vector(finalTransform, a2);
    b2 = multiply_matrix_vector(finalTransform, b2);
    c2 = multiply_matrix_vector(finalTransform, c2);
    d2 = multiply_matrix_vector(finalTransform, d2);

    // ȭ�� ���ۿ� �簢�� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        int adjustedY = HEIGHT - 1 - y;
        for (int x = 0; x < WIDTH; x++) {
            Vector3D p = { x, adjustedY, 1 };
            if (isInsideSquare(p, a2, b2, c2, d2)) {
                screenBuffer[y * WIDTH * 2 + x * 2] = 'E';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'E';
            }
        }
    }
}

void RotateMoon(float elapsedTime) {
    static Vector3D moon;
    static bool isInitialized = false;

    if (!isInitialized) {
        moon = (Vector3D){ squareCenter.x + 4, squareCenter.y, 1 };
        isInitialized = true;
    }

    // ���� ���� ��� (2�ʴ� 1����, �ݽð� ����)
    float orbitTheta = 180.0f * elapsedTime; // �ʴ� 180��
    Matrix3x3 orbitMoveToOrigin = translation_matrix(-squareCenter.x, -squareCenter.y);
    Matrix3x3 orbitRotation = rotation_matrix(orbitTheta); // �ݽð� ���� ȸ��
    Matrix3x3 orbitMoveBack = translation_matrix(squareCenter.x, squareCenter.y);
    Matrix3x3 orbitTransform = multiply_matrices(orbitMoveBack, multiply_matrices(orbitRotation, orbitMoveToOrigin));

    // ���� ���� ��� (1�ʴ� 1����, �ð� ����)
    float spinTheta = -360.0f * elapsedTime; // �ʴ� 360��
    Matrix3x3 spinMoveToOrigin = translation_matrix(-moon.x, -moon.y);
    Matrix3x3 spinRotation = rotation_matrix(spinTheta); // �ð� ���� ����
    Matrix3x3 spinMoveBack = translation_matrix(moon.x, moon.y);
    Matrix3x3 spinTransform = multiply_matrices(spinMoveBack, multiply_matrices(spinRotation, spinMoveToOrigin));

    // ���� ��ȯ ����
    moon = multiply_matrix_vector(orbitTransform, moon);

    // ȭ�� ���ۿ� �� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        int adjustedY = HEIGHT - 1 - y;
        for (int x = 0; x < WIDTH; x++) {
            Vector3D p = { x, adjustedY, 1 };
            if (isInsideCircle(p, moon, 2.0f)) { // ���� ������ 1
                screenBuffer[y * WIDTH * 2 + x * 2] = 'M';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'M';
            }
        }
    }
}









void DrawAllShapes(float elapsedTime) {
    Init();  // ȭ�� �ʱ�ȭ


    // �ﰢ��(SS) �߽� ���
    Vector3D triangleCenter = GetTriangleCenter();

    // �簢��(EE) ȸ�� �� ���� ó��
    RotateSquare(elapsedTime, triangleCenter);
    Vector3D squareCenter = GetSquareCenter(); // ����(���簢��) �߽� ��ǥ ����

    RotateMoon(elapsedTime);
    // �ﰢ��(SS) ȸ�� ó��
    RotateTriangle(elapsedTime);

    Draw();  // ȭ�� ���
}



// ���� �Լ�
int main() {
    ShowInitialScreen();  // �ʱ� ȭ�� ���

    int spacebarCount = 0;
    float previousTime = clock() / (float)CLOCKS_PER_SEC;

    while (1) {
        float currentTime = clock() / (float)CLOCKS_PER_SEC;
        float deltaTime = currentTime - previousTime;  // ������ �� ��� �ð�
        previousTime = currentTime;

        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) {  // ESC Ű�� ������ ����
                break;
            }
            else if (ch == 32) {  // �����̽��� �Է�
                spacebarCount++;
                if (spacebarCount == 1) {
                    Init();
                    DrawShape();  // �ʱ� ���� ���
                }
            }
        }

        // �� ��° �����̽��� �Է� ����
        if (spacebarCount == 2) {
            DrawAllShapes(deltaTime);
            Sleep(33);
        }



    }

    return 0;
}