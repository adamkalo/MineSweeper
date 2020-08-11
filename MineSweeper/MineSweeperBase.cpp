#include <utility>
#include <stdlib.h>
#include "MineSweeperBase.h"

int MineSweeperBase::CoordinatesToIndex(std::pair<int, int> coords)
{
    return coords.second * mine_field_height + coords.first;
}

std::pair<int, int> MineSweeperBase::IndexToCoordinates(int index)
{
	return std::pair<int, int>(index % mine_field_height, index / mine_field_height);
}

bool MineSweeperBase::FieldIsValid(std::pair<int, int> coord)
{
	return coord.first >= 0 && coord.first < mine_field_width&& coord.second >= 0 && coord.second <= mine_field_height;
}
