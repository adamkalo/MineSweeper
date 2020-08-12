#pragma once
#include <queue>

#include "wx/wx.h"
#include "IndependentMineSweeper.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	void on_left_button_clicked(wxEvent& evt);
	void on_right_button_clicked(wxEvent& evt);

private:
	
	void reset_minesweeper(wxString mes);

private:
	int number_of_mines = 15;
	int mine_field_width = 10;
	int mine_field_height = 10;
	int found_safe_places = 0;
	wxButton** bts_mines;
	int* mine_values = nullptr;
	bool first_click = true;

	MineSweeperLogic* MineLogic;
};

