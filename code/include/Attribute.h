#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "Observable.h"

namespace NOP
{

	template <typename T>
	class Attribute: public Observable
	{

	public:
		Attribute() = delete;
		Attribute(Attribute&) = delete;
		Attribute(Attribute&&) = delete;
		explicit Attribute(const T value);
		Attribute& operator=(Attribute&) = delete;
		Attribute& operator=(Attribute&&) = delete;
		~Attribute() = default;

		static const bool RENOTIFY{ true };
		void SetValue(const T value, const bool reNotify = false);
		T GetValue(void) const;

	private:
		T value_;
		std::recursive_mutex mutex_;

	public:
		void operator=(const T& rhs) { SetValue(rhs); };
		T operator+(const Attribute& rhs) { return GetValue() + rhs.GetValue(); };
		T operator-(const Attribute& rhs) { return GetValue() - rhs.GetValue(); };
		T operator*(const Attribute& rhs) { return GetValue() * rhs.GetValue(); };
		T operator/(const Attribute& rhs) { return GetValue() / rhs.GetValue(); };
		bool operator==(const Attribute& rhs) { return GetValue() == rhs.GetValue(); };
		bool operator!=(const Attribute& rhs) { return GetValue() != rhs.GetValue(); };
	};

	template <typename T>
	Attribute<T>::Attribute(const T value) : value_{ value }
	{

	}

	template <typename T>
	void Attribute<T>::SetValue(T value, const bool reNotify)
	{
		const std::lock_guard<std::recursive_mutex> lock{ mutex_ };
		if ( (value_ != value) || reNotify )
		{
			value_ = value;
			Notify(reNotify);
		}
	}

	template <typename T>
	T Attribute<T>::GetValue(void) const
	{
		return value_;
	}
	
	template <typename T>
	auto BuildAttribute(const T value)
	{
		return std::make_shared<Attribute<T>>(value);
	}
}

