#include "CGuiViewLoadingScreen.h"
#include "VID_Main.h"
#include "CGuiViewResourceManager.h"
#include "CGuiMain.h"
#include <string.h>

#define DEBUG_LOG_LOAD_TIME	3500

CGuiViewLoadingScreen::CGuiViewLoadingScreen(float posX, float posY, float posZ, float sizeX, float sizeY)
: CGuiViewBaseLoadingScreen(posX, posY, posZ, sizeX, sizeY)
{
	this->name = "CGuiViewLoadingScreen";
	
	imGuiNoWindowPadding = true;
	imGuiNoScrollbar = true;

	memset(this->loadingText, 0x00, GUIVIEWLOADINGSCREEN_TEXT_LEN);
	this->SetLoadingText("idle");
}

CGuiViewLoadingScreen::~CGuiViewLoadingScreen()
{
}

void CGuiViewLoadingScreen::SetLoadingText(const char *text)
{
	guiMain->LockMutex();
	strncpy(this->loadingText, text, GUIVIEWLOADINGSCREEN_TEXT_LEN-2);
	guiMain->UnlockMutex();
}

void CGuiViewLoadingScreen::DoLogic()
{
	CGuiView::DoLogic();
}

void CGuiViewLoadingScreen::Render()
{
	//LOGD2("CGuiViewLoadingScreen::Render");
	
#if !defined(FINAL_RELEASE)
	//guiMain->fntConsole->BlitText("LOADING", 100, 50, 0, 11, 1.0);
	guiMain->fntConsole->BlitText(this->loadingText, 0, 0, 0, 11, 1.0);
	
	u64 loadTime = SYS_GetCurrentTimeInMillis() - loadStartTime;
	TimeToStr(loadTime);
	guiMain->fntConsole->BlitText(this->strTime, sizeX-(8*11), 0, 0, 11, 1.0);
	
	guiMain->viewResourceManager->Render(0.0f, 0.0f);

	CGuiView::Render();
#endif
	
}

void CGuiViewLoadingScreen::Render(float posX, float posY)
{
	CGuiView::Render(posX, posY);
}

//@returns is consumed
bool CGuiViewLoadingScreen::DoTap(float x, float y)
{
	LOGG("CGuiViewLoadingScreen::DoTap:  x=%f y=%f", x, y);
	
	return guiMain->viewResourceManager->DoTap(x, y);
	//return CGuiView::DoTap(x, y);
}

bool CGuiViewLoadingScreen::DoFinishTap(float x, float y)
{
	LOGG("CGuiViewLoadingScreen::DoFinishTap: %f %f", x, y);
	return guiMain->viewResourceManager->DoFinishTap(x, y);
	return CGuiView::DoFinishTap(x, y);
}

//@returns is consumed
bool CGuiViewLoadingScreen::DoDoubleTap(float x, float y)
{
	LOGG("CGuiViewLoadingScreen::DoDoubleTap:  x=%f y=%f", x, y);
	return CGuiView::DoDoubleTap(x, y);
}

bool CGuiViewLoadingScreen::DoFinishDoubleTap(float x, float y)
{
	LOGG("CGuiViewLoadingScreen::DoFinishTap: %f %f", x, y);
	return CGuiView::DoFinishDoubleTap(x, y);
}


bool CGuiViewLoadingScreen::DoMove(float x, float y, float distX, float distY, float diffX, float diffY)
{
	return guiMain->viewResourceManager->DoMove(x, y, distX, distY, diffX, diffY);
	return CGuiView::DoMove(x, y, distX, distY, diffX, diffY);
}

bool CGuiViewLoadingScreen::FinishMove(float x, float y, float distX, float distY, float accelerationX, float accelerationY)
{
	return guiMain->viewResourceManager->FinishMove(x, y, distX, distY, accelerationX, accelerationY);
	return CGuiView::FinishMove(x, y, distX, distY, accelerationX, accelerationY);
}

bool CGuiViewLoadingScreen::InitZoom()
{
	return guiMain->viewResourceManager->InitZoom();
	return CGuiView::InitZoom();
}

bool CGuiViewLoadingScreen::DoZoomBy(float x, float y, float zoomValue, float difference)
{
	return guiMain->viewResourceManager->DoZoomBy(x, y, zoomValue, difference);
	return CGuiView::DoZoomBy(x, y, zoomValue, difference);
}

void CGuiViewLoadingScreen::ActivateView()
{
	LOGG("CGuiViewLoadingScreen::ActivateView()");
	loadStartTime = SYS_GetCurrentTimeInMillis();
}

void CGuiViewLoadingScreen::DeactivateView()
{
	LOGG("CGuiViewLoadingScreen::DeactivateView()");
}

void CGuiViewLoadingScreen::LoadingFinishedSetView(CGuiView *nextView)
{
	LOGM("CGuiViewLoadingScreen::LoadingFinishedSetView");

	u64 loadTime = SYS_GetCurrentTimeInMillis() - loadStartTime;
	
	if (loadTime > DEBUG_LOG_LOAD_TIME)
	{
		TimeToStr(loadTime);
		LOGWarning("CGuiViewLoadingScreen: loadTime=%s", strTime);
	}
	
	guiMain->SetView(nextView);

	VID_ResetLogicClock();
}

// returns local buffer
void CGuiViewLoadingScreen::TimeToStr(long time)
{
	long tms = time % 1000;
	u16 tms2 = tms / 10;
	long ts = (time / 1000) % 60;
	long tm = time / 60000;
	
	sprintf(strTime, "%02ld:%02ld.%02d", tm, ts, tms2);
}
