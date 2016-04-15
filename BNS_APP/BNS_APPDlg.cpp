// BNS_APPDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "BNS_APP.h"
#include "BNS_APPDlg.h"
#include "cdib.h"
#include <fstream>
#include "math.h"
//#include "Windows.h"
#include "WzdSplash.h"
#include "Out.h"
#include "afx.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_LINE	300
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBNS_APPDlg 对话框




CBNS_APPDlg::CBNS_APPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBNS_APPDlg::IDD, pParent)
	, m_EDIT_BN(0)
	, m_EDIT_EN(0)
	, m_speed(0)
	, m_Now(0)
	, m_CompensatePhase(FALSE)
	, m_L0(0)
	, m_i0(0)
	, m_r0(0)
	, m_Width_m(0)
	, m_Len_m(0)
	, m_frame(0)
	, m_T(0)
	, m_now_frame(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBNS_APPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_Picture);
	DDX_Text(pDX, IDC_EDIT_Begin_Num, m_EDIT_BN);
	DDX_Text(pDX, IDC_EDIT_End_Num, m_EDIT_EN);
	DDX_Text(pDX, IDC_EDIT_Time, m_speed);
	DDX_Text(pDX, IDC_EDIT_Now, m_Now);
	DDX_Control(pDX, IDC_COMPENSATE_PHASE_CHECKBOX, m_CompensatePhaseCheckbox);
	DDX_Control(pDX, IDC_START_STOP_BUTTON, m_StartStopButton);
	DDX_Control(pDX, IDC_SLM_PWR_BUTTON, m_SlmPwrButton);
	DDX_Check(pDX, IDC_COMPENSATE_PHASE_CHECKBOX, m_CompensatePhase);
	DDX_Control(pDX, IDC_BUTTON_UP, m_UP);
	DDX_Control(pDX, IDC_BUTTON_Down, m_DOWN);
	DDX_Text(pDX, IDC_EDIT1, m_L0);
	DDX_Text(pDX, IDC_EDIT2, m_i0);
	DDX_Text(pDX, IDC_EDIT3, m_r0);
	DDX_Text(pDX, IDC_EDIT8, m_Width_m);
	DDX_Text(pDX, IDC_EDIT10, m_Len_m);
	DDX_Text(pDX, IDC_EDIT9, m_frame);
	DDX_Control(pDX, IDC_BUTTON_YuSheZhi, m_Prepare_value);
	DDX_Control(pDX, IDC_BUTTON_Open, m_Open);
	DDX_Control(pDX, IDC_BUTTON_KaiShi, m_Begin);
	DDX_Control(pDX, IDC_BUTTON_Out, m_out);
	DDX_Control(pDX, IDC_BUTTON_Save, m_Save);
	DDX_Control(pDX, IDC_ADD, m_Load);
	DDX_Control(pDX, IDC_BUTTON_Add, m_Add);
	DDX_Text(pDX, IDC_EDIT_T, m_T);
	DDX_Text(pDX, IDC_EDIT5, m_now_frame);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CBNS_APPDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Open, &CBNS_APPDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_START_STOP_BUTTON, &CBNS_APPDlg::OnBnClickedStartStopButton)
	ON_BN_CLICKED(IDC_SLM_PWR_BUTTON, &CBNS_APPDlg::OnBnClickedSlmPwrButton)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CBNS_APPDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_Down, &CBNS_APPDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_COMPENSATE_PHASE_CHECKBOX, &CBNS_APPDlg::OnBnClickedCompensatePhaseCheckbox)
//	ON_WM_TIMER()
//	ON_EN_CHANGE(IDC_EDIT_Begin_Num, &CBNS_APPDlg::OnEnChangeEditBeginNum)
//	ON_EN_CHANGE(IDC_EDIT_End_Num, &CBNS_APPDlg::OnEnChangeEditEndNum)
	ON_BN_CLICKED(IDC_BUTTON_YuSheZhi, &CBNS_APPDlg::OnBnClickedButtonYushezhi)
	ON_BN_CLICKED(IDC_BUTTON_KaiShi, &CBNS_APPDlg::OnBnClickedButtonKaishi)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CBNS_APPDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_Out, &CBNS_APPDlg::OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_ADD, &CBNS_APPDlg::OnBnClickedAdd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Add, &CBNS_APPDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CBNS_APPDlg::OnBnClickedButtonGo)
END_MESSAGE_MAP()


// CBNS_APPDlg 消息处理程序

BOOL CBNS_APPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CWzdSplash wndSplash;                     
	wndSplash.Create(IDB_BITMAP1);
	wndSplash.CenterWindow();
	wndSplash.UpdateWindow();
	wndSplash.SetTimer(0,40000,NULL);
	Sleep(2000);
	srand((unsigned)time(NULL));                //时间数种子
	m_hicn1=AfxGetApp()->LoadIcon(IDI_ICON1);   
	m_Add.SetIcon(m_hicn1);
	m_hicn2=AfxGetApp()->LoadIcon(IDI_ICON2);
	m_DOWN.SetIcon(m_hicn2);
	Page_0=0;
	key=false;
	Down_Up=1;
	Pixel=1;
	Mosaic_Pixel=Mosaic;
 
	INFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+256*sizeof(RGBQUAD));    //BMP文件信息头数据
	(*INFO).bmiHeader.biSize=0x28;
	(*INFO).bmiHeader.biWidth=512;
	(*INFO).bmiHeader.biHeight=512;
	(*INFO).bmiHeader.biPlanes=0x01;
	(*INFO).bmiHeader.biBitCount=0x08;
	(*INFO).bmiHeader.biCompression=0x00;
	(*INFO).bmiHeader.biSizeImage=0x00;
	(*INFO).bmiHeader.biXPelsPerMeter=0x800;
	(*INFO).bmiHeader.biYPelsPerMeter=0x800;
	(*INFO).bmiHeader.biClrUsed=0x00;
	(*INFO).bmiHeader.biClrImportant=0x00;
	for(int i=0;i<256;i++)
	{
		(*INFO).bmiColors[i].rgbRed=i;
		(*INFO).bmiColors[i].rgbGreen=i;
		(*INFO).bmiColors[i].rgbBlue=i;
		(*INFO).bmiColors[i].rgbReserved=0;
	}



    m_StartStopButton.EnableWindow(false);
	m_SlmPwrButton.EnableWindow(false);
	m_UP.EnableWindow(false);
	m_DOWN.EnableWindow(false);
	m_Add.EnableWindow(false);
	m_Save.EnableWindow(false);
	m_Load.EnableWindow(false);
	m_out.EnableWindow(false);
	UpdateData(false);
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBNS_APPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBNS_APPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBNS_APPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////
//
//函数名：OnBnClickedButtonOpen()
//
//函数参数：无
//
//函数功能：打开一副待显示的文件，并获得一些信息，如文件名、文件单位数。
//
//函数返回值：无
//
////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDC *pDC;             //定义一个句柄指针
	//pDC=m_Picture.GetDC();//得到Picture control 的句柄 
	biWidth=POINT;        //得到相位屏的大小信息
	biHeight=POINT;
    TCHAR szFilter[] = _T("所有文件(*.*)|*.*|相位屏文件（*.4wf）|*.4wf||");   	 // 设置过滤器
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, NULL, NULL,0, szFilter, this);   //创建一个CFileDiloge对象  
  
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   //如果打开了文件
	{
	   // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里 
		strFilePath = fileDlg.GetPathName(); //得到文件路径名
		SetDlgItemText(IDC_EDIT_Path, strFilePath); //将文件路径名“打印”出来
	}

	//----以读写方式打开需要加载的文件（需要加载的文件是以二进制形式存储的），----//

	//----如果顺利打开。则，将数据加载到内存中。

	if (file.Open(strFilePath,  CFile::modeRead))
	{
			file.SeekToBegin();
			Page=(file.GetLength())/(8*biWidth)-511;     //获得相位屏帧数  -sizeof(file_head)
			CS_Page.Format(_T("file long %d "),Page);       //打印相位屏帧数信息
			SetDlgItemText(IDC_EDIT_Page,CS_Page);  

            //----      给动态数组分配内存。实际上是一个三维的组数--------//

            //----  大小为：Page*biWidth*biHeigth。这样做是有道理的-------//

            //----  一、在定义数组之前，我们并不知道要定义多大的数组------//

            //----- 采用动态数组可以节省空间，并保证程序的安全。----------//

		    // ---- 二、在使用结束之后，可以尽快的释放内存空间。----------//

			ColorBuff=new double[512*(Page+511)];           
			/*for(int i=0;i<Page;i++)                        
			{                                              
				ColorBuff[i]=new unsigned char[biWidth*biHeight];
			                                              
			}*/
			//file.Read(&file_head,sizeof(file_head));
			file.Read(ColorBuff,8*512*(Page+511));
			/*m_L0=file_head.m_L0;
	        m_i0=file_head.m_i0;
	        m_r0=file_head.m_r0;
	        m_speed=file_head.m_speed;
	        m_frame=file_head.m_frame;
	        m_Width_m=file_head.m_Width_m;
	        m_Len_m=file_head.m_Len_m;
	        m_T=file_head.m_T;*/
			file.Close();
			UpdateData(Up);
			if(m_Width<POINT)                  //申请一个512*512的数组，用于当生成的相位屏小于512时，这将其转化为512*512
			{
				ColorBuff_512=new unsigned __int8[POINT*POINT];
			    for(int i=0;i<POINT*POINT;i++)
			    {
				ColorBuff_512[i]=0;
			    }

			}
			key=true;//将一个bool类型变量设置为true 通知系统已经为动态数组分配内存
			MessageBox(_T("图片装载完成！"),MB_OK,MB_ICONASTERISK);
			m_Begin.EnableWindow(false);//将“开始”按钮设置为不可用
	        m_Prepare_value.EnableWindow(false);
	        m_SlmPwrButton.EnableWindow(false);
			m_UP.EnableWindow(true);
			m_DOWN.EnableWindow(true);
			m_Add.EnableWindow(true);
			m_out.EnableWindow(true);
			m_Load.EnableWindow(true);


			//当文件加载完毕之后，上电按钮就可以正常工作。
	}

}
//////////////////////////////////////////////////////////////////////
//
//函数名：OnBnClickedStartStopButton()
//
//参数：无
//
//返回值：无
//
//函数功能：开始/停止加载图片按钮
//
//
////////////////////////////////////////////////////////////////////

void CBNS_APPDlg::OnBnClickedStartStopButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString SpSt;
	m_StartStopButton.GetWindowText(SpSt);
	//设置一个CString变量，来获得开始/停止按钮的状态信息
	UpdateData(Down);//将面板上设置的参数传递给程序变量
	Page_0=m_Now;    //Page_0这个变量很重要，它是将要显示相位屏的标号。例如Page_0==0；则将要显示的相位屏就是第一幅相位屏。
	
    //-----当确定按钮为“START”（开始）时，开始加载相位屏数据。--//
	if (0==SpSt.Compare(_T("START")))  
	{
		if(m_speed==0&&m_frame==0)
		{
			MessageBox(_T("请选择定时器时间") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }
		Pixel=floor((1/m_frame)*(POINT/m_Width_m)*m_speed);  //根据风速和帧率换算出来的相位屏间隔数
	    m_SlmPwrButton.EnableWindow(false);
		m_Add.EnableWindow(false);
		m_UP.EnableWindow(false);
		m_DOWN.EnableWindow(false);

		//-------相位屏显示信息，本程序是不对初值进行强制要求用户设定的。---//

		//---但，数据并不能超过“0--Page”这个范围，所以程序对此作了处理----//

		if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	   /*else if(m_EDIT_EN>=m_EDIT_BN)
	       {
			   MessageBox(_T("注意：结束号要大于开始号！！！") ,MB_OK,MB_ICONEXCLAMATION);
			   return;
		   }*/
	   else if(m_EDIT_BN>=Page)//如果初值或终值超出（Page-），则将初值设置为0，终值设置为（Page-1）
	       {
			   m_EDIT_BN=0;
			   m_EDIT_EN=Page-1;
			   UpdateData(false);
		       Page_0=m_EDIT_BN;
		       Page_end=m_EDIT_EN;
		    }                                 //
	   Page_0=m_EDIT_BN;
	   Page_end=m_EDIT_EN;
	   while(Page_0< m_EDIT_EN)//Page_0 != m_EDIT_EN
		{
			QueryPerformanceCounter(&M_Begin);//得到系统当前计数器值
			if(!QueryPerformanceFrequency(&Frequence))//得到系统时钟频率
			{
				MessageBox(_T("对不起，您的电脑不支持高精度计数器！"),MB_OK,MB_ICONEXCLAMATION);
				return;
			}

			TimeToL.QuadPart= Frequence.QuadPart*(1000000/m_frame-2600)/1000000;//通过频率换算微妙数到对应的数量（与CPU有关），1秒=1000000微妙；
			My_Delay(TimeToL);                                  //延时 单位：微秒
			LoadHardBoard();                                    //加载相位屏到硬件
			QueryPerformanceCounter(&M_End);                    //得到系统当前计数器值
			m_now_frame=int ((Frequence.QuadPart)*1.0/((M_End.QuadPart-M_Begin.QuadPart)*1.0));//得到相位屏加载帧率。帧率的是计算公式为：帧率=系统频率/（计数差值）；
			UpdateData(false);
		}

		m_StartStopButton.SetWindowText(_T("STOP"));
	  
	}
	if (0==SpSt.Compare(_T("STOP")))  
	{
		m_StartStopButton.SetWindowText(_T("START"));
    	m_SlmPwrButton.EnableWindow(true);
		m_UP.EnableWindow(true);
		m_DOWN.EnableWindow(true);
		m_Save.EnableWindow(true);
	}

}

///////////////////////////////////////////////////////////
//
//
//
//
//
//
//功能：电源开关按钮。控制硬件的上电/掉电功能。
//
//
/////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedSlmPwrButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	for(int board = 0; board < NumBoards; board++)    //监测硬件个数，并逐一进行上电/掉电操作。
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		bool bPowerOn = (bool)!pBoard->theBoard->GetPower();//获得硬件电源情况
		pBoard->theBoard->SetPower(bPowerOn);               //上电/掉电

		if(pBoard->theBoard->GetPower())
		{
				m_SlmPwrButton.SetWindowText(_T("OFF POWER"));
		    m_StartStopButton.EnableWindow(true);
			m_out.EnableWindow(false);
			m_UP.EnableWindow(false);
			m_DOWN.EnableWindow(false);
		}
		
		else
		{
			m_SlmPwrButton.SetWindowText(_T("ON POWER"));
		    m_StartStopButton.EnableWindow(false);
			m_out.EnableWindow(true);
			m_UP.EnableWindow(true);
			m_DOWN.EnableWindow(true);

		}
			
	}

}

void CBNS_APPDlg::OnBnClickedButtonGo()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(Down);
	if(m_frame==0)
		{
			MessageBox(_T("请选择帧率") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }
	if(m_speed==0)
		{
			MessageBox(_T("请选择风速") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }
	if(m_Width_m==0)
		{
			MessageBox(_T("请选择相位屏宽度") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }

	Pixel=(1/m_frame)*(POINT/m_Width_m)*m_speed;
	CString Stop_Up;
	m_UP.GetWindowText(Stop_Up);
	//设置一个CString变量，来获得开始/停止按钮的状态信息
	if (0==Stop_Up.Compare(_T("Go")))  
	{
		SetTimer(1,floor(1000.0/m_frame),NULL); //启动ID为1的定时器，定时器单位为 ms;
		m_UP.SetWindowText(_T("STOP"));
	}
	if (0==Stop_Up.Compare(_T("STOP")))  
	{
		KillTimer(1);
		m_UP.SetWindowText(_T("Go"));
	}

}
void CBNS_APPDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	//QueryPerformanceFrequency(&Frequence);//得到系统时钟频率
	//QueryPerformanceCounter(&M_Begin);//得到系统当前计数器值
	//QueryPerformanceCounter(&M_End);
	//m_frame=((M_End.QuadPart-M_Begin.QuadPart)*1.0)/(Frequence.QuadPart*1.0);//得到相位屏加载帧率。帧率的是计算公式为：帧率=系统频率/（计数差值）；
	// 
	Down_Up=1;
	Page_0=m_Now;
	Page_0++;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0>m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0>m_EDIT_BN)
	       {
		      Page_0=m_EDIT_EN;
	       }
	}
	Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	 m_Now=Page_0;
	 UpdateData(false);
	 m_Save.EnableWindow(true);
	
}

void CBNS_APPDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	Down_Up=0;
	Page_0=m_Now;
	Page_0--;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0<m_EDIT_BN)
	       {
		      Page_0=m_EDIT_EN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0<m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}

	 Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	 m_Now=Page_0;
	 UpdateData(false);
	 m_Save.EnableWindow(true);
}

void CBNS_APPDlg::OnBnClickedCompensatePhaseCheckbox()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

}
///////////////////////////////////////////////////////////////////
//
//函数名：ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512)
//
//函数参数：unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512 
//         
//
//函数功能：将一幅小于POINT（#define POINT 512）的相位屏转化为（说成粘贴可能更为恰当点）POINT的相位屏。
//
//
//函数返回值：无
//
//
//////////////////////////////////////////////////////////////////
void CBNS_APPDlg::ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512)
{   
	int i,j,s=0;
    for(i=(POINT-biWidth)/2; i<(POINT+biWidth)/2; i++)
      for( j=(POINT-biHeight)/2 ; j<(POINT+biHeight)/2 ; j++)

         ColorBuff_512[i*POINT+j]=ColorBuff1[s++];
}


//////////////////////////////////////////////////////////////////////////////////
//
//  LoadSequence()
//
//  Inputs: none
//
//  Returns: none
//
//  Purpose: This function will load a series of two images to the PCI board memory. The
//			 first image is written to the first frame of memory in the hardware, and the
//			 second image is written to the second frame of memory in the hardware. 
//
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
void  CBNS_APPDlg::LoadSequence(double *ColorBuff1)
{
	unsigned __int8  *ColorBuff2;
	ColorBuff2=new unsigned __int8[POINT*POINT];

	for(int j=0;j<POINT*POINT;j++)
	{
		ColorBuff2[j]=char(255*(ColorBuff1[j]/(2*PI)));
	}
	int i;

	//loop through each PCIe board found, read in the calibrations for that SLM
	//as well as the images in the sequence list, and store the merged image/calibration
	//data in an array that will later be referenced
	for(int board = 0; board < NumBoards; board++)
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		//if the user has a nematic SLM and the user is viewing the SLM through an interferometer,
		//then the user has the option to correct for SLM imperfections by applying a predetermined 
		//phase compensation. BNS calibrates every SLM before shipping, so every SLM ships with its own
		//custom phase correction file. This step is either reading in that correction file, or setting
		//the data in the array to 0 for users that don't want to correct or for users with amplitude
		//devices
		if(m_CompensatePhase)
		{
			ReadAndScaleBitmap(pBoard->PhaseCompensationData, pBoard->PhaseCompensationFileName);
			ReadAndScaleBitmap(pBoard->SystemPhaseCompensationData, pBoard->SystemPhaseCompensationFileName);
		}
		else
		{
			memset(pBoard->PhaseCompensationData, 0, ImgHeight*ImgWidth);
			memset(pBoard->SystemPhaseCompensationData, 0, ImgHeight*ImgWidth);
		}
        if(m_Width<ImgHeight)
		{

			ChangeTo512(ColorBuff2,ColorBuff_512);
			int total;
		//Superimpose the SLM phase compensation, the system phase compensation, and
		//the image data and then store the image in the FrameOne Array
		    for(i = 0; i< ImgHeight*ImgWidth; i++)
		      {
			        total = ColorBuff_512[i] + 
					pBoard->PhaseCompensationData[i] + 
					pBoard->SystemPhaseCompensationData[i];
			        ColorBuff_512[i] = total%256;
		      }
		    pBoard->theBoard->WriteFrameBuffer(ColorBuff_512);
		}
		else 
		{
			int total;
		//Superimpose the SLM phase compensation, the system phase compensation, and
		//the image data and then store the image in the FrameOne Array
		    for(i = 0; i< ImgHeight*ImgWidth; i++)
		     {
			        total = ColorBuff1[i] + 
					pBoard->PhaseCompensationData[i] + 
					pBoard->SystemPhaseCompensationData[i];
			        ColorBuff1[i] = total%256;
		     }
		    pBoard->theBoard->WriteFrameBuffer(ColorBuff2);

		}
		
		
	}
}


