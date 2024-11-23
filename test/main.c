#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Shape.h"
#include "Elfmath.h"

#define WIDTH 40
#define HEIGHT 24



// 전역 변수로 스크린 버퍼 선언
char screenBuffer[HEIGHT * (2 * WIDTH)];

// 화면 초기화 함수
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

// 화면 출력 함수
void Draw() {
    system("cls");  // 화면 지우기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH * 2; x++) {
            putchar(screenBuffer[y * WIDTH * 2 + x]);
        }
        putchar('\n');
    }
}


void ShowInitialScreen() {
    Init();  // 화면 초기화
    const char* message = "20201552 임동민";  // 출력할 한글 포함 메시지
    int msgLen = strlen(message);  // 메시지의 실제 길이 (바이트 단위)

    // 한글은 2바이트 문자이므로 중앙 위치 계산 (문자 개수 기준)
    int charCount = msgLen / 2;  // 한글은 2바이트, 총 문자 수 계산
    int startX = (WIDTH - charCount) / 2;  // 중앙 위치 계산
    int startY = HEIGHT / 2;

    // 메시지를 화면 버퍼에 삽입 (한글 2바이트 처리)
    int bufferIndex = startY * WIDTH * 2 + startX * 2;
    for (int i = 0; i < msgLen; i += 2) {
        screenBuffer[bufferIndex] = message[i];         // 첫 번째 바이트
        screenBuffer[bufferIndex + 1] = message[i + 1]; // 두 번째 바이트
        bufferIndex += 2;  // 한 글자당 2칸(픽셀)씩 이동
    }

    Draw();  // 화면 출력
}


// 외적 계산 함수


// 도형 내부 체크 함수


