#pragma once
#include <utility>
#include "MineSweeperEnums.h"
class MineSweeperBase
{
public:
	MineSweeperBase(int number_of_mines, int mine_field_width, int mine_field_height) :
		number_of_mines(number_of_mines), mine_field_width(mine_field_width), mine_field_height(mine_field_height) {};
	MineSweeperBase() = default;
	~MineSweeperBase() {};

	int CoordinatesToIndex(std::pair<int, int> coords);
	std::pair<int, int> IndexToCoordinates(int index);

	bool FieldIsValid(std::pair<int, int> coord);

protected:
	int number_of_mines = 15;
	int mine_field_width = 10;
	int mine_field_height = 10;
};

