/*Maria Messaoud-Nacer
21007612*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

struct vecfloat
{
    int nbele;
    float *v;
};
typedef struct vecfloat vec_t;

vec_t creeretremplir(int nb)
{
    vec_t w;
    int i;
    float x, y, z, *pt;
    if (nb < 2)
        nb = 10;
    w.nbele = nb;
    w.v = (float *)malloc(nb * sizeof(float));
    assert(w.v);
    x = 1.0;
    y = 0.13;
    z = 0.021;
    pt = w.v;
    for (i = 0; i < nb; i++)
    {
        *pt++ = x;
        x += y;
        y += z;
        if (x > 1.5)
        {
            x -= 1.01;
        }
        if (x < 0.5)
        {
            x += 0.499;
        }
        if (y > 1.)
        {
            y = y - 1.01;
        }
        if (x < 0.5)
        {
            y += 0.5001;
        }
    }
    return w;
}

void affvec_t(vec_t vec)
{
    int i;
    printf("Nombre d'éléments : %d\n", vec.nbele);
    for (i = 0; i < vec.nbele; i++)
    {
        printf("%f\t", vec.v[i]);
    }
    printf("\n");
}

vec_t trii(vec_t vec)
{
    int i, j;
    float temp;
    for (i = 1; i < vec.nbele; i++)
    {
        temp = vec.v[i];
        j = i - 1;
        while (j >= 0 && vec.v[j] > temp)
        {
            vec.v[j + 1] = vec.v[j];
            j = j - 1;
        }
        vec.v[j + 1] = temp;
    }
    return vec;
}

vec_t bull(vec_t vec)
{
    int i, j;
    float temp;
    for (i = 0; i < vec.nbele - 1; i++)
    {
        for (j = 0; j < vec.nbele - i - 1; j++)
        {
            if (vec.v[j] > vec.v[j + 1])
            {
                temp = vec.v[j];
                vec.v[j] = vec.v[j + 1];
                vec.v[j + 1] = temp;
            }
        }
    }
    return vec;
}

vec_t tri_select(vec_t vec)
{
    int i, j;
    float temp;

    for (i = 0; i < vec.nbele - 1; i++)
    {
        for (j = i + 1; j < vec.nbele; j++)
        {
            if (vec.v[i] > vec.v[j])
            {
                temp = vec.v[i];
                vec.v[i] = vec.v[j];
                vec.v[j] = temp;
            }
        }
    }
    return vec;
}

vec_t qs(vec_t vec)
{
    int i;
    vec_t lte;
    lte.v = (float *)malloc(vec.nbele * sizeof(float));
    lte.nbele = 0;

    vec_t gt;
    gt.v = (float *)malloc(vec.nbele * sizeof(float));
    gt.nbele = 0;

    if (vec.nbele <= 1)
    {
        return vec;
    }

    float pivot = vec.v[0];

    for (i = 1; i < vec.nbele; i++)
    {
        if (vec.v[i] <= pivot)
        {
            lte.v[lte.nbele] = vec.v[i];
            lte.nbele += 1;
        }
        else if (vec.v[i] > pivot)
        {
            gt.v[gt.nbele] = vec.v[i];
            gt.nbele += 1;
        }
    }

    lte = qs(lte);
    gt = qs(gt);

    vec_t vres;
    vres.v = (float *)malloc(vec.nbele * sizeof(float));
    vres.nbele = 0;

    for (i = 0; i < lte.nbele; i++)
    {
        vres.v[vres.nbele] = lte.v[i];
        vres.nbele += 1;
    }

    vres.v[vres.nbele] = pivot;
    vres.nbele += 1;

    for (i = 0; i < gt.nbele; i++)
    {
        vres.v[vres.nbele] = gt.v[i];
        vres.nbele += 1;
    }

    free(lte.v);
    free(gt.v);

    return vres;
}

int main(int argc, char **argv)
{
    vec_t v = creeretremplir(5);
    affvec_t(v);
    int n;
    vec_t ll, lt;
    clock_t td, ta;
    if (argc == 2)
        n = atoi(argv[1]);
    else
        n = 1000;
    ll = creeretremplir(n);
    td = clock();
    lt = trii(ll);
    ta = clock();
    printf("Tri insertion\t taille %d\t temps %d\n", n, (int)(ta - td));
    ll = creeretremplir(n);
    td = clock();
    lt = bull(ll);
    ta = clock();
    // affvec_t(lt);
    printf("Tri bulles\t taille %d\t temps %d\n", n, (int)(ta - td));
    ll = creeretremplir(n);
    td = clock();
    lt = qs(ll);
    ta = clock();
    // affvec_t(lt);
    printf("Quicksort\t taille %d\t temps %d\n", n, (int)(ta - td));
    ll = creeretremplir(n);
    td = clock();
    lt = tri_select(ll);
    ta = clock();
    // affvec_t(lt);
    printf("Tri selection\t taille %d\t temps %d\n", n, (int)(ta - td));
    return 0;
}