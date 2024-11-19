#include "pch.h"
#include "PlayerScript.h"
#include "Model.h"
#include "Camera.h"
#include "ModelAnimator.h"
#include "MyCoroutine.h"
#include <coroutine>

void PlayerScript::Start()
{
}

std::coroutine_handle<MyCoroutine::promise_type> coroutineHandle;

void EndAttackCoroutine() {
	if (coroutineHandle) {
		coroutineHandle.destroy();
		coroutineHandle = nullptr;
	}
}

// 플레이어공격 코루틴 함수 정의
MyCoroutine PlayAttackAnimation(PlayerScript* playerScript, float animationDuration)
{
	// 애니메이션 재생 시간 대기
	co_await AwaitableSleep(chrono::milliseconds(static_cast<int>(animationDuration * 1000)));
	// 애니메이션이 끝난 후 상태 복귀
	playerScript->ResetAnimationState();
}

void PlayerScript::Update()
{
	float dt = TIME->GetDeltaTime();
	_transform = GetTransform();

	Vec3 moveDir = Vec3(0.0f);
	bool isRunning = INPUT->GetButton(KEY_TYPE::SHIFT);  // Shift 키로 달리기 모드 여부 확인
	bool isAttack = false;  // 좌클릭으로 공격 여부 확인


	// 이동 입력 처리
	if (INPUT->GetButton(KEY_TYPE::W))
		moveDir += Vec3(0.0f, 0.0f, 1.0f);
	if (INPUT->GetButton(KEY_TYPE::S))
		moveDir += Vec3(0.0f, 0.0f, -1.0f);
	if (INPUT->GetButton(KEY_TYPE::A))
		moveDir += Vec3(-1.0f, 0.0f, 0.0f);
	if (INPUT->GetButton(KEY_TYPE::D))
		moveDir += Vec3(1.0f, 0.0f, 0.0f);
	if (INPUT->GetButton(KEY_TYPE::LBUTTON))
		isAttack = true;

	if (isAttack && !_isPlayeringAttackAnimation)
	{
		OutputDebugString(L"x\n");
		// 공격 애니메이션 재생 중 상태 설정
		_isPlayeringAttackAnimation = true;

		// 공격 애니메이션 재생 상태로 설정
		SetAnimationState(AnimationState::Attack);

		// 공격 애니메이션 코루틴 실행
		float attackDuration = _player->GetAnimationDuration(AnimationState::Attack);
		MyCoroutine attackCoroutine = PlayAttackAnimation(this, attackDuration);
		coroutineHandle = attackCoroutine.GetHandler();
		coroutineHandle.resume();

	}

	// 공격 애니메이션이 재생 중이면 다른 애니메이션 상태로 전환되지 않음
	if (_isPlayeringAttackAnimation)
		return;

	// 이동 방향의 크기를 기준으로 애니메이션 상태 결정
	AnimationState targetAnimationState;

	if (moveDir.LengthSquared() > 0.0f)  // 이동 벡터가 0이 아니라면 이동 중으로 간주
	{
		moveDir.Normalize();
		float speed = isRunning ? _speed*2 : _speed;
		_transform->SetPosition(_transform->GetPosition() + moveDir * speed * dt);

		targetAnimationState = isRunning ? AnimationState::Run : AnimationState::Walk;


		// 이동 방향에 따라 회전 설정
		Vec3 targetForward = moveDir;					// 캐릭터가 이동하려는 방향
		Vec3 currentForward = _transform->GetLook();	// 캐릭터가 현재 바라보는 방향

		// 두 벡터 사이의 각도를 계산하여 회전
		float angle = std::acos(currentForward.Dot(targetForward));	// 두 벡터 사이의 각도
		if (angle != 0.f)
		{
			Vec3 rotationAxis = currentForward.Cross(targetForward);	// 두 벡터가 이루는 평면의 법선벡터
			rotationAxis.Normalize();

			// 회전 축의 y 값으로 좌우 방향을 구분
			if (rotationAxis.y < 0) {
				angle = -angle;  // 왼쪽으로 회전
			}
			_transform->SetRotation(_transform->GetRotation() + Vec3(0, angle, 0));

		}
	}
	else
	{
		targetAnimationState = AnimationState::Idle;
	}

	// 애니메이션 상태가 변경되었을 때만 상태 전환
	if (_currentAnimationState != targetAnimationState)
	{
		SetAnimationState(targetAnimationState);
	}

	if (INPUT->GetButton(KEY_TYPE::KEY_1))
	{
		Camera::S_IsWireFrame = false;
	}

	if (INPUT->GetButton(KEY_TYPE::KEY_2))
	{
		Camera::S_IsWireFrame = true;
	}
}

// 공격 애니메이션 상태 관리
void PlayerScript::SetAnimationState(AnimationState state)
{
	_modelAnimator->ChangeAnimation(state);
	_currentAnimationState = state;
}

void PlayerScript::ResetAnimationState()
{
	_isPlayeringAttackAnimation = false;
	EndAttackCoroutine();
	SetAnimationState(AnimationState::Idle); // 기본 상태로 복귀
}
