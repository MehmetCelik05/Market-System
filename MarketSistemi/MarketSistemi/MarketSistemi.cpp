#include<iostream>
#include<list>
#include<time.h>
#include<cstdlib>
#include<ctime>
#include"Urun.h"
using namespace std;

/*
Yeni ürün eklenmesi(adet,isim,fiyatýyla beraber) +
Satýþ fiyatý ve stok adet güncellestirme  +
Ürünleri kod ile satma  +
Satýlan ürünlerin faturada gösterilmesi(En sonda toplam tutar gözükmesi,Faturada üründen kaç tane alýnmýþ ve birim fiyatý gösterilsin)  +
Ürün silme +
Fatura iptali  +
Belli bir üründen bir tarih aralýðýnda kaç tane satýlmýþ listelesi  +
Stokta olan tüm ürünlerin listesi  +
Toplam satýlan ürünlerin listelenmesi  +
Belirli bir deðerin altýna düþen ürünlerin listelenmesi  +
*/
void menu();
void YeniUrun(list<Urun>* lst);
void FiyatGuncelleme(list<Urun>* lst);
void StokGuncelleme(list<Urun>* lst);
void UrunSilme(list<Urun>* lst);
void Satis(list<Urun>* lst, list<Urun>* flst);
void UrunList(list<Urun>* lst);
void StokUrunList(list<Urun>* slst);
void SatUrunList(list<Urun>* flst);
void AltUrunList(list<Urun>* lst);
void FaturaIptal(list<Urun>* lst,list<Urun>* flst);

int kod = 0, adet = 0;
float bFiyat = 0.0;
string isim;

list<Urun>* Satislst;
list<Urun>* SUrunlst;

int main() {
	Satislst = new list<Urun>;
	SUrunlst = new list<Urun>;

	menu();
	delete SUrunlst;
	delete Satislst;
}

void YeniUrun(list<Urun>* lst) {
	srand(time(0));
	list<Urun>::iterator it;
	bool KodAyni = false;
	cout << "Urun ismi giriniz: ";
	cin >> isim;
	cout << "Urun adeti giriniz: ";
	cin >> adet;
	cout << "Urun birim fiyati giriniz: ";
	cin >> bFiyat;
	do {
		kod = rand() % 900+100;
		for (it = lst->begin(); it != lst->end(); it++) {
			if (kod == it->getKod()) {
				KodAyni = true;
				break;
			}
		}
	}
	while (KodAyni);
	Urun urun1(kod, isim, adet, bFiyat);
	cout << "Urun kodu: " << urun1.getKod()<<endl;
	lst->push_back(urun1);
	cout << endl << endl;
	menu();
}

void FiyatGuncelleme(list<Urun>* lst) {
	float yFiyat;
	cout << "Fiyati degisecek urunun kodunu giriniz: ";
	cin >> kod;
	list<Urun>::iterator it;
	for (it = lst->begin(); it != lst->end(); it++) {
		if (kod == it->getKod()) {
			cout << "Yeni fiyat artisini giriniz: ";
			cin >> yFiyat;
			it->setbFiyat(yFiyat+it->getbFiyat());
			cout << "Yeni fiyat: " << it->getbFiyat();
			break;
		}
	}
	cout << endl << endl;
	menu();
}

void StokGuncelleme(list<Urun>* lst) {
	int yAdet;
	cout << "Stogu degisecek urunun kodunu giriniz: ";
	cin >> kod;
	list<Urun>::iterator it;
	for (it = lst->begin(); it != lst->end(); it++) {
		if (kod == it->getKod()) {
			cout << "yeni gelen urun adedini giriniz: ";
			cin >> yAdet;
			it->setAdet(yAdet + it->getAdet());
			cout << "yeni adet sayisi: " << it->getAdet();
			break;
		}
	}
	cout << endl << endl;
	menu();
}

void UrunSilme(list<Urun>* lst) {
	cout << "Silinecek urunun kodunu giriniz: ";
	cin >> kod;
	list<Urun>::iterator it;
	for (it = lst->begin(); it != lst->end(); it++) {
		if (kod == it->getKod()) {
			lst->erase(it);
			break;
		}
	}
	cout << endl << endl;
	menu();
}

