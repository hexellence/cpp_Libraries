#include <stdio.h>
#include "hxlstr.h"
#include "trim.h"

namespace hxl {

	//default constructor
	hxlstr::hxlstr() : hxlstr("") { }


	//constructor that constructs from a memory area
	hxlstr::hxlstr(const uint8_t* init, int size, ENC enc) : m_temp(nullptr), m_text(nullptr), m_size(0), m_enc(ENC::NONE) {

		if (init != nullptr) {
			if (enc == ENC::UNICD)
			{
				m_size = size;
				m_text = new uint8_t[m_size + 2];
				m_enc = ENC::UNICD;
				memcpy(m_text, init, m_size);
				m_text[m_size] = '\0';
				m_text[m_size + 1] = '\0';
			}
			else
			{
				//ASCII
				m_size = size * 2;
				m_text = new uint8_t[m_size + 2];
				m_enc = ENC::ASCII;
				convert_char_to_char16(init, size, m_text);
				m_text[m_size] = '\0';
				m_text[m_size + 1] = '\0';
			}
		}
		else {
			m_size = size * 2;
			m_text = new uint8_t[m_size + 2];
			m_enc = ENC::ASCII;
			m_text[m_size] = '\0';
			m_text[m_size + 1] = '\0';
		}
	}

	hxlstr::hxlstr(const char* init, int size) : hxlstr((const uint8_t*)init, size) { }


	hxlstr::hxlstr(const char* init) : hxlstr((const uint8_t*)init, bytes(init)) { }


	hxlstr::hxlstr(char init, int size) : m_temp(nullptr), m_text(nullptr), m_size(0), m_enc(ENC::NONE) {
		char* tempInit = new char[size];
		//fill the array
		for (int i = 0; i < size; ++i) {
			tempInit[i] = init;
		}
		this->hxlstr::hxlstr((const uint8_t*)tempInit, size);
		delete[] tempInit;
	}


	hxlstr::hxlstr(const char16_t* init) : hxlstr((const uint8_t*)init, bytes(init), ENC::UNICD) {

	}

	// copy constructor
	hxlstr::hxlstr(const hxlstr& other) : m_enc(ENC::NONE), m_size(0), m_text(nullptr), m_temp(nullptr) {

		if (other.m_text != nullptr) {
			m_enc = other.m_enc;
			m_size = other.m_size;
			m_text = new uint8_t[m_size + 2];
			memcpy(m_text, other.m_text, m_size + 2);
		}
	}

	hxlstr::hxlstr(int number) {
		int size = 0;
		char temp[12]{};
		sprintf_s(temp, "%d", number);
		size = bytes(temp);
		this->hxlstr::hxlstr((const uint8_t*)temp, size);
	}

	//assignment operator
	const hxlstr& hxlstr::operator=(const hxlstr& other) {
		delete[] m_text;
		delete[] m_temp;
		m_text = nullptr;
		m_temp = nullptr;
		m_enc = other.m_enc;
		m_size = other.m_size;
		if (other.m_text != nullptr) {
			m_text = new uint8_t[m_size + 2];
			memcpy(m_text, other.m_text, m_size + 2);
		}
		return *this;
	}


	const hxlstr& hxlstr::operator=(const char* str) {
		if (str != nullptr) {
			delete[] m_text;
			delete[] m_temp;
			m_text = nullptr;
			m_temp = nullptr;
			m_enc = ENC::ASCII;
			int sourceSize = bytes(str);
			m_size = sourceSize * 2;
			m_text = new uint8_t[m_size + 2];
			convert_char_to_char16((const uint8_t*)str, sourceSize, m_text);
			m_text[m_size] = '\0';
			m_text[m_size + 1] = '\0';
		}
		return *this;
	}


	const hxlstr& hxlstr::operator=(const char16_t* str) {
		if (str != nullptr) {
			delete[] m_text;
			delete[] m_temp;
			m_text = nullptr;
			m_temp = nullptr;
			m_enc = ENC::UNICD;
			int sourceSize = bytes(str);
			m_size = sourceSize;
			m_text = new uint8_t[m_size + 2];
			memcpy(m_text, str, sourceSize);
			m_text[m_size] = '\0';
			m_text[m_size + 1] = '\0';
		}
		return *this;
	}

