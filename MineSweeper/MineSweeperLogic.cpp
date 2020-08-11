#include "MineSweeperEnums.h"
#include "MineSweeperBase.h"
#include "MineSweeperLogic.h"
#include "MineSweeperField.h"

MineSweeperLogic::MineSweeperLogic(int number_of_mines, int mine_field_width, int mine_field_height):
	MineSweeperBase(number_of_mines, mine_field_width, mine_field_height)
{
	field_state = new int[mine_field_height * mine_field_width];
	for (int i = 0; i < mine_field_width * mine_field_height; i++)
	{
		field_state[i] = ACTIVE;
	}

	MineField = new MineSweeperField(number_of_mines, mine_field_width, mine_field_height);
}

MineSweeperLogic::~MineSweeperLogic()
{
	delete[] field_state;
	delete MineField;
}

std::pair<int, bool> MineSweeperLogic::OnLeftClickEvent(int index)
{
	if ((*MineField)[index] == MINE)
	{
		return std::pair<int, bool>(MINE, false);
	}
	else if ((*MineField)[index] == CLEAR)
	{
		DisableClearFieldsInVicinity(index);
		return std::pair<int, bool>(CLEAR, true);
	}
	else 
	{
		return std::pair<int, bool>((*MineField)[index], false);
	}
	
	return std::pair<int, bool>();
}

std::pair<int, bool> MineSweeperLogic::OnLeftClickEvent(std::pair<int, int> coord)
{
	return OnLeftClickEvent(CoordinatesToIndex(coord));
}

bool MineSweeperLogic::OnRightClickEvent(int index)
{
	return false;
}

bool MineSweeperLogic::OnRightClickEvent(std::pair<int, int> coord)
{
	return OnRightClickEvent(CoordinatesToIndex(coord));
}

void MineSweeperLogic::DisableClearFieldsInVicinity(int index)
{
	zero_elements.push(IndexToCoordinates(index));
	while (!zero_elements.empty())
	{
		std::pair<int, int> current = zero_elements.front();
		zero_elements.pop();
		field_state[CoordinatesToIndex(current)] = DISABLED;
		SearchForTheClear(current);
	}
}

void MineSweeperLogic::SearchForTheClear(std::pair<int, int> coord)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			std::pair<int, int> test_coord(coord.first + i, coord.second + j);
			if (FieldIsValid(test_coord) && test_coord != coord)
			{
				if ((*MineField)[CoordinatesToIndex(test_coord)] == CLEAR && field_state[CoordinatesToIndex(test_coord)] == ACTIVE)
					zero_elements.push(test_coord);
				else if ((*MineField)[CoordinatesToIndex(test_coord)] > 0 && field_state[CoordinatesToIndex(test_coord)] == ACTIVE)
				{
					field_state[CoordinatesToIndex(test_coord)] = DISABLED;
				}
			}
		}
	}
}
