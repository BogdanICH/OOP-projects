/// Proiect PP - criptare si decriptare imagine bmp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    unsigned char r,g,b;

} pixel;

typedef struct
{
    unsigned int coltLinie, coltColoana, n;
    int cifra;
    double corelatie;
} ferestre;

void XORSHIFT32(unsigned int *R, int n)
{
    unsigned int r, k;
    r = R[0];
    for(k = 1; k <= n; k++)
    {
        r = r ^ r << 13;
        r = r ^ r >> 17;
        r = r ^ r << 5;
        R[k] = r;
    }
}
int fpadding(int latime)
{
    int padding;
    if (latime % 4 != 0)
        padding = 4 - (3 * latime) % 4;
    else
        padding = 0;
    return padding;
}

pixel* liniarizare(char *nume_imagine)
{
    FILE *fin = fopen(nume_imagine, "rb");
    if (fin == NULL)
    {
        fprintf(stderr, "Fisierul binar %s NU se poate deschide", nume_imagine);
        return NULL;
    }
    int k;
    unsigned int latime, inaltime;
    fseek(fin, 18, SEEK_SET); /// ma mut pe octetul 18
    fread(&latime, sizeof(unsigned int), 1, fin); /// citesc latimea
    fread(&inaltime, sizeof(unsigned int), 1, fin); /// citesc latimea
    fseek(fin, 54, SEEK_SET); /// ma mut la sfarsitul octetului 54
    pixel *L = (pixel*)malloc(latime * inaltime * sizeof(pixel)); /// aloc dinamic vectorul de liniarizare
    for (int i = 0; i < inaltime; i++) /// copiez pixelii din imagine in vectorul meu L
    {
        k = (latime * inaltime - latime - 1) - (latime * i); /// prima linie citita din imagine este ultima in vector
        for (int j = 0; j < latime; j++)
        {
            k++;
            fread(&L[k].b, 1, 1, fin);
            fread(&L[k].g, 1, 1, fin);
            fread(&L[k].r, 1, 1, fin);
        }
        fseek(fin, fpadding(latime), SEEK_CUR); /// sar peste padding
    }
    fclose(fin);
    return L;
}

void salveaza_imagine(char *nume_imagine_export, char *nume_imagine_initiala, pixel *L)
{
    FILE *fex = fopen(nume_imagine_export, "wb+"); /// imaginea care va fi scrisa
    FILE *fin = fopen(nume_imagine_initiala, "rb"); /// imaginea din care citesc header-ul
    if(fin == NULL)
    {
        fprintf(stderr, "Fisierul binar %s NU se poate deschide", nume_imagine_initiala);
        return 0;
    }
    unsigned char c, pun0 = 0;
    unsigned int latime, inaltime;
    for (int i = 0 ; i < 54; i++) /// copiez header-ul
    {
        fread(&c,1,1,fin);
        fwrite(&c,1,1,fex);
        fflush(fex);
    }
    fseek(fex, 18, SEEK_SET); /// ma mut pe octetul 18
    fread(&latime, sizeof(unsigned int), 1, fex); /// citesc latimea
    fread(&inaltime, sizeof(unsigned int), 1, fex); /// citesc latimea
    fseek(fex, 54, SEEK_SET); /// ma mut la sfarsitul lui 54
    int k = 0, padding = fpadding(latime); /// in variabila padding, tin padding-ul imaginii
    for (int i = 0; i < inaltime; i++) /// scriu pixelii in imaginea noua
    {
        k = (latime * inaltime - latime - 1) - (latime * i);
        for (int j = 0; j < latime; j++)
        {
            k++;
            fwrite(&L[k].b, 1, 1, fex);
            fflush(fex);
            fwrite(&L[k].g, 1, 1, fex);
            fflush(fex);
            fwrite(&L[k].r, 1, 1, fex);
            fflush(fex);
        }
        for (int pad = 0; pad < padding; pad++) /// adaug padding-ul daca e cazul
        {
            fwrite(&pun0, 1, 1, fex);
            fflush(fex);
        }
    }

    fclose(fin);
    fclose(fex);
}
unsigned int* Durstenfeld(char *nume_imagine_initiala, unsigned int *R)
{
    FILE *f = fopen(nume_imagine_initiala, "rb"); /// imaginea din care citesc
    if (f == NULL)
    {
        fprintf(stderr, "Fisierul binar %s NU se poate deschide", nume_imagine_initiala);
        return 0;
    }
    unsigned int latime, inaltime;
    fseek(f, 18, SEEK_SET); /// ma mut pe octetul 18
    fread(&latime, sizeof(unsigned int), 1, f); /// citesc latimea
    fread(&inaltime, sizeof(unsigned int), 1, f); /// citesc latimea
    unsigned int aux, r, k = 1, n = inaltime * latime;
    unsigned int *p = (unsigned int*)malloc(n * sizeof(unsigned int)); /// vectorul permutare
    XORSHIFT32(R, (2 * inaltime * latime - 1)); /// incarc R cu numere generate aleator
    for (int i = 0; i < n; i++)
        p[i] = i;

    for (int i = n-1; i >= 1; i--) /// permut vectorul p
    {
        r = R[k] % (i + 1);
        aux = p[r];
        p[r] = p[i];
        p[i] = aux;
        k = k + 1;
    }

    fclose(f);
    return p;
}

