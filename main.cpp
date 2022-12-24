/*
Mustafa Cenk Aydin  - 402523
Sumeyra Seyma Tutar - 394781
Mehmet Kocadag     - 394822
*/


#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <conio.h>
#include <cstring>
#include <unistd.h> //for sleep


using namespace std;

class zaman {
public:
    int saat;
    int dakika;
};

class clothesinfo
{
        private:
            int q;
                long long price;
            char size[50];
                char name[50],colour[50];
        public:
            void add();
            void viewallclothes();
            void find(char *);
            void cut(char *);
            void update(char *);
            void buy();
}cloth;

class kiyafet {
    char kategori;
    int kiyafet_adi;
    double fiyat;
    char boyut;
    char renk;
};

class kisi {
    char ad_soyad;
    char telno;
};

class siparis : public kiyafet {
    int siparis_no;
    double siparis_fiyat;
    zaman siparis_baslangic;
    zaman siparis_ulasim;
};

class kullanici : public kisi {
    char kullanici_adi;
    char eposta;
    char adres_ilce;
    char sifre;
    char indirim_kodu;
    char dtarihi;
};

class yonetici : public kisi {
    char sifre;
};

class kurye : public kisi {
    zaman dagitim_bitisler;
    int siparis_numaralari;
};

class uye_kaydi {
public:
    vector<string> v_vasif;
    vector<string> v_ad_soyadlar;
    vector<string> v_telnolar;
    vector<string> v_kullanici_adlari;
    vector<string> v_epostalar;
    vector<string> v_adres_ilceler;
    vector<string> v_sifreler;
    vector<string> v_dtarihler;
    vector<string> v_indirim_kodlari;
    void veri_cekme();
    void kullanici_okuma();
    void kullanici_ekleme();
    void sifre_degistir();
};

vector<string> v_sikayetler;

void ana_menu(uye_kaydi obj);
void sisteme_giris(uye_kaydi obj);
void yonetici_menusu(uye_kaydi obj);
void musteri_menusu(uye_kaydi obj);
void sikayet();
void fatura();
void siparis_takip();
void sikayet_oku();
void kiyafet_listeleme();
void kiyafet_yonetim();


int main()
{
    uye_kaydi obj;
    obj.veri_cekme();
    ana_menu(obj);
}

void uye_kaydi::veri_cekme() {
    ifstream kullanicilar;
    kullanicilar.open("kullanicilar.txt");
    if (!kullanicilar.is_open()) {
        cout << "Txt dosyasi acilamadi!";
        exit(1);
    }
    string line;
    string temp;
    while (!kullanicilar.eof()) {
        getline(kullanicilar, temp, '~');
        v_vasif.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_ad_soyadlar.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_telnolar.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_kullanici_adlari.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_epostalar.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_adres_ilceler.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_sifreler.push_back(temp);

        getline(kullanicilar, temp, '~');
        v_dtarihler.push_back(temp);

        getline(kullanicilar, temp, '\n');
        v_indirim_kodlari.push_back(temp);
    }
}

void uye_kaydi::kullanici_okuma() {
    int i = 0;
    int vector_uzunluk = v_ad_soyadlar.size();
    while (i < vector_uzunluk) {
        if (v_vasif[i] == "musteri") {
            cout << endl << i << ". Kisi Bilgileri: " << endl;
            cout << "Ad-Soyad        : " << v_ad_soyadlar[i] << endl;
            cout << "Telefon Numarasi: " << v_telnolar[i] << endl;
            cout << "Kullanici adi   : " << v_kullanici_adlari[i] << endl;
            cout << "E-posta         : " << v_epostalar[i] << endl;
            cout << "Adres           : " << v_adres_ilceler[i] << endl;
            cout << "Sifre           : " << v_sifreler[i] << endl;
            cout << "Dogum tarihi    : " << v_dtarihler[i] << endl;
            cout << "Indirim kodu    : " << v_indirim_kodlari[i] << endl;
        }
        i = i + 1;
    }
}

bool bul(string metin, string kelime) // e mail control
{

    for (int i = 0; i < metin.size() - kelime.size() + 1; ++i)
    {

        int check = 0;
        for (int c = 0; c < kelime.size(); ++c)
        {
            if (metin[i + c] == kelime[c])
            {
                check++;
            }
        }

        if (check == kelime.size())
        {
            return true;
        }

    }
    return false;
}

void uye_kaydi::kullanici_ekleme() {
    ofstream kullanicilar;
    kullanicilar.open("kullanicilar.txt", ios::app);
    if (!kullanicilar.is_open()) {
        cout << "Txt dosyasi acilamadi!";
        exit(1);
    }
    string temp;
    bool kucuk_var = false, buyuk_var = false, sayi_var = false, ozel_var = false;
    string normal = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
    string sayilar = "0123456789";
    string slash = "/";
    string dummy;
    getline(cin, dummy);

    kullanicilar << '\n' << "musteri" << '~';

    cout << "Ad Soyad giriniz : ";
    getline(cin, temp);
    kullanicilar << temp << '~';
    v_ad_soyadlar.push_back(temp);

telefonjump:
    cout << "Telefon numarasi giriniz(0 ile baslayan toplam 11 haneli): ";
    getline(cin, temp);
    if (temp.length() != 11) {
        cout << "Lutfen 11 haneli sayi giriniz!" << endl;
        goto telefonjump;
    }
    kullanicilar << temp << '~';
    v_telnolar.push_back(temp);

    cout << "Kullanici adi giriniz: ";
    getline(cin, temp);
    kullanicilar << temp << '~';
    v_kullanici_adlari.push_back(temp);

epostajump:
    cout << "E-posta giriniz: ";
    string kelime = "@";
    string kelime2 = ".com";
    getline(cin, temp);
    if (!bul(temp, kelime))
    {
        cout << "@ isareti kullanmayi unuttun." << endl;
        goto epostajump;
    }
    else if (!bul(temp, kelime2)){
        cout << ".com uzantili olmalidir." << endl;
        goto epostajump;
    }
    kullanicilar << temp << '~';
    v_epostalar.push_back(temp);

    cout << "Adres giriniz: ";
    getline(cin, temp);
    kullanicilar << temp << '~';
    v_adres_ilceler.push_back(temp);

sifrejump:
    cout << "Sifre giriniz(Buyuk ve kucuk harfler, sayilar ve sembollerden olusan en az 8 karakterli sifre): ";
    string pass = "";
    char ch;
    ch = _getch();
    while (ch != 13) {
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl;

    for (int i = 0; i < pass.length(); i++) {
        if (islower(pass[i]))
            kucuk_var = true;
        if (isupper(pass[i]))
            buyuk_var = true;
        if (isdigit(pass[i]))
            sayi_var = true;
        size_t ozel = pass.find_first_not_of(normal);
        if (ozel != string::npos)
            ozel_var = true;
    }
    if ((kucuk_var == true) && (buyuk_var == true) && (sayi_var == true) && (ozel_var == true) && ((pass.length() >= 8))) {
        cout << "Sifreniz basariyla kaydedildi. Guclu sifre." << endl;
        kullanicilar << pass << '~';
        v_sifreler.push_back(pass);
    }
    else {
        cout << "Daha guclu bir sifre belirleyiniz." << endl;
        goto sifrejump;
    }

dogumjump:
    int gun, ay, yil;

    cout << "Dogum yilinizi giriniz(1900-2022): ";
    cin >> yil;
    if (yil < 1900 || yil > 2022)
        goto dogumjump;

    cout << "Dogum ayinizi giriniz(1-12): ";
    cin >> ay;
    if (ay < 1 || ay > 12)
        goto dogumjump;

    cout << "Dogum gununuzu giriniz(1-31): ";
    cin >> gun;
    if (gun < 1 || gun > 31)
        goto dogumjump;

    temp = to_string(gun) + '/' + to_string(ay) + '/' + to_string(yil);
    kullanicilar << temp;
    v_dtarihler.push_back(temp);

    //cout << "Indirim kodu giriniz: ";
    //getline(cin, temp);
    kullanicilar << '~';
    v_indirim_kodlari.push_back("0");
}

void ana_menu(uye_kaydi obj) {
    int secim = 0;
    cout << endl << endl << "***************************************************************" << endl;
    cout << "**************** KIYAFET SEPETINE HOSGELDINIZ *****************" << endl;
    cout << "***************************************************************" << endl << endl;
    cout << "[1] Sisteme Giris" << endl;
    cout << "[2] Uye Kaydi" << endl;
    cout << "[0] Cikis" << endl << endl;
    cout << "***************************************************************" << endl;
    cout << "***************************************************************" << endl << endl << endl;
    cin >> secim;
    switch (secim)
    {
    case 1:
        sisteme_giris(obj);
        break;
    case 2:
        obj.kullanici_ekleme();
        ana_menu(obj);
        break;
    case 0:
        cout << endl << "***************************************************************" << endl;
        cout << "************************* IYI GUNLER **************************" << endl;
        cout << "***************************************************************" << endl << endl;
        break;
    default:
        cout << endl << "Gecersiz islem girildi." << endl;
        cout << "Tekrar deneyiniz.";
        ana_menu(obj);
        break;
    }
}

void sisteme_giris(uye_kaydi obj) {
    int secim = 0;
    string kullanici_adi;
    string sifre;
    bool k_kontrol = false;
    bool s_kontrol = false;
    int sayac = obj.v_ad_soyadlar.size();
    int dongu = 0;
    int sifre_sayac = 0;
    cout << endl << "***************************************************************" << endl;
    cout << "[1] Yonetici Girisi" << endl;
    cout << "[2] Musteri Girisi" << endl;
    cout << "***************************************************************" << endl << endl << endl;
    cin >> secim;
    switch (secim)
    {
    case 1:

        cout << "Kullanici adi giriniz: ";
        cin >> kullanici_adi;
        while (k_kontrol == false)
        {
            if (dongu >= sayac) {
                cout << "Kullanici adi bulunamadi tekrar deneyiniz." << endl;
                sisteme_giris(obj);
            }
            if (obj.v_kullanici_adlari[dongu] == kullanici_adi) {
                cout << "buldu" << endl;
                if (obj.v_vasif[dongu] == "yonetici") {
                    k_kontrol = true;
                }
                else {
                    cout << "Kullanici yonetici degil!!!" << endl;
                    sisteme_giris(obj);
                }
            }
            dongu = dongu + 1;
        }
        while (s_kontrol == false)
        {
            if (sifre_sayac >= 5) {
                cout << "Sifre deneme limitine ulasildi!!" << endl;
                sisteme_giris(obj);
            }
            cout << "Sifre giriniz: ";
            cin >> sifre;
            sifre_sayac = sifre_sayac + 1;
            if (sifre == obj.v_sifreler[dongu - 1]) {
                s_kontrol = true;
            }
        }
        if (k_kontrol == true && s_kontrol == true) {
            yonetici_menusu(obj);
        }
        break;
    case 2:

        cout << "Kullanici adi giriniz: ";
        cin >> kullanici_adi;
        while (k_kontrol == false)
        {
            if (dongu >= sayac) {
                cout << "Kullanici adi bulunamadi tekrar deneyiniz." << endl;
                sisteme_giris(obj);
            }
            if (obj.v_kullanici_adlari[dongu] == kullanici_adi) {
                if (obj.v_vasif[dongu] == "musteri") {
                    k_kontrol = true;
                }
                else {
                    cout << "Kullanici musteri degil!!!" << endl;
                    sisteme_giris(obj);
                }
            }
            dongu = dongu + 1;
        }
        while (s_kontrol == false)
        {
            if (sifre_sayac >= 5) {
                cout << "Sifre deneme limitine ulasildi!!" << endl;
                sisteme_giris(obj);
            }
            cout << "Sifre giriniz: ";
            cin >> sifre;
            sifre_sayac = sifre_sayac + 1;
            if (sifre == obj.v_sifreler[dongu - 1]) {
                s_kontrol = true;
            }
        }

        musteri_menusu(obj);
        break;
    default:
        cout << endl << "Gecersiz islem girildi." << endl;
        cout << "Tekrar deneyiniz.";
        sisteme_giris(obj);
        break;
    }
}

void yonetici_menusu(uye_kaydi obj) {
    int secim = 0;
    cout << endl << "***************************************************************" << endl;
    cout << "[1] Urun Yonetim Merkezi" << endl;
    cout << "[2] Sisteme Kurye Ekleme" << endl;
    cout << "[3] Sikayetleri ve Onerileri Goruntule" << endl;
    cout << "[4] Kullaniciya Indirim Kodu Tanimlama" << endl;
    cout << "[5] Yapilan Siparislerin Faturalarini Goruntule" << endl;
    cout << "[6] Butun Kullanicilari Listele" << endl;
    cout << "[0] Ana Menu" << endl;
    cout << "***************************************************************" << endl << endl << endl;
    cin >> secim;
    string indirim_kullanici;
    int indirim_dongu = 0;
    int indirim_sayac = obj.v_kullanici_adlari.size();
    bool indirim_kontrol = false;
    string indirim_kodu;
    switch (secim)
    {
    case 1:
        cout << "Urun girisi islemi";
        kiyafet_yonetim();
        yonetici_menusu(obj);
        break;
    case 2:
        cout << "Kurye ekleme islemi";
        yonetici_menusu(obj);
        break;
    case 3:
        cout << "Sikayet/oneri okuma islemi";
        sikayet_oku();
        yonetici_menusu(obj);
        break;
    case 4:
        cout << "Kullaniciya indirim kodu tanimlama islemi";
        cout << "Indirim kodu tanimlamak istediginiz kullanicinin kullanici adini giriniz: " << endl;
        cin >> indirim_kullanici;
        while (indirim_kontrol == false)
        {
            if (indirim_dongu >= indirim_sayac) {
                cout << "Kullanici adi bulunamadi tekrar deneyiniz." << endl;
                yonetici_menusu(obj);
            }
            if (obj.v_kullanici_adlari[indirim_dongu] == indirim_kullanici) {
                cout << "Kullanici bulundu." << endl;
                cout << "Indirim kodunu giriniz: " << endl;
                cin >> indirim_kodu;
                obj.v_indirim_kodlari[indirim_dongu] = indirim_dongu;
                indirim_kontrol = true;
            }
            indirim_dongu = indirim_dongu + 1;
        }
        yonetici_menusu(obj);
        break;
    case 5:
        cout << "Yapilan siparislerin faturalarini goruntuleme islemi";
        fatura();
        yonetici_menusu(obj);
        break;
    case 6:
        obj.kullanici_okuma();
        cout << endl;
        yonetici_menusu(obj);
        break;
    case 0:
        ana_menu(obj);
        break;
    default:
        cout << endl << "Gecersiz islem girildi." << endl;
        cout << "Tekrar deneyiniz.";
        yonetici_menusu(obj);
        break;
    }
}
int microToSeconds = 1000000;
double delay = 3 * microToSeconds;     //3 saniye
void musteri_menusu(uye_kaydi obj) {
    int secim = 0;
    cout << endl << "***************************************************************" << endl;
    cout << "[1] Kiyafet Kategorilerinin Gosterimi ve Urun Secimi" << endl;
    cout << "[2] Siparis Takip" << endl;
    cout << "[3] Sikayet/Oneriler" << endl;
    cout << "[4] Sifre Degistir" << endl;
    cout << "[0] Geri Don" << endl;
    cout << "***************************************************************" << endl << endl << endl;
    cin >> secim;
    switch (secim)
    {
    case 1:

        cout << "Urun secimi islemi" << endl;
        kiyafet_listeleme();

        musteri_menusu(obj);
        break;
    case 2:
        cout << "Siparis takip islemi" << endl;
        siparis_takip();
        musteri_menusu(obj);
        break;
    case 3:
        cout << "Sikayet/oneri yazma islemi" << endl;
        sikayet();
        musteri_menusu(obj);
        break;
    case 4:
        cout << "Sifre degistirme islemi" << endl;
        obj.sifre_degistir();
        musteri_menusu(obj);
        break;
    case 0:
        cout << "Geri donme islemi" << endl;
        ana_menu(obj);
        break;
    default:
        cout << endl << "Gecersiz islem girildi." << endl;
        cout << "Tekrar deneyiniz." << endl;
        musteri_menusu(obj);
        break;
    }
}


void sikayet() {
    fstream sikayet("oneri.txt", ios::app);
    string sikayetOneri;
    string temp;
    cout << "Sikayet veya onerinizi giriniz." << endl;
    cin >> sikayetOneri;
    getline(cin, temp);
    sikayet << temp << sikayetOneri;

    v_sikayetler.push_back(temp);
}

void siparis_takip() {
    int ortahisar = 35;
    int akcaabat = 50;
    int vakfikebir = 90;
    int besikduzu = 110;
    int yomra = 55;
    int arsin = 70;
    int arakli = 100;

}

void kurye_ekle() {

}

void sikayet_oku() {
    ifstream read("oneri.txt");
    string str, str1;

    if (read.is_open())
    {
        getline(read, str);
        while (read)
        {
            str1 += str;
            getline(read, str);
        }
        cout << str1 << endl;
    }
    else
        cout << "\nDosya acilamadi\n";
}

void uye_kaydi::sifre_degistir() {
sifrejump:
    ofstream kullanicilar;
    kullanicilar.open("kullanicilar.txt", ios::app);
    if (!kullanicilar.is_open()) {
        cout << "Txt dosyasi acilamadi!";
        exit(1);
    }
    string temp;
    string dummy;
    bool kucuk_var = false, buyuk_var = false, sayi_var = false, ozel_var = false;
    string normal = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
    string sayilar = "0123456789";
    string slash = "/";
    getline(cin, dummy);

    cout << "Yeni sifrenizi giriniz. (Buyuk ve kucuk harfler, sayilar ve sembollerden olusan en az 8 karakterli sifre): ";
    string pass = "";
    char ch;
    ch = _getch();
    while (ch != 13) {
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl;

    for (int i = 0; i < pass.length(); i++) {
        if (islower(pass[i]))
            kucuk_var = true;
        if (isupper(pass[i]))
            buyuk_var = true;
        if (isdigit(pass[i]))
            sayi_var = true;
        size_t ozel = pass.find_first_not_of(normal);
        if (ozel != string::npos)
            ozel_var = true;
    }
    if ((kucuk_var == true) && (buyuk_var == true) && (sayi_var == true) && (ozel_var == true) && ((pass.length() >= 8))) {
        cout << "Sifreniz basariyla degistirildi. Guclu sifre." << endl;
    }
    else {
        cout << "Daha guclu bir sifre belirleyiniz." << endl;
        goto sifrejump;
    }

    v_sifreler.pop_back();
    v_sifreler.push_back(pass);
}
ofstream fout;
ifstream fin;
fstream file;

void clothesinfo::add()
{
        cout<<"                 Eklemek istediginiz giysinin ayrintilarini girin:\n\n";
        cout<<"                 Type(Pantolon/Elbise/Gomlek/Etek/Ayakkabi/Tisort): ";
        cin>>name;
        cout<<"\n               Size(XS/S/M/L/XL/XXL): ";
        cin>>size;
        cout<<"\n               Renk: ";
        cin>>colour;
        cout<<"\n               Miktar: ";
        cin>>q;
        cout<<"\n               Fiyat: ";
        cin>>price;
        fout.write((char*)this,sizeof(*this));
        cout<<"\n               Kiyafet basariyla eklendi!";
        fout.close();
}

void clothesinfo::buy()
{
        cout <<"Satin almak istediginiz giysinin ayrintilarini giriniz:\n\n";
        cout << "[1] Elbise" << endl;
        cout << "[2] Tisort" << endl;
        cout << "[3] Pantolon" << endl;
        cout << "[4] Gomlek" << endl;
        cout << "[5] Etek" << endl;
        cout << "[6] Ayakkabi" << endl;
        cout<<"                 Type(Pantolon/Elbise/Gomlek/Etek/Ayakkabi/Tisort): ";
        cin>>name;
        cout<<"\n               Size(XS/S/M/L/XL/XXL): ";
        cin>>size;
        cout<<"\n               Renk: ";
        cin>>colour;
        cout<<"\n               Miktar: ";
        cin>>q;
        cout<<"\n               Fiyat: ";
        cin>>price;
        fout.write((char*)this,sizeof(*this));
        cout<<"\n               Kiyafet basariyla alindi!";
        fout.close();
}

void clothesinfo::viewallclothes()
{
        fin.read((char*)&cloth,sizeof(cloth));
        while(!fin.eof())
        {

                cout<<"\n   "<<name;
                int k=strlen(name);
                int n=k-5;
            for (int i=0;i<22-n;i++)
            {
                cout<<" ";
            }
                cout<<size;
                k=strlen(size);
            n=k-5;
                for (int i=0;i<18-n;i++)
            {
                cout<<" ";
            }
                cout<<colour;
                k=strlen(colour);
            n=k-5;
                for (int i=0;i<21-n;i++)
            {
                cout<<" ";
            }
                cout<<q;
                int j=0;
                while(q>0)
                {
                        int r=q%10;
                        j++;
                        q=q/10;
                        }
                        if(j>3)
            {   n=j-5;    }
            else
            {   n=5-j;   }
                for (int i=0;i<27-n;i++)
            {
                cout<<" ";
            }
                cout<<price;

                fin.read((char*)&cloth,sizeof(cloth));
                }
        fin.close();
}

void clothesinfo::find(char *t)
{
        cout<<"\n\n        Aramak istediginiz kiyafetin ismini giriniz.\n\n";
    int counter=0;
    fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
                if(!strcmp(t,name))
            {
                counter++;
                cout<<"        Type:"<<name<<"            Size:"<<size<<"            Colour:";
                                cout<<colour<<"            Quantity:"<<q<<"            Price):"<<price<<endl;
                        }
            fin.read((char*)this,sizeof(*this));
            }
            if(counter==0)
            {
                cout<<"        Bulunamadi!";
                }
        fin.close();
}

void clothesinfo::cut(char *t)
{
        int counter=0;
        fout.open("NEWCLOTH.dat",ios::out);
    fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
                if(strcmp(t,name))
            {
                fout.write((char*)this,sizeof(*this));
                        }
                        else
                        {
                                counter++;
                        }
            fin.read((char*)this,sizeof(*this));
            }
            if(counter==0)
            {
                cout<<"\n        BULUNAMADI!";
                }
                else
                    cout<<"\n        Kiyafet basariyla silindi!";
        fin.close();
        fout.close();
        remove("CLOTH.dat");
        rename("NEWCLOTH.dat","CLOTH.dat");
}

void clothesinfo::update(char *t)
{
        cout<<"        Kiyafetlerin ayrintilarini degistirme!\n\n";
        int counter=0;
    file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
                if(!strcmp(t,name))
            {
                counter++;
                cout<<"        Name:";
                cin>>name;
                cout<<"        Size(XS/S/M/L/XL/XXL):";
                cin>>size;
                cout<<"        Colour:";
                cin>>colour;
                cout<<"        Quantity:";
                cin>>q;
                cout<<"        Price:";
                cin>>price;
                file.seekp(file.tellp()-sizeof(*this));
                file.write((char*)this,sizeof(*this));
                        }
            file.read((char*)this,sizeof(*this));
            }
            if(counter==0)
            {
                cout<<"        BULUNAMADI!";
                }
                else
                    cout<<"\n        Basariyla guncellendi!";
        file.close();
}

void kiyafet_listeleme(){
main:
        cout<<"\n               Kiyafet Listeleme Merkezi :) \n";
        cout<<"                 =====================================\n\n\n\n";
        cout<<"                 [1] Tum Kiyafetleri Listele\n\n";
        cout<<"                 [2] Kiyafet Ara\n\n";
        cout<<"                 [3] Kiyafet Al\n\n";
        cout<<"                 [4] Satin Alinan Kiyafetleri Listele\n\n";
        cout<<"                 [0] Cikis yap\n\n";
        cout<<"                 Lutfen Gerekli Secenegi Giriniz.: ";
        int c;
        cin>>c;
        switch(c)
        {
                case 1:
                        system("cls");
                        cout<<"\n                                                   TUM KIYAFETLER\n";
                        cout<<"                                                   ===========";
                        cout<<"\n\n\n\n";
                        fin.open("CLOTH.dat",ios::in);
                        if(!fin)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
            }
            else
            {
                    cout<<"                Name";
                    cout<<"                Size";
                    cout<<"                Colour";
                    cout<<"                Quantity";
                    cout<<"                Price\n";
                    cout<<"  ------------------------------------------------------";
                    cout<<"-----------------------------------------------------------";

                cloth.viewallclothes();
                        }
                        getch();
                        goto main;
                        break;

find:
                case 2:
                        char namee[50],r;
                        system("cls");
                        cout<<"\n                                            KIYAFET ARA\n";
                        cout<<"                                              ============";
                        cout<<"\n\n\n\n";
                        cout<<"        Bulmak istedigin kiyafetin adi: ";
                        cin>>namee;
                        fin.open("CLOTH.dat");
                        if(!fin)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
                goto main;
            }
            else
            {
                cloth.find(namee);
            }
                getch();
                cout<<"\n        Daha fazla kiyafet aramak istiyor musun (y/n)?";
                cin>>r;
                    if((r=='Y')||(r=='y'))
                    {
                        goto find;
                        }
                        goto main;
                        break;
add:
                case 3:
                    system("cls");
                    char m;
                    cout<<"\n                                   KIYAFET SATIN AL\n";
                    cout<<"                                     ============\n\n\n\n";
                    fout.open("BUYCLOTH.dat",ios::app);
                    cloth.buy();
                    getch();
                    cout<<"          Daha fazla kiyafet almak istiyor musun? (y/n)";
                    cin>>m;
                    if((m=='Y')||(m=='y'))
                    {
                        goto add;
                        }
                        goto main;
                        break;

                case 4:
                        system("cls");
                        cout<<"\n                                                   SATIN ALINAN KIYAFETLER\n";
                        cout<<"                                                   ===========";
                        cout<<"\n\n\n\n";
                        fin.open("BUYCLOTH.dat",ios::in);
                        if(!fin)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
            }
            else
            {
                    cout<<"                Name";
                    cout<<"                Size";
                    cout<<"                Colour";
                    cout<<"                Quantity";
                    cout<<"                Price\n";
                    cout<<"  ------------------------------------------------------";
                    cout<<"-----------------------------------------------------------";

                cloth.viewallclothes();
                        }
                        getch();
                        goto main;
                        break;

exit:
                case 0:
                        system("cls");
            cout<<"\n\n\n Cikmak istedigine emin misin(y/n)?";
            char yn;
            cin>>yn;
            if((yn=='Y')||(yn=='y'))
            {
                cout << "Urununuzun faturasi gosteriliyor..." << endl;
                usleep(delay);
                fatura();
                system("cls");
                cout<<"\n\n\n\n\n\n\n\n                     ";
                            cout<<"******************************* TESEKKURLER *******************************";
                getch();
                exit(0);
            }
            else if((yn=='N')||(yn=='n'))
                goto main;
            else
            {
               cout<<"Evet icin Y veya y, Hayir icin N veya n tuslarini kullaniniz.(y/n)";
               goto exit;
            }

                default:
                        cout<<"\n\n           Yanlis secim, tekrar deneyiniz!!!";
                        getch();
                        goto main;
        }
}

void fatura() {
    cout << "***** Faturaniz listeleniyor. *****" << endl << endl << endl;
    fin.open("BUYCLOTH.dat",ios::in);
                        if(!fin)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
            }
            else
            {
                    time_t now = time(0);
                    tm* localtm = localtime(&now);
                    int num;
                    srand(time(0));
                    num = rand() % 10 + 1;
                    cout<<"                Name";
                    cout<<"                Size";
                    cout<<"                Colour";
                    cout<<"                Quantity";
                    cout<<"                Price\n";
                    cout<<"  ------------------------------------------------------";
                    cout<<"-----------------------------------------------------------";
                    cout<<"\n\n\n";
                cloth.viewallclothes();
                    cout << "Siparis saati -> " << asctime(localtm) << endl;
                    cout << "Fiyat bilgisi -> " << num << "$";
            }
            getch();

}

void kiyafet_yonetim(){
    main:
        system("cls");
        cout<<"\n               Giyim Yonetim Sistemine Hosgeldiniz!\n";
        cout<<"                 =====================================\n\n\n";
        cout<<"                 [1] Tum Kiyafetleri Listele\n\n";
        cout<<"                 [2] Kiyafet Ekle\n\n";
        cout<<"                 [3] Kiyafet Duzenle\n\n";
        cout<<"                 [4] Kiyafet Sil\n\n";
        cout<<"                 [5] Kiyafet Ara\n\n";
        cout<<"                 [0] Cikis Yap\n\n";
        cout<<"                 Girmek istediginiz menuyu seciniz: ";
        int c;
        cin>>c;
        switch(c)
        {
                case 1:
                        system("cls");
                        cout<<"\n                                                   TUM KIYAFETLER\n";
                        cout<<"                                                   ===========";
                        cout<<"\n\n\n\n";
                        fin.open("CLOTH.dat",ios::in);
                        if(!fin)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
            }
            else
            {
                    cout<<"                Name";
                    cout<<"                Size";
                    cout<<"                Colour";
                    cout<<"                Quantity";
                    cout<<"                Price\n";
                    cout<<"  ------------------------------------------------------";
                    cout<<"-----------------------------------------------------------";

                cloth.viewallclothes();
                        }
                        getch();
                        goto main;
                        break;
add:
                case 2:
                        system("cls");
                        char m;
                        cout<<"\n                                   KIYAFET EKLEME\n";
                        cout<<"                                     ============\n\n\n\n";
                    fout.open("CLOTH.dat",ios::app);
                    cloth.add();
                    getch();
                    cout<<"          Daha fazla kiyafet eklemek istiyor musun? (y/n)";
                    cin>>m;
                    if((m=='Y')||(m=='y'))
                    {
                        goto add;
                        }
                        goto main;
                        break;
edit:
                case 3:
                        char b[50],z;
                        system("cls");
                        cout<<"                                     \nKIYAFET GUNCELLEME\n";
                        cout<<"                                     =============\n\n\n\n";
                        cout<<" Guncellemek istedigin kiyafetin ismi:";
                        cin>>b;
                        cout<<"\n\n";
                        file.open("CLOTH.dat",ios::in|ios::out|ios::ate);
                        file.seekg(0);
                        if(!file)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
                goto main;
            }
            else
            {
                cloth.update(b);
                        }
                        getch();
                    cout<<"          Daha fazla kiyafet guncellemek istiyor musun?(y/n)";
                    cin>>z;
                    if((z=='Y')||(z=='y'))
                    {
                        goto edit;
                        }
                        goto main;
                        break;

remove:
                case 4:
                        char namme[50],l;
                        system("cls");
                        cout<<"\n                                           KIYAFET SILME\n";
                        cout<<"                                             ===============\n\n\n\n";
                        cout<<"    Silmek istediginiz kiyafetin adi:";
                        cin>>namme;
                        fin.open("CLOTH.dat");
                        if(!fin)
            {
                cout<<"\n\nDOSYA BULUNAMADI!!!";
                goto main;
            }
            else
            {
                cloth.cut(namme);
                        }
                        getch();
                        cout<<"Daha fazla kiyafet silmek istiyor musunuz?(y/n)";
                    cin>>l;
                    if((l=='Y')||(l=='y'))
                    {
                        goto remove;
                        }
                        goto main;
                        break;
find:
                case 5:
                        char namee[50],r;
                        system("cls");
                        cout<<"\n                                                 KIYAFET BUL\n";
                        cout<<"                                                   ============\n\n\n\n";
                        cout<<"        Bulmak istediginiz kiyafetin adi:";
                        cin>>namee;
                        fin.open("CLOTH.dat");
                        if(!fin)
            {
                cout<<"\n\n DOSYA BULUNAMADI!!!";
                goto main;
            }
            else
            {
                cloth.find(namee);
                        }
                        getch();
                        cout<<"\n Daha fazla kiyafet mi bulmak istiyor musunuz?(y/n)";
                    cin>>r;
                    if((r=='Y')||(r=='y'))
                    {
                        goto find;
                        }
                        goto main;
                        break;
exit:
                case 0:
            system("cls");
            cout<<"\n\n\n           Cikis yapmak istedigine emin misin (y/n)?";
            char yn;
            cin>>yn;
            if((yn=='Y')||(yn=='y'))
            {
                system("cls");
                cout<<"\n\n\n\n\n\n\n\n  ";
                            cout<<"******************************* TESEKKURLER *******************************";
                getch();
                exit(0);
            }
            else if((yn=='N')||(yn=='n'))
                goto main;
            else
            {
               cout<<"Evet icin Y veya y, Hayir icin N veya n tuslarini kullaniniz.(y/n)";
               goto exit;
            }

                default:
                        cout<<"\n\n           Yanlis Secim, Tekrar Deneyiniz!!!";
                        getch();
                        goto main;
        }
}


