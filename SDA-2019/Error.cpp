#include"pch.h"
#include"Error.h"
namespace Error {
	//����� ������: 0 - 99 - ��������� ������
	//				100 - 109 - ������ ����������
	//				110 - 119 - ������ �������� � ������ ������
	ERROR errors[ERROR_MAX_ENTRY] = {		//������� ������
	ERROR_ENTRY(0,"������������ ��� ������"),	//��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
	ERROR_ENTRY(1,"��������� ����"),
	ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100,"�������� -in ������ ���� �����"),
	ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104,"��������� ����� �������� ���������"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110,"������ ��� �������� ����� � �������� ����� (-in)"),
	ERROR_ENTRY(111,"������������ ������ � �������� ����� (-in)"),
	ERROR_ENTRY(112,"������ ��� �������� ����� ��������� (-log)"),
	ERROR_ENTRY_NODEF(113),	ERROR_ENTRY_NODEF(114),	ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY(200,"������ ��� ������� �������"),
	ERROR_ENTRY(201,"������� ������ ���������"),
	ERROR_ENTRY(202,"������� ��������������� ���������"),
	ERROR_ENTRY(203,"��������� ����� ���������� ��������"),
	ERROR_ENTRY_NODEF(204),ERROR_ENTRY_NODEF(205),ERROR_ENTRY_NODEF(206),
	ERROR_ENTRY_NODEF(207),ERROR_ENTRY_NODEF(208),ERROR_ENTRY_NODEF(209),
	ERROR_ENTRY_NODEF10(210),ERROR_ENTRY_NODEF10(220),ERROR_ENTRY_NODEF10(230),ERROR_ENTRY_NODEF10(240),
	ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
	ERROR_ENTRY(300,"����������� ����� �����"),
	ERROR_ENTRY(301,"���������� ��������� ����� �����"),
	ERROR_ENTRY(302,"��� ���������� �� ����� ���� �������� ������"),
	ERROR_ENTRY(303,"� �������� ��������� ���������� ������� ���������� ����������"),
	ERROR_ENTRY(304,"��� ������� � ������������ ���������� �� ���������"),
	ERROR_ENTRY(305,"����� ����� ���������� ������� ��������"),
	ERROR_ENTRY(306,"�������� �� �������� �����������"),
	ERROR_ENTRY(307,"�������� ���������"),
	ERROR_ENTRY_NODEF(308),ERROR_ENTRY_NODEF(309),
	ERROR_ENTRY_NODEF10(310),ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),
	ERROR_ENTRY_NODEF10(350),ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),

	ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
	ERROR_ENTRY_NODEF(600),
	ERROR_ENTRY(601,"�������� ��������� ���������"),
	ERROR_ENTRY(602,"������� ������ ��������� �������"),
	ERROR_ENTRY(603,"������� ������������ ��������� �����������"),
	ERROR_ENTRY(604,"������ � ����������, ������������ � �������"),
	ERROR_ENTRY(605,"������ � ���������"),
	ERROR_ENTRY(606,"������ � ����������"),
	ERROR_ENTRY(607,"������ � �������� ���������"),
	ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
	ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR getError(int id) {
		if (id >= 0 && id < 1000)
			return errors[id];
		return errors[0];
	}
	ERROR getErrorIn(int id, int line = 0, int column = 0) {
		if (id >= 0 && id < 1000) {
			errors[id].inext.line = line + 1;
			errors[id].inext.column = column + 1;
			return errors[id];
		}
		return errors[0];
	}
};