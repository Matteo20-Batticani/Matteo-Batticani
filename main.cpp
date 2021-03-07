//
//  main.cpp
//  prova2
//
//  Created by Matteo Batticani💻🖥 on 04/03/21.
//

#include<iostream>
#include<string.h>
#include<stdio.h>
# define NO_OF_CHARS 256
using namespace std;
 // Funzione massimo
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Heuristica del carattere discordante
void preBmBc(string pat , int m, int bmBc[]) {
   int i;
 
   for (i = 0; i < NO_OF_CHARS; ++i)
      bmBc[i] = m;
   for (i = 0; i < m - 1; ++i)
      bmBc[pat[i]] = m - i - 1;  // La funzione di spostamento dei caratteri discordanti  sono memorizzati in array  che chiamo  bmBc
}
 
// Heuristica del buon suffiso
void suffixes(string pat , int m, int *suff) {
   int f, g, i;
 
   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && pat[g] == pat[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}

// La funzione di spostamento del euristica del  buono suffisso vengono memorizzate in un array  che chiamo  bmGs
 
void preBmGs(string pat, int m, int bmGs[]) {
   int i, j, suff[NO_OF_CHARS];
 
   suffixes(pat, m, suff);
 
   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   j = 0;
   for (i = m - 1; i >= 0; --i)
      if (suff[i] == i + 1)
         for (; j < m - 1 - i; ++j)
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}
 
 
void BM(string txt ,  string pat) {
   int i, j, bmGs[NO_OF_CHARS], bmBc[NO_OF_CHARS];
    
    int m = (int)pat.size();
    int n = (int)txt.size();
 
   /* Preprocessing */ /* I due array  BmGs e BmBc memorizzano gli spostamenti delle
                        due euristcihe */
preBmGs(pat, m, bmGs);
   preBmBc(pat, m, bmBc);
 
   /* Searching */
   j = 0;   // j è lo spostamento del pattern rispetto al testo
   while (j <= n - m) {
      for (i = m - 1; i >= 0 && pat[i] == txt[i + j]; --i);
      if (i < 0) {
          cout << "pattern si verifica allo shift = " <<  j<< endl;
         j += bmGs[0];
      }
      else
         j += max(bmGs[i], bmBc[txt[i + j]] - m + 1 + i);
       // Prendiamo il massimo spostamento tra le due euristcihe 
   }
}
   

int main()
{
    string testo= "abacdsffdeaasbcdf";
    string pattern = "acdsff";
    BM(testo, pattern);
    return 0;
}
