#pragma once
class DebugManager
{
	DECLARE_SINGLE(DebugManager);

public:
	bool IsDebugEnabled() const { return _isDebugEnabled; }
	void EnableDebug(bool enable) { _isDebugEnabled = enable; }
private:
	bool _isDebugEnabled = false;
};