void Satis(list<Urun>* lst, list<Urun>* flst) {
	int sAdet;
	int kod;
	bool satis = false;
	list<Urun>::iterator it;
	while (!satis)
	{
		cout << "Satin alinacak urunun kodunu giriniz (Satisi tamamlamak icin 0'a basiniz): ";
		cin >> kod;
		for (it = lst->begin(); it != lst->end(); it++) {
			if (kod == it->getKod()) {
				cout << "Alinacak urun adedini giriniz: ";
				cin >> sAdet;
				if (sAdet <= it->getAdet()) {
					//Faturada alýnan sayý,kalan sayý
					it->setAdet(it->getAdet() - sAdet);
					cout<<"Kalan urun sayisi: "<<it->getAdet()<<endl;
					it->setAdet(sAdet);
					flst->push_back(*it);
					it->setAdet(adet-sAdet);
				}
				else if (sAdet > it->getAdet()) {
					cout << it->getIsim() << " isimli urunun adedi yetersiz" << endl;
				}
			}
		}
		if (kod == 0) {
			cout << endl << "Faturaya yonlendiriliyorsunuz..." << endl;
			float sum = 0.0;
			cout << "-----Fatura-----" << endl;
			for (it = flst->begin(); it != flst->end(); it++) {
				cout << it->getIsim() << endl << it->getbFiyat() << "x" << it->getAdet() << "		" << it->getAdet() * it->getbFiyat() << endl;
				sum += it->getAdet() * it->getbFiyat();
			}
			cout << endl<<"Toplam fiyat: " << sum << endl << endl;
			satis = true;
			cout << "Faturayi iptal etmek ister misiniz ?(Iptal icin 1'e basiniz, devam etmek icin 0'a basiniz)";
			cin >> kod;
			if (kod == 1) {
				break;
				FaturaIptal(SUrunlst, Satislst);
			}
			cout << endl << endl;
		}
	}
	cout << "Menuye donuluyor..." << endl;
	menu();
}

void UrunList(list<Urun>* lst) {
	list<Urun>::iterator it;
	cout << "Urunun kodunu giriniz: ";
	cin >> kod;
	for (it = lst->begin(); it != lst->end(); it++) {
		if (kod == it->getKod()) {
			if (it->getAdet() != 0) {
				it->UrunBilg();
				break;
			}
			else
				cout << "Urun stoklarda kalmadi" << endl;
		}
		else if(it==lst->end())
			cout << "Hatali kod girildi..." << endl;
	}
	cout << endl << endl;
	menu();
}

void StokUrunList(list<Urun>* slst) {
	list<Urun>::iterator it;
	int i = 0;
	for (it = slst->begin(); it != slst->end(); it++) {
		if (it->getAdet() != 0) {
			++i;
			cout << i << ":" << endl;
			it->UrunBilg();
		}
	}
	cout << endl << endl;
	menu();
}

void SatUrunList(list<Urun>* flst) {
	list<Urun>::iterator it;
	for (it = flst->begin(); it != flst->end(); it++) {
		it->UrunBilg();
	}
	cout << endl << endl;
	menu();
}

void AltUrunList(list<Urun>* lst) {
	int Uadet ;
	cout << "hangi adet degerinin altindaki urunleri gormek istersiniz: ";
	cin >> Uadet;
	list<Urun>::iterator it;
	for (it = lst->begin(); it != lst->end(); it++) {
		if (it->getAdet() <= Uadet) {
			cout << it->getIsim() << " urunun adeti: " << it->getAdet()<<endl;
		}
	}
	cout << endl << endl;
	menu();
}

void FaturaIptal(list<Urun>* lst,list<Urun>* flst) {
	for (auto it = flst->begin(); it != flst->end(); it++) {   
		int get_kod = it->getKod();
		for (auto sit = lst->begin(); sit != lst->end(); sit++) {
			if (get_kod == sit->getKod()) {
				it->setAdet(it->getAdet() + sit->getAdet());
				cout << endl << "menuye donuluyor..." << endl;
			}
		}
	}
	flst->clear();
	menu();
}

void menu() {
	int islem = 0;
	cout <<"Hosgeldiniz..." << endl;
	cout <<"1)Yeni urun ekleme " << endl;
	cout << "2)Fiyat guncelleme" << endl;
	cout << "3)Stok guncelleme" << endl;
	cout << "4)Urun silme"<<endl;
	cout << "5)Satis yapma" << endl;
	cout << "6)Bir urunun stok listesi(Tarih araliginda)" << endl;
	cout << "7)Stokta olan tum urunlerin listesi" << endl;
	cout << "8)Toplam satilan tum urunlerin listesi" << endl;
	cout << "9)Bir deger altina dusen urunlerin listesi" << endl;
	cout << "hangi islemi yapmak istersiniz : (cikmak icin 0 a basiniz)"<<endl;
	cin >> islem;
	if (islem == 1)
		YeniUrun(SUrunlst);
	else if (islem == 2)
		FiyatGuncelleme(SUrunlst);
	else if (islem == 3)
		StokGuncelleme(SUrunlst);
	else if (islem == 4)
		UrunSilme(SUrunlst);
	else if (islem == 5)
		Satis(SUrunlst, Satislst);
	else if (islem == 6)
		UrunList(SUrunlst);
	else if (islem == 7)
		StokUrunList(SUrunlst);
	else if (islem == 8)
		SatUrunList(Satislst);
	else if (islem == 9)
		AltUrunList(SUrunlst);
}