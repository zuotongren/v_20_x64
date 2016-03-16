///****************************************************//
//***  WzdSplash类的头文件，本类的声明是为在程序的开头添加一段flash动画。

//* 对程序的运行并没有直接的作用。
#pragma once


// CWzdSplash

class CWzdSplash : public CWnd
{
	DECLARE_DYNAMIC(CWzdSplash)

public:
	CWzdSplash();
	virtual ~CWzdSplash();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBitmap m_bitmap;
	void Create (UINT nBitmapID);
	
};


