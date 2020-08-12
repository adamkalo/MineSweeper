#pragma once
#include <utility>
#include "MineSweeperEnums.h"
#include "MineSweeperBase.h"

class MineSweeperField : MineSweeperBase
{

public:
	MineSweeperField(int number_of_mines, int mine_field_width, int mine_field_height);
	MineSweeperField() = default;
	~MineSweeperField();

	const int& operator[](std::size_t idx) { int ret = field_values[idx]; return ret; }

	const int& operator[](std::pair<int, int> coord) { return field_values[CoordinatesToIndex(coord)]; }

private:
	void plantMines();
	void setMineFieldValues();
	int SearchNeighboursForMines(int index);

private:
	int found_safe_places = 0;
	int* field_values = nullptr;

	
};