//////////////////////////////////////////////////////////////////////////////////
//
//  OnClose()
//
//  Inputs: none
//
//  Returns: none
//
//  Purpose: This function is used clean up everything at the close of the program.
//			 This function is called when the user clicks on the little X in the 
//			 upper corner of the screen. MAKE SURE THAT THE SLM POWER IS OFF 
//			 BEFORE LEAVING THE PROGRAM!!!
//			 
//
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::ToOnClose() 
{
	for(int board = 0; board < NumBoards; board++)
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		//first set the SLM power off, then deconstruct the board class
		pBoard->theBoard->SetPower(false);
		if (pBoard->theBoard)
			delete pBoard->theBoard;

		//clean up allocated memory to avoid memory leaks (this isn't technically necessary,
		//but it is good practice)
		delete []pBoard->PhaseCompensationData;
		delete []pBoard->SystemPhaseCompensationData;
		delete []pBoard->LUT;
		delete pBoard;
	}

	//close out the dialog
	//CDialog::OnClose();
}
//////////////////////////////////////////////////////////////////////////////////
//
//  OnOK()
//
//  Inputs: none
//
//  Returns: none
//
//  Purpose: This function is used so that you don't accidentally exit the program
//			 by hitting the enter button. This function now causes nothing to happen if enter
//			 is clicked. It forces the user to purposely exit the program using
//			 the exit button which will ensure that the proper shutdown procedure
//			 of the hardware is followed. This will prevent possible accidental damage
//			 to the hardware and or SLM
//			 
//
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnOK() 
{

}


//////////////////////////////////////////////////////////////////////////////////
//
//  ReadAndScaleBitmap()
//
//  Inputs: empty array to fill, the file name to read in
//
//  Returns: true if no errors, otherwise false
//
//  Purpose: This function will read in the bitmap and x axis flip it. If there is a 
//			 problem reading in the bitmap, then we fill the array with zeros. This 
//			 function then calls ScaleBitmap so that we can scale the 
//			 bitmap to an images size based on the board type.
//			 读取.BMP格式的图片信息
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
bool CBNS_APPDlg::ReadAndScaleBitmap(unsigned char *Image, CString fileName)      //得到图片的数据值
{
	int width, height, bytespixel;

	//need a tmpImage because we cannot assume that the bitmap we 
	//read in will be of the correct dimensions
	unsigned char* tmpImage;

	//get a handle to our file
	CFile *pFile = new CFile();
	if (pFile == NULL)
		MessageBox(_T("Error allocating memory for pFile,ReadandScaleBitmap"), _T("MEMORY ERROR"), MB_ICONERROR);
	//if it is a bmp file and we can open it
	if (pFile->Open(fileName, CFile::modeRead | CFile::shareDenyNone, NULL))
	{
		//read in the bitmap dimensions
		CDib dib;
		dib.Read(pFile);
		width = dib.GetDimensions().cx;
		height = dib.GetDimensions().cy;
		bytespixel = dib.m_lpBMIH->biBitCount;                  //色深值
		pFile->Close();
		delete pFile;
		
		//allocate our tmp array based on the bitmap dimensions
		tmpImage = new unsigned char[height*width];

		//flip the image right side up (INVERT)
		for (int i=0; i<height; i++)
		{
			for (int j=0; j<width; j++)
			{
				if (bytespixel == 4)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*(height/2)+(j/2)];
				if (bytespixel == 8)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*height+j];
				if (bytespixel == 16)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*2*height+j*2];
				if (bytespixel == 24)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*3*height+j*3];
			}
		}
 
		dib.~CDib();
	}
	//we could not open the file or the file was not a .bmp file
	else 
	{
		//depending on if we are trying to read a bitmap to download
		//or if we are trying to read it for the screen, memset
		//the array to zero and return false
		memset(Image, '0', ImgWidth*ImgHeight);
		return false;
	}

	//scale the bitmap
	unsigned char* ScaledImage = ScaleBitmap(tmpImage, height, ImgHeight);

	//copy the scaled bitmap into the array passed into the function
	memcpy(Image, ScaledImage, ImgWidth*ImgHeight);

	//delete our tmp array to avoid mem leaks
	delete []tmpImage;

	return true;
}
//////////////////////////////////////////////////////////////////////////////////
//
//  ScaleBitmap()
//
//  Inputs: none
//
//  Returns: the array that holds the image to scale, the current bitmap size, the final
//			 bitmap size
//
//  Purpose: This will scale the bitmap from whatever size it is initially to a 128x128
//			 if load is set to false. Otherwise the images is scaled to a 512x512 if 
//			 the board type is set to 512ASLM or 256x256 if the board type is set to
//			 256ASLM.
//           将图片信息进行拉伸或者压缩
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
unsigned char * CBNS_APPDlg::ScaleBitmap(unsigned char* InvertedImage, int BitmapSize, int FinalBitmapSize)
{	
	int height = BitmapSize;
	int width = BitmapSize;

	//make an array to hold the scaled bitmap
	unsigned char* ScaledImage = new unsigned char[FinalBitmapSize*FinalBitmapSize];
	if (ScaledImage == NULL)
		AfxMessageBox(_T("Error allocating memory for CFile,LoadSIFRec"), MB_OK);
	//EXPAND THE IMAGE to FinalBitmapSize
	if (height < FinalBitmapSize)
	{
		int r, c, row, col, Index;
		int Scale = FinalBitmapSize/height;

		for (row = 0; row < height; row++)
		{
			for (col = 0; col < width; col++)
			{
				for (r = 0; r < Scale; r++)
				{
					for(c = 0; c < Scale; c++)
					{
						Index = ((row*Scale)+r)*FinalBitmapSize + (col*Scale)+c;
						ScaledImage[Index] = InvertedImage[row*height+col];
					}
				}
			}
		}
	}
	//SHRINK IT DOWN
	else if (height > FinalBitmapSize)
	{
		int Scale = height/FinalBitmapSize;
		for (int i = 0; i<height; i+=Scale)
			for (int j=0; j<width; j+=Scale)
				ScaledImage[(i/Scale)+FinalBitmapSize*(j/Scale)] = InvertedImage[i+height*j];
	}
	//if the image is the correct size already, just copy the array over
	else
		memcpy(ScaledImage, InvertedImage, FinalBitmapSize*FinalBitmapSize);
	
	return(ScaledImage);

}

//////////////////////////////////////////////////////////////////////////////////
//
//  ReadLUTFile()
//
//  Inputs: the name of the LUT file to read, and an array to store the file in
//
//  Returns: true if read successfully, false if linear.lut was generated
//
//  Purpose: This will read in the LUT file. This is a look up table that we process 
//			 our images through. What it does is map the pixel values to the values
//			 specified by the LUT. For example with Linear.LUT we have a direct 
//			 mapping, so if the pixel value is 255, Linear.LUT will keep it at 255.
//			 However, skew.LUT will alter the pixel values. With skew.LUT if the 
//			 initial pixel value is 60, then it is mapped to a value of 139. 
//           读取查阅表文件
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
bool CBNS_APPDlg::ReadLUTFile( unsigned char *LUTBuf, CString LUTPath)
{
	FILE *stream;
	int i, seqnum, ReturnVal, tmpLUT;
	bool errorFlag;

	//set the error flag to indicate that there are no errors so far, and open
	//the LUT file
	errorFlag=false;
	stream = fopen("LUTPath","r");
	if ((stream != NULL)&&(errorFlag == false))
	{
		//read in all 256 values
		for (i=0; i<256; i++)
		{
		   ReturnVal=fscanf(stream, "%d %d", &seqnum, &tmpLUT); 
		   if (ReturnVal!=2 || seqnum!=i || tmpLUT<0 || tmpLUT>255)
		   {
			   	fclose(stream);
				errorFlag=true;
				break;
		   }
		   LUTBuf[i] = (unsigned char) tmpLUT;
		}
		fclose(stream);
	}
	//if there was an error reading in the LUT, then default to a linear LUT
	if ((stream == NULL)||(errorFlag == true))                    
	{
		for (i=0; i<256; i++)
			LUTBuf[i]=i;
		return false;
	}

	return TRUE;
}

////////////////////////////////////////////////////
//
//函数名：My_Delay(LARGE_INTEGER Interval)
//
//函数参数：LARGE_INTEGER Interval
//
//函数功能：实现微秒级别的定时
//
//函数返回值：无
//
/////////////////////////////////////////////////////////
void CBNS_APPDlg::My_Delay(LARGE_INTEGER Interval)
{
    LARGE_INTEGER pricious, current;                      
	QueryPerformanceCounter(&pricious);
	current = pricious;
	while(current.QuadPart -pricious.QuadPart < Interval.QuadPart)
		QueryPerformanceCounter(&current);
}
///////////////////////////////////////
//
//函数名：
//
//函数参数：
//
//函数功能：将相位屏数据加载到硬件上的步骤打包起来，实现程序的明了性
//
//函数返回值：无
//
///////////////////////////////////////////////////
void CBNS_APPDlg::LoadHardBoard()
{
    if(Page_0==Page_end)
	{
		LoadSequence(ColorBuff+Page_0*512);
		Page_0=m_EDIT_BN;
	}
	else
	{
		LoadSequence(ColorBuff+Page_0*512);
		Page_0+=Pixel;
	}
	m_Now=Page_0;
	UpdateData(false);

}
////////////////////////////////////////
//
//函数名：OnTimer(UINT_PTR nIDEvent)
//
//函数参数：消息
//
//函数功能：实现毫秒级别的定时，以消息形式触发定时器函数，执行相应程序
//
//函数返回值：无
//
//
/////////////////////////////////////////////////
//void CBNS_APPDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	UpdateData(TRUE);
//	if(m_EDIT_BN==m_EDIT_EN)
//	{
//		Display_Picture(ColorBuff[Page_0]);
//		LoadSequence(ColorBuff[Page_0]);
//		KillTimer(1);
//	}
//	if(m_EDIT_BN>m_EDIT_EN)//逆序显示
//	{
//		if(Page_0==Page_end)
//		{
//			Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//			Page_0=m_EDIT_BN;
//		}
//		else
//		{
//		    Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//		    Page_0--;
//		}
//
//	}
//	if(m_EDIT_BN<m_EDIT_EN)
//	{
//		if(Page_0==Page_end)
//		{
//			Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//			Page_0=m_EDIT_BN;
//		}
//		else
//		{
//		    Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//		    Page_0++;
//		}
//	}
//
//	m_Now=Page_0;
//	UpdateData(false);
//	//CDialogEx::OnTimer(nIDEvent);
//}
///////////////////////////////////////////////////////////////////////////
//
//函数名：Display_Picture(unsigned __int8 *ColorBuff1)
//
//函数参数：unsigned __int8 *ColorBuff1
//
//函数返回值：无
//
//
//函数功能：实现读取图像数据的显示
//
//
/////////////////////////////////////////////////////////////////////////////
void  CBNS_APPDlg::Display_Picture(double *ColorBuff1)
{
	unsigned __int8  *ColorBuff2;
	ColorBuff2=new unsigned __int8[POINT*POINT];

	for(int j=0;j<POINT*POINT;j++)
	{
		ColorBuff2[j]=char(255*(ColorBuff1[j]/(2*PI)));
	}
	CRect picture;
	CDC *pDC;
	m_Picture.GetClientRect(&picture);
	pDC=m_Picture.GetDC();
	 /*if((int(m_Width*m_Rr))<POINT)
		{
			ChangeTo512(ColorBuff2,ColorBuff_512);
			SetDIBitsToDevice(pDC->m_hDC, 0, 0, 512, 512, 0,0, 0, 512, ColorBuff_512, (BITMAPINFO *)INFO, 0);
	    }
	 else*/
    SetDIBitsToDevice(pDC->m_hDC, 0, 0, 512, 512, 0,0, 0, 512, ColorBuff2, (BITMAPINFO *)INFO, 0);
	delete []ColorBuff2;
}

void CBNS_APPDlg::OnBnClickedButtonYushezhi()
{
	// TODO: 在此添加控件通知处理程序代码
	CString SPV;
	m_Prepare_value.GetWindowText(SPV);
	if(0==SPV.Compare(_T("预设值")))
	{
		m_L0=10;
	    m_i0=0.01;
	    m_r0=0.1;
	    m_Width_m=2;
	    m_Len_m=20;
		m_speed=5;
		m_frame=100;
		m_T=2;
	    UpdateData(false);
	    m_Prepare_value.SetWindowText(_T("确定"));
	}
	if(0==SPV.Compare(_T("确定")))
	{
		UpdateData(true);
		m_Prepare_value.SetWindowText(_T("预设值"));
	}


}

/***************************************************/
//
//函数名：integral(double(CNUFFTDlg:: *fun)(double), double a, double b)
//
//输入参数：CNUFFTDlg:: *fun)(double), double a, double b （函数入口和积分区间）
//
//输出： 积分结果（double类型）
//
//函数说明：积分函数，实现联系函数在一个区间（明显区间两端的点对积分结果无影响）上的积分
//
//
/******************************************************/
double CBNS_APPDlg::integral(double(CBNS_APPDlg::*fun)(double), double a, double b)      //求fun在a，b区间定积分
{
	double s, h;
	int i;
	s = ((this->*fun)(a)+(this->*fun)(b)) / 2.0;
	int N = 1000;
	h = (b - a) / N;
	for (i = 1; i<N; i++)
		s += (this->*fun)(a + i*h);
	return(s*h);
}
/**************************************************************/
//
//函数名：psdevalfunKolspf(double x)
//
//输入参数：double x （函数自变量）
//
//输出：double类型的函数因变量
//
//函数功能：函数实现
//
/****************************************************************/
double CBNS_APPDlg::psdevalfunKolspf(double x)
{
	double Kolspf;
	//double r0 = 0.1;
	Kolspf = pow(0.023*pow(m_r0, (-5.0 / 3))*pow(x, (-11.0 / 3)), 0.5);
	return Kolspf;
}
/***************************************************************/
//
//
//
//
//
//
//
//
//
//
/****************************************************************/
long double CBNS_APPDlg::psdevalfun(double f0, double f1, double f2, int samppoints)
{

	double theoryresult = integral(&CBNS_APPDlg::psdevalfunKolspf, f0, f2);
	double discreresult = psdevalfunKolspf(f1)*(f2 - f0);
	double psderror = abs((theoryresult - discreresult)) / (samppoints / f1);
	return psderror;
}
void CBNS_APPDlg::OnBnClickedButtonKaishi()
{
	// TODO: 在此添加控件通知处理程序代码
	////---------------------注释说明：---------------------/////
	//    
	//              本程序注释位子右侧、上侧                /////
	//
	//         右侧注释以“//”开始，字体颜色为蓝色         /////
	//
	//                                 “////////////////////// 
	//     上侧注释以“//--..--//”或则  //
    //                                   :  注释内容...
	//
	//                                   //////////////////////
	//
	//
	UpdateData(Down);
	if(m_L0==0||m_i0==0||m_r0==0||m_Len_m==0||m_Width_m==0||m_speed==0||m_frame==0)//如果没有进行参数设置，这返回该程序，直到参数设置完成
	{
		MessageBox(_T("请初始化参数") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}
	file_head.m_L0=m_L0;
	file_head.m_i0=m_i0;
	file_head.m_r0=m_r0;
	file_head.m_speed=m_speed;
	file_head.m_frame=m_frame;
	file_head.m_Width_m=m_Width_m;
	file_head.m_Len_m=m_Len_m;
	file_head.m_T=m_T;

	m_r0=m_r0/2.25;     //修正r0

	Mosaic_Pixel=Mosaic;
	m_Len=int(m_Len_m*m_Rr);        //将相位屏的长物理尺度（单位 米）变换到像素尺度（单位 pixel）
	m_Width=int(m_Width_m*m_Rr);    //将相位屏的宽物理尺度（单位 米）变换到像素尺度（单位 pixel）
	double Efc_S=floor(m_Len/((1/m_frame)*(POINT/m_Width_m)*m_speed));  //根据风速和帧率计算得到 一副长相位屏有效的屏数
	T_Len= int(ceil(m_T*60/((1/m_frame)*Efc_S)));                       //生成需要长的相位屏而需要进行拼接的原始相位屏个数
	m_Progress.SetRange32(0,T_Len+2);
	m_Progress.SetPos(0);
	m_Progress.SetStep(1); 
	m_fm=1000;
	double f,f0=1/(1000*m_L0),totalpoints;
	double  step, f1, f2,f10,f20;
	f = f0;
	step = 0.001;//步长
	f2 = (1 + step)*f;
	f1 = 0.618*f2 + 0.382*f;
	double samplistx[1000] = { 0.0 };//X方向的样本点
	double samplisty[1000] = { 0.0 };//Y方向的样本点

	totalpoints = m_Len;
	int i = 0, k = 0;
	m_errorboundd=0.5/m_Len;
	m_errorboundu=1/m_Len;
	if((1/m_Len)<0.0002)
	{
		m_errorboundd=0.0001;
		m_errorboundu=0.0002;
	}
	/**************************************/
	//
	//X方向采样
	//
	/*************************************/
	while (f < m_fm)
	{    
		if (psdevalfun(f, f1, f2, totalpoints)<m_errorboundd)
		{
			f2 = f2*(1 + step);
			f1 = 0.618*f2 + 0.382*f;;
		}
		else if (psdevalfun(f, f1, f2, totalpoints)>m_errorboundu)
		{
			f2 = f2 / (1 + step*0.01);
			f1 = 0.618*f2 + 0.382*f;
		}
		else if ((psdevalfun(f, f1, f2, totalpoints)<m_errorboundu) && (psdevalfun(f, f1, f2, totalpoints)>m_errorboundd))
		{
			f10 = f + 0.382*(f2 - f);
			f20 = f + 0.618*(f2 - f);
			for (int k = 0; k < 10; k++)
			{
				if (psdevalfun(f, f10, f2, totalpoints) < psdevalfun(f, f20, f2, totalpoints))
				{
					f20 = f + 0.618*(f2 - f10);
				}
				else
					f10 = f + 0.382*(f20 - f);
			}
			samplistx[i] = f10 + 0.618*(f20 - f10);
			i = i + 1;
			f = f10 + 0.618*(f20 - f10);
			f2 = f2*(1 + step);
			f1 = 0.618*f2 + 0.382*f;
		}
	}
	double *samplist_x;
	 samplist_x = new double [i+1];
	int com_x=0;
	samplist_x[0] = 0.0;
	for (int j = 0; j <i; j++)
	{
		if (samplistx[j] != 0)

		{
			com_x++;
			samplist_x[com_x] = samplistx[j];

		}
	}
	totalpoints = m_Width;
	step = 0.001;
	f = f0;
	f2 = (1 + step)*f;
	f1 = 0.618*f2 + 0.382*f;
	i = 0;
	k = 0;
	/**************************************/
	//
	//Y方向采样
	//
	/*************************************/
	while (f<m_fm)
	{
		if (psdevalfun(f, f1, f2, totalpoints) < m_errorboundd)
		{
			f2 = f2*(1 + step);
			f1 = 0.618*f2 + 0.382*f;

		}	
		else if (psdevalfun(f, f1, f2, totalpoints) > m_errorboundu)
		{
			f2 = f2 / (1 + step*0.1);
			f1 = 0.618*f2 + 0.382*f;
		}
		else if ( (psdevalfun(f, f1, f2, totalpoints) < m_errorboundu) && (psdevalfun(f, f1, f2, totalpoints) > m_errorboundd) )
		{
			f10 = f + 0.382*(f2 - f);
			f20 = f + 0.618*(f2 - f);
			for (k = 0; k < 10; k++)
			{
				if (psdevalfun(f, f10, f2, totalpoints)<psdevalfun(f, f20, f2, totalpoints))
					f20 = f + 0.618*(f2 - f10);
				else
					f10 = f + 0.382*(f20 - f);
			}
		samplisty[i] = f10 + 0.618*(f20 - f10);
		i = i + 1;
		f = f10 + 0.618*(f20 - f10);
		f2 = f2*(1 + step);
		f1 = 0.618*f2 + 0.382*f;
		}
	}
	double *samplist_y;
	samplist_y = new double[i+1];
	int com_y = 0;
	samplist_y[0] = 0.0;
	for (int j = 0; j <i; j++)
	{

		if (samplisty[j] != 0)
		{
			com_y++;
			samplist_y[com_y] = samplisty[j];
		}

	}
	double **f_area;
	f_area = new double *[com_x + 1];
	for (int i = 0; i < com_x + 1; i++)
	{
		f_area[i] = new double[com_y + 1];
	}
	Norseque2(samplist_x, com_x, samplist_y, com_y, f_area);

	double *sequex;
	sequex = new double[com_x+1];
	for (int i = 0; i < com_x+1; i++)
	{
		sequex[i] = samplist_x[i];
	}
	delete []samplist_x; //删除不再使用的中间动态数组samplist_x

	double *sequey;
	sequey = new double[com_y+1];
	for (int i = 0; i < com_y+1; i++)
	{
		sequey[i] = samplist_y[i];
	}
	delete []samplist_y;  //删除不再使用的中间动态数组samplist_y

	
	double *kax_dbside;
	kax_dbside = new double[2 * com_x + 1];
	for (int i = 0; i < com_x; i++)
	{
		kax_dbside[i] = -1*sequex[com_x - i];

	}
	for (int i = com_x; i < 2 * com_x + 1; i++)
	{
		kax_dbside[i] = sequex[i-com_x];
	}

	double *kay_dbside;
	kay_dbside = new double[2 * com_y + 1];
	for (int i = 0; i < com_y; i++)
	{
		kay_dbside[i] = -1*sequey[com_y - i];

	}
	for (int i = com_y; i < 2 * com_y + 1; i++)
	{
		kay_dbside[i] = sequey[i - com_y];
	}
	m_Progress.StepIt();//进度条+1
	double **PSD_sample;
	PSD_sample = new double *[com_x + 1];
	for (int i = 0; i < com_x+1; i++)
	{
		PSD_sample[i] = new double[com_y + 1];
	}
	for (int i = 0; i < com_x + 1; i++)
		for (int j = 0; j < com_y + 1; j++)
		{
			if (i == 0 && j == 0)
			{
				PSD_sample[i][j] = 0.0;
			}
			else
			{
				PSD_sample[i][j] = 0.490*(pow(m_r0, -(5.0 / 3.0)))*pow((pow(sequex[i],2.0)+pow(sequey[j],2.0)),-(11.0/6.0));
			}
		}
	double **Spectrum_temp1;
	Spectrum_temp1 = new double *[com_x + 1];
	for (int i = 0; i < com_x + 1; i++)
	{
		Spectrum_temp1[i] = new double[com_y + 1];
	}
	for (int i = 0; i < com_x + 1; i++)
		for (int j = 0; j < com_y + 1; j++)
		{
			Spectrum_temp1[i][j] = sqrt(PSD_sample[i][j]*f_area[i][j]);
		}
	double **Spectrum1;//将Spectrum_temp1[][]进行一个块翻转 【A B    转化为【D C
	                   //                                     C D】          B A】

	Spectrum1 = new double*[2 * com_x + 1];
	for (int i = 0; i < 2 * com_x + 1; i++)
	{
		Spectrum1[i] = new double[2 * com_y + 1];
	}
	for (int i = 0; i<2 * com_x + 1; i++)
		for (int j = 0; j<2 * com_y + 1; j++)
		{
			Spectrum1[i][j] = 0.0;//初始化为0.0
		}
	for (int i = 0; i < com_x + 1; i++)
		for (int j = 0; j < com_y + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[com_x - i][com_y - j];
		}
	for (int i = 0; i < com_x; i++)
		for (int j = com_y + 1; j < 2 * com_y + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[com_x - i][j - com_y];
		}
	for (int i = com_x + 1; i < 2 * com_x + 1; i++)
		for (int j = 0; j < com_y + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[i - com_x][com_y - j];
		}
	for (int i = com_x; i < 2 * com_x + 1; i++)
		for (int j = com_y; j < 2 * com_y + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[i - com_x][j - com_y];
		}
	for (int i = 0; i < com_x + 1; i++)  //删除中间不再使用的变量数组
	{
		delete[]Spectrum_temp1[i];
	}
	delete[]Spectrum_temp1;

	m_Progress.StepIt();//进度条+1

	A_P = new double*[m_Width];    //为A_P申请动态数组，A_P是用来存放生成的相位屏数据的指针
	for (int i = 0; i<m_Width; i++)
	{
		A_P[i] = new double[m_Len];
	}
	double **End_AP;
	End_AP = new double*[POINT];
	for (int i = 0; i<POINT; i++)
	{
		End_AP[i] = new double[Mosaic_Pixel];
	}

	double *C_end;
	C_end=new double[Mosaic_Pixel];
	for(int k=0;k<Mosaic_Pixel;k++)
	{
		C_end[k]=pow(cos(PI*k/(2.0*Mosaic_Pixel)),2.0);//相位屏末尾拼接系数函数
	}
	double *C_Bg;
	C_Bg=new double[Mosaic_Pixel];
	for(int k=0;k<Mosaic_Pixel;k++)
	{
		C_Bg[k]=pow(sin(PI*k/(2.0*Mosaic_Pixel)),2.0);//相位屏开头拼接系数函数
	}
	Create_File();
	//save_headata();
	/**************************************/
	//
	//下面的for循环实现了相位屏的生成和拼接
	//
	/*************************************/
	Nufft(Spectrum1,kax_dbside, com_x, kay_dbside,com_y);
	for (int i = m_Len-Mosaic_Pixel; i<m_Len; i++)
	   for (int j = 0; j<POINT; j++)
		 {
			End_AP[j][i-(m_Len-Mosaic_Pixel)]=A_P[j][i];
		 }
	save_data(A_P);	
    m_Progress.StepIt();//进度条+1
	for(int kkk=1;kkk<T_Len-1;kkk++)
	{
	  Nufft(Spectrum1,kax_dbside, com_x, kay_dbside,com_y);
		for(int i=0;i<POINT;i++)
		 for(int j=0;j<Mosaic_Pixel;j++)
		    {
			 A_P[i][j]=A_P[i][j]*C_Bg[j]+End_AP[i][j]*C_end[j];
			}
		for (int i = m_Len-Mosaic_Pixel; i<m_Len; i++)
		  for (int j = 0; j<POINT; j++)
		     {
			   End_AP[j][i-(m_Len-Mosaic_Pixel)]=A_P[j][i];
		     }
	 save_data(A_P);
	 m_Progress.StepIt();//进度条+1
	}
	Nufft(Spectrum1,kax_dbside, com_x, kay_dbside,com_y);
	for(int i=0;i<POINT;i++)
	 for(int j=0;j<Mosaic_Pixel;j++)
		{
			A_P[i][j]=A_P[i][j]*C_Bg[j]+End_AP[i][j]*C_end[j];
	    }
	 Mosaic_Pixel=0;
	 save_data(A_P);


	//Mosaic_Pixel=0;
	//for(int s=0;s<50;s++)
	//{
	//	Nufft(Spectrum1,kax_dbside, com_x, kay_dbside,com_y);
	//	m_Progress.StepIt();//进度条+1
	//	save_data(A_P);	
	//}
	
	m_Progress.StepIt();//进度条+1
	MessageBox(_T("数据生成完毕,已保存...") ,MB_OK,MB_ICONASTERISK);
	  m_Prepare_value.EnableWindow(true);
	  m_Open.EnableWindow(true);

//	m_Prepare_value.EnableWindow(false);
//	m_Open.EnableWindow(false);
//	m_progress.SetRange32(0,m_N*3+m_Zn*8);
//	m_progress.SetPos(0);
//	m_progress.SetStep(1); 
//	m_progress_file.SetRange32(0,m_N);
//	m_progress_file.SetPos(0);
//	m_progress_file.SetStep(1);		
//  m_progress.StepIt();     ////--N:0 Zn:1---///
//	progress.SetPos(m_N*3+m_Zn*8);
	  


}
/****************************************************************/
//
//
//
//
//
//
//
//
//
//
/*******************************************************************/
void CBNS_APPDlg::Nufft(double **Spectrum1,double *kax_dbside, int com_x, double *kay_dbside, int com_y)

{
	double_complex **Rand_Spect1;
	Rand_Spect1 = new double_complex*[2 * com_x + 1];
	for (int i = 0; i < 2 * com_x + 1; i++)
	{
		Rand_Spect1[i] = new double_complex[2 * com_y + 1];
	}
	for (int i = 0; i < 2 * com_x + 1; i++)
		for (int j = 0; j < 2 * com_y + 1; j++)
		{
			Rand_Spect1[i][j].real = Spectrum1[i][j] * randn();
			Rand_Spect1[i][j].imag = Spectrum1[i][j] * randn();
		}
	double_complex **Nuphz;
	Nuphz = new double_complex*[m_Width];
	for(int i = 0; i < m_Width; i++)
	{
		Nuphz[i] = new double_complex [m_Len];
	}

	int   Desired_accuracy;
	Desired_accuracy = 12;
	FGG_2d_type1(Rand_Spect1, Nuphz, kax_dbside, com_x, kay_dbside, com_y, m_Width, m_Len, Desired_accuracy);
	double **Nuphz_1;
	Nuphz_1 = new double*[m_Width];
	for (int i = 0; i < m_Width; i++)
	{
		Nuphz_1[i] = new double[m_Len];
	}
	double min,max,sum;
	long double long_sum=0.0;
	min = sqrt(pow(Nuphz[0][0].real, 2) + pow(Nuphz[0][0].imag, 2));
	sum=min;
	max = sqrt(pow(Nuphz[0][0].real, 2) + pow(Nuphz[0][0].imag, 2));
	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			Nuphz_1[i][j] = sqrt(pow(Nuphz[i][j].real, 2)+pow(Nuphz[i][j].imag,2));
			long_sum=long_sum+Nuphz_1[i][j];
			if (Nuphz_1[i][j] < min)
			{
				min = Nuphz_1[i][j];
			}
			if (Nuphz_1[i][j] > max)
			{
				max = Nuphz_1[i][j];
			}
		}
	sum=double(long_sum/(m_Width*m_Len));
	double kk=pow(6.88*(pow(m_Width_m/m_r0,5.0/3.0)),0.5);
	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			A_P[i][j] =Mod_double(kk*((Nuphz_1[i][j]-min)/(max-min)),2*PI);// kk*(Nuphz_1[i][j]-min)/(max-min);
		}
}

/**************************************************************/
//
//
//
//
//
//
//
//
/***************************************************************/
void CBNS_APPDlg::Norseque2(double *sequencex, int com_x, double *sequencey, int com_y, double **f_area)
{
	double *f_fixx;
	f_fixx = new  double[com_x + 3];
	for (int i = 0; i < com_x + 1; i++)
	{
		f_fixx[i] = sequencex[i];
	}
	f_fixx[com_x + 1] = sequencex[com_x] + 10;
	f_fixx[com_x + 2] = sequencex[com_x] + 50;
	double *f_fixy;
	f_fixy = new  double[com_y + 3];
	for (int i = 0; i < com_y + 1; i++)
	{
		f_fixy[i] = sequencey[i];
	}
	f_fixy[com_y + 1] = sequencey[com_y] + 10;
	f_fixy[com_y + 2] = sequencey[com_y] + 50;
	for (int loop_x = 0; loop_x < com_x + 1; loop_x++)
		for (int loop_y = 0; loop_y < com_y + 1; loop_y++)
		{
			if (loop_x == 0 || loop_y == 0 || loop_x == com_x || loop_y == com_y)
			{
				f_area[loop_x][loop_y] = 0.0;
			}
			else
			{
				f_area[loop_x][loop_y] = (f_fixx[loop_x - 1] - f_fixx[loop_x + 1])*(f_fixy[loop_y - 1] - f_fixy[loop_y + 1]) / 4;
			}
		}

	//-----什么意义？--//
	/*for (int i = 0; i < com_y;i++)
	{
	f_area[0][i] = 4 * f_area[0][i];
	}
	for (int i = 1; i < com_x; i++)
	{
	f_area[i][0] = 4 * f_area[i][0];
	}*/

}
/*************************************************************/
//
//函数名:double CNUFFTDlg::Min(double *ka_dbside, int point)
//
//输入参数:double *ka_dbside, int point (一维数组,数组长度)
//
//输出参数: double类型,一维数组的最小值
//
//函数功能:找出一维数组的最小值
//
/****************************************************************/
double CBNS_APPDlg::Min(double *ka_dbside, int point)
{
	double min;
	min = ka_dbside[0];
	for (int i = 0; i < point; i++)
	{
		if (ka_dbside[i] < min)
		{
			min = ka_dbside[i];
		}
	}
	return min;
}
/*************************************************************/
//
//函数名:double CNUFFTDlg::Max(double *ka_dbside, int point)
//
//输入参数:double *ka_dbside, int point (一维数组,数组长度)
//
//输出参数: double类型,一维数组的最大值
//
//函数功能:找出一维数组的最大值
//
/****************************************************************/
double CBNS_APPDlg::Max(double *ka_dbside, int point)
{
	double max;
	max = ka_dbside[0];
	for (int i = 0; i < point; i++)
	{
		if (ka_dbside[i]>max)
		{
			max = ka_dbside[i];
		}
	}
	return max;
}
/*************************************************************/
//
//函数名:double CNUFFTDlg::Mod_double(double dividend, double divisor)
//
//输入参数:double dividend, double divisor (被除数，除数)
//
//输出参数: double类型,被除数除以除数剩下的模
//
//函数功能:求一个数对另一个数的模值（除数和被除数可以使负数）
//
/****************************************************************/
double CBNS_APPDlg::Mod_double(double dividend, double divisor)
{
	double sum, Decimals, mod_sum;

	double integer;
	sum = dividend / divisor;
	integer = floor(sum);
	Decimals = sum - integer;
	mod_sum = Decimals*divisor;
	return mod_sum;
}
float CBNS_APPDlg::Mod_float(float dividend, double divisor)
{
	float sum, Decimals, mod_sum;

	float integer;
	sum = dividend / divisor;
	integer = floor(sum);
	Decimals = sum - integer;
	mod_sum = Decimals*divisor;
	return mod_sum;
}
/*************************************************************/
//
//函数名:void fftshift（）；
//
//输入参数：double_complex **matrix_old, double_complex **matrix_new, int row, int column
//
//输出参数：无
//
//函数功能：实现对一个二维矩阵的 快（快是原矩阵的一部分） 转换
//
/*********************************************************************/
void CBNS_APPDlg::fftshift(double_complex **matrix_old, double_complex **matrix_new, int row, int column)
{
	for (int i = 0; i < row; i++)                 //for循环为将相位结构函数进行转化
	{
		for (int j = 0; j<column; j++)
		{
			if ((i <= (row / 2 - 1)) && (j <= (column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i + row / 2][j + column / 2];
			if ((i <= (row / 2 - 1)) && (j>(column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i + row / 2][j - column / 2];
			if ((i >(row / 2 - 1)) && (j <= (column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i - row / 2][j + column / 2];
			if ((i > (row / 2 - 1)) && (j > (column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i - row / 2][j - column / 2];
		}
	}
}
//*******************************************//
//
//
//函数名：randn（）
//
//输入参数：无
//
//输出参数：随机数
//
//函数功能：生成满足标准正太分布的随机数
//
//*******************************************//
double CBNS_APPDlg::randn()
{
	double u1 = double(rand() % 1024) / 1024.0, u2 = double(rand() % 1024) / 1024.0, r;
	while (u1 == 0)
	{
		u1 = double(rand() % 1024) / 1024.0;
	}
	r = sqrt(-2.0*(log(u1) / log(e)))*cos(2 * PI*u2);
	return r;
}
/********************************************************////
//
//
//功能：获得一个由系统时间来决定的字符串
//
//
//*******************************************************////
CString CBNS_APPDlg::rands()
{
	CString R_string;
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	R_string = m_time.Format(_T("%Y-%m-%d-%H_%M_%S"));
	return R_string;

}

void CBNS_APPDlg::FGG_2d_type1 (double_complex **Rand_Spect1, 

	                             double_complex **Nuphz, double *kax_dbside,

	                             int com_x, double *kay_dbside, int com_y,
								
								 int Nx, int Ny, int Desired_accuracy)

{
	long M;
	M = (2 * com_x + 1) * (2 * com_y + 1);
	int R = 2;
	int M_sp = Desired_accuracy;
	double_xy tau, scale, shift;
	int_xy  M_r;
	tau.x = PI * M_sp / (Nx*Nx*R*(R - 0.5));
	tau.y = PI * M_sp / (Ny*Ny*R*(R - 0.5));
	M_r.x = R * Nx;
	M_r.y = R * Ny;
	double_xy kmin, kmax, bw;
	kmin.x = Min(kax_dbside, 2 * com_x + 1);
	kmin.y = Min(kay_dbside, 2 * com_y + 1);
	kmax.x = Max(kax_dbside, 2 * com_x + 1);
	kmax.y = Max(kay_dbside, 2 * com_y + 1);
	bw.x = kmax.x - kmin.x;
	bw.y = kmax.y - kmin.y;
	scale.x = (Nx - 1) / bw.x;
	scale.y = (Ny - 1) / bw.y;
	shift.x = (-Nx / 2) - (kmin.x * scale.x);
	shift.y = (-Ny / 2) - (kmin.y * scale.y);

	double **knots;
	knots = new double *[M];
	for (int i = 0; i < M; i++)
	{
		knots[i] = new double[2];
	}

	for (int i = 0; i < M; i++)
	{
		knots[i][0] = 2 * PI*(scale.x * kax_dbside[i % (2 * com_x + 1)] + shift.x) / Nx;
		knots[i][1] = 2 * PI*(scale.y * kay_dbside[i / (2 * com_x + 1)] + shift.y) / Ny;
	}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < 2; j++)
		{
			knots[i][j] = Mod_double(knots[i][j], 2 * PI);
		}

	double *E_3x;
	E_3x = new double[M_sp];
	for (int i = 0; i < M_sp; i++)
	{
		E_3x[i] = exp(-(pow(PI* (i + 1) / M_r.x, 2)) / tau.x);
	}
	double *E_3X;
	E_3X = new double[2 * M_sp];
	for (int i = 0; i < 2 * M_sp; i++)
	{
		if (i >= M_sp)
		{
			E_3X[i] = E_3x[i - M_sp];
		}
		else if (i<M_sp - 1)
		{
			E_3X[i] = E_3x[M_sp - 2 - i];
		}
		else
		{
			E_3X[i] = 1.0;
		}
	}
	delete[]E_3x;

	double *E_3y;
	E_3y = new double[M_sp];
	for (int i = 0; i < M_sp; i++)
	{
		E_3y[i] = exp(-(pow(PI* (i + 1) / M_r.y, 2)) / tau.y);
	}
	double *E_3Y;
	E_3Y = new double[2 * M_sp];
	for (int i = 0; i < 2 * M_sp; i++)
	{
		if (i >= M_sp)
		{
			E_3Y[i] = E_3y[i - M_sp];
		}
		else if (i<M_sp - 1)
		{
			E_3Y[i] = E_3y[M_sp - 2 - i];
		}
		else
		{
			E_3Y[i] = 1.0;
		}
	}
	delete[]E_3y;

	int  * kx_vec;
	kx_vec = new int[Nx];
	for (int i = 0; i<Nx; i++)
	{
		kx_vec[i] = -(Nx / 2) + i;
	}
	double *E_4X;
	E_4X = new double[Nx];
	for (int i = 0; i < Nx; i++)
	{
		E_4X[i] = sqrt(PI / tau.x) * exp(tau.x * pow(kx_vec[i], 2.0));
	}

	int  * ky_vec;
	ky_vec = new int[Ny];
	for (int i = 0; i<Ny; i++)
	{
		ky_vec[i] = -(Ny / 2) + i;
	}
	double *E_4Y;
	E_4Y = new double[Ny];
	for (int i = 0; i < Ny; i++)
	{
		E_4Y[i] = sqrt(PI / tau.y) * exp(tau.y * pow(ky_vec[i], 2.0));
	}
	double_complex **f_tau;
	f_tau = new double_complex *[M_r.x];
	for (int i = 0; i < M_r.x; i++)
	{
		f_tau[i] = new double_complex[M_r.y];
	}
	for (int i = 0; i < M_r.x; i++)
		for (int j = 0; j < M_r.y; j++)
		{
			f_tau[i][j].real = 0.0;
			f_tau[i][j].imag = 0.0;
		}
	double  *f_taui;
	f_taui = new double[M_r.x*M_r.y];
	double *f_taur;
	f_taur = new double[M_r.x*M_r.y];
	for (int m = 0; m<M_r.x*M_r.y; m++)
	{
		f_taui[m] = 0.0;
		f_taur[m] = 0.0;
	}
	FGG_Convolution2D(f_taui, f_taur, Rand_Spect1, com_x, com_y, knots, E_3X, E_3Y, M_sp, tau, M_r);
	for (int i = 0; i < M_r.y; i++)
		for (int j = 0; j < M_r.x; j++)
		{
			f_tau[j][i].real = f_taur[i*M_r.x + j];
			f_tau[j][i].imag = f_taui[i*M_r.x + j];

		}
	double_complex **f_tau_new;
	f_tau_new = new double_complex *[M_r.x];
	for (int i = 0; i<M_r.x; i++)
	{
		f_tau_new[i] = new double_complex[M_r.y];
	}

	fftw_complex * In = (fftw_complex  *)fftw_malloc(sizeof(fftw_complex)*M_r.x * M_r.y );
	fftw_complex * out = (fftw_complex  *)fftw_malloc(sizeof(fftw_complex)*M_r.x * M_r.y );

	fftshift(f_tau, f_tau_new, M_r.x, M_r.y);
	for (int i = 0; i < M_r.x * M_r.y; i++)
	{
		
		In[i][0] = f_tau_new[i / M_r.y][i % M_r.y].real;
		In[i][1] = f_tau_new[i / M_r.y][i % M_r.y].imag;
	}
	//
	//fftw_plan P = fftw_plan_dft_2d(M_r.x, M_r.y, In, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	//FFTW_BACKWARD 是逆变换 FFTW_FORWARD 是正变换
	//FFTW_ESTIMATE 不寻优  FFTW_MEASURE 寻优
	fftw_plan P = fftw_plan_dft_2d(M_r.x, M_r.y, In, out, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftw_execute(P);
	for (int i = 0; i < M_r.x * M_r.y; i++)
	{
		f_tau_new[i / M_r.y][i % M_r.y].real = out[i][0];
		f_tau_new[i / M_r.y][i % M_r.y].imag = out[i][1];
	}
	fftw_destroy_plan(P);
	fftw_free(In);
	fftw_free(out);
	for (int i = 0; i < M_r.x; i++)//删除中间不再使用的数组变量
	{
		delete[]f_tau[i];
	}
	delete[]f_tau;
	delete[]f_taur;
	delete[]f_taui;

	double_complex **f_tau_new1;
	f_tau_new1 = new double_complex *[M_r.x];
	for (int i = 0; i<M_r.x; i++)
	{
		f_tau_new1[i] = new double_complex[M_r.y];
	}
	fftshift(f_tau_new, f_tau_new1, M_r.x, M_r.y);
	/**********************砍掉多余的像素***********************/
	for (int i = 0; i < Nx; i++)
		for (int j = 0; j < Ny; j++)
		{
			Nuphz[i][j] = f_tau_new1[i + Nx / 2][j + Ny / 2];
			Nuphz[i][j].real = Nuphz[i][j].real * (E_4X[i] * E_4Y[j]) / (M*R*R);
			Nuphz[i][j].imag = Nuphz[i][j].imag * (E_4X[i] * E_4Y[j]) / (M*R*R);
		}
	for (int i = 0; i < M_r.x; i++)//删除中间不再使用的数组变量
	{
		delete[]f_tau_new[i];
		delete[]f_tau_new1[i];
	}
	delete[]f_tau_new;
	delete[]f_tau_new1;
}
/*************************************************************/
//
//
//
//
//
//
//
//
//
/****************************************************************/
void  CBNS_APPDlg::FGG_Convolution2D(double  *f_taui, double  *f_taur, double_complex **Rand_Spect1, int com_x, int com_y, double **knots, double *E_3X, double *E_3Y, int M_sp, double_xy tau, int_xy M_r)
{
	double  knotx, knoty, x, y, E_1x, E_1y, E_2xdummy, E_2ydummy, V0r, V0i,
		V1r, V1i, M_rxd2, M_ryd2, E_1xy, E_23y, E_23x,
		E_2xdummy_inv, E_2ydummy_inv;
	int M, N2, m1, m2, lx, rx, ly, ry, xind, yind, ind, TwoM_sp;
	M = (2 * com_x + 1)*(2 * com_y + 1);
	N2 = M_r.x * M_r.y;
	M_rxd2 = M_r.x / 2;
	M_ryd2 = M_r.y / 2;
	TwoM_sp = 2 * M_sp;

	double_complex *Rand_Spect;
	Rand_Spect = new double_complex[M];
	for (int i = 0; i < M; i++)
	{
		Rand_Spect[i] = Rand_Spect1[(i % (2 * com_x + 1))][i / (2 * com_x + 1)];

	}
	double *E_2x;
	E_2x = new double[TwoM_sp];
	double *E_2y;
	E_2y = new double[TwoM_sp];

	for (int i = 0; i < N2; i++)
	{
		f_taui[i] = 0.0;
		f_taur[i] = 0.0;

	}
	E_2x[M_sp - 1] = 1;
	E_2y[M_sp - 1] = 1;

	for (int i = 0; i < M; i++)

	{
		/*store the ith datum's knot location*/
		knotx = knots[i][0];/*The ith knot's x location*/
		knoty = knots[i][1];/*The ith knot's y location*/
		/*Determine the closest index [m1,m2]*/
		m1 = floor(M_r.x*knotx / (2 * PI));
		m2 = floor(M_r.y*knoty / (2 * PI));/*wasting FLOPs here*/
		/*compute the Gaussian factors (we would precompute these in an
		iterative scheme to save FLOPs)
		We could compute some of these scalars outside of the loop, too.*/
		x = knotx - m1*PI / M_rxd2;
		E_1x = exp(-x*x / (4 * tau.x));
		E_2xdummy = exp(x*PI / (M_r.x*tau.x));
		E_2xdummy_inv = 1 / E_2xdummy;
		y = knoty - m2*PI / M_ryd2;
		E_1y = exp(-y*y / (4 * tau.y));
		E_2ydummy = exp(y*PI / (M_r.y*tau.y));
		E_2ydummy_inv = 1 / E_2ydummy;
		/*Compute the E_2 vector of powers of the exponential:
		for(j=0;j<TwoM_sp;j++)//E_2x=E_2xdummy.^((1-M_sp):M_sp);
		{Here, we are avoiding unnecessary exponential calculations
		E_2x[j] = pow(E_2xdummy,j-M_sp+1);
		E_2y[j] = pow(E_2ydummy,j-M_sp+1);
		}*/
		/*Is pow() the fastest thing we have at our disposal?!? It seems
		very slow. Instead of the pow() loop, we can calculate:*/
		for (int j = M_sp; j<TwoM_sp; j++)/*E_2x=E_2xdummy.^((1-M_sp):M_sp);*/
		{/*Here, we are avoiding unnecessary exponential calculations AND
		 calls to pow()*/
			E_2x[j] = E_2xdummy*E_2x[j - 1];
			E_2y[j] = E_2ydummy*E_2y[j - 1];
		}
		for (int j = M_sp - 2; j >= 0; j--)//E_2x=E_2xdummy.^((1-M_sp):M_sp);
		{/*Here, we are avoiding unnecessary exponential calculations AND
		 calls to pow()*/
			E_2x[j] = E_2x[j + 1] * E_2xdummy_inv;
			E_2y[j] = E_2y[j + 1] * E_2ydummy_inv;
		}
		/*The to small loops above appear to be much faster than the call
		to pow().  As a non-C programmer, I am very disappointed that I
		had to do this explicitly.*/
		/*Now we can compute the first constants (see the algorithm
		description on page 448 of [1])*/
		E_1xy = E_1x*E_1y;
		V0r = Rand_Spect[i].real * E_1xy;
		V0i = Rand_Spect[i].imag * E_1xy;/*Some redundant FLOPs here*/
		/*Compute f[i]'s contribution to the neighboring grid points
		Note: lots of redundant FLOPS here...should be optimized.*/
		for (int l2 = (1 - M_sp); l2 <= M_sp; l2++)/*loop over y dimension*/
		{
			E_23y = E_2y[M_sp + l2 - 1] * E_3Y[M_sp + l2 - 1];
			V1r = V0r*E_23y;
			V1i = V0i*E_23y;
			ly = (m2 + l2 + M_ryd2) >= 0;/*ly is true when reference is above
										 the lower y boundary*/
			ry = (m2 + l2)<M_ryd2;   /*ry is true when reference is below
									 the upper y boundary*/
			yind = m2 + l2 + (ry - ly)*M_r.y + M_ryd2;/*number in [0, M_ry -1]*/
			for (int l1 = (1 - M_sp); l1 <= M_sp; l1++)/*loop over x dimension*/
			{   /*Note: We need to make sure the convolution wraps around
				at the boundaries
				Calculate the boundary tests:*/
				lx = (m1 + l1 + M_rxd2) >= 0;/*lx is true when reference is above
											 the lower x boundary*/
				rx = (m1 + l1)<M_rxd2;   /*rx is true when reference is below
										 the upper x boundary*/
				xind = m1 + l1 + (rx - lx)*M_r.x + M_rxd2;/*number in [0, M_rx -1]*/
				ind = xind + M_r.x*yind;
				E_23x = E_2x[M_sp + l1 - 1] * E_3X[M_sp + l1 - 1];
				f_taur[ind] += V1r*E_23x;
				f_taui[ind] += V1i*E_23x;
			}
		}
	}

	delete[]E_2x;
	delete[]E_2y;
}


void CBNS_APPDlg::Create_File()
{
	//*********************************************************//
	//  创建一个新文件夹，用来存放相位屏数据  
	FileToSavePath = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // 宽字符的长度;
	char * pstr = new char[strsize]; //分配空间;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // 字符串已经由原来的CString 转换成了 const char*   */
	system("md " + FileToSavePath);
	CFile File_1(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //创建文件，准备存储数据
	File_1.Close();

}

void CBNS_APPDlg::save_headata()
{

	if (File.Open(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		File.Write((char*)&file_head, sizeof(file_head));    //将生成的数据写到硬盘中
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("您要打开的文件不存在") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}

	

}


/***********************************************************/
//
//
//
//
//
//
//
//
/**************************************************************/
void CBNS_APPDlg::save_data(double **A_P)
{

	if (File.Open(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		for (int i = 0; i<m_Len-Mosaic_Pixel; i++)
		 for (int j = 0; j<m_Width; j++)
		  {
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //将生成的数据写到硬盘中
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("您要打开的文件不存在") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}

	

}
///////////////////////////////////////////////////////////
//
//
//
//
//
//
//函数功能：将一幅相位屏保存到硬盘当中（格式为BMP）
//
//
//
///////////////////////////////////////////////////////////////////
void CBNS_APPDlg::Save_Pic_BMP(double *PictureBuff,int page,int Height,int Width)
{
	DWORD File_Size;                        //BMP格式的文件头大小
	RGB=new RGBQUAD[256];                   //调色板信息
	CString filename="Picture";             //命名将要保存的BMP图片
	CString Now_Page;                       //将要保存的图片页数（也是图片名的一部分）
	CString PictureToSavePath;              //将要半寸图片的路径。
	unsigned char Buwei=0;                  //调色板的第四位为0x00;
	Now_Page.Format(_T("%d"),page);         //格式化图片页码，并赋值给Now_Page
	File_Size=Height*Width+sizeof(fileheader)+sizeof(infoheader)+256*4;   //获取BMP文件头大小值
	for(int i=0;i<=255;i++)                 //给调色板赋值
	{
		RGB[i].rgbRed=i;
		RGB[i].rgbGreen=i;
		RGB[i].rgbBlue=i;
	}
	//------以下为BMP格式的文件头具体信息值-----//
	//------具体信息可参考： http://wenku.baidu.com/view/4cc859eb0975f46527d3e160.html   -----//
	fileheader.bfType='MB';
	fileheader.bfSize=File_Size;
	fileheader.bfReserved1=0x00;
	fileheader.bfReserved2=0x00;
	fileheader.bfOffBits=sizeof(fileheader)+sizeof(infoheader)+256*4;
	infoheader.biSize=0x28;
	infoheader.biWidth=Width;
	infoheader.biHeight=Height;
	infoheader.biPlanes=0x01;
	infoheader.biBitCount=0x08;
	infoheader.biCompression=0x00;
	infoheader.biSizeImage=0x00;
	infoheader.biXPelsPerMeter=0x00;
	infoheader.biYPelsPerMeter=0x00;
	infoheader.biClrUsed=0x100;
	infoheader.biClrImportant=0x00;
    PictureToSavePath=GetPathToSave();
	CFile file(PictureToSavePath+(_T("\\"))+filename+Now_Page+".BMP", CFile::modeCreate | CFile::modeWrite);    //创建文件，准备存储数据
	file.SeekToBegin();
	file.Write((char*)&fileheader,sizeof(fileheader));         //写位图文件头
	file.Write((char*)&infoheader,sizeof(infoheader));         //写位图信息头
	for(int i=0;i<=255;i++)                                    //写位图调色板
	{

		file.Write((char*)&RGB[i].rgbBlue,sizeof(RGB[i].rgbBlue));
		file.Write((char*)&RGB[i].rgbGreen,sizeof(RGB[i].rgbGreen));
		file.Write((char*)&RGB[i].rgbRed,sizeof(RGB[i].rgbRed));
		file.Write((char*)&Buwei,1);
	}
	/*double min,max;
	min=PictureBuff[0];
	max=PictureBuff[0];
	for(int i=1;i<512*512;i++)
	{
		if(PictureBuff[i]<min)
		{
			min=PictureBuff[i];
		}
		if(PictureBuff[i]>max)
		{
			max=PictureBuff[i];
		}
	}*/
	unsigned __int8  ColorBuff1[512*512];
	for(int j=0;j<512*512;j++)
	{
		ColorBuff1[j]=char(255*(PictureBuff[j]/(2*PI)));
	}
		  for(int j=0;j<512*512;j++)                      //写位图数据
		    {
				 file.Write((char*)&ColorBuff1[j],sizeof(ColorBuff1[j])); 
                
		    }
		  file.Close();                                        //关闭文件
   MessageBox(_T("图片已保存！") ,MB_OK,MB_ICONEXCLAMATION);

}
//////////////////////////////////////////////////////////////
//
//
//
//函数功能:点击“保存”按钮，开始调用Save_Pic_BMP(unsigned char *PictureBuff,int page,int Height,int Width)
//          
//         函数，完成图片的保存
//
//
/////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	Save_Pic_BMP(ColorBuff+Page_0*512,Page_0,biHeight,biWidth);

}
////////////////////////////////////////////////////////
//
//
//函数功能：将一个绝对路径（盘号+路径+文件名+扩展名）中
//          的文件路径（盘号+路径）提取出来
//
//
//////////////////////////////////////////////////////////
CString CBNS_APPDlg::GetPathToSave()
{
	char Drive[10],Dir[40],Fname[40],Ext[10];    //定义char 类型数组 用于存放解析绝对路径得到的：盘符、路径、文件名、扩展名
	CString drive;
	CString dir;
	_splitpath(strFilePath,Drive,Dir,Fname,Ext);//解析“打开”按钮获得的绝对路径。
	drive=Drive;                                //将盘符信息赋值给drive,实现 char 类型转 CString 类型
	dir=Dir;                                    //路径信息
	return drive+dir;                           //返回盘符+路径
}
//*******************************************************//
//
//
//功能：点选此按钮可退出程序、格式化程序。
//
//
//*******************************************************//
void CBNS_APPDlg::OnBnClickedButtonOut()
{
	// TODO: 在此添加控件通知处理程序代码
	COut ProgramToOut;
	INT_PTR nRes;
	nRes=ProgramToOut.DoModal();
	switch (nRes)
	{
	case (IDOK):
		{
		  if(key==true)
		   {
			delete []ColorBuff;
			if(m_Len<ImgHeight)
			{
				delete []ColorBuff_512;          //删除数组
			}
		   }
		ToOnClose();   //删除和硬件连接时生成的数组
		OnCancel();    //退出程序
		return;
		}
	case (IDCANCEL):       //格式化程序
		{
		 if(key==true)
		  { 
			delete []ColorBuff; //删除加载到内存中的相位屏数据
			if(m_Len<ImgHeight)
			{ 
				delete []ColorBuff_512;         //删除数组
			}
		  }
		 key=false;
		 m_Begin.EnableWindow(true);
		 m_Prepare_value.EnableWindow(true);
		 m_UP.EnableWindow(false);
		 m_DOWN.EnableWindow(false);
		 m_Add.EnableWindow(false);
		 m_StartStopButton.EnableWindow(false);//使“上电”、“START”、“UP”、“DOWN”、“保存”按钮处于不可用状态。
		 m_SlmPwrButton.EnableWindow(false);
		 m_Save.EnableWindow(false);
		 m_EDIT_BN=0; 
	     m_EDIT_EN=0;
         m_speed=0;                //将控制面板上的定时等参数归零。
	     m_frame=0.0;
	     m_Now=0;
		 m_L0=0;
		 m_i0=0;
		 m_r0=0;
		 m_Width_m=0;
		 m_Len_m=0;
		 m_T=0;
		 UpdateData(false);
		 return;        //格式化程序完成之后返回主程序。
		}
	default:
		{
			return; //返回主程序
		}
	}
}


void CBNS_APPDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//BNS CODE
	//Usually the following parameters are read in from the registry,
	//for simpicity they are hard-coded. Use the ReadRegistry() function in Blink
	//to read these values from the registry.
	CString BoardName = _T("PCIe512");
	LC_Type = 1; //0 = Ferroelectric LC, 1 = Nematic LC
	FrameRate =  5; //Frame rate is measured in Hz and can range from 1 - 1000 Hz
	TrueFrames = 6;

	CBNSPCIeFactory boardFactory;
	char buffer[_MAX_PATH];
	char buffer1[_MAX_PATH];
	bool VerifyHardware = true;
	bool Initialize = true;
	bool TestEnable = false;
	bool RAMWriteEnable = false;
	
	//open communication with our first PCIe board
	Board_Entry *pBoard = new Board_Entry;
	pBoard->theBoard = boardFactory.BuildBoard(BoardName, buffer, buffer1, Initialize, TestEnable, RAMWriteEnable, &VerifyHardware);
	
	//build paths to the calibrations for this SLM
	CString SLMSerialNum = _T("slm616");
	pBoard->LUTFileName.Format(_T("%s.LUT"), SLMSerialNum);
	pBoard->PhaseCompensationFileName.Format(_T("%s.bmp"), SLMSerialNum);
	pBoard->SystemPhaseCompensationFileName.Format(_T("Blank.bmp"));

	//allocate arrays for this SLM
	ImgWidth = pBoard->theBoard->BoardSpec()->FrameWidth;
	ImgHeight = pBoard->theBoard->BoardSpec()->FrameHeight;
	pBoard->LUT = new unsigned char[256];
	pBoard->PhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];
	pBoard->SystemPhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];

	//add this information to the board list
	BoardList.AddTail(pBoard);

	//read the LUT file and write it to the hardware. Images are processed through
	//the LUT in the hardware.
	ReadLUTFile(pBoard->LUT, pBoard->LUTFileName);
	pBoard->theBoard->WriteLUT(pBoard->LUT);

	//set true frames for this SLM. If we are working with an FLC SLM then 
	//True Frames must be calculated based on hardware parameters and on the Frame rate
	if(LC_Type == 0) //FLC
	{
		//for an FLC SLM Frame Rate and TrueFrames are related.
		float TimeIncrement = (pBoard->theBoard->BoardSpec()->TimeIncrement)*1e-7;
		float fTrueFrames = 1.0/(FrameRate*2.0*TimeIncrement);
		TrueFrames = (int)fTrueFrames;
	}


	pBoard->theBoard->SetTrueFrames(TrueFrames);

	//set the LC Type
	pBoard->theBoard->SetLCType(LC_Type);

	//check how many PCIe boards are present so that we can loop through the 
	//remaining boards, and open communication with them.
	NumBoards = pBoard->theBoard->BoardSpec()->NumDevices;

	//open communication and repeat the above process with the rest of our PCIe boards
	Initialize = false;
	for(int board = 2; board <= NumBoards; board++)
	{
		Board_Entry *pBoard = new Board_Entry;
		pBoard->theBoard = boardFactory.BuildBoard(BoardName, buffer, buffer1, Initialize, TestEnable, RAMWriteEnable, &VerifyHardware);
		
		//build paths to the calibrations for this SLM
		CString SLMSerialNum = _T("slm616");
		pBoard->LUTFileName.Format(_T("%s.LUT"), SLMSerialNum);
		pBoard->PhaseCompensationFileName.Format(_T("%s.bmp"), SLMSerialNum);
		pBoard->SystemPhaseCompensationFileName.Format(_T("Blank.bmp"));

		//allocate arrays for this SLM
		pBoard->LUT = new unsigned char[256];
		pBoard->PhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];
		pBoard->SystemPhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];		
		BoardList.AddTail(pBoard);

		//read the LUT file and write it to the hardware. Images are processed through
		//the LUT in the hardware.
		ReadLUTFile(pBoard->LUT, pBoard->LUTFileName);
		pBoard->theBoard->WriteLUT(pBoard->LUT);

		//set True Frames for this SLM
		pBoard->theBoard->SetTrueFrames(TrueFrames);

		//set the LC Type
		pBoard->theBoard->SetLCType(LC_Type);
	}
	for(int board = 0; board < NumBoards; board++)
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		bool bPower = (bool)pBoard->theBoard->GetPower();
		if(bPower)
		pBoard->theBoard->SetPower(!(bPower));
	}
	m_SlmPwrButton.SetWindowText(_T("ON POWER"));          //初始化上电控件为："ON POWER",表示等待上电状态。
	m_StartStopButton.SetWindowText(_T("START"));         //初始化开始控件，设置为“START”,表示等待加载相位屏数据。
	if(LC_Type == 1)
		m_CompensatePhaseCheckbox.ShowWindow(false);      //如果液晶为向列型液晶，则不使用补偿。
	else
		m_CompensatePhaseCheckbox.ShowWindow(true);       //否则使用补偿。
	m_SlmPwrButton.EnableWindow(true);
	m_Load.EnableWindow(false);

}


void CBNS_APPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (Down_Up)
	{
	case 1:
		UpdateData(true);
	Page_0=m_Now;
	Page_0+=Pixel;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0>m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0>m_EDIT_BN)
	       {

		      Page_0=m_EDIT_EN;
	       }
	}
	
	 Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	 m_Now=Page_0;
	 UpdateData(false);
	 m_Save.EnableWindow(true);
	 
		break;
	case 0:
		UpdateData(true);
	Page_0=m_Now;
	Page_0-=Pixel;;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-Pixel）
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0<m_EDIT_BN)
	       {
		      Page_0=m_EDIT_EN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0<m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}

	 Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	
	 m_Now=Page_0;
	 UpdateData(false);
		break;
	default:   
        break;
	}

}