
// Lab01View.cpp : implementation of the CLab01View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab01.h"
#endif

#include "Lab01Doc.h"
#include "Lab01View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab01View

IMPLEMENT_DYNCREATE(CLab01View, CView)

BEGIN_MESSAGE_MAP(CLab01View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLab01View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GO_STARTSIMULATIONS, &CLab01View::OnGoStartsimulations)
	ON_COMMAND(ID_SPEED_SPEEDDOWN, &CLab01View::OnSpeedSpeeddown)
	ON_COMMAND(ID_SPEED_S, &CLab01View::OnSpeedS)
END_MESSAGE_MAP()

// CLab01View construction/destruction
void TransparentPNG(CImage *png)
{
	for (int i = 0; i < png->GetWidth(); i++)  				//遍历像素处理
	{
		for (int j = 0; j < png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

CLab01View::CLab01View() noexcept
{
	// TODO: add construction code here
	imgLeft.Load(_T("antLeft.png"));
	imgRight.Load(_T("antRight.png"));
	TransparentPNG(&imgLeft);
	TransparentPNG(&imgRight);
	psm = NULL;
}

CLab01View::~CLab01View()
{
}

BOOL CLab01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab01View drawing

void CLab01View::OnDraw(CDC* pDC)
{
	CLab01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	if (psm==NULL)
	{
		return;
	}


	//GetWindows Size
	CRect rectDlg;
	GetClientRect(rectDlg);//获得窗体的大小
	int x_size = rectDlg.Width();
	int y_size = rectDlg.Height();
	int scale_coef = 5;
	int real_left = x_size / 2 - (rightEnd - leftEnd)*scale_coef / 2;
	int real_right = x_size / 2 + (rightEnd - leftEnd)*scale_coef / 2;

	//Draw Round Text;
	stringstream ss;
	ss << roundNumber<<"    Least Time : "<<least<<"    Most Time : "<<most<<"    FPS : "<<fps;
	string s1("Round : ");
	s1.append(ss.str());
	CString str(s1.data());

	CFont font; 
	font.CreateFontW(50,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial")
	);
	pDC->SelectObject(font);

	pDC->TextOut(x_size/8, y_size/8, str);

	//Draw Pole
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
	pDC->SelectObject(&penBlack);
	pDC->MoveTo(real_left, y_size/2);
	pDC->LineTo(real_right, y_size/2);
	
	//Draw Ants
	//imgLeft.Draw(pDC->m_hDC, x_size/2, y_size/2); //demo
	CFont font2;
	font2.CreateFontW(12,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial")
	);
	pDC->SelectObject(font2);
	int left_H = imgLeft.GetHeight();
	int left_W = imgLeft.GetWidth();
	int right_H = imgRight.GetHeight();
	int right_W = imgRight.GetWidth();
	for (size_t i = 0; i < ants.size(); i++)
	{
		if (!ants[i].isDie())
		{
			int realPos = (real_right*(ants[i].getPos() - leftEnd) + real_left * (rightEnd - ants[i].getPos())) / (rightEnd - leftEnd);
			if (ants[i].getDir())
			{
				imgLeft.Draw(pDC->m_hDC, realPos - left_W / 2, y_size / 2 - left_H);
			}
			else {
				imgRight.Draw(pDC->m_hDC, realPos - right_W / 2, y_size / 2 - right_H);
			}

			stringstream ss2;
			ss2 << ants[i].no;
			CString str2(ss2.str().data());
			pDC->TextOut(realPos, y_size / 2 - right_H - 8, str2);
		}
	}

}


// CLab01View printing


void CLab01View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLab01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLab01View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab01View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab01View diagnostics

#ifdef _DEBUG
void CLab01View::AssertValid() const
{
	CView::AssertValid();
}

void CLab01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab01Doc* CLab01View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab01Doc)));
	return (CLab01Doc*)m_pDocument;
}
#endif //_DEBUG

void CLab01View::onDrawDataRefresh(int left, int right, const vector<Ant> & _ants, int round)
{
	roundNumber = round;
	leftEnd = left;
	rightEnd = right;
	ants.clear();
	for (size_t i = 0; i < _ants.size(); i++)
	{
		ants.push_back(_ants.at(i));
	}
	Invalidate(true);
	UpdateWindow();
}

void  CLab01View::onFPSRefresh(int  _fps)
{
	fps = _fps;
}


UINT StartSM(LPVOID lpParam)
{
	CLab01View *pview = (CLab01View *)lpParam;
	SimulationManager sm(pview);
	pview->psm = &sm;
	pview->psm->caseInit();
	if (pview != NULL)
	{
		pview->psm->startSimulation();
	}
	int a = pview->psm->getLeast();
	int b = pview->psm->getMost();
	pview->psm = NULL;
	CString cstr;
	cstr.Format(_T("Simulation Accomplished\nThe least time is %d\nThe most time is %d"), a, b);//reference printf
	pview->MessageBox(cstr);
	pview->Invalidate();
	return 1;
}

void CLab01View::OnGoStartsimulations()
{
	// TODO: Add your command handler code here
	if (psm != NULL)
	{
		return;
	}
	CWinThread*	m_pThread;
	m_pThread = nullptr;
	m_pThread = AfxBeginThread(StartSM, this);

}




void CLab01View::OnSpeedSpeeddown()
{
	// TODO: Add your command handler code here
	if (psm != NULL)
	{
		psm->modifyRefreshingRate(false);
	}
}


void CLab01View::OnSpeedS()
{
	// TODO: Add your command handler code here
	if (psm != NULL)
	{
		psm->modifyRefreshingRate(true);
	}
}
