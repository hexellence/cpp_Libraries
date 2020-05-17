#pragma once

#include <iostream>
#include "trim.h"

namespace hxl {

	class hxlstr
	{
	public:

		enum class ENC {
			NONE,
			ASCII,
			UTF16LE,
			UTF16BE,
		};

	private:
		char* m_text = nullptr;
		char* m_temp = nullptr;
		int m_size = 0;
		ENC m_enc = ENC::NONE;		
		const char16_t* m_pchar16 = nullptr;
		
		int getSize(const char* str);
		int getSize(const char16_t* str);

	public:			

		hxlstr();
		hxlstr(const uint8_t* init, int size, ENC enc);
		hxlstr(const char* init);
		hxlstr(const char16_t* init);
		hxlstr(const hxlstr& other);
		hxlstr(char init, int size = 1);
		hxlstr(int number);
		~hxlstr();

		const hxlstr& operator=(const hxlstr& other);
		const hxlstr& operator=(const char* str);
		const hxlstr& operator=(const char16_t* str);
		
				
		const char* c_str() const;
		const char16_t* c16_str() const;
		const char* raw() const;
		int size() const;
		int rtrim(const char16_t* chars = u" \t");
		int ltrim(const char16_t* chars = u" \t");
		int trim(const char16_t* chars = u" \t");

		void remove(const char16_t chars);


		friend std::ostream& operator<<(std::ostream& out, const hxlstr& obj);
		friend bool operator==(const hxlstr& obj1, const hxlstr& obj2);
		friend hxlstr operator+(const hxlstr& obj1, const hxlstr& obj2);
		friend bool operator!=(const hxlstr& obj1, const hxlstr& obj2);
		friend void hxlstrcopy(char* dest, hxlstr source, int destSizelimit = -1);


	};
}//namespace hxl



