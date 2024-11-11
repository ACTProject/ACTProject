#pragma once
#include "MonoBehaviour.h"
class Model;

class WeaponScript : public MonoBehaviour
{

public:
	virtual void Update() override;
	virtual void Start() override;

public:	
	shared_ptr<Model> GetPlayer() { return _player; }
	void SetPlayer(shared_ptr<Model> player) { _player = player; }
	shared_ptr<Model> GetWeapon() { return _weapon; }
	void SetWeapon(shared_ptr<Model> weapon) { _weapon = weapon; }

	void AttachWeaponToHand();

private:
	shared_ptr<Model> _player;
	shared_ptr<Model> _weapon;
	shared_ptr<Transform> _transform;
};