// 도형 그리기 함수
void DrawShape() {
    Vector3D a1 = { 15, 10, 0 };
    Vector3D b1 = { 20, 17, 0 };
    Vector3D c1 = { 25, 10, 0 };

    // 사각형 좌표
    Vector3D a2 = { 30, 10, 0 };
    Vector3D b2 = { 34, 10, 0 };
    Vector3D c2 = { 34, 14, 0 };
    Vector3D d2 = { 30, 14, 0 };

    // 원의 중심과 반지름
    Vector3D center = { 36, 12, 0 };
    float radius = 1.5;

    // 화면 버퍼에 삼각형, 사각형, 원 그리기
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
    // 삼각형 꼭짓점 초기화 (초기 좌표는 static으로 유지)
    static Vector3D a1 = { 15, 10, 1 };
    static Vector3D b1 = { 20, 17, 1 };
    static Vector3D c1 = { 25, 10, 1 };

    // 삼각형 중심 계산
    Vector3D center = {
        (a1.x + b1.x + c1.x) / 3.0f,
        (a1.y + b1.y + c1.y) / 3.0f,
        1
    };

    // 회전 각도 계산 (3초에 1바퀴, 반시계 방향)
    float theta = 120.0f * elapsedTime;  // 초당 120도 회전

    // 회전 행렬 생성
    Matrix3x3 moveToOrigin = translation_matrix(-center.x, -center.y);
    Matrix3x3 rotation = rotation_matrix(theta);
    Matrix3x3 moveBack = translation_matrix(center.x, center.y);

    // 최종 변환 행렬 계산
    Matrix3x3 transform = multiply_matrices(moveBack, multiply_matrices(rotation, moveToOrigin));

    // 각 점에 변환 적용
    a1 = multiply_matrix_vector(transform, a1);
    b1 = multiply_matrix_vector(transform, b1);
    c1 = multiply_matrix_vector(transform, c1);

    // 화면 버퍼에 삼각형 그리기
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





// 전역 변수로 지구의 중심 선언
static Vector3D squareCenter;

void RotateSquare(float elapsedTime, Vector3D triangleCenter) {
    static Vector3D a2 = { 30, 10, 1 };
    static Vector3D b2 = { 34, 10, 1 };
    static Vector3D c2 = { 34, 14, 1 };
    static Vector3D d2 = { 30, 14, 1 };

    // 사각형 중심 계산
    squareCenter = (Vector3D){
        (a2.x + b2.x + c2.x + d2.x) / 4.0f,
        (a2.y + b2.y + c2.y + d2.y) / 4.0f,
        1
    };

    // 공전 각도 계산 (3초에 1바퀴, 시계 방향)
    float orbitTheta = 120.0f * elapsedTime;
    Matrix3x3 orbitMoveToOrigin = translation_matrix(-triangleCenter.x, -triangleCenter.y);
    Matrix3x3 orbitRotation = rotation_matrix2(orbitTheta);  // 시계 방향 회전
    Matrix3x3 orbitMoveBack = translation_matrix(triangleCenter.x, triangleCenter.y);
    Matrix3x3 orbitTransform = multiply_matrices(orbitMoveBack, multiply_matrices(orbitRotation, orbitMoveToOrigin));

    // 자전 각도 계산 (2초에 1바퀴, 시계 방향)
    float spinTheta = -180.0f * elapsedTime;
    Matrix3x3 spinMoveToOrigin = translation_matrix(-squareCenter.x, -squareCenter.y);
    Matrix3x3 spinRotation = rotation_matrix(spinTheta);  // 시계 방향 자전
    Matrix3x3 spinMoveBack = translation_matrix(squareCenter.x, squareCenter.y);
    Matrix3x3 spinTransform = multiply_matrices(spinMoveBack, multiply_matrices(spinRotation, spinMoveToOrigin));

    // 최종 변환 (공전 + 자전)
    Matrix3x3 finalTransform = multiply_matrices(orbitTransform, spinTransform);

    // 각 꼭짓점에 최종 변환 적용
    a2 = multiply_matrix_vector(finalTransform, a2);
    b2 = multiply_matrix_vector(finalTransform, b2);
    c2 = multiply_matrix_vector(finalTransform, c2);
    d2 = multiply_matrix_vector(finalTransform, d2);

    // 화면 버퍼에 사각형 그리기
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

    // 공전 각도 계산 (2초당 1바퀴, 반시계 방향)
    float orbitTheta = 180.0f * elapsedTime; // 초당 180도
    Matrix3x3 orbitMoveToOrigin = translation_matrix(-squareCenter.x, -squareCenter.y);
    Matrix3x3 orbitRotation = rotation_matrix(orbitTheta); // 반시계 방향 회전
    Matrix3x3 orbitMoveBack = translation_matrix(squareCenter.x, squareCenter.y);
    Matrix3x3 orbitTransform = multiply_matrices(orbitMoveBack, multiply_matrices(orbitRotation, orbitMoveToOrigin));

    // 자전 각도 계산 (1초당 1바퀴, 시계 방향)
    float spinTheta = -360.0f * elapsedTime; // 초당 360도
    Matrix3x3 spinMoveToOrigin = translation_matrix(-moon.x, -moon.y);
    Matrix3x3 spinRotation = rotation_matrix(spinTheta); // 시계 방향 자전
    Matrix3x3 spinMoveBack = translation_matrix(moon.x, moon.y);
    Matrix3x3 spinTransform = multiply_matrices(spinMoveBack, multiply_matrices(spinRotation, spinMoveToOrigin));

    // 공전 변환 적용
    moon = multiply_matrix_vector(orbitTransform, moon);

    // 화면 버퍼에 달 그리기
    for (int y = 0; y < HEIGHT; y++) {
        int adjustedY = HEIGHT - 1 - y;
        for (int x = 0; x < WIDTH; x++) {
            Vector3D p = { x, adjustedY, 1 };
            if (isInsideCircle(p, moon, 2.0f)) { // 달의 반지름 1
                screenBuffer[y * WIDTH * 2 + x * 2] = 'M';
                screenBuffer[y * WIDTH * 2 + x * 2 + 1] = 'M';
            }
        }
    }
}









void DrawAllShapes(float elapsedTime) {
    Init();  // 화면 초기화


    // 삼각형(SS) 중심 계산
    Vector3D triangleCenter = GetTriangleCenter();

    // 사각형(EE) 회전 및 공전 처리
    RotateSquare(elapsedTime, triangleCenter);
    Vector3D squareCenter = GetSquareCenter(); // 지구(정사각형) 중심 좌표 갱신

    RotateMoon(elapsedTime);
    // 삼각형(SS) 회전 처리
    RotateTriangle(elapsedTime);

    Draw();  // 화면 출력
}



// 메인 함수
int main() {
    ShowInitialScreen();  // 초기 화면 출력

    int spacebarCount = 0;
    float previousTime = clock() / (float)CLOCKS_PER_SEC;

    while (1) {
        float currentTime = clock() / (float)CLOCKS_PER_SEC;
        float deltaTime = currentTime - previousTime;  // 프레임 간 경과 시간
        previousTime = currentTime;

        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) {  // ESC 키가 눌리면 종료
                break;
            }
            else if (ch == 32) {  // 스페이스바 입력
                spacebarCount++;
                if (spacebarCount == 1) {
                    Init();
                    DrawShape();  // 초기 도형 출력
                }
            }
        }

        // 두 번째 스페이스바 입력 이후
        if (spacebarCount == 2) {
            DrawAllShapes(deltaTime);
            Sleep(33);
        }



    }

    return 0;
}