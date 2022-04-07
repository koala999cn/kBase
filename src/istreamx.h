#pragma once
#include <istream>
#include "KmEndianed.h"


namespace stdx 
{

	/// std::istream的扩展

	class istreamx : public KmEndianed
	{
	public:

		istreamx(std::istream& strm, bool bin) 
			: strm_(strm), bin_(bin) {}

		istreamx(istreamx& strmx)
			: strm_(strmx.strm_), bin_(strmx.bin_) {}


		// 读取标量数据
		template<class T>
		typename std::enable_if_t<std::is_trivial<T>::value, istreamx&>
		read(T& val) {
			if (!bin_)
				strm_ >> val;
			else if(strm_.read(reinterpret_cast<char*>(&val), sizeof(T)))
				matchEndian(val);
				
			return *this;
		}

		istreamx& read(std::string& val) {
			if (!bin_) strm_ >> std::ws;
			strm_ >> val;

			if (!isspace(strm_.peek()))
				strm_.setf(std::istream::failbit);
			else
				strm_.get(); // consume the space

			return *this;
		}

		template<class T, typename SIZE_TYPE = std::uint32_t>
		typename std::enable_if_t<std::is_trivial<T>::value, istreamx&>
		read(std::vector<T>& val) {
			if (bin_) {
				SIZE_TYPE c;
				if (read(c)) {
					val.resize(c);
					return read(&val[0], c);
				}
			}
			else {
				val.clear();
				auto pos = strm_.tellg();
				while (true) {
					T x;
					if (!read(x)) break;

					val.push_back(x);
					pos = strm_.tellg();
				}
				
				strm_.seekg(pos);
				strm_.unsetf(std::istream::failbit);
			}

			return *this;
		}

		template<typename T>
		istreamx& operator>>(T& val) { return read(val); }


		// 读取数组
		template<typename T>
		typename std::enable_if_t<std::is_scalar<T>::value, istreamx&>
		read(T* val, unsigned count) {
			if(bin_ && strm_.read(reinterpret_cast<char*>(val), sizeof(T) * count))
				matchEndian(val, count);
			else {
				while (strm_ && count-- != 0) 
					strm_ >> std::ws >> *val++;
			}

			return *this;
		}


		template<typename T>
		typename std::enable_if_t<std::is_scalar<T>::value, T>
		peek() {
			T val{};
			auto pos = strm_.tellg();
			read(val);
			strm_.seekg(pos);
			return val;
		}


		// 读取以长度开头的字符串，无'\0'结尾
		template<typename CHAR, typename SIZE_TYPE = std::uint32_t>
		istreamx& readBinString(std::basic_string<CHAR>& retString) {
			SIZE_TYPE len = 0;
			if (read(len)) {
				retString.resize(len);
				return read(&retString[0], len);
			}

			return *this;
		}


		bool operator !() { return !strm_; }
		operator bool() { return bool(strm_); }

		std::istream* operator->() { return &strm_; }

		bool binary() const { return bin_; }

	private:
		std::istream& strm_;
		bool bin_; // 是否二进制读写模式
	};

}