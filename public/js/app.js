// Three.js를 사용한 3D 씬 설정
let scene, camera, renderer, cube;
let Module; // Emscripten 모듈

function initScene() {
    // 씬 생성
    scene = new THREE.Scene();
    scene.background = new THREE.Color(0x333333);

    // 카메라 설정
    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.z = 3;

    // 렌더러 설정
    renderer = new THREE.WebGLRenderer({ canvas: document.getElementById('canvas'), antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);

    // 조명 추가
    const ambientLight = new THREE.AmbientLight(0x404040);
    scene.add(ambientLight);

    const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
    directionalLight.position.set(1, 1, 1);
    scene.add(directionalLight);

    // 컨트롤 추가
    const controls = new THREE.OrbitControls(camera, renderer.domElement);
    controls.enableDamping = true;

    // 큐브 생성 (WASM에서 데이터를 받기 전 임시)
    const geometry = new THREE.BoxGeometry(1, 1, 1);
    const material = new THREE.MeshPhongMaterial({ color: 0x44aa88 });
    cube = new THREE.Mesh(geometry, material);
    scene.add(cube);

    // 애니메이션 루프
    function animate() {
        requestAnimationFrame(animate);
        cube.rotation.x += 0.01;
        cube.rotation.y += 0.01;
        controls.update();
        renderer.render(scene, camera);
    }

    animate();

    // 윈도우 크기 변경 이벤트
    window.addEventListener('resize', () => {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth, window.innerHeight);
    });
}

// WASM 모듈이 로드되면 호출
function onModuleReady(wasmModule) {
    Module = wasmModule;
    console.log("WASM 모듈이 로드되었습니다.");
    console.log(Module.getStlData()); // C++ 함수 호출 테스트

    // 이후에 WASM에서 제공하는 데이터로 3D 모델을 구성할 수 있습니다
}

// 페이지 로드 시 초기화
window.onload = function () {
    initScene();

    // WASM 모듈이 이미 로드되었다면
    if (typeof Module !== 'undefined') {
        onModuleReady(Module);
    } else {
        // 아직 로드 중이라면 콜백 설정
        window.Module = {
            onRuntimeInitialized: function () {
                onModuleReady(this);
            }
        };
    }
};