// BNS_APPDlg.h : 头文件
//
#include "FFTW/fftw3.h"
#pragma once


#include "BNSPCIeBoard\BNSPCIeHardware.h" //添加赢家驱动头文件
#include "BNSPCIeBoard\BNSPCIeBoard.h"

#include <iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include <fstream>
#include <string>
#include "afxwin.h"
#include "afxcmn.h" 

using namespace std;


#define PI 3.1415926f      //π的定义
#define e  2.7182818f      //自然数e的定义
#define LC 0.00768        //液晶屏的宽度为7.68mm
#define POINT 512          //液晶屏上列（行）向像素点个数为512个
#define Mosaic 400         //拼接部分为500个pixel
#define T_1_1 0.0044       //加载一副相位屏所用时间
#define Up false
#define Down true
#define m_Rr POINT/m_Width_m //宏定义m_Rr

//***** 此下的定义为向列型液晶硬件库所需要用到的变量  ****//
typedef struct
{
	//pointer to the board
	CBNSPCIeBoard* theBoard;
	unsigned char*	PhaseCompensationData;
	unsigned char*  SystemPhaseCompensationData;
	unsigned char*	LUT;

	CString			LUTFileName;
	CString			PhaseCompensationFileName;
	CString			SystemPhaseCompensationFileName;
} Board_Entry;

typedef CTypedPtrList<CPtrList, Board_Entry*> CBoard_List;
struct double_complex
{
	double real;
	double imag;
};//定义结构体类型：复数由两个double类型的数组成
struct  double_xy
{
	double x;
	double y;
};//定义结构体类型：包含两个double类型数据
struct int_xy
{
	int x;
	int y;
};//定义结构体类型：包含两个int类型数据
struct My_st
{
	double m_L0;
	double m_i0;
	double m_r0;
	int m_speed;    //定时器定时时间
	float m_frame;   //帧率
	int m_Width_m;
	int m_Len_m;
	int m_T;
};
// CBNS_APPDlg 对话框
class CBNS_APPDlg : public CDialog
{
// 构造
public:


/****************************************************/

    LARGE_INTEGER M_Begin;  //计数器起始数
	LARGE_INTEGER M_End;    //计数器终止数
    LARGE_INTEGER TimeToL;  //
	LARGE_INTEGER Frequence;//取高精度运行计数器的频率
   
	HICON m_hicn1;
	HICON m_hicn2;
	CFile file;      // CFile对象 
	CFile File;
	double *ColorBuff; //用于存放相位屏信息的动态数组
	unsigned __int8 *ColorBuff_512;//和液晶像素点个数相同的一个数组，可用于暂时存放相位屏数据
	double **A_P;

	CBNS_APPDlg(CWnd* pParent = NULL);	// 标准构造函数
	void			LoadSequence(double *ColorBuff);    //向硬件加载相位屏数据
	bool			ReadAndScaleBitmap(unsigned char* buffer, CString ImagePath);//读取并变化位图大小
	unsigned char*	ScaleBitmap(unsigned char* InvertedImage, int BitmapSize, int FinalBitmapSize);//调整位图大小
	bool			ReadLUTFile(unsigned char* LUTBuf, CString LUTPath);//读取LUT文件

    //Global variables
	int			NumBoards;    //正在使用的硬件个数
	bool		LC_Type;      //bool 型变量 用于区别液晶类型  1：向列型  0：铁电型
	int			FrameRate;    //帧率
	unsigned short TrueFrames; //实际帧率
	int			ImgHeight;     //液晶屏高度，表示列向像素点
	int			ImgWidth;      //液晶屏宽度，表示行向像素点
	CBoard_List BoardList;     
  // 对话框数据
	enum { IDD = IDD_BNS_APP_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();   //初始化函数
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    virtual void	OnOK();  
    afx_msg void	ToOnClose();  //将驱动硬件生成的数组释放掉
	DECLARE_MESSAGE_MAP()
public:

	BITMAPFILEHEADER fileheader;  //保存BMP格式图片时的头信息
	BITMAPINFOHEADER infoheader;  //保存BMP格式图片时候的信息头
	//BITMAPINFO INFO;
	BITMAPINFO *INFO;
	RGBQUAD *RGB;                 //用于存放调色板的动态数组

