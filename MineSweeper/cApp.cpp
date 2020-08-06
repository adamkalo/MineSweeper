#include "cApp.h"

wxIMPLEMENT_APP(cApp); 

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	my_frame1 = new cMain();
	my_frame1->Show();
	return true;
}
