#include "stdafx.h"
#include "MainDlg.h"
#include <CommDlg.h>
#include "SVideoPlayer.h"
#include "CChineseCode.h"
extern SOUI::SApplication *theApp;
namespace SOUI
{
	CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
	{
		m_bLayoutInited=FALSE;
	} 

	CMainDlg::~CMainDlg()
	{

	}


	void CMainDlg::OnClose()
	{
		AnimateHostWindow(200,AW_CENTER|AW_HIDE);
		DestroyWindow();
		exit(0);
	}
	void CMainDlg::OnMaximize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	
	void CMainDlg::OnRestore()
	{
		
		SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	
	void CMainDlg::OnMinimize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}
	
	

	void CMainDlg::OnSize(UINT nType, CSize size)
	{
		SetMsgHandled(FALSE);
		if(!m_bLayoutInited) 
			return;
	}
	int  CMainDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
	{
		
		SetMsgHandled(FALSE);
		//定时器
		this->SetTimer(1,1000);
		
		return 0;
	}
	void CMainDlg::OnTimer(UINT_PTR cTimerID)
	{
		if(cTimerID==1){

		}else{
			SHostWnd::OnTimer(cTimerID);
		}
	}

	int OpenLocalFile(HWND hWnd,std::wstring &path)
	{
		OPENFILENAME ofn = { 0 };  
		TCHAR strFilename[2048] = { 0 };//用于接收文件名  
		ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小  
		ofn.hwndOwner = hWnd;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
		
        ofn.lpstrFilter = TEXT("视频文件(*.mp4,*.mkv,*.flv,*.avi,*.rm,*.rmvb)\0*.mp4;*.mkv;*.flv;*.avi;*.rm;*.rmvb\0\0");
		
		ofn.nFilterIndex = 1;//过滤器索引  
		ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL  
		ofn.nMaxFile = sizeof(strFilename);//缓冲区长度  
		ofn.lpstrInitialDir = NULL;//初始目录为默认  
		
		ofn.lpstrTitle=L"选择视频文件";

		bool mulSel=false;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//文件、目录必须存在，隐藏只读选项  
        if (GetOpenFileName(&ofn))  
		{ 
			path= strFilename;
			return 1;
		}
		return 0;
	}
	void CMainDlg::OnOpenFile1()
	{
	    std::wstring path;
	   int ret=OpenLocalFile(m_hWnd,path);
	   if(ret==1){
	      SVideoPlayer* player=(SVideoPlayer*)this->FindChildByName("S_AVLayout4_1");
		  char temp[1024]="";
		  CChineseCode::wcharTochar( path.c_str(),temp,1024);
		  player->OpenMedia(temp,100);
		  player->SetAVVisible(1);
	   }
	}
	void CMainDlg::OnOpenFile2()
	{
	    std::wstring path;
	   int ret=OpenLocalFile(m_hWnd,path);
	   if(ret==1){
	      SVideoPlayer* player=(SVideoPlayer*)this->FindChildByName("S_AVLayout4_2");
		  char temp[1024]="";
		  CChineseCode::wcharTochar( path.c_str(),temp,1024);
		  player->OpenMedia(temp,100);
		  player->SetAVVisible(1);
	   }
	}
	BOOL CMainDlg::OnInitDialog( HWND hWnd, LPARAM lParam )
	{
		m_bLayoutInited=TRUE;
		
		return 0;
	}
	
	
}

