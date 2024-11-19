#include <coroutine>
#include <thread>

#pragma once

// co_await(값 반환x 중지), co_yield(값 반환o 중지), co_return(코루틴 함수 종료)
class MyCoroutine
{
public:
	// promise_type: 코루틴의 상태를 관리하고, 코루틴을 제어하는 역할을 함
	struct promise_type
	{
		// 코루틴 객체를 반환. promise_type과 연결된 코루틴 핸들러를 생성
		MyCoroutine get_return_object() { return MyCoroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
		

		// 코루틴의 초기 상태를 지정. 코루틴을 실행하기 전에 항상 중단하도록 설정
		std::suspend_always initial_suspend() { return std::suspend_always{}; }

		// 코루틴의 최종 상태를 지정. 코루틴이 종료될 때 항상 중단하도록 설정
		std::suspend_always final_suspend() noexcept { return std::suspend_always{}; }

		// co_return을 사용하는 경우 구현
		std::suspend_never return_void() { return std::suspend_never{}; }

		void unhandled_exception() { std::exit(1); }
	};
	
	// 생성자: promise_type으로부터 생성된 코루틴 핸들러를 저장
	MyCoroutine(std::coroutine_handle<promise_type> handler) : _handler(handler) {}

	// 소멸자: 핸들러가 유효하면 코루틴 핸들러를 파괴
	~MyCoroutine() {}

	// 핸들러를 외부에서 관리할 수 있도록 제공
	std::coroutine_handle<promise_type> GetHandler() { return _handler; }

private:
	std::coroutine_handle<promise_type> _handler;
};

struct AwaitableSleep 
{
	std::chrono::milliseconds duration;
	explicit AwaitableSleep(std::chrono::milliseconds d) : duration(d) {}

	bool await_ready() const noexcept { return false; }
	void await_suspend(std::coroutine_handle<> handle) const
	{
		// 핸들러를 안전하게 캡처하기 위해 shared_ptr 사용
		auto handlePtr = std::make_shared<std::coroutine_handle<>>(handle);

		std::thread t([handle, d = duration]() {
			std::this_thread::sleep_for(d);
			if (!handle)
				handle.resume();
			});
		t.detach();
	}
	void await_resume() const noexcept {}
};