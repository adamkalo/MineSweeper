#pragma once

#include "wx/wx.h"
#include <queue>
#include "Coords.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	void on_left_button_clicked(wxEvent& evt);
	void on_right_button_clicked(wxEvent& evt);

private:
	
	int get_array_num_from_coords(Coords coords);

	//place bombs
	void init_minesweeper(Coords coords);

	//fill label of every button
	void set_minefield();

	//clear minefield and button labels
	void reset_minesweeper(wxString mes);

	//get number of mines in neighbouring fields
	int search_neighbours(Coords coords);

	//check wether neighbour field coordinates are valid
	bool field_isvalid(Coords coords);

	void disable_zero_fields();

	void search_for_zeros(Coords coords);

	bool all_zones_cleared();

	void debug_show_labels();

	int number_of_mines = 15;
	int mine_field_width = 10;
	int mine_field_height = 10;
	int found_safe_places = 0;
	wxButton** bts_mines;
	int* mine_values = nullptr;
	bool first_click = true;

	std::queue<Coords> zero_elements;

};

