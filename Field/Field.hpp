#ifndef _FIELD
#define _FIELD

#include <Windows.h>
#include "..\Stuff.hpp"

class Builder;

struct Portal 
{
	POINT portal;
	char type;
};

// Двумерное поле для игры
class Field
{
private:
	short rows;
	short columns;
	char** field;
	Portal portals[PORTALCOUNT];
	void drawPortals();

	friend Builder; // Обозначение дружественного класса Строителя. (см. далее)
public:
	Field(short rows, short columns);
	Field();
	~Field();

	void addFruit(int x, int y);
	void addPortal(Portal a);
	void CreatePortals();


	void clearField();
	void printField();

	char** getCharField();
	short getRows();
	short getColumns();
	Portal* getPortals();
};


// Класс-Builder для класса Field.
// Основное предназначение паттерна(шаблона проектирования) Builder - оптимизация создания экземпляров класса.
// 
// Если требуется n-oe кол-во однородных объектов, то для них можно создать отдельный класс Builder,
// который получит параметры и будет создавать каждый такой экземпляр с такими параметрами по щелчку пальца.
class Builder
{
private:
	// Важные параметры для двумерного поля - строки и столбцы. Эти поля и копирует Builder.
	short rows;
	short columns;

public:
	// Вызывает setSettings с параметрами конструктора сразу.
	Builder(short rows, short columns);
	Builder();

	// Настраивает параметры строителя.
	void setSettings(short rows, short columns);

	// Здесь реализованы две версии работы строителя вследствие различных подходов к самой архитектуре.
	// По своей логике оба строителя абсолютно одинаковы.
	// Использование прямого строителя возвращающего экземпляр класса - каноничный вариант.
	// В проекте же используется настройка по ссылке.
	
	// Это обусловлено тем, что работа по очистке памяти новосозданных экземпляров класса Field возложена на деструктор класса,
	// а создание экземпляров в локальном конструкторе автоматически вызовет деструктор по возвращению этого объекта, 
	// что не даст ничего хорошего. (Сломает всё к чертям)

	// P.S Справедливости ради, всю настройку полей можно было снести в одну функцию лежащую в том же классе, 
	// но как базовое обучение паттернам я решил это здесь оставить.
	// TODO: строки кода для использования

	// Настраивает экземпляр класса Field по ссылке.
	void buildbyReference(Field* newfield);
	// Строит экземпляр класса Field возвращая его.
	Field buildByCreation();
};

#endif // !_FIELD