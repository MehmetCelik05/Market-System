#include"Urun.h"

Urun::Urun(int _kod,string _isim, int _adet, float _bFiyat) {
	isim = _isim;
	adet = _adet;
	bFiyat = _bFiyat;
	kod = _kod;
}

void Urun::setIsim(string _isim) {
	isim = _isim;
}
string Urun::getIsim() {
	return isim;
}

void Urun::setAdet(int _adet) {
	adet = _adet;
}
int Urun::getAdet() {
	return adet;
}

void Urun::setbFiyat(float _bFiyat) {
	bFiyat = _bFiyat;
}
float Urun::getbFiyat() {
	return bFiyat;
}

void Urun::UrunBilg() {
	cout << "Urun kodu: " << kod<<endl;
	cout << "Urun ismi: " << isim << endl;
	cout << "Urun adedi: " << adet << endl;
	cout << "Urun birim fiyati: " << bFiyat << endl;
}

void Urun::setKod(int _kod) {
	kod = _kod;
}
int Urun::getKod() {
	return kod;
}
