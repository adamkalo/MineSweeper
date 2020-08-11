#include "MineSweeperField.h"
#include <stdlib.h>

MineSweeperField::MineSweeperField(int number_of_mines, int mine_field_width, int mine_field_height) :
	MineSweeperBase(number_of_mines, mine_field_width, mine_field_height)
{
	field_values = new int[mine_field_height * mine_field_width];
	for (int i = 0; i < mine_field_width * mine_field_height; i++)
	{
		field_values[i] = CLEAR;
	}
	plantMines();
	setMineFieldValues();
}

MineSweeperField::~MineSweeperField()
{
	delete[] field_values;
}

void MineSweeperField::plantMines()
{
	int mines = number_of_mines;

	while (mines)
	{
		int try_index = rand() % mine_field_width * mine_field_height;

		if (field_values[try_index] == CLEAR)
		{
			field_values[try_index] = MINE;
			mines--;
		}
	}
}

void MineSweeperField::setMineFieldValues()
{
	for (int i = 0; i < mine_field_height * mine_field_width; i++)
	{
		if (field_values[i] != MINE)
			field_values[i] = SearchNeighboursForMines(i);
	}
}


int MineSweeperField::SearchNeighboursForMines(int index)
{
	std::pair<int, int> coords = IndexToCoordinates(index);

	int mine_count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			std::pair<int, int> neighbour (coords.first + i, coords.second + j);

			if ( FieldIsValid(neighbour) && coords != neighbour)
			{
				if (field_values[CoordinatesToIndex(neighbour)] == MINE)
					mine_count++;
			}
		}
	}

	return mine_count;
}


