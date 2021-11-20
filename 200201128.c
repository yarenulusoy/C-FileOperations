//190201069 ESRA DINC  200201128 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct kayit
{
    int ogrNo;
    int dersKodu;
    int puan;
};
struct kayit ogrenci;

struct index
{
    int ogrNo;
    int adres;
};
struct index indx;

char *dataFileName = "veri.bin";
char *indexFileName = "index.txt";
FILE *file;
FILE *file_gecici;

void islem(int sec);
void kayitEkle(void);
void kayitGuncelle(void);
void kayitSil(void);
void kayitBul(void);
void veriDosyasiniGoster(void);
void indeksDosyasiOlustur();
void indeksDosyasiniGoster(void);
void indeksDosyasiniSil(void);

void menu()
{
    int sec;
    while (1)
    {
        printf("\n--- MENU ---\n1-Kayit Ekle\n2-Kayit Guncelle\n3-Kayit Sil\n4-Kayit Bul\n5-Veri Dosyasindaki Tum Kayitlari Listele\n6-Index Dosyasindaki Tum Kayitlari Listele\n7-Index Dosyasini Sil\n8-Cikis");

        printf("\n\nYapmak istediginiz islemi seciniz: ");
        fflush(stdin);
        scanf("%d", &sec);
        printf("\n");

        if (sec >= 1 && sec <= 8)
            islem(sec);
        else
            printf("\n\nHATALI SECIM\n\n");
    }
}

int main()
{
    menu();
    return 0;
}

void islem(int sec)
{
    switch (sec)
    {
    case 1:
    	system("cls");
        kayitEkle();
        break;
    
    case 2:
    	system("cls");
        kayitGuncelle();
        break;
    case 3:
    	system("cls");
        kayitSil();
        break;
    case 4:
    	system("cls");
        kayitBul();
        break;
    case 5:
    	system("cls");
    	indeksDosyasiOlustur();
        veriDosyasiniGoster();
        break;
    case 6:
    	system("cls");
        indeksDosyasiniGoster();
        break;
    case 7:
    	system("cls");
        indeksDosyasiniSil();
        break;
    case 8:
        exit(0);
        break;
    default:
        printf("Hatali Secim\n");
    }
}

void kayitEkle()
{
	int gec=0;   
	int satir=0;
    
    file = fopen(dataFileName, "rb");
    while (fread(&ogrenci, sizeof(ogrenci), 1, file)) {	satir++;}
    fclose(file);
    int a = 0;
    int ogrNo[satir];
    int kod[satir];

    file = fopen(dataFileName, "rb");


   	while (fread(&ogrenci, sizeof(ogrenci), 1, file))

    {
        ogrNo[a] = ogrenci.ogrNo;
        kod[a]=ogrenci.dersKodu;
        a++;
    }
    
    fclose(file);
    
    printf("Ogrenci Numarasi: ");
    scanf("%d", &ogrenci.ogrNo);
    
    printf("Ders Kodu : ");
    scanf("%d", &ogrenci.dersKodu);
   
    printf("Puani : ");
    scanf("%d", &ogrenci.puan);
    
    if(ogrenci.puan<=0 || ogrenci.puan>100){
    	printf("Girilen ogrenci notu gecersiz.\nKayit eklenemedi\n");
		gec=1;	
	}
    	
    for(int i=0;i<satir;i++){
   		if(ogrenci.ogrNo==ogrNo[i] && ogrenci.dersKodu==kod[i]){
    	    printf("\nKayit eklenemedi!\n");
    	   	printf("Bu ogrencinin bu derse ait bir notu var.\nLutfen ders kodunu kontrol ediniz.\n\n");
    	   	gec=1;    	   	
		}	   
   }
  	if(gec!=1){
 
  	file = fopen(dataFileName, "a+b");
    fseek(file, 0, SEEK_END);

    if (fwrite(&ogrenci, sizeof(ogrenci), 1, file))
    {
        printf("Kayit Eklendi\n\n");
        
    }
    else
    {
        printf("Kayit Eklenemedi\n\n");
    }


    fclose(file);
    indeksDosyasiOlustur();
  }  

}

void kayitGuncelle()
{
    int alt = 0;
    int sonuc = -1;
    int guncellenen;
    int guncellenenkod;
    int puan;
    int a = 0;
    int satir = 0;
    int ogrNo[satir];
    int adres[50];
    int sayac=0;
     
    file = fopen(indexFileName, "r");
     
        
    printf("Guncellenecek ogrenci numarasi: ");
    scanf("%d", &guncellenen);
        

    if (file == NULL)
    {
        printf("Acilamadi\n");
    }
    else
    {
        while (1)
        {
            fscanf(file, "%d %d", &indx.ogrNo, &indx.adres);
            if (feof(file))
                break;
            ogrNo[a] = indx.ogrNo;
            adres[a] = indx.adres;
            a++;
            satir++;
        }
    }
    fclose(file);
    
    int ust = satir - 1;

    while (alt <= ust)
    {

        int orta = (alt + ust) / 2;

        if (guncellenen == ogrNo[orta])
        {
            sonuc = orta;
            ust = orta - 1;
        }
        else if (guncellenen <ogrNo[orta])
        {
            ust = orta - 1;
        }

        else
        {
            alt = orta + 1;
        }
    }
	file = fopen(dataFileName, "rb");


    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) == ogrNo[sonuc])
        {
            sayac++;
        }
    }
    printf("\n\n");
    fclose(file);
    if(sayac==0){
    	printf("Guncellemek istediginiz ogrenci icin bir kayit bulunamadi.\nLutfen ogrenci numarasini kontrol ediniz.");
	}
	else{
	file = fopen(dataFileName, "rb");
	printf( "%-15s%-10s%10s\n","Ogrenci No", "Ders Kodu", "Puani");

    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) == ogrNo[sonuc])
        {
               printf( "%-15d%-10d%10d\n",
			ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
    }
    printf("\n\n");	
    printf("Guncellemek istediginiz ogrenciye ait %d adet kayit bulundu.\n",sayac);
	printf("Guncellemek istediginiz dersi seciniz:");
    scanf("%d",&guncellenenkod);
    
    printf("Guncellemek istediginiz puani giriniz:");
    scanf("%d",&puan);	
    
    printf("Guncelleme gerceklesti.\n");
	}
	 fclose(file);
   
    
    file = fopen(dataFileName, "rb");
    file_gecici = fopen("gecici.bin", "a+b");

    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
    	 if ((ogrenci.ogrNo == guncellenen) && (ogrenci.dersKodu==guncellenenkod)){
    	 		ogrenci.puan=puan;
		 }
        if (!feof(file)) 
            {fwrite(&ogrenci, sizeof(ogrenci), 1, file_gecici);}       
    }
    printf("\n\n");

    fclose(file);
    fclose(file_gecici);
    remove(dataFileName);  		
    rename("gecici.bin", dataFileName); 	
    
    
    indeksDosyasiOlustur();

}

void kayitSil()
{
	int alt = 0;
    int sonuc = -1;
    int silinen;
    int silinenkod;
    int a = 0;
    int satir = 0;
    int ogrNo[satir];
    int adres[50];
    int sayac=0;
    
    
    file = fopen(indexFileName, "r");
        
    printf("Silinecek ogrenci numarasi: ");
    scanf("%d", &silinen);
        

    if (file == NULL)
    {
        printf("Acilamadi\n");
    }
    else
    {
        while (1)
        {
            fscanf(file, "%d %d", &indx.ogrNo, &indx.adres);
            if (feof(file))
                break;
            ogrNo[a] = indx.ogrNo;
            adres[a] = indx.adres;
            a++;
            satir++;
        }
    }
    fclose(file);
    
    int ust = satir - 1;

    while (alt <= ust)
    {

        int orta = (alt + ust) / 2;

        if (silinen == ogrNo[orta])
        {
            sonuc = orta;
            ust = orta - 1;
        }
        else if (silinen <ogrNo[orta])
        {
            ust = orta - 1;
        }

        else
        {
            alt = orta + 1;
        }
    }
    file = fopen(dataFileName, "rb");

    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) == ogrNo[sonuc])
        {
            sayac++;
        }
    }
    printf("\n\n");
    fclose(file);

    if(sayac==0){
    	printf("Silmek istediginiz ogrenci icin bir kayit bulunamadi.\nLutfen ogrenci numarasini kontrol ediniz.");
	}
	else{
		 file = fopen(dataFileName, "rb");

    printf( "%-15s%-10s%10s\n","Ogrenci No", "Ders Kodu", "Puani");

    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) == ogrNo[sonuc])
        {
            printf( "%-15d%-10d%10d\n",
			ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
    }
		printf("\nSilmek istediginiz ogrenciye ait %d adet kayit bulundu.\n",sayac);
	    printf("Silmek istediginiz dersi seciniz:");
        scanf("%d",&silinenkod);
        printf("Silme gerceklesti.\n");
	}
    fclose(file);
    
    file = fopen(dataFileName, "rb");
    file_gecici = fopen("gecici.bin", "a+b");

    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if (!feof(file)) 
            {
                if ((ogrenci.ogrNo) != silinen || ogrenci.dersKodu!=silinenkod)
                {
                     fwrite(&ogrenci, sizeof(ogrenci), 1, file_gecici);
                 
                }
            }
               
    }
    printf("\n\n");

    fclose(file);
    fclose(file_gecici);
    remove(dataFileName);  		
    rename("gecici.bin", dataFileName); 	
    
    indeksDosyasiOlustur();

}

void kayitBul()
{

    int alt = 0;
    int sonuc = -1;
    int aranan_eleman;
    int a = 0;
    int satir = 0;
    int ogrNo[satir];
    int adres[50];
    file = fopen(indexFileName, "r");

    if (file == NULL)
    {
        printf("Acilamadi\n");
    }
    else
    {
        while (1)
        {

            fscanf(file, "%d %d", &indx.ogrNo, &indx.adres);
            if (feof(file))
                break;
            ogrNo[a] = indx.ogrNo;
            adres[a] = indx.adres;
            a++;
            satir++;
        }
    }
    fclose(file);
    
    int ust = satir - 1;

    printf("Aradiginiz ogrencinin numarasini giriniz :");
    scanf("%d", &aranan_eleman);

    while (alt <= ust)
    {

        int orta = (alt + ust) / 2;

        if (aranan_eleman == ogrNo[orta])
        {
            sonuc = orta;
            ust = orta - 1;
        }
        else if (aranan_eleman <ogrNo[orta])
        {
            ust = orta - 1;
        }

        else
        {
            alt = orta + 1;
        }
    }
    printf("\n\n");
    if(sonuc>=0){
    	   file = fopen(dataFileName, "rb");
     printf( "%-15s%-10s%10s\n","Ogrenci No", "Ders Kodu", "Puani");

    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) == ogrNo[sonuc])
        {
           printf( "%-15d%-10d%10d\n",ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
        }
    }
    fclose(file);
    printf("\n");

    int gecis=0;	   
	file = fopen(dataFileName, "rb");
    printf("Aradiginiz ogrenciye ait ilk kayit:\n"); 	   
    printf( "%-15s%-10s%10s\n","Ogrenci No", "Ders Kodu", "Puani");
    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) == ogrNo[sonuc])
        {
           printf( "%-15d%-10d%10d\n", ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
           gecis++;
		}
        if(gecis>0){
        	break;
		}
    }
    printf("\n\n");

    fclose(file);


	}
	else{
		printf("Aradiginiz numarada bir ogrenci kaydi bulunamadi.\n");
		printf("Lutfen ogrenci numarasini kontrol ediniz.\n");
	}
 
}

void veriDosyasiniGoster()

{
    file = fopen(dataFileName, "rb");

    printf( "%-15s%-10s%10s\n","Ogrenci No", "Ders Kodu", "Puani");
    int sat=0;
    while (fread(&ogrenci, sizeof(ogrenci), 1, file))
    {
        if ((ogrenci.ogrNo) != 0)
        {
            printf( "%-15d%-10d%10d\n",
			ogrenci.ogrNo,ogrenci.dersKodu,ogrenci.puan);
            sat++;
        }
        else
            printf("\n\nKayit Bulunamadi");
    }
    printf("\n\n");
    fclose(file);
}

void indeksDosyasiOlustur()
{
    int a = 0;
    int sayi = 0;

    file = fopen(dataFileName, "rb");
    FILE *file_index;
    int k = 0;
    while (fread(&ogrenci, sizeof(ogrenci), 1, file)) {sayi++;}

    fclose(file);
    int ogrNo[sayi];
    int *adres[sayi];
    int no[sayi];
    int gecici;
    int *gecici2[1];

    file = fopen(dataFileName, "rb");
    while (fread(&ogrenci, sizeof(ogrenci), 1, file))

    {
        ogrNo[a] = ogrenci.ogrNo;
        adres[a] = &ogrNo[a];
        a++;
    }
    fclose(file);

    for (int i = 0; i < sayi; i++)
    {
        for (int j = 1; j < sayi; j++)
        {
            if (ogrNo[j - 1] > ogrNo[j])
            {
                gecici = ogrNo[j];
                ogrNo[j] = ogrNo[j - 1];
                ogrNo[j - 1] = gecici;

                gecici2[0] = adres[j];
                adres[j] = adres[j - 1];
                adres[j - 1] = gecici2[0];
            }
        }
    }


    file = fopen(dataFileName, "rb");
    file_index = fopen(indexFileName, "w+");
    int b = 0;
    while (fread(&ogrenci, sizeof(ogrenci), 1, file))

    {
        fprintf(file_index, "%d %u\n", ogrNo[b], adres[b]);
        b++;
    }
    fclose(file);
    fclose(file_index);
}
void indeksDosyasiniGoster()
{

    file = fopen(indexFileName, "r");
    
     printf( "%-15s%-10s%\n","Ogrenci No", "Adres");

    if (file == NULL)
    {
        printf("Acilamadi\n");
    }
    else
    {
        while (1)
        {

            fscanf(file, "%d %d", &indx.ogrNo, &indx.adres);
            if (feof(file))
                break;
            printf("%-15d%-10d% \n", indx.ogrNo, indx.adres);
        }
    }
    fclose(file);
}

void indeksDosyasiniSil()
{
    int sil = remove(indexFileName);

    if (sil == 0)
    {
        fprintf(stdout, "Index dosyasi silindi.\n");
    }
    else
    {
        fprintf(stderr, "Index dosyasi silinemedi.\n");
    }
}
