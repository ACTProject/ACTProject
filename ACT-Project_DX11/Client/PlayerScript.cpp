#include "pch.h"
#include "PlayerScript.h"
#include "Model.h"
#include "Camera.h"
#include "ModelAnimator.h"
#include "MyCoroutine.h"
#include <coroutine>

// Coroutine
std::coroutine_handle<MyCoroutine::promise_type> currentCoroutine;

void EndAttackCoroutine() {
	if (currentCoroutine) {
		currentCoroutine.destroy();
		currentCoroutine = nullptr;
	}
}

// ?뚮젅?댁뼱怨듦꺽 肄붾（???⑥닔 ?뺤쓽
MyCoroutine PlayAttackCoroutine(PlayerScript* playerScript, float animationDuration)
{
	co_await AwaitableSleep(chrono::milliseconds(static_cast<int>(animationDuration * 1000)));
	EndAttackCoroutine();
}

void PlayerScript::Start()
{

}

void PlayerScript::Update()
{
	if (DEBUG->IsDebugEnabled())
		return;


	_FPS = static_cast<float>(TIME->GetFps());
	float dt = TIME->GetDeltaTime();
	for (int i = 0; i < 4; ++i) {
		_attackDurations[i] = _player->GetAnimationDuration(static_cast<AnimationState>((int)AnimationState::Attack1 + i));
	}
	_transform = GetTransform();

	Vec3 moveDir = Vec3(0.0f);
	bool isRunning = INPUT->GetButton(KEY_TYPE::SHIFT);  // Shift ?ㅻ줈 ?щ━湲?紐⑤뱶 ?щ? ?뺤씤

	// ?대룞 ?낅젰 泥섎━
	if (INPUT->GetButton(KEY_TYPE::W))
		moveDir += Vec3(0.0f, 0.0f, 1.0f);
	if (INPUT->GetButton(KEY_TYPE::S))
		moveDir += Vec3(0.0f, 0.0f, -1.0f);
	if (INPUT->GetButton(KEY_TYPE::A))
		moveDir += Vec3(-1.0f, 0.0f, 0.0f);
	if (INPUT->GetButton(KEY_TYPE::D))
		moveDir += Vec3(1.0f, 0.0f, 0.0f);
	// 怨듦꺽 ?낅젰 泥섎━
	if (INPUT->GetButtonDown(KEY_TYPE::LBUTTON)) {
		if (_attackStage > 0)
			_currentDuration = _attackDurations[_attackStage - 1] / _FPS;	// ?꾩옱 ?좊땲硫붿씠??吏???쒓컙

		_isPlayeringAttackAnimation = true;
		if (!_isAttacking) {
			StartAttack();
		}
		else if (_attackTimer >= (_currentDuration / 2.5f) && _attackTimer <= _currentDuration)
		{
			ContinueAttack();
		}
	}

	// 怨듦꺽 ??대㉧ 媛깆떊
	if (_isAttacking) 
	{
		_attackTimer += dt;

		// 怨듦꺽 ?④퀎 ?쒓컙 珥덇낵 ??Idle濡?蹂듦?
		if (_attackTimer >= (_attackDurations[_attackStage - 1] / _FPS)) {
			_attackStage = 0;
			_isAttacking = false;
			ResetToIdleState();
		}
	}

	// 怨듦꺽 ?좊땲硫붿씠?섏씠 ?ъ깮 以묒씠硫??ㅻⅨ ?좊땲硫붿씠???곹깭濡??꾪솚?섏? ?딆쓬
	if (_isPlayeringAttackAnimation)
		return;

	// ?대룞 諛⑺뼢???ш린瑜?湲곗??쇰줈 ?좊땲硫붿씠???곹깭 寃곗젙
	AnimationState targetAnimationState;

	if (moveDir.LengthSquared() > 0.0f)  // ?대룞 踰≫꽣媛 0???꾨땲?쇰㈃ ?대룞 以묒쑝濡?媛꾩＜
	{
		moveDir.Normalize();
		float speed = isRunning ? _speed * 2 : _speed;
		_transform->SetPosition(_transform->GetPosition() + moveDir * speed * dt);

		targetAnimationState = isRunning ? AnimationState::Run : AnimationState::Walk;


		// ?대룞 諛⑺뼢???곕씪 ?뚯쟾 ?ㅼ젙
		Vec3 targetForward = moveDir;					// 罹먮┃?곌? ?대룞?섎젮??諛⑺뼢
		Vec3 currentForward = _transform->GetLook();	// 罹먮┃?곌? ?꾩옱 諛붾씪蹂대뒗 諛⑺뼢

		// ??踰≫꽣 ?ъ씠??媛곷룄瑜?怨꾩궛?섏뿬 ?뚯쟾
		float angle = std::acos(currentForward.Dot(targetForward));	// ??踰≫꽣 ?ъ씠??媛곷룄
		if (angle != 0.f)
		{
			Vec3 rotationAxis = currentForward.Cross(targetForward);	// ??踰≫꽣媛 ?대（???됰㈃??踰뺤꽑踰≫꽣
			rotationAxis.Normalize();

			// ?뚯쟾 異뺤쓽 y 媛믪쑝濡?醫뚯슦 諛⑺뼢??援щ텇
			if (rotationAxis.y < 0) {
				angle = -angle;  // ?쇱そ?쇰줈 ?뚯쟾
			}
			_transform->SetRotation(_transform->GetRotation() + Vec3(0, angle, 0));

		}
	}
	else
	{
		targetAnimationState = AnimationState::Idle;
	}

	// ?좊땲硫붿씠???곹깭媛 蹂寃쎈릺?덉쓣 ?뚮쭔 ?곹깭 ?꾪솚
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

void PlayerScript::SetAnimationState(AnimationState state)
{
	_modelAnimator->ChangeAnimation(state);
	_currentAnimationState = state;
}

void PlayerScript::StartAttack()
{
	_isAttacking = true;
	_attackStage = 1;
	_attackTimer = 0.0f;

	float duration = _attackDurations[_attackStage - 1] / _FPS;

	// 1? 怨듦꺽 ?좊땲硫붿씠???ъ깮
	PlayAttackAnimation(_attackStage);
	MyCoroutine attackCoroutine = PlayAttackCoroutine(this, duration);
	currentCoroutine = attackCoroutine.GetHandler();
	currentCoroutine.resume();
}

void PlayerScript::ContinueAttack()
{
	if (_attackStage < 4) {
		_attackStage++;
		_attackTimer = 0.0f;
		EndAttackCoroutine();

		float duration = _attackDurations[_attackStage - 1] / _FPS;

		// ?ㅼ쓬 怨듦꺽 ?좊땲硫붿씠???ъ깮
		PlayAttackAnimation(_attackStage);
		MyCoroutine attackCoroutine = PlayAttackCoroutine(this, duration);
		currentCoroutine = attackCoroutine.GetHandler();
		currentCoroutine.resume();
	}
}

void PlayerScript::PlayAttackAnimation(int stage)
{
	switch (stage)
	{
	case 1:
		SetAnimationState(AnimationState::Attack1);
		break;
	case 2:
		SetAnimationState(AnimationState::Attack2);
		break;
	case 3:
		SetAnimationState(AnimationState::Attack3);
		break;
	case 4:
		SetAnimationState(AnimationState::Attack4);
		break;
	default:
		SetAnimationState(AnimationState::Idle);
		break;
	}
}

void PlayerScript::ResetToIdleState() {
	_isPlayeringAttackAnimation = false;
	EndAttackCoroutine();
	SetAnimationState(AnimationState::Idle);
}
