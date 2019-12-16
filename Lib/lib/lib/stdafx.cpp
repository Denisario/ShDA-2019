#include "stdafx.h"
#include <iostream>
extern "C" {
	void __stdcall outint(int num) {
		std::cout << num;
	}

	void __stdcall outstr(char* str) {
		std::cout << str;
	}

	void __stdcall outintn(int num) {
		std::cout << num<<std::endl;
	}

	void __stdcall outstrn(char* str) {
		std::cout << str << std::endl;
	}

	void __stdcall checkLines(char* str2, char* str1)
	{
		int len1 = NULL, len2 = NULL, out = 0;

		for (; str1[len1] != '\0'; len1++);
		for (; str2[len2] != '\0'; len2++);

		for (int j = 0; str1[j] != '\0'; j++)
		{
			if (len1 != len2) std::cout << "false"<<std::endl;
			else {
				if(str1[j]!=str2[j])std::cout << "false" << std::endl;
				if (str1[j] == str2[j]) out++;
				if(out==len1) std::cout << "true" << std::endl;
			}
			
		}
	}
	void __stdcall isGreather(int x1, int x2) {
		if(x1>x2) std::cout << "true" << std::endl;
		else std::cout << "false" << std::endl;
	}
}