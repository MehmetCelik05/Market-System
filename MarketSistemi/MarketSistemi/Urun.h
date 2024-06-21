#pragma once
#include<iostream>
using namespace std;

class Urun {
private:
	int kod;
	string isim;
	int adet;
	float bFiyat;
public:
	Urun(int _kod,string _isim,int _adet,float _bFiyat);
	
	void setIsim(string _isim);
	string getIsim();

	void setAdet(int _adet);
	int getAdet();

	void setbFiyat(float _bFiyat);
	float getbFiyat();
	
	void UrunBilg();

	void setKod(int _kod);
	int getKod();
};
