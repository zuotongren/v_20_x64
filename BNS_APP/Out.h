#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 COlePropertyPage。"
#endif 

// COut : 属性页对话框

class COut : public COlePropertyPage
{
	DECLARE_DYNCREATE(COut)
	DECLARE_OLECREATE_EX(COut)

// 构造函数
public:
	COut();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};
