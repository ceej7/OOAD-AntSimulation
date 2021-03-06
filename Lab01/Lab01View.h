// Lab01View.h : interface of the CLab01View class
//

#pragma once
#include <sstream>
#include "Lab01Doc.h"
#include "SimulationManager.h"

class CLab01View : public CView
{
protected: // create from serialization only
	CLab01View() noexcept;
	DECLARE_DYNCREATE(CLab01View)

// Attributes
public:
	CLab01Doc* GetDocument() const;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	
public:
	int least = -1;
	int most = -1;
	SimulationManager *psm;
private:
	//TODO: Drawing INFO
	int leftEnd;
	int rightEnd;
	vector<Ant> ants;
	int roundNumber=-1;
	CImage imgLeft;
	CImage imgRight;
	int fps = 0;

	// Operations
public:
	void onFPSRefresh(int  _fps);
	void onDrawDataRefresh(int left, int right, const vector<Ant> & _ants,  int round);
private:
	afx_msg void OnGoStartsimulations();
	afx_msg void OnSpeedSpeeddown();
	afx_msg void OnSpeedS();
};

#ifndef _DEBUG  // debug version in Lab01View.cpp
inline CLab01Doc* CLab01View::GetDocument() const
   { return reinterpret_cast<CLab01Doc*>(m_pDocument); }
#endif

