#pragma once

#include <iostream>

namespace hxl {

	class hxlstr
	{
	public:

		enum class ENC {
			NONE,
			ASCII,
			UNICD,			
		};

	private:
		char* m_temp = nullptr;
		uint8_t* m_text = nullptr;
		int m_size = 0;
		ENC m_enc = ENC::NONE;		
		static int convert_char_to_char16(const uint8_t* in, int size, uint8_t* out);
		static int convert_char16_to_char(const uint8_t* in, int size, uint8_t* out);

	public:			

		hxlstr();
		hxlstr(const uint8_t* init, int size, ENC enc = ENC::ASCII);
		hxlstr(const char* init, int size);
		hxlstr(const char* init);
		hxlstr(const char16_t* init);
		hxlstr(const hxlstr& other);
		hxlstr(char init, int size = 1);
		hxlstr(int number);
		~hxlstr();

		const hxlstr& operator=(const hxlstr& other);
		const hxlstr& operator=(const char* str);
		const hxlstr& operator=(const char16_t* str);
		
		const uint8_t* raw() const;
		const char* c_str();
		const char16_t* c16_str() const;		
		int size() const;
		int len() const;
		ENC enc();
		int rtrim();
		int ltrim();
		int trim();

		void drop(const char16_t chars);
		void drop(const char chars);

		friend std::ostream& operator<<(std::ostream& out, const hxlstr& obj);
		friend bool operator==(const hxlstr& obj1, const hxlstr& obj2);
		friend hxlstr operator+(const hxlstr& obj1, const hxlstr& obj2);
		friend bool operator!=(const hxlstr& obj1, const hxlstr& obj2);
	};
}//namespace hxl



