#pragma once
#include <stdlib.h>
#include <utility>
#include <queue>

#include "MineSweeperEnums.h"
#include "MineSweeperBase.h"
#include "MineSweeperField.h"


class MineSweeperLogic : MineSweeperBase
{
public:
	MineSweeperLogic(int number_of_mines, int mine_field_width, int mine_field_height);
	MineSweeperLogic() = default;
	~MineSweeperLogic();

	std::pair<int, bool> OnLeftClickEvent(int index);
	std::pair<int, bool> OnLeftClickEvent(std::pair<int, int> coord);

	int OnRightClickEvent(int index);
	int OnRightClickEvent(std::pair<int,int> coord);

	const int& operator[](std::size_t idx) { return field_state[idx]; }
	const int& operator[](std::pair<int, int> coord) { return field_state[CoordinatesToIndex(coord)]; }

	int GetMineFieldValue(int index)
	{
		return (*MineField)[index];
	}
private:
	void DisableClearFieldsInVicinity(int index);
	void SearchForTheClear(std::pair<int, int> coord);

private:
	int* field_state = nullptr;
	MineSweeperField* MineField;
	std::queue<std::pair<int, int>> zero_elements;
	
};