	int m_EDIT_BN;   //控件“开始显示号”的变量
	int m_EDIT_EN;   //“结束显示号”的变量
	int Page;        //打开文件时，获得文件分割个数的变量
	int Page_0;      //用于显示、打印当前相位屏
	int biWidth;     //相位屏宽度（像素点数）
	int	biHeight;    //相位屏高度（像素点数）
	int Page_end;    //用于记录循环显示结束号
	long Pixel;
	int Mosaic_Pixel;
	int m_Now;       //用于版面显示当前相位屏号
	bool key;        //用于是否为存放相位屏数据的数组分配内存的标志
	bool Down_Up;

	//void ReadFileToBuff(unsigned char *ColorBuff);    //读取相位屏数据到指定数组
	void Display_Picture(double *ColorBuff);  //将读取到的相位屏信息打印到屏幕上
	void ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512); //将小于POINT的相位屏转化为POINT*POINT大小
	void LoadHardBoard();                             //将相位屏信息加载到硬件上
	void My_Delay(LARGE_INTEGER Interval);            //定时函数
	void Save_Pic_BMP(double *PictureBuff,int page,int Height,int Width); //保存相位屏信息（BMP格式）
    
	CButton m_Begin;         //面板“开始”控件的变量
    CStatic m_Picture;       //面板“图片”控件的变量
	CString CS_Page;         //面板“文件单位数”控件的变量
	CButton m_CompensatePhaseCheckbox; //（在向列型液晶中此控件不显示）
	CButton m_StartStopButton;         //面板“STATE”控件的变量
	CButton m_SlmPwrButton;            //面板“ON POWER”控件的变量
	BOOL m_CompensatePhase;            //（在向列型液晶中此控件不显示）
	CButton m_UP;       //面板“UP”控件的变量
	CButton m_DOWN;     //面板“DOWN”控件的变量
	CButton m_Open;     //面板“打开”控件的变量
	CButton m_out;      //面板“退出”控件的变量
	CButton m_Save;     //面板“保存”控件的变量
	CString strFilePath;//面板“文件路径”控件的变量

	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedStartStopButton();
	afx_msg void OnBnClickedSlmPwrButton();
	afx_msg void OnBnClickedButtonGo();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedCompensatePhaseCheckbox();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnEnChangeEditBeginNum();
//	afx_msg void OnEnChangeEditEndNum();

	double m_L0;
	double m_i0;
	double m_r0;
	double m_fm;
	double m_errorboundd;
	double m_errorboundu;
	int m_Width;
	int m_Width_m;
	int m_Len;
	int m_Len_m;
	int m_speed;    
	float m_frame;   //帧率
	int T_Len;
	int m_T;
	int m_now_frame;
	My_st file_head;
	CString FileToSavePath;
	/*CProgressCtrl m_progress;
	CProgressCtrl m_progress_file;*/
	CButton m_Prepare_value;
	CString GetPathToSave();

	double integral(double(CBNS_APPDlg:: *fun)(double), double a, double b);
	double psdevalfunKolspf(double x);
	double randn();
	CString rands();
	long double psdevalfun(double f0, double f1, double f2, int samppoints);
	void Norseque2(double *sequencex, int com_x, double *sequencey, int com_y, double **f_area);
	void FGG_2d_type1(double_complex **Rand_Spect1, double_complex **Nuphz, double *kax_dbside, int com_x, double *kay_dbside, int com_y, int Nx, int Ny, int Desired_accuracy);
	double Min(double *ka_dbside, int point);
	double Max(double *ka_dbside, int point);
	double Mod_double(double dividend, double divisor);
	float Mod_float(float dividend, double divisor);
	void fftshift(double_complex **matrix_old, double_complex **matrix_new, int row, int column);
	void  FGG_Convolution2D(double  *f_taui, double  *f_taur, double_complex **Rand_Spect1, int com_x, int com_y, double **knots, double *E_3X, double *E_3Y, int M_sp, double_xy tau, int_xy M_r);
	void Nufft(double **Spectrum1,double *kax_dbside, int com_x, double *kay_dbside, int com_y);
	void save_data(double **A_P);
	void save_headata();
	void Create_File();

	afx_msg void OnBnClickedButtonYushezhi();
	afx_msg void OnBnClickedButtonKaishi();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonOut();
	
	afx_msg void OnBnClickedAdd();
	CButton m_Load;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonAdd();
	CButton m_Add;
	CProgressCtrl m_Progress;
};

