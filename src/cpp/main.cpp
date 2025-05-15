#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <vector>
#include <string>
#include <iostream>

// WebGL 컨텍스트를 위한 캔버스 ID
#define CANVAS_ID "canvas"

// 정육면체 정점 데이터
std::vector<float> getCubeVertices() {
    return {
        // 앞면 (z=1)
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f, // 빨간색
         0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,
        
        // 뒷면 (z=-1)
        -0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f, // 초록색
         0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,
        
        // 윗면 (y=1)
        -0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f, // 파란색
         0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,
        
        // 아랫면 (y=-1)
        -0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f, // 노란색
         0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,
        
        // 오른쪽면 (x=1)
         0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 1.0f, // 청록색
         0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
        
        // 왼쪽면 (x=-1)
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f, // 자주색
        -0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f
    };
}

// 정육면체 인덱스 데이터
std::vector<unsigned int> getCubeIndices() {
    return {
        // 앞면
        0, 1, 2,    0, 2, 3,
        // 뒷면
        4, 5, 6,    4, 6, 7,
        // 윗면
        8, 9, 10,   8, 10, 11,
        // 아랫면
        12, 13, 14, 12, 14, 15,
        // 오른쪽면
        16, 17, 18, 16, 18, 19,
        // 왼쪽면
        20, 21, 22, 20, 22, 23
    };
}

// JavaScript에서 호출할 C++ 함수
std::string getStlData() {
    return "STL 데이터를 반환하는 함수입니다.";
}

// Emscripten 바인딩
EMSCRIPTEN_BINDINGS(WebSTLEditor) {
    emscripten::function("getStlData", &getStlData);
    emscripten::function("getCubeVertices", &getCubeVertices);
    emscripten::function("getCubeIndices", &getCubeIndices);
}

// 메인 함수
int main() {
    std::cout << "Web STL 에디터가 초기화되었습니다." << std::endl;
    return 0;
}