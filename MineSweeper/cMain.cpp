#include "cMain.h"

#define BUTTON_BASE_ID 10000


cMain::cMain() : wxFrame(nullptr,wxID_ANY,"MineSweeper - still demo")
{
	bts_mines = new wxButton * [mine_field_height * mine_field_width];

	wxGridSizer* grid = new wxGridSizer(mine_field_height, mine_field_width, 0, 0);

	

	wxFont font(16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false);
	
	for (int index = 0; index < mine_field_height * mine_field_width; index++)
	{
		bts_mines[index] = new wxButton(this, BUTTON_BASE_ID + index);
		bts_mines[index]->SetFont(font);
		grid->Add(bts_mines[index], 1, wxEXPAND | wxALL);

		bts_mines[index]->Bind(wxEVT_LEFT_UP, &cMain::on_left_button_clicked, this);
		bts_mines[index]->Bind(wxEVT_RIGHT_UP, &cMain::on_right_button_clicked, this);
	}
	this->SetSizer(grid);
	grid->Layout();

	MineLogic = new MineSweeperLogic(number_of_mines, mine_field_width, mine_field_height);
}
cMain::~cMain()
{
	delete MineLogic;
	delete[] bts_mines;
}



void cMain::on_left_button_clicked(wxEvent& evt)
{


	//Coords coords((evt.GetId() - BUTTON_BASE_ID) % mine_field_height, (evt.GetId() - BUTTON_BASE_ID) / mine_field_height);

	int index = evt.GetId() - BUTTON_BASE_ID;

	if ((*MineLogic)[index] == ACTIVE)
	{
		std::pair<int, bool> mine_event = MineLogic->OnLeftClickEvent(index);

		if (mine_event.first == MINE)
		{
			reset_minesweeper("BOOM! :(");
		}
		else if (mine_event.first == CLEAR)
		{
			for (int i = 0; i < mine_field_width * mine_field_height; i++)
			{
				if ((*MineLogic)[i] == DISABLED)
				{
					bts_mines[i]->Enable(false);
					int tv = MineLogic->GetMineFieldValue(i);
					if (tv != CLEAR)
						bts_mines[i]->SetLabel(std::to_string(tv));

				}
			}
		}
		else
		{
			int tv = MineLogic->GetMineFieldValue(index);
			bts_mines[index]->SetLabel(std::to_string(MineLogic->GetMineFieldValue(index)));
			bts_mines[index]->Enable(false);
		}
	}

	

		int sum = 0;
		for (int i = 0; i < mine_field_height * mine_field_width; i++)
			if (!bts_mines[i]->IsEnabled()) sum++;
		if (sum == mine_field_height * mine_field_width - number_of_mines)
			reset_minesweeper("Noice");
	
	evt.Skip();
}

void cMain::on_right_button_clicked(wxEvent& evt)
{
	
	int index = evt.GetId() - BUTTON_BASE_ID;

	if (MineLogic->OnRightClickEvent(index) == MARKED)
		bts_mines[index]->SetLabel("X");
	else
		bts_mines[index]->SetLabel("");	
	evt.Skip();
}



void cMain::reset_minesweeper(wxString mes)
{
	wxMessageBox(mes);

	for (int index = 0; index < mine_field_width * mine_field_height; index++)
	{
		bts_mines[index]->SetLabel("");
		bts_mines[index]->Enable(true);
	}

	MineSweeperLogic* temp = MineLogic;
	MineLogic = nullptr;
	delete temp;

	MineLogic = new MineSweeperLogic(number_of_mines, mine_field_width, mine_field_height);
}



