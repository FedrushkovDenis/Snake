#include "Field.hpp"
#include "..\Stuff.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

Field::Field() {}

char** Field::getCharField()
{
	return field;
}

short Field::getColumns()
{
	return columns;
}

short Field::getRows()
{
	return rows;
}

POINT* Field::getPortals()
{
	return portals;
}

void Field::addFruit(int x, int y)
{
	this->field[y][x] = FRUIT;
}

void Field::addPortal(POINT a)
{
	this->field[a.y][a.x] = PORTAL;
}

void Field::CreatePortals()
{
	portals[0].x = 5;
	portals[0].y = 5;

	portals[1].x = 5;
	portals[1].y = 20;

	portals[2].x = 20;
	portals[2].y = 5;

	portals[3].x = 20;
	portals[3].y = 20;
}

void Field::drawPortals()
{
	for (short i = 0; i < 4; i++)
	{
		this->field[portals[i].y][portals[i].x] = PORTAL;
	}
}

void Field::clearField()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			if (this->field[i][j] != FRUIT)
			{
				this->field[i][j] = ' ';
			}
			if (i == 0 || j == 0 || i == (this->rows - 1) || j == (this->columns - 1))
			{
				this->field[i][j] = '#';
			}

			this->drawPortals();
		}
	}
}

Field::Field(short rows, short columns)
{
	this->rows = rows;
	this->columns = columns;
	this->field = new char*[this->rows];

	for (int i = 0; i < this->rows; i++)
	{
		this->field[i] = new char[this->columns];
	}

	int i = 0;
	int j = 0;

	for (i = 0; i < this->rows; i++)
	{
		for (j = 0; j < this->columns; j++)
		{
			this->field[i][j] = ' ';
			if (i == 0 || j == 0 || i == (this->rows - 1) || j == (this->columns - 1))
				this->field[i][j] = '#';
		}
	}
}

Field::~Field()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] field[i];
	}
	delete field;
}

void Field::printField()
{
	for (int i = 0; i < this->rows; i++)
	{
		cout << this->field[i];
		cout << endl;
	}
}

Builder::Builder() {}

Builder::Builder(short rows, short columns)
{
	this->setSettings(rows, columns);
}

void Builder::setSettings(short rows, short columns)
{
	this->rows = rows;
	this->columns = columns;
}

void Builder::buildbyReference(Field* newfield)
{
	newfield->rows = this->rows;
	newfield->columns = this->columns;
	newfield->field = new char* [newfield->rows+1];

	for (int i = 0; i < newfield->rows; i++)
	{
		newfield->field[i] = new char[newfield->columns+1];
	}

	int i = 0;
	int j = 0;

	for (i = 0; i < newfield->rows; i++)
	{
		for (j = 0; j < newfield->columns; j++)
		{
			newfield->field[i][j] = ' ';
			if (i == 0 || j == 0 || i == (newfield->rows - 1) || j == (newfield->columns - 1))
				newfield->field[i][j] = '#';
		}
		newfield->field[i][j] = '\0';
	}

}

Field Builder::buildByCreation()
{
	Field newfield;
	newfield.rows = this->rows;
	newfield.columns = this->columns;
	newfield.field = new char* [this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		newfield.field[i] = new char[this->columns];
	}
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			newfield.field[i][j] = ' ';
			if (i == 0 || j == 0 || i == (this->rows - 1) || j == (this->columns - 1))
				newfield.field[i][j] = '#';
		}
	}
	return newfield;
}
