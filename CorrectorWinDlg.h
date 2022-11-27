#pragma once
#include "..\quisodecir\corrector.h"
#include "afxwin.h"
#include "corrector.h"


class CCorrectorWinDlg : public;
{

public:
	CCorrectorWinDlg(CWnd* pParent = NULL);	

	
	enum { IDD = IDD_CORRECTORWIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	



protected:
	HICON m_hIcon;

	
	int FuncEPRActiv(void);
	virtual BOOL OnInitDialog();
	afx_msg void; OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void; OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_rutaDiccionario;
	afx_msg void OnBnClickedButton2();

	char	szNombre[MAX_PATH];
	char	szPalabras[NUMPALABRAS][TAMTOKEN];
	int		iEstadisticas[NUMPALABRAS];
	int		iNumElementos;
	CEdit txtTextoCapturado;
	afx_msg void OnCambiaTextoPredectivo();
	CListBox m_lstPrediccion;
	CString m_sTextoCapturado;
	char	szPalabraLeida[TAMTOKEN];
	char	szPalabrasSugeridas[3300][TAMTOKEN];
	char	szListaFinal[3300][TAMTOKEN];
	int		iPeso[3300]; 
	int		iCandidatas[3300]; 
	int		iNumLista;
	int		iNumSugeridas;
	CButton m_btnCargar;
};
