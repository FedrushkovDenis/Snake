#ifndef _FIELD
#define _FIELD

// Стили двумерного поля 
#define FSTYLE_NONE 				0x000		// Отсутствие стиля поля.
#define FSTYLE_SQUARE				0x001		// Стена из квадратов по краям.
#define FSTYLE_VDASH				0x002		// Вертикальная черта по центру поля.
#define FSTYLE_HDASH				0x004		// Горизонтальная черта по центру поля.
#define FSTYLE_SLASH				0x008		// Косая черта из левого нижнего до правого верхнего угла.
#define FSTYLE_BACKSLASH			0x010		// Обратная косая черта из левого верхнего до правого нижнего угла.
#define FSTYLE_CROSS	(FSTYLE_SLASH | FSTYLE_BACKSLASH)
#define FSTYLE_PLUS		(FSTYLE_VDASH | FSTYLE_HDASH)

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
	char fruitmass[3];
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
	char fruitmass[3];
	short style;

public:
	// Вызывает все методы-сеттеры с параметрами конструктора сразу.
	Builder(short rows, short columns, short style);
	Builder();

	// Устанавливает размеры
	void setSize(short rows, short columns);
	// Устанавливает стиль.
	void setStyle(short style);

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
};

#endif // !_FIELD