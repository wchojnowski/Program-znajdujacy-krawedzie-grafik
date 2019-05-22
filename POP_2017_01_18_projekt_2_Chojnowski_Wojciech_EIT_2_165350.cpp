/* POP 2017-01-18 projekt 2 Chojnowski Wojciech EIT 2 165350
Dev-C++ 5.11*/
#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;


const int MaxRozmiar=775;


int main()
{
	int biWidth;
	int biHeight;
	char Hdr[54];
	int Kol;
	int IleR;
	int R1;
	int R2;
	int X;
	int BajtowNaWiersz;
	char W1[MaxRozmiar];
	char W2[MaxRozmiar];
	char R[MaxRozmiar];
	
	fstream PlikZ;
	PlikZ.open( "sonar_aktywny3.bmp", ios::in | ios::binary);
	if(PlikZ.good()==false)
	{
		cout<<" Nie ma takiego pliku ";
		PlikZ.close();	
	}
	
	PlikZ.read(Hdr, 54);
	biWidth=173;//Hdr[19];//19 bajt nag³ówka(Iloœæ punktów na wiersz)
	biHeight=239;//Hdr[23];//23 bajt nag³ówka(Iloœæ punktów na kolumne)
	
	fstream PlikDo;
	PlikDo.open("roberts.bmp", ios::out | ios::binary);
	PlikDo.write(Hdr,54);
	
	BajtowNaWiersz=biWidth*3; 
	
	if((BajtowNaWiersz % 4)!=0)	BajtowNaWiersz=BajtowNaWiersz+4-(BajtowNaWiersz % 4);

	
	W1[MaxRozmiar]={};
	W2[MaxRozmiar]={};
	
	PlikZ.read(W1,BajtowNaWiersz);	

		
		
	for(int j=1;j<=biHeight;j++)
	{
		PlikZ.read(W2,BajtowNaWiersz);
		R[MaxRozmiar]={};
		for(int Kol=0;Kol<=2;Kol++)
		{
			for(int i=1;i<=biWidth-1;i++)
			{
				X=(i-1)*3+Kol;
				R1=W1[X]-W2[X+3];
				R2=W2[X]-W1[X+3];
				R[X]=abs(R1)+abs(R2);
			}
			R[biWidth*3+Kol]=0;
		}
		PlikDo.write(R,BajtowNaWiersz);
		W1[MaxRozmiar]=W2[MaxRozmiar];
	}		

	R[MaxRozmiar]={};
//	PlikDo.write(R,BajtowNaWiersz);
	PlikZ.close();
	PlikDo.close();
	return 0;
}
