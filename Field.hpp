#ifndef _FIELD
#define _FIELD

#include <Windows.h>
#include "Stuff.hpp"

class Builder;

// ��������� ���� ��� ����
class Field
{
private:
	short rows;
	short columns;
	char** field;
	POINT portals[PORTALCOUNT];
	void drawPortals();

	friend Builder; // ����������� �������������� ������ ���������. (��. �����)
public:
	Field(short rows, short columns);
	Field();
	~Field();

	void addFruit(int x, int y);
	void addPortal(POINT a);
	void CreatePortals();


	void clearField();
	void printField();

	char** getCharField();
	short getRows();
	short getColumns();
	POINT* getPortals();
};


// �����-Builder ��� ������ Field.
// �������� �������������� ��������(������� ��������������) Builder - ����������� �������� ����������� ������.
// 
// ���� ��������� n-oe ���-�� ���������� ��������, �� ��� ��� ����� ������� ��������� ����� Builder,
// ������� ������� ��������� � ����� ��������� ������ ����� ��������� � ������ ����������� �� ������ ������.
class Builder
{
private:
	// ������ ��������� ��� ���������� ���� - ������ � �������. ��� ���� � �������� Builder.
	short rows;
	short columns;

public:
	// �������� setSettings � ����������� ������������ �����.
	Builder(short rows, short columns);
	Builder();

	// ����������� ��������� ���������.
	void setSettings(short rows, short columns);

	// ����� ����������� ��� ������ ������ ��������� ���������� ��������� �������� � ����� �����������.
	// �� ����� ������ ��� ��������� ��������� ���������.
	// ������������� ������� ��������� ������������� ��������� ������ - ���������� �������.
	// � ������� �� ������������ ��������� �� ������.
	
	// ��� ����������� ���, ��� ������ �� ������� ������ ������������� ����������� ������ Field ��������� �� ���������� ������,
	// � �������� ����������� � ��������� ������������ ������������� ������� ���������� �� ����������� ����� �������, 
	// ��� �� ���� ������ ��������. (������� �� � ������)

	// P.S �������������� ����, ��� ��������� ����� ����� ���� ������ � ���� ������� ������� � ��� �� ������, 
	// �� ��� ������� �������� ��������� � ����� ��� ����� ��������.
	// TODO: ������ ���� ��� �������������

	// ����������� ��������� ������ Field �� ������.
	void buildbyReference(Field* newfield);
	// ������ ��������� ������ Field ��������� ���.
	Field buildByCreation();
};

#endif // !_FIELD