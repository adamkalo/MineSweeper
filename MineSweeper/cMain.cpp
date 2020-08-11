#include "cMain.h"

#define BUTTON_BASE_ID 10000


cMain::cMain() : wxFrame(nullptr,wxID_ANY,"MineSweeper - still demo")
{
	//Create an array for the buttons(mines)
	bts_mines = new wxButton * [mine_field_height * mine_field_width];

	//Create the grid to place the mines
	wxGridSizer* grid = new wxGridSizer(mine_field_height, mine_field_width, 0, 0);

	//Create the place for the mines
	mine_values = new int[mine_field_height * mine_field_width];

	//Bigger font size
	wxFont font(16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false);
	//wxPanel* p = new wxPanel(this);
	//p->Bind(wxEVT_LEFT_UP, &cMain::on_right_button_clicked, this);
	for (int x = 0; x < mine_field_width; x++)
	{
		for (int y = 0; y < mine_field_height; y++)
		{
			Coords coords(x, y);
			int mine_num = get_array_num_from_coords(coords);
			bts_mines[mine_num] = new wxButton(this, BUTTON_BASE_ID + mine_num);
			bts_mines[mine_num]->SetFont(font);
			grid->Add(bts_mines[mine_num], 1, wxEXPAND | wxALL);

			bts_mines[mine_num]->Bind(wxEVT_LEFT_UP, &cMain::on_left_button_clicked, this);
			bts_mines[mine_num]->Bind(wxEVT_RIGHT_UP, &cMain::on_right_button_clicked, this);
			mine_values[mine_num] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}
cMain::~cMain()
{
	delete[] mine_values;
	delete[] bts_mines;
}



void cMain::on_left_button_clicked(wxEvent& evt)
{


	Coords coords((evt.GetId() - BUTTON_BASE_ID) % mine_field_height, (evt.GetId() - BUTTON_BASE_ID) / mine_field_height);

	if (first_click)
	{
		init_minesweeper(coords);
	}

	if(bts_mines[mine_num]->GetLabel() != "X")
	{

		


		if (mine_values[mine_num] == -1)
		{
			reset_minesweeper("BOOM! :(");
		}
		else if (mine_values[mine_num] == 0)
		{
			zero_elements.push(coords);
			disable_zero_fields();
		}
		else if (mine_values[mine_num] > 0)
		{
			bts_mines[mine_num]->SetLabel(std::to_string(mine_values[mine_num]));
			bts_mines[mine_num]->Enable(false);
			found_safe_places++;
		}

		int sum = 0;
		for (int i = 0; i < mine_field_height * mine_field_width; i++)
			if (!bts_mines[i]->IsEnabled()) sum++;
		if (sum == mine_field_height * mine_field_width - number_of_mines)
			reset_minesweeper("Noice");
	}
	evt.Skip();
}

void cMain::on_right_button_clicked(wxEvent& evt)
{
	
	Coords coords((evt.GetId() - BUTTON_BASE_ID) % mine_field_height, (evt.GetId() - BUTTON_BASE_ID) / mine_field_height);
	int mine_num = get_array_num_from_coords(coords);
	if(bts_mines[mine_num]->GetLabel() == "" && bts_mines[mine_num]->IsEnabled())
	{
		bts_mines[mine_num]->SetLabel("X");
	}
	else if(bts_mines[mine_num]->GetLabel() == "X" && bts_mines[mine_num]->IsEnabled())
	{
		
		bts_mines[mine_num]->SetLabel("");
	}
	
	
	evt.Skip();
}


void cMain::init_minesweeper(Coords coords)
{
	first_click = false;
	
	for (int i = 0; i < mine_field_width * mine_field_height; i++)
		mine_values[i] = 0;
	
	int mines = number_of_mines;

	while (mines)
	{
		Coords mcoords(rand() % mine_field_width, rand() % mine_field_height);

		if (mine_values[get_array_num_from_coords(mcoords)] == 0  && mcoords != coords)
		{
			mine_values[get_array_num_from_coords(mcoords)] = -1;
			mines--;
		}
	}	
}


void cMain::reset_minesweeper(wxString mes)
{
	wxMessageBox(mes);

	first_click = true;
	for (int x = 0; x < mine_field_width; x++)
	{
		for (int y = 0; y < mine_field_height; y++)
		{
			Coords coords(x, y);
			int array_num = get_array_num_from_coords(coords);
			mine_values[array_num] = 0;
			bts_mines[array_num]->SetLabel("");
			bts_mines[array_num]->Enable(true);
		}
	}
}



