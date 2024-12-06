#include "pch.h"
#include "Camera.h"
#include "Scene.h"

Matrix	Camera::S_MatView			= Matrix::Identity;
Matrix	Camera::S_MatProjection		= Matrix::Identity;
Matrix	Camera::S_UIMatView			= Matrix::Identity;
Matrix	Camera::S_UIMatProjection	= Matrix::Identity;
bool	Camera::S_IsWireFrame	= false;

void Camera::SetCameraOffset(Vec3 v)
{	
	_cameraOffset.x = v.x; 
	_cameraOffset.y = v.y; 
	_cameraOffset.z = v.z; 

	_cameraDistance = _cameraOffset.Length();
}
void Camera::SortGameObject()
{
	shared_ptr<Scene> scene = CUR_SCENE;
	unordered_set<shared_ptr<GameObject>>& gameObjects = scene->GetObjects();

	_vecForward.clear();

	// 모든 게임오브젝트를 대상으로 내가 그려줘야할 대상인지 체크
	for (auto& gameObject : gameObjects)
	{
		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetMeshRenderer() == nullptr
			&& gameObject->GetModelRenderer() == nullptr
			&& gameObject->GetModelAnimator() == nullptr)
		{
			if (gameObject->GetCollider() == nullptr)
				continue;
		}

		// 내가 그려줘야할 대상인 gameObject
		_vecForward.push_back(gameObject);		
	}
}

void Camera::Render_Forward()
{
    if (IsMainCamera())
    {
        S_MatView = _matView;
        S_MatProjection = _matProjection;
        //FRUSTUM->FinalUpdate();
        //vector<std::shared_ptr<GameObject>> visibleObjects = CUR_SCENE->FrustumCulling(_vecForward);
        //GET_SINGLE(InstancingManager)->Render(visibleObjects);
        GET_SINGLE(InstancingManager)->Render(_vecForward);
    }
    else 
    {
        S_UIMatView = _matView;
        S_UIMatProjection = _matProjection;
        GET_SINGLE(InstancingManager)->Render(_vecForward);
    }

}

Camera::Camera() : Super(ComponentType::Camera)
{
	_width = static_cast<float>(GAME->GetGameDesc().width);
	_height = static_cast<float>(GAME->GetGameDesc().height);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	if (DEBUG->IsDebugEnabled())
	{
		if (!_debugInitialized) // 디버깅 모드 최초 진입
		{
			_debugInitialized = true;

			// 디버깅 모드 초기 위치와 방향 설정
			_cameraPosition = Vec3(0.0f, 20.0f, -5.0f); // 위에서 아래를 바라보는 위치
			_focusPosition = Vec3(0.0f, 0.0f, 0.0f);     // 초점은 원점
			_yaw = XM_PIDIV4;                           // 45도 회전
			_pitch = -XM_PIDIV4;                        // 아래를 45도 바라봄

			UpdateMatrix();
			return;
		}
		FreeCameraMovement();
	}
	else
	{
		if (_debugInitialized) // 디버깅 모드 종료
		{
			_debugInitialized = false;
		}

		UpdateCameraWithMouseInput();
	}

	// 카메라 매트릭스 업데이트
	UpdateMatrix();
}

void Camera::FreeCameraMovement()	// WASD 키로 이동, 마우스로 회전
{
	// WASD 이동
	Vec3 movement(0.0f);
	// 방향 벡터 계산
	Vec3 forward(
		cosf(_pitch) * sinf(_yaw),
		sinf(_pitch),
		cosf(_pitch) * cosf(_yaw)
	);
	forward.Normalize();

	Vec3 right = forward.Cross(Vec3(0.0f, 1.0f, 0.0f));
	right.Normalize();

	Vec3 up = right.Cross(forward);
	up.Normalize();

	if (INPUT->GetButton(KEY_TYPE::W)) movement += forward;    // 앞으로
	if (INPUT->GetButton(KEY_TYPE::S)) movement -= forward;    // 뒤로
	if (INPUT->GetButton(KEY_TYPE::A)) movement += right;      // 왼쪽
	if (INPUT->GetButton(KEY_TYPE::D)) movement -= right;      // 오른쪽
	if (INPUT->GetButton(KEY_TYPE::Q)) movement -= up;         // 아래로
	if (INPUT->GetButton(KEY_TYPE::E)) movement += up;         // 위로

	// 이동 속도 (Shift 키로 속도 변경)
	float speed = (INPUT->GetButton(KEY_TYPE::SHIFT)) ? _fastSpeed : _normalSpeed;
	_cameraPosition += movement * speed * TIME->GetDeltaTime();

	if (INPUT->GetButton(KEY_TYPE::LBUTTON)) // 드래그 상태 확인
	{
		// 마우스 입력
		float dx = INPUT->GetMouseDeltaX();
		float dy = INPUT->GetMouseDeltaY();

		// yaw와 pitch 각도를 마우스 이동에 따라 조절
		_yaw += dx * _sensitivity;
		_pitch -= dy * _sensitivity;

		// pitch 값의 범위를 제한하여 카메라가 뒤집히지 않도록 조정 (-90도 ~ 90도 사이)
		_pitch = std::clamp(_pitch, -XM_PIDIV4, XM_PIDIV4);
	}	
	// 카메라 초점 갱신
	forward = Vec3(
		cosf(_pitch) * sinf(_yaw),
		sinf(_pitch),
		cosf(_pitch) * cosf(_yaw)
	);
	forward.Normalize(); 
	_focusPosition = _cameraPosition + forward;
}

void Camera::UpdateCameraWithMouseInput()
{
	_player = CUR_SCENE->GetPlayer();

	float dx = INPUT->GetMouseDeltaX(); // x축 마우스 이동량
	float dy = INPUT->GetMouseDeltaY(); // y축 마우스 이동량

	// yaw와 pitch 각도를 마우스 이동에 따라 조절
	_yaw += dx * _sensitivity;
	_pitch += dy * _sensitivity;

	// pitch 값의 범위를 제한하여 카메라가 뒤집히지 않도록 조정 (-90도 ~ 90도 사이)
    _pitch = std::clamp(_pitch, 0.08f, XM_PIDIV2 - 0.1f);

	// 카메라 위치 계산
	float x = _cameraDistance * cosf(_pitch) * sinf(_yaw);
	float y = _cameraDistance * sinf(_pitch);
	float z = _cameraDistance * cosf(_pitch) * cosf(_yaw);



    if (_pitch < 0.09f)
    {
        if (_player != nullptr)
        {
            Vec3 playerPosition = _player->GetTransform()->GetPosition();

            Vec3 forward(
                sinf(_yaw),
                0.0f,
                cosf(_yaw)
            );
            forward.Normalize();

            
            _cameraPosition = playerPosition + forward * _cameraDistance + Vec3(0.f, y, 0.f);
            _focusPosition = playerPosition;
            return;
        }
    }

	// 카메라 위치를 플레이어 위치 기준으로 설정
	if (_player == nullptr)
	{
		Vec3 cameraposition = GetTransform()->GetPosition();
		_cameraPosition = cameraposition + Vec3(x, y, z);
		_focusPosition = cameraposition;
	}
	else 
	{
		Vec3 playerPosition = _player->GetTransform()->GetPosition();
		_cameraPosition = playerPosition + Vec3(x, y, z);
		_focusPosition = playerPosition;
	}
}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition;
	Vec3 focusPosition;
	Vec3 upDirection;

	if (_type == ProjectionType::Perspective) // Main 카메라
	{
		eyePosition = _cameraPosition;
		focusPosition = _focusPosition;
		upDirection = Vec3(0.0f, 1.0f, 0.0f);
	}
	else // UI 카메라
	{
		eyePosition = GetTransform()->GetPosition();
		focusPosition = eyePosition + GetTransform()->GetLook();
		upDirection = GetTransform()->GetUp();
	}

	_matView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	if (_type == ProjectionType::Perspective) 
	{
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
		S_MatView = _matView;
		S_MatProjection = _matProjection;
	}
	else
	{
		_matProjection = ::XMMatrixOrthographicLH(_width, _height, _near, _far);
		S_UIMatView = _matView;
		S_UIMatProjection = _matProjection;
	}
	
}

