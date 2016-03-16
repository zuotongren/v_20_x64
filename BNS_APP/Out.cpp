// Out.cpp : 实现文件
//

#include "stdafx.h"
#include "BNS_APP.h"
#include "Out.h"


// COut 对话框

IMPLEMENT_DYNCREATE(COut, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(COut, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

// {579F2844-8045-43A8-B145-FD1BD5D53629}
IMPLEMENT_OLECREATE_EX(COut, "BNS_APP.Out",
	0x579f2844, 0x8045, 0x43a8, 0xb1, 0x45, 0xfd, 0x1b, 0xd5, 0xd5, 0x36, 0x29)



// COut::COutFactory::UpdateRegistry -
// 添加或移除 COut 的系统注册表项

BOOL COut::COutFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 定义页类型的字符串资源；用 ID 替换下面的“0”。

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, 0);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// COut::COut - 构造函数

// TODO: 定义页标题的字符串资源；用 ID 替换下面的“0”。

COut::COut() :
	COlePropertyPage(IDD, 0)
{

}



// COut::DoDataExchange - 在页和属性间移动数据

void COut::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// COut 消息处理程序
