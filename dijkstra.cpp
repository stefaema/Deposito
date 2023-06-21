#include <cstdlib>
#include <iostream>
#define INFI  1000000
#define MAXNODO  361
#define MIEMBRO   1
#define NO_MIEMBRO 0

class Dijkstra
{
    int** matrizAdyacencia[MAXNODO][MAXNODO];
    int *dijkstra(); //devuelve una matriz con las distintas distancias minimas
    Dijkstra(int* *matAdy)
    {
        matrizAdyacencia = matAdy;
    }

};







int *dijkstra(int C[][MAXNODO],int s, int t, int P[]);
void camino(int P[], int s, int t);

using namespace std;

int main(int argc, char *argv[])
{   int C[MAXNODO][MAXNODO]={   INFI, INFI,    4,   13, INFI,
                                  INFI, INFI,    1, INFI, INFI,
                                  INFI,    5, INFI,    2,   11,
                                  INFI, INFI, INFI,INFI,     2,
                                  INFI, INFI, INFI,    1, INFI       
                                 };
    int *pdist, i, j, P[MAXNODO],s,t;
    
    for(i=0;i<MAXNODO;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODO;j++){
                  printf(" %5i",C[i][j]);                 
           }                 
    }
    s=1;  // vertice de inicio
    t=4;  // vertice final
    pdist=dijkstra(C,s,t,P);
    if (pdist[t]!=INFI){
        cout<<"\n\n distancia minima del nodo "<<s
            <<" al nodo "<<t<<" es= "<<pdist[t];
   
        cout<<"\n\n CAMINO= ";
        camino(P,s,t);
       
    }                
    else cout<<"\n NO HAY CAMINO";
    
    cout<<endl<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
// C[i][j] Costo del arco de i a j (matriz de adyacencia)
// D[i] costo del camino minimo conocido hasta el 
//              momento de s a i
//              inicialmente D[s]=0 y D[i]=INFI
// S[i] conjunto de nodos cuya distancia minima a s es conocida (si ya paso por el nodo o no)
//         y permanente, inicialmente S[] solo contiene a s
//         S[i]=1 si i pertenece, 0 si i no pertenece
// Pre[i] contiene el vertice que precede a i en el camino 
//            minimo encontrado hasta el momento

int *dijkstra(int C[][MAXNODO],int s, int t, int Pre[])
{
 static int D[MAXNODO];
 int S[MAXNODO];
 int actual, i, k, b;
 int menordist, nuevadist;
// inicializacion
 for(i=0;i<MAXNODO;i++){
                         S[i]=NO_MIEMBRO;
                         D[i]=INFI;
                         Pre[i]= -1;
 }//fin for
 S[s]=MIEMBRO; D[s]=0; actual=s; b=1; k=0;
 while((actual!=t)&&(b==1)){
                  b=0;
                  menordist=INFI;
                  //printf("\n\n   D[%i]=%3i ",actual,D[actual]);
                  for(i=0;i<MAXNODO;i++){
                          //cout<<"\n  i= "<<i;                
                          if(S[i]==NO_MIEMBRO){
                                 nuevadist=D[actual]+C[actual][i];
                                 //printf("\n nuevadist=%3i D[%2i]=%3i ",nuevadist,i,D[i]);
                                 if(nuevadist<D[i]){
                                        D[i]=nuevadist;//actual es menor que la anterior
                                        Pre[i]=actual; b=1;
                                 }//fin if
                                 //printf("\n menordist=%3i D[%2i]=%3i ",menordist,i,D[i]);
                                 if(D[i]<menordist){
                                        menordist=D[i];
                                        k=i;  b=1;//guardo el nodo de la menor distancia
                                 }//fin if
                          }//fin if
                  }//fin for
                               
                  actual=k; // actual se ubica en el nodo de menor distancia
                  S[actual]=MIEMBRO;
                  printf("\n\n         D     S     Pre");
                  for(i=0;i<MAXNODO;i++){
                           printf("\n[%2i] %5i %5i %5i     ",i,D[i], S[i],Pre[i]);
                   } 
      
                  //printf("\n\n   D[%i]=%3i ",actual,D[actual]);
                  
                   system("PAUSE");
 }//fin while
 return D;
}// fin dijkstra


void camino(int P[], int s, int t)
{ 
     if (t==s) cout<< s<<"  ";
   else{
        camino(P,s,P[t]);
        cout<<t<<"  ";
   }
 
     
}