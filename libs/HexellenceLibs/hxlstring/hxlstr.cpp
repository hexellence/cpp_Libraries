#include <stdio.h>
#include "hxlstr.h"
#include "trim.h"

namespace hxl {	

	int convert_char_to_char16(const uint8_t* in, int size, uint8_t* out) {
		//does not convert termination chars
		for (int i = 0; i < size; ++i) {
			out[i * 2] = in[i];
			out[(i * 2) + 1] = '\0';
		}
		return size * 2;
	}


	int convert_char16_to_char(const uint8_t* in, int size, uint8_t* out) {
		//does not convert termination chars
		for (int i = 0; i < size; i = i + 2) {
			out[i / 2] = in[i];
		}
		return size / 2;
	}




	int hxlstr::getSize(const char* str) 
	{
		return length(str);
	}


	int hxlstr::getSize(const char16_t* str) 
	{
		return length(str) * 2;
	}

	//default constructor
	hxlstr::hxlstr() {}


	//constructor that constructs from a memory area
	hxlstr::hxlstr(const uint8_t* init, int size, ENC enc) {

		if ((init != nullptr) && (size > 0)) {			
			switch (enc) {
			case ENC::ASCII:
				m_size = 2 * size;
				m_text = new char[m_size + 2];
				m_temp = new char[m_size + 2];
				m_pchar16 = (const char16_t*)m_text;
				convert_char_to_char16(init, size, (uint8_t*)m_text);
				m_text[m_size] = '\0';
				m_text[m_size + 1] = '\0';
				break;
			case ENC::UTF16LE:
				m_size = size;
				m_text = new char[m_size + 2];
				m_temp = new char[m_size + 2];
				m_pchar16 = (const char16_t*)m_text;
				memcpy(m_text, init, m_size);
				m_text[m_size] = '\0';
				m_text[m_size + 1] = '\0';
				break;
			default:
				break;
			}
		}
		else {
			std::cout << "Illegal parameters" << std::endl;
		}
	}


	hxlstr::hxlstr(const char* init) : hxlstr((const uint8_t*)init, getSize(init), ENC::ASCII) { }


	hxlstr::hxlstr(char init, int size) {
		char* tempInit = new char[size];
		//fill the array
		for (int i = 0; i < size; ++i) {
			tempInit[i] = init;
		}		
		this->hxlstr::hxlstr((const uint8_t*)tempInit, size, ENC::ASCII);
		delete[] tempInit;
	}


	hxlstr::hxlstr(const char16_t* init) : hxlstr((const uint8_t*)init, getSize(init), ENC::UTF16LE) { }

	// copy constructor
	hxlstr::hxlstr(const hxlstr& other) {
		m_size = other.m_size;
		m_text = new char[m_size + 2];
		m_pchar16 = (const char16_t*)m_text;
		m_enc = other.m_enc;
		memcpy(m_text, other.m_text, m_size + 2);
	}

	hxlstr::hxlstr(int number) {
		int len = 0;
		char temp[12]{};
		sprintf_s(temp, "%d", number);
		len = getSize(temp);
		this->hxlstr::hxlstr((const uint8_t*)temp, len, ENC::ASCII);
	}

	const hxlstr& hxlstr::operator=(const hxlstr& other) {
		delete[] m_text;
		m_size = other.m_size;
		m_text = new char[m_size + 2];
		m_pchar16 = (const char16_t*)m_text;
		memcpy(m_text, other.m_text, m_size + 2);
		return *this;
	}


	const hxlstr& hxlstr::operator=(const char* str) {
		delete[] m_text;
		int sourceSize = getSize(str);
		m_size = sourceSize * 2;
		m_text = new char[m_size + 2];
		m_pchar16 = (const char16_t*)m_text;
		convert_char_to_char16((const uint8_t*)str, sourceSize, (uint8_t*)m_text);
		m_text[m_size] = '\0';
		m_text[m_size + 1] = '\0';
		return *this;
	}


	const hxlstr& hxlstr::operator=(const char16_t* str) {
		delete[] m_text;
		int sourceSize = getSize(str);
		m_size = sourceSize;
		m_text = new char[m_size + 2];
		m_pchar16 = (const char16_t*)m_text;
		memcpy(m_text, (const char*)str, m_size + 2);
		return *this;
	}

	hxlstr::~hxlstr() {
		delete[] m_text;
		delete[] m_temp;
	}

	const char* hxlstr::raw() const {
		
		return m_text;
	}

	const char* hxlstr::c_str() const {
		memset(m_temp, 0, m_size + 2);
		convert_char16_to_char((const uint8_t*)m_text, m_size, (uint8_t*)m_temp);
		return m_temp;
	}

	const char16_t* hxlstr::c16_str() const {

		return (const char16_t*)m_text;
	}


	int hxlstr::size() const {
		return m_size;
	}


	int hxlstr::rtrim(const char16_t* chars) {
		m_size = trim_right((char16_t*)m_text, m_size / 2, chars);
		m_size = m_size * 2;
		return m_size;
	}


	int hxlstr::ltrim(const char16_t* chars) {
		m_size = trim_left((char16_t*)m_text, m_size / 2, chars);
		m_size = m_size * 2;
		return m_size;
	}


	int hxlstr::trim(const char16_t* chars) {

		m_size = trim_both((char16_t*)m_text, m_size / 2, chars);
		m_size = m_size * 2;
		return m_size;
	}

	void hxlstr::remove(const char16_t chars) {

		replace_char((char16_t*)m_text, m_size / 2, chars);
	}

	//Fiends
	std::ostream& operator<<(std::ostream& out, const hxlstr& obj) {
		if ((obj.m_text != nullptr) && (obj.m_size > 0)) {
			char* tempText = new char[(obj.m_size / 2) + 1];
			convert_char16_to_char((const uint8_t*)obj.m_text, obj.m_size + 2, (uint8_t*)tempText);
			out << tempText;
			delete[] tempText;
		}
		return out;
	}


	bool operator==(const hxlstr& obj1, const hxlstr& obj2) {
		bool retVal = false;
		if (obj1.m_size == obj2.m_size) {
			retVal = true;
			for (int i = 0; i < obj1.m_size; ++i) {
				if (obj1.m_text[i] != obj2.m_text[i]) {
					retVal = false;
					break;
				}
			}
		}
		else {
			retVal = false;
		}
		return retVal;
	}


	bool operator!=(const hxlstr& obj1, const hxlstr& obj2) {

		bool retVal = !(obj1 == obj2);
		return retVal;
	}

	hxlstr operator+(const hxlstr& obj1, const hxlstr& obj2) {
		
		int size = obj1.m_size + obj2.m_size;
		char* text = new char[size + 2];
		memcpy(text, obj1.m_text, obj1.m_size);
		memcpy(&text[obj1.m_size], obj2.m_text, obj2.m_size);
		text[size] = '\0';
		text[size + 1] = '\0';
		hxlstr retVal((char16_t*)text);
		return retVal;
	}


	void hxlstrcopy(char* dest, hxlstr source, int destSizelimit) {
		int size = source.size();	//this size is for char16 representation
		//so limit is given in bytes
		if (destSizelimit > 0)
		{
			if (destSizelimit < (size / 2))
			{
				size = destSizelimit * 2;
			}
		}
		convert_char16_to_char((uint8_t*)source.c_str(), size, (uint8_t*)dest);
	}

}//namespace hxl