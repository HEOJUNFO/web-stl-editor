cmake_minimum_required(VERSION 3.10)
project(WebSTLEditor)

# Emscripten 환경 확인 부분 수정
# emcmake를 사용하면 이미 CMAKE_TOOLCHAIN_FILE이 설정되므로 이 부분 확인
if(NOT CMAKE_TOOLCHAIN_FILE MATCHES "Emscripten.cmake")
    message(WARNING "Emscripten 툴체인 파일이 설정되지 않았습니다. emcmake를 사용하여 빌드하세요.")
endif()

# 출력 디렉토리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/public)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 소스 파일 지정
set(SOURCES
    src/cpp/main.cpp
)

# 실행 파일 설정
add_executable(wasm_module ${SOURCES})

# Emscripten 컴파일 옵션
set_target_properties(wasm_module PROPERTIES
    SUFFIX ".js"
    LINK_FLAGS "-s WASM=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=['_main'] -s EXPORT_NAME='Module' -s MODULARIZE=1 --bind -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1"
)

# 빌드 후 파일 복사 (수정된 부분)
add_custom_command(TARGET wasm_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/public/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
)

# Three.js 및 OrbitControls.js 파일 다운로드
add_custom_command(TARGET wasm_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/js
    COMMAND ${CMAKE_COMMAND} -E echo "Downloading Three.js library..."
    COMMAND curl -L https://cdn.jsdelivr.net/npm/three@0.149.0/build/three.min.js -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/js/three.min.js
    COMMAND curl -L https://cdn.jsdelivr.net/npm/three@0.149.0/examples/js/controls/OrbitControls.js -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/js/OrbitControls.js
    COMMENT "Downloading Three.js dependencies"
)