	hxlstr::~hxlstr() {
		delete[] m_text;
		delete[] m_temp;
	}


	const char* hxlstr::c_str()
	{
		delete[] m_temp;
		m_temp = new char[m_size / 2 + 1];
		convert_char16_to_char((const uint8_t*)m_text, m_size, (uint8_t*)m_temp);
		m_temp[m_size / 2] = '\0';
		return m_temp;
	}

	const char16_t* hxlstr::c16_str() const
	{
		return (char16_t*)m_text;
	}

	const uint8_t* hxlstr::raw() const
	{
		return (const uint8_t*)m_text;
	}


	int hxlstr::size() const {

		return m_size;
	}

	int hxlstr::len() const {

		return m_size / 2;
	}

	hxlstr::ENC hxlstr::enc() {
		return m_enc;
	}


	int hxlstr::rtrim() {

		m_size = 2 * trim_right((char16_t*)m_text, len(), u" \t\r\n");

		return len();
	}


	int hxlstr::ltrim() {

		m_size = 2 * trim_left((char16_t*)m_text, len(), u" \t\r\n");

		return len();
	}


	int hxlstr::trim() {
		m_size = 2 * trim_both((char16_t*)m_text, len(), u" \t\r\n");

		return len();
	}

	void hxlstr::drop(const char16_t chars) {

		replace_char((char16_t*)m_text, len(), chars);
	}

	void hxlstr::drop(const char chars) {
		char16_t wchars;
		char* pwchars = (char*)&wchars;
		pwchars[0] = chars;
		pwchars[1] = '\0';
		drop(wchars);
	}

	//Fiends
	std::ostream& operator<<(std::ostream& out, const hxlstr& obj) {

		if ((obj.m_text != nullptr) && (obj.m_size > 0)) {

			uint8_t* tempText = new uint8_t[obj.m_size + 1];
			hxlstr::convert_char16_to_char((const uint8_t*)obj.m_text, obj.m_size, tempText);
			tempText[obj.m_size / 2] = '\0';
			out << tempText;
			delete[] tempText;
		}
		return out;
	}


	bool operator==(const hxlstr& obj1, const hxlstr& obj2) {
		bool retVal = false;
		if (obj1.m_enc == obj2.m_enc) {
			if (obj1.m_size == obj2.m_size) {				
				retVal = memcmp(obj1.m_text, obj2.m_text, obj1.m_size) == 0;
			}//compare len
		}//compare enc	
		return retVal;
	}


	bool operator!=(const hxlstr& obj1, const hxlstr& obj2) {

		bool retVal = !(obj1 == obj2);
		return retVal;
	}

	hxlstr operator+(const hxlstr& obj1, const hxlstr& obj2) {
		int size = 0;
		hxlstr retVal;

		size = obj1.m_size + obj2.m_size;

		char* text = new char[size + 2];

		memcpy(text, obj1.m_text, obj1.m_size);
		memcpy(&text[obj1.m_size], obj2.m_text, obj2.m_size);
		text[size] = '\0';
		text[size + 1] = '\0';		
		
		retVal = hxlstr((uint8_t*)text, size, hxlstr::ENC::UNICD);

		return retVal;
	}

	int hxlstr::convert_char_to_char16(const uint8_t* in, int size, uint8_t* out) {
		//does not convert termination chars
		for (int i = 0; i < size; ++i) {
			out[i * 2] = in[i];
			out[(i * 2) + 1] = '\0';
		}
		return size * 2;
	}


	int hxlstr::convert_char16_to_char(const uint8_t* in, int size, uint8_t* out) {
		//does not convert termination chars
		for (int i = 0; i < size; i = i + 2) {
			out[i / 2] = in[i];
		}
		return size / 2;
	}

}//namespace hxl