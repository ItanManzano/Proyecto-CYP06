/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES ARAGON
	Computadoras y programacion.
	Itandehui Manzano Mejía | Numero de cuenta:320040964 
******************************************************************************************************************/
#include "stdafx.h"
#include <string.h>
#include "corrector.h"

void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* stream;
	char szRecibePalabras[NUMPALABRAS][TAMTOKEN];
	char szControl[TAMTOKEN];
	int  szCaracter, i, j, iSegurofin, iControl;
	fopen_s(&stream, szNombre, "r");
	if (stream == NULL)
		return;

	iNumElementos = 0; j = 0;
	szCaracter = fgetc(stream);
	while (feof(stream) == 0)
	{
		if (!((szCaracter == 9) || (szCaracter == 10) || (szCaracter == 13) || (szCaracter == 32) || (szCaracter == 41) || (szCaracter == 44) || (szCaracter == 46) || (szCaracter == 59) || (szCaracter == 40)))
		{
			szRecibePalabras[iNumElementos][j] = towlower((char)szCaracter);
			szCaracter = fgetc(stream);
			j++;

		}
		else
		{
			if (j > 0)
			{
				szRecibePalabras[iNumElementos][j] = '\0';
				iEstadisticas[iNumElementos] = 1;

				if (iNumElementos > 0)
				{
					for (i = 0; i < iNumElementos; i++)
						if (strcmp(szRecibePalabras[i], szRecibePalabras[iNumElementos]) == 0)
						{
							iEstadisticas[i] = iEstadisticas[i] + 1;
							i = iNumElementos;
							iNumElementos = iNumElementos - 1;
						}
				}

				iNumElementos++;
				j = 0;
			}
			szCaracter = fgetc(stream);
		}
	}
	fclose(stream);

	szRecibePalabras[iNumElementos][j] = '\0';
	iEstadisticas[iNumElementos] = 1;

	for (i = 0; i < iNumElementos; i++)
		if (strcmp(szRecibePalabras[i], szRecibePalabras[iNumElementos]) == 0)
		{
			iEstadisticas[i] = iEstadisticas[i] + 1;
			strcpy_s(szRecibePalabras[iNumElementos], "");
			i = iNumElementos;
		}

	for (i = 0; i < iNumElementos; i++)
	{
		iSegurofin = 0;
		for (j = 0; j < iNumElementos; j++)
		{
			if (strcmp(szRecibePalabras[j + 1], szRecibePalabras[j]) < 0)
			{
				strcpy_s(szControl, szRecibePalabras[j]);
				iControl = iEstadisticas[j];
				strcpy_s(szRecibePalabras[j], szRecibePalabras[j + 1]);
				iEstadisticas[j] = iEstadisticas[j + 1];
				strcpy_s(szRecibePalabras[j + 1], szControl);
				iEstadisticas[j + 1] = iControl;
			}
			else
				iSegurofin += 1;
		}
		if (iSegurofin == iNumElementos)
			i = iNumElementos;
	}

	if (strcmp(szRecibePalabras[0], "") == 0)
	{
		for (i = 0; i < iNumElementos; i++)
		{
			strcpy_s(szPalabras[i], szRecibePalabras[i + 1]);
			iEstadisticas[i] = iEstadisticas[i + 1];
		}
		iEstadisticas[i] = '\0';
	}
	else
	{
		iNumElementos++;
		for (i = 0; i < iNumElementos; i++)
			strcpy_s(szPalabras[i], szRecibePalabras[i]);
	}
}

void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	
	int		iNumSugeridas,						
	char	szPalabras[][TAMTOKEN],				
	int		iEstadisticas[],					
	int		iNumElementos,					
	char	szListaFinal[][TAMTOKEN],		
	int		iPeso[],							
	int& iNumLista)							
{

	int ci, cii;
	
	iNumLista = 0;
	for (ci = 0; ci < iNumSugeridas; ci++)
	{
		for (cii = 0; cii < iNumElementos; cii++)
		{
			if (strcmp(szPalabrasSugeridas[ci], szPalabras[cii]) == 0)
			{
				strcpy_s(szListaFinal[iNumLista], szPalabras[cii]);
				iPeso[iNumLista++] = iEstadisticas[cii];
			}
		}
	}



	int limbo1, limbo2;
	char limboc1[TAMTOKEN], limboc2[TAMTOKEN];
	

	ci = 0;
	while (iNumLista > ci)
	{
		for (cii = ci + 1; cii < iNumLista; cii = cii + 1)
		{
			if (iPeso[ci] < iPeso[cii])
			{
				limbo1 = iPeso[ci];
				limbo2 = iPeso[cii];
				strcpy_s(limboc1, szListaFinal[ci]);
				strcpy_s(limboc2, szListaFinal[cii]);
				
				iPeso[ci] = limbo2;
				iPeso[cii] = limbo1;
				strcpy_s(szListaFinal[ci], limboc2);
				strcpy_s(szListaFinal[cii], limboc1);
				
			}
		}
		ci++;
	}

	int nSug = iNumLista, iii, iNumT = iNumElementos;
	ci = 0;
	while (nSug > ci)
	{
		for (cii = ci + 1; cii <= nSug; cii++)
		{
			if (strcmp(szListaFinal[ci], szListaFinal[cii]) == 0)
			{
				for (iii = cii; iii < iNumT; iii++)
				{
					
					strcpy_s(szListaFinal[iii], szListaFinal[iii + 1]);
					iPeso[iii] = iPeso[iii + 1];
				}
				nSug--;
				cii--;
				
			}
		}
		ci++;
	}
	iNumLista = nSug;
}



int nletrasPLs;

void	ClonaPalabras(
	char* szPalabraLeida,						
	char	szPalabrasSugeridas[][TAMTOKEN], 	
	int& iNumSugeridas)						
{
	
	char PLedit[TAMTOKEN] = "v";
	_strnset(PLedit, '\0', TAMTOKEN);
	int i, ii;
	iNumSugeridas = 0;
	nletrasPLs = strlen(szPalabraLeida);
	
	for (i = 0; i <= nletrasPLs; i++) 
	{
		
		for (ii = 0; ii < nletrasPLs; ii++) 
		{
			PLedit[ii] = szPalabraLeida[ii];
		}

		for (ii = i; ii < nletrasPLs; ii++)
		{
			PLedit[ii] = PLedit[ii + 1];
		}

		if (PLedit[0] != ' ' && PLedit[0] != '\0')
		{
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], PLedit);
		}
	}


	char limbolizq, limbolder;
	int cizqDer;
	_strnset(PLedit, '\0', TAMTOKEN);
	i = 0;
	for (cizqDer = 1; cizqDer < nletrasPLs; cizqDer++) 
	{
	
		for (ii = 0; ii < nletrasPLs; ii++)
		{
			PLedit[ii] = szPalabraLeida[ii];
		}

		limbolizq = szPalabraLeida[i];
		limbolder = szPalabraLeida[i + 1];

		PLedit[i] = limbolder;
		PLedit[i + 1] = limbolizq;
		if (PLedit[0] != ' ' && PLedit[0] != '\0')
		{
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], PLedit);
		}
		i++;
	}

	_strnset(PLedit, '\0', TAMTOKEN);


	char abc[] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
	int longabc = strlen(abc), cCopy;

	for (i = 0; i < nletrasPLs; i++)
	{
		for (ii = 0; ii < longabc; ii++) 
		{
			
			for (cCopy = 0; cCopy < nletrasPLs; cCopy++)
			{
				PLedit[cCopy] = szPalabraLeida[cCopy];
			}

			PLedit[i] = abc[ii];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], PLedit);
		}
	}

	
	_strnset(PLedit, '\0', TAMTOKEN);
	
	for (i = 0; i <= nletrasPLs; i++)
	{
	
		for (ii = 0; ii < nletrasPLs; ii++)
		{
			PLedit[ii] = szPalabraLeida[ii];
		}

		
		for (ii = nletrasPLs; ii > i; ii--)
		{
			PLedit[ii] = PLedit[ii - 1];
		}

		for (ii = 0; ii < longabc; ii++) 
		{
			PLedit[i] = abc[ii];
			if (PLedit[0] != ' ' && PLedit[0] != '\0')
			{
				strcpy_s(szPalabrasSugeridas[iNumSugeridas++], PLedit);
			}
		}
	}


	char limboc1[TAMTOKEN], limboc2[TAMTOKEN];
	
	i = 0;
	while (iNumSugeridas > i)
	{
		for (ii = i + 1; ii < iNumSugeridas; ii = ii + 1)
		{
			if (strcmp(szPalabrasSugeridas[i], szPalabrasSugeridas[ii]) > 0)
			{
				
				strcpy_s(limboc1, szPalabrasSugeridas[i]);
				strcpy_s(limboc2, szPalabrasSugeridas[ii]);
				

		
				strcpy_s(szPalabrasSugeridas[i], limboc2);
				strcpy_s(szPalabrasSugeridas[ii], limboc1);
				
			}
		}
		i++;
	}
	_strnset(szPalabraLeida, '\0', TAMTOKEN);
}