void criptare(char *nume_imagine_initiala, char *nume_imagine_criptata, char *secret_key)
{
    FILE *fkey = fopen(secret_key, "rt");
    unsigned int skey, SV, *R;
    fscanf(fkey, "%u %u", &skey, &SV);
    fclose(fkey);
    FILE *f = fopen(nume_imagine_initiala, "rb");
    unsigned int latime, inaltime;
    fseek(f, 18, SEEK_SET); /// ma mut pe octetul 18
    fread(&latime, sizeof(unsigned int), 1, f); /// citesc latimea
    fread(&inaltime, sizeof(unsigned int), 1, f); /// citesc latimea
    R = (unsigned int*)malloc(2 * latime * inaltime * sizeof(unsigned int));
    R[0] = skey;
    unsigned int *p = Durstenfeld(nume_imagine_initiala, R); /// aplic algoritmul lui Durstenfeld
    pixel *L;
    L = liniarizare(nume_imagine_initiala);
    pixel *Lp = (pixel*)malloc(latime * inaltime * sizeof(pixel));
    for(int i = 0; i < latime*inaltime; i++)
    {
        Lp[p[i]] = L[i];
    }
    /// criptare

    pixel *C = (pixel*)malloc(latime * inaltime * sizeof(pixel));
    C[0].r = ((SV >> 16) & 0xFF) ^ Lp[0].r ^ ((R[latime*inaltime] >> 16) & 0xFF);
    C[0].g = ((SV >> 8) & 0xFF) ^ Lp[0].g ^ ((R[latime*inaltime] >> 8) & 0xFF);
    C[0].b = (SV & 0xFF)  ^ Lp[0].b ^ (R[latime*inaltime] & 0xFF);
    for (int i = 1; i < latime*inaltime; i++)
    {
        C[i].r = C[i-1].r ^ Lp[i].r ^ ((R[latime*inaltime + i] >> 16) & 0xFF);
        C[i].g = C[i-1].g ^ Lp[i].g ^ ((R[latime*inaltime + i] >> 8) & 0xFF);
        C[i].b = C[i-1].b ^ Lp[i].b ^ (R[latime*inaltime + i] & 0xFF);
    }
    salveaza_imagine(nume_imagine_criptata, nume_imagine_initiala, C);
    fclose(f);
    free(L);
    free(Lp);
    free(R);
    free(C);
    free(p);
}

void decriptare(char *nume_imagine_initiala, char *nume_imagine_criptata, char *nume_imagine_decriptata, char *secret_key)
{
    FILE *fkey = fopen(secret_key, "rt");
    unsigned int R0, SV;
    fscanf(fkey, "%u %u", &R0, &SV);
    fclose(fkey);
    pixel *C;
    C = liniarizare(nume_imagine_criptata);
    FILE *fic = fopen(nume_imagine_criptata, "rb");
    if (fic == NULL)
    {
        fprintf(stderr, "Fisierul binar %s NU se poate deschide", nume_imagine_criptata);
        return 0;
    }
    unsigned int latime, inaltime, *R, *p, *pINV;
    fseek(fic, 18, SEEK_SET); /// ma mut pe octetul 18
    fread(&latime, sizeof(unsigned int), 1, fic); /// citesc latimea
    fread(&inaltime, sizeof(unsigned int), 1, fic); /// citesc latimea
    R = (unsigned int*)malloc(2 * latime * inaltime * sizeof(unsigned int));
    pINV = (unsigned int*)malloc(latime * inaltime * sizeof(unsigned int));
    R[0] = R0;
    XORSHIFT32(R, (2 * inaltime * latime - 1));
    p = Durstenfeld(nume_imagine_criptata, R);
    int n = latime * inaltime - 1;
    for (int i = n; i >=0; i--) /// construiesc permutarea inversa
        pINV[p[i]] = i;
    pixel *Cp = (pixel*)malloc(latime * inaltime * sizeof(pixel));
    pixel *D = (pixel*)malloc(latime * inaltime * sizeof(pixel));

    /// decriptare
    Cp[0].r = ((SV >> 16) & 0xFF) ^ C[0].r ^ ((R[latime*inaltime] >> 16) & 0xFF);
    Cp[0].g = ((SV >> 8) & 0xFF) ^ C[0].g ^ ((R[latime*inaltime] >> 8) & 0xFF);
    Cp[0].b = (SV & 0xFF) ^ C[0].b ^ (R[latime*inaltime] & 0xFF);
    for (int i = 1; i < latime*inaltime; i++)
    {
        Cp[i].r = C[i-1].r ^ C[i].r ^ ((R[latime*inaltime + i] >> 16) & 0xFF);
        Cp[i].g = C[i-1].g ^ C[i].g ^ ((R[latime*inaltime + i] >> 8) & 0xFF);
        Cp[i].b = C[i-1].b ^ C[i].b ^ (R[latime*inaltime + i] & 0xFF);
    }

    for (int i = 0; i < latime*inaltime; i++) /// aplic permutarea inversa pentru a decripta
        D[pINV[i]] = Cp[i];
    salveaza_imagine(nume_imagine_decriptata, nume_imagine_initiala, D);
    fclose(fic);
    free(C);
    free(Cp);
    free(R);
    free(p);
    free(D);
}

void chipatrat(char *nume_imagine)
{
    FILE *fin = fopen(nume_imagine, "rb");
    if (fin == NULL)
    {
        fprintf(stderr, "Fisierul binar %s NU se poate deschide", nume_imagine);
        return 0;
    }
    double fb;
    unsigned int latime, inaltime, *fir, *fig, *fib;
    fseek(fin, 18, SEEK_SET); /// ma mut pe octetul 18
    fread(&latime, sizeof(unsigned int), 1, fin); /// citesc latimea
    fread(&inaltime, sizeof(unsigned int), 1, fin); /// citesc latimea
    fb = (latime*inaltime)/256;
    pixel *L = liniarizare(nume_imagine);
    fir = (unsigned int*)malloc(256 * sizeof(unsigned int));
    fig = (unsigned int*)malloc(256 * sizeof(unsigned int));
    fib = (unsigned int*)malloc(256 * sizeof(unsigned int));
    double xr = 0, xg = 0, xb = 0;
    for (int i = 0; i < 256; i++)
    {
        fir[i] = 0;
        fig[i] = 0;
        fib[i] = 0;
    }
    for (int i = 0; i < latime*inaltime; i++) /// culeg frecventele
    {
        fir[L[i].r]++;
        fig[L[i].g]++;
        fib[L[i].b]++;
    }

    for (int i = 0; i < 256; i++) /// calculez suma
    {
        xr = xr + ((fir[i]-fb)*(fir[i]-fb))/fb;
        xg = xg + ((fig[i]-fb)*(fig[i]-fb))/fb;
        xb = xb + ((fib[i]-fb)*(fib[i]-fb))/fb;
    }
    printf("\nRGB(%.2lf, %.2lf, %.2lf)\n\n", xr, xg, xb);
    fclose(fin);
    free(L);

}

int main()
{
    char nume_imagine_initiala[30], secret_key[30], nume_imagine_criptata[30], nume_imagine_decriptata[30];
    printf("Nume imagine initiala: ");
    scanf("%s", nume_imagine_initiala);
    printf("Nume imagine ce va fi criptata: ");
    scanf("%s", nume_imagine_criptata);
    printf("Nume fisier (R0, Sv): ");
    scanf("%s", secret_key);

    criptare(nume_imagine_initiala, nume_imagine_criptata, secret_key);
    printf("Nume imagine in care se va decripta: ");
    scanf("%s", nume_imagine_decriptata);
    decriptare(nume_imagine_initiala, nume_imagine_criptata, nume_imagine_decriptata, secret_key);
    printf("\nTestul chi-patrat pentru %s", nume_imagine_initiala);
    chipatrat(nume_imagine_initiala);
    printf("\nTestul chi-patrat pentru %s", nume_imagine_criptata);
    chipatrat(nume_imagine_criptata);
    return 0;
}
