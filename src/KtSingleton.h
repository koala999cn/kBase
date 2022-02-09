#pragma once
#include <memory>
#include <mutex>


// 一个单例实现
// @use_shared_ptr: 是否使用std::shared_ptr
// @use_lock: 是否提供线程安全支持
template<typename T, bool use_shared_ptr = true, bool use_lock = false>
class KtSingleton
{
public:
	using pointer = std::conditional_t<use_shared_ptr, std::shared_ptr<T>, std::add_pointer_t<T>>;
	using lock_type = std::conditional_t<use_lock, std::mutex, void>;

	KtSingleton() = delete;

	static pointer instance() {
		if (instance_ == nullptr) {
			std::add_pointer_t<lock_type> lockObjPtr = nullptr;

			if constexpr (use_lock) {
				static lock_type lockObj;
				lockObjPtr = &lockObj;
				lockObj.lock();
			}

			if (instance_ == nullptr) {
				if constexpr (use_shared_ptr)
					instance_.reset(new T); // 当T的构造非public时，无法使用std::make_shared
				else
				    instance_ = new T;
			}

			if constexpr (use_lock) 
				lockObjPtr->unlock();
		}

		return instance_;
	}

	static void destroy() {
		if constexpr (use_shared_ptr)
			instance_.reset();
		else {
			delete instance_;
			instance_ = nullptr;
		}
	}

private:
	static pointer instance_;
};


template<typename T, bool use_shared_ptr, bool use_lock>
typename KtSingleton<T, use_shared_ptr, use_lock>::pointer KtSingleton<T, use_shared_ptr, use_lock>::instance_{};