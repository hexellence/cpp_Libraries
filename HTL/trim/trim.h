#pragma once

namespace hxl {

	template<class T>
	bool trim_checkChar(T c, const T* chars) {
		bool retVal = false;
		T termChar{};

		for (int i = 0; chars[i] != termChar; ++i) {
			if ((c == chars[i]) || (c == termChar)) {
				retVal = true;
				break;
			}
		}
		return retVal;
	}

	template<class T>
	int replace_char(T* str, int length, const T chars)
	{
		//length is without the termination
		for (int i = 0; i < length; i++) {
			//check each char starting at the end
			if (str[i] == chars) {
				if (typeid(T) == typeid(char)) {
					str[i] = ' ';
				}
				else if (typeid(T) == typeid(char16_t)) {
					str[i] = u' ';
				}	
			}
		}
		return length;
	}


	template<class T>
	int trim_right(T* str, int length, const T* chars)
	{
		int tempLength = length;
		//length is without the termination
		for (int i = length - 1; i > -1; i--) {
			//check each char starting at the end
			if (trim_checkChar(str[i], chars) == true) {
				if (typeid(T) == typeid(char)) {
					str[i] = '\0';
					tempLength = tempLength - 1;
				}
				else if (typeid(T) == typeid(char16_t)) {
					str[i] = u'\0';
					tempLength = tempLength - 1;
				}
			}
			else {
				break;
			}
		}
		return tempLength;;
	}

	template<class T>
	int trim_left(T* str, int length, const T* chars)
	{
		int firstCharLoc = 0;
		T termChar{};

		for (int i = 0; i < length; i++) {
			if (!trim_checkChar(str[i], chars)) {
				firstCharLoc = i;
				break;
			}
		}

		memcpy(str, &str[firstCharLoc], (length - firstCharLoc) * sizeof(T));
		for (int i = 0; i < firstCharLoc; ++i) {
			str[length - 1 - i] = termChar;
		}
		return length - firstCharLoc;
	}


	template<class T>
	int trim_both(T* str, int length, const T* chars)
	{
		int newLength = trim_right<T>(str, length, chars);
		newLength = trim_left<T>(str, newLength, chars);
		return newLength;
	}

	template<class T>
	int length(T* str)
	{
		int len = 0;
		if (str != nullptr)
		{
			T termChar{};	//assuming the defualt is also the term character
			while (str[len] != termChar)
			{
				len++;
			}
		}
		return len;
	}


	template<class T>
	int bytes(T* str)
	{
		int len = length(str);
		return len * sizeof(T);
	}


}//hxl namespace