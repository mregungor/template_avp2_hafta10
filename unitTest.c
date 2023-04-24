
#include <stdio.h>
#include <time.h>
#include "hafta10.c"

//SYSTEM SPESIFIK TANIMLAMALAR--------------------------------------------------------//
#if defined(__linux__)
// https://linux.die.net/man/3/malloc_usable_size
#include <malloc.h>
size_t MSIZE(const void *p) {
    return malloc_usable_size((void*)p);
}
#elif defined(__APPLE__)
// https://www.unix.com/man-page/osx/3/malloc_size/
#include <malloc/malloc.h>
size_t MSIZE(const void *p) {
    return malloc_size(p);
}
#elif defined(_WIN32)
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/msize
#include <malloc.h>
size_t MSIZE(const void *p) {
    return _msize((void *)p);
}
#else
#error "Unknown System"
#endif
//-----------------------------------------------------------------------------------//

//Lab icin hafta8_fonksiyon prototipleri
void hafta10_fonksiyon1(int **ptrPtr1, int elemanSayisi1);
void hafta10_fonksiyon2(int *ptr1, int **ptrPtr2, int elemanSayisi1, int elemanSayisi2);

/*
Fonksiyon icerisinde yapilacak islemler
    1- hafta10_fonksiyon1 icerisinde isaretci olusturarak elemansayisi1 kadar hafizadan yer ayiriniz.
    2- [8,32] araliginda rastgele tamsayi olusturarak dinamik hafiza olusturarak olusturdugunuz diziye atayiniz.
    3- olusturdugunuz isaretci adres degerini ptrPtr1 kullanarak unitTest icerisindeki ptr1 isaretcisine atayiniz.
    4- hafta10_fonksiyon2 icerisinde isaretci olusturarak elemansayisi2 kadar hafizadan yer ayiriniz. 
    5- ptr1 isaretcisini kullanarak onceden olusturdugunuz dizinin elemanlarini, olusturdugunuz isaretcide tutulan adresle gosterilen alana sirasiyla atayiniz.
    6- Yeni actığınız bu alanda bos kalan dizi elemanlari icin de [48,102] araliginda sayilar atayiniz.
    7- olusturdugunuz isaretci adres degerini ptrPtr2 kullanarak unitTest icerisindeki ptr2 isaretcisine atayiniz.
    Not:    hafizada olusturdugunuz alan unitTest icerisinde islemler bittikten sonra hafizaya geri verilecektir. 
            Fonksiyon icerisinde free fonksiyonunu kullanmayiniz.
*/

int main()
{
    FILE *fp;
    fp = fopen("not.txt", "w");
    int dogrutestsayisi=0;

    //create a .txt file
    if (fp == NULL) {
        printf("File Pointer Null. Dosya acilamadi.\n");
        return -1;
    }

    //Degiskenler
    int *ptr1=NULL; //dizi tutma islemi icin -int isaretci null atanmis
    int *ptr2=NULL; //dizi tutma islemi icin -int isaretci null atanmis
    int elemanSayisi1=10; //ptr1'de tutulacak dizinin eleman sayisi
    int elemanSayisi2=15; //ptr2'de tutulacak dizinin eleman sayisi
    int **ptrPtr1=&ptr1;  //fonksiyona gonderilecek - ptr1 isaretcisinin icerisindeki degeri degistirebilmek icin
    int **ptrPtr2=&ptr2;  //fonksiyona gonderilecek - ptr2 isaretcisinin icerisindeki degeri degistirebilmek icin

    printf("\n");

    //Fonksiyon Cagirma
    hafta10_fonksiyon1(ptrPtr1, elemanSayisi1);
    hafta10_fonksiyon2(ptr1, ptrPtr2, elemanSayisi1, elemanSayisi2);

    printf("\n");
    printf("Fonksiyon Sonrasi Degerler:\n");

    printf("\n");

    //Temel Kontrol
    if(ptr1 == NULL || ptr2 == NULL)
    {
        printf("HATA - FONKSIYON DONUSUNDE PTRler hala NULL Getiriyor.\n");
        //Dosya isaretcisi ile dosya yazma islemi kapatilmasi
        fclose(fp);
        return 0;
    }

    //TEST - 1:
    printf("\nTEST - 1\n");
    printf("Hafizadan yer ayrilma kontrolu: \n");
    printf("sizeof:ptr1: %d \n", (int)(MSIZE(ptr1)) );

    if(MSIZE(ptr1)==elemanSayisi1*sizeof(int))
    {
        printf("DOGRU\n");
        dogrutestsayisi++;
    }else{printf("YANLIS\n");}


    //TEST - 2:
    printf("\nTEST - 2\n");
    printf("Hafizadan yer ayrilma kontrolu: \n");
    printf("sizeof:ptr2: %d \n", (int)(MSIZE(ptr2)) );

    if(MSIZE(ptr2)==elemanSayisi2*sizeof(int))
    {
        printf("DOGRU\n");
        dogrutestsayisi++;
    }else{printf("YANLIS\n");}

    //TEST - 3:
    printf("\nTEST - 3\n");
    printf("dizi 1 atama kontrolu: \n");

    if(MSIZE(ptr1)==elemanSayisi1*sizeof(int) && MSIZE(ptr2)==elemanSayisi2*sizeof(int))
    {
        //Deger araligi kontrolu
        int i;
        int dogruKontrol=1;
        for(i=0;i<elemanSayisi1;i++)
        {
            if(ptr1[i]<8 || ptr1[i]>32)
            {
                dogruKontrol=0; //HATA
            }
        }
        if(dogruKontrol==1)
        {
            printf("DOGRU\n");
            dogrutestsayisi++;
        }
    }else{printf("YANLIS\n");}

    //TEST - 4:
    printf("\nTEST - 4\n");
    printf("dizi 2 atama kontrolu: \n");

    if(MSIZE(ptr1)==elemanSayisi1*sizeof(int) && MSIZE(ptr2)==elemanSayisi2*sizeof(int))
    {
        //Deger araligi kontrolu
        int i;
        int dogruKontrol=1;
        int dogruKontrol2=1;
        for(i=0;i<elemanSayisi1;i++)
        {
            if(ptr2[i]<8 || ptr2[i]>32)
            {
                dogruKontrol=0; //HATA
            }
        }
        //[48,102] araliginda sayilar mi?
        for(i=elemanSayisi1;i<elemanSayisi2;i++)
        {
            if(ptr2[i]<48 || ptr2[i]>102)
            {
                dogruKontrol2=0; //HATA
            }
        }

        if(dogruKontrol==1 && dogruKontrol2==1)
        {
            printf("DOGRU\n");
            dogrutestsayisi++;
            dogrutestsayisi++;
        }
    }else{printf("YANLIS\n");}


    printf("\n");

    //Puan Hesaplama
    int puan=dogrutestsayisi*20;
    printf("Puan: %d", puan);
    fprintf(fp, "Puan: %d", puan);

    //Alinan hafiza bolgesinin iade edilmesi
    free(ptr1);
    free(ptr2);

    //Dosya isaretcisi ile dosya yazma islemi kapatilmasi
    fclose(fp);

    return 0;
}
