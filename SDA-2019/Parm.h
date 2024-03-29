#pragma once
#include <tchar.h>
#define PARM_IN L"-in:"			//���� ��� ����� ��������� ����
#define PARM_OUT L"-out:"		//���� ��� ����� ����������� ����
#define PARM_LOG L"-log:"		//���� ��� ����� �������
#define PARM_MAX_SIZE 100		//������������ ����� ������ ���������
#define PARM_OUT_DEFAULT_EXT L"out.txt"	//���������� ����� ����������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L"log.txt"	//���������� ����� ��������� �� ���������

namespace Parm {					//��������� ������� ����������
	struct PARM {				//������� ���������
		wchar_t in[PARM_MAX_SIZE];		//-in: ��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];		//-out: ��� ����� ��������� ����
		wchar_t log[PARM_MAX_SIZE];		//-log: ��� ����� ��������� ����
	};
	//������������ STRUCT PARM �� ������ ���������� ������� main
	PARM getParm(int argc, _TCHAR* argv[]);
}
