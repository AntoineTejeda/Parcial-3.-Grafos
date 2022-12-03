#include <stdio.h>
#include <string.h>
#define N 10

typedef struct
{
 int cola[N];
 int inicio, fin;
 int tam;

}TCola;

typedef struct
{
    char nombre[30];
}TAlumno;

typedef struct
{
    TAlumno Nodos[N];
    int Adyacencia[N][N];
    int Vertices;
}TGrafo;
TGrafo G;

int Menu();
int dequeue(TCola * c, int *d);
void InicializaCola(TCola * c, int tam);
int enqueue(TCola * c, int d);
int colaLlena(TCola c);
int colaVacia(TCola c);
void InicializaGrafo(TGrafo *G);
TAlumno captura();
TAlumno SeleccionarAlumno(TGrafo G);
int InsertaNodo(TGrafo *G, TAlumno n);
int InsertaArista(TGrafo *G, TAlumno n1, TAlumno n2);
int EliminaArista(TGrafo *G, TAlumno n1, TAlumno n2);
int EliminaNodo(TGrafo *G, TAlumno n);
int Compara(TAlumno n1, TAlumno n2);
void Imprime(TAlumno aux);
void ImprimeGrafo(TGrafo G);
void ImprimeNodos(TGrafo G);

int main()
{
    int op,verifica;
    TAlumno aux;
    TAlumno aux2;
    InicializaGrafo(&G);
    do
        {
            op=Menu();
            printf("\n");
            switch(op)
            {
                case 1:
                    aux=captura();
                    verifica=InsertaNodo(&G,aux);
                break;

                case 2:
                    printf("Selecciona el primer alumno para hacer la union \n");
                    printf("\n");
                    aux=SeleccionarAlumno(G);
                    printf("Selecciona el segundo alumno para hacer la union \n");
                    printf("\n");
                    aux2=SeleccionarAlumno(G);
                    InsertaArista(&G,aux,aux2);
                break;

                case 3:
                    printf("Selecciona el alumno al cual eliminaras de la relacion \n");
                    printf("\n");
                    aux=SeleccionarAlumno(G);
                    printf("Selecciona otra alumno al cual eliminaras de la relacion\n");
                    printf("\n");
                    aux2=SeleccionarAlumno(G);
                    EliminaArista(&G,aux,aux2);
                break;

                case 4:
                    printf("Selecciona el alumno que deseas eliminar \n");
                    printf("\n");
                    aux=SeleccionarAlumno(G);
                    EliminaNodo(&G,aux);
                break;

                case 5:
                    ImprimeGrafo(G);
                break;
                case 6:
                    op =8 ;
                break;
        }
          printf("\n");
    }while(op<7);
    return 0;
}

int Menu()
{
    int c;
    printf("(Oprime 1) Para ingresar a un nuevo alumno\n");
    printf("(Oprime 2) Para una nueva relacion \n");
    printf("(Oprime 3) Para eliminar relacion \n");
    printf("(Oprime 4) Para eliminar alumno\n");
    printf("(Oprime 5) Para imprimir grafo\n");
    printf("(Oprime 6) Para Terminar el programa\n");
    scanf("%d",&c);
    return(c);
}
TAlumno captura()
{
    TAlumno n;

    printf("Ingrese el nombre del alumno \n");
    fflush(stdin);
    gets(n.nombre);

    return(n);
}

TAlumno SeleccionarAlumno(TGrafo G)
{
    int i;
    TAlumno aux;
    ImprimeNodos(G);

    printf("Selecciona el inidice de alumno \n");
    printf("\n");
    scanf("%d",&i);
    aux=G.Nodos[i];

    return (aux);
}

void InicializaGrafo(TGrafo *G)
{
    G->Vertices=0;
}

int InsertaNodo(TGrafo *G, TAlumno n)
{
    int i;
    if(G->Vertices==N)
    {
        return(0);
    }
    G->Nodos[G->Vertices]=n;
    for(i=0;i<=G->Vertices;i++)
    {
        G->Adyacencia[i][G->Vertices]=0;
        G->Adyacencia[G->Vertices][i]=0;
    }
    G->Vertices++;
    return(1);
}

int InsertaArista(TGrafo *G, TAlumno n1, TAlumno n2)
{
    int v1=-1,v2=-1,i;

    for(i=0;i<G->Vertices;i++)
    {
        if(Compara(G->Nodos[i],n1))
        {
            v1=i;
        }
        if(Compara(G->Nodos[i],n2))
        {
            v2=i;
        }
    }
    if(v1==-1 || v2==-1)
    {
        return(0);
    }
    printf("v1:%d, v2:%d\n", v1, v2);
    G->Adyacencia[v1][v2]=1;
    G->Adyacencia[v2][v1]=1;

    return(1);
}

int EliminaArista(TGrafo *G, TAlumno n1, TAlumno n2)
{
    int v1=-1,v2=-1,c;

    for(c=0;c<G->Vertices;c++)
    {
        if(Compara(G->Nodos[c], n1))
        {
            v1=c;
        }
        if(Compara(G->Nodos[c], n2))
        {
            v2=c;
        }
    }
    if(v1==-1 || v2==-1)
    {
        return(0);
    }
    G->Adyacencia[v1][v2]=0;
    G->Adyacencia[v2][v1]=0;
    return(1);
}

int Compara(TAlumno n1, TAlumno n2)
{

    if(strcmp(n1.nombre,n2.nombre)!=0)
    {
        return(0);
    }
    return(1);
}

int EliminaNodo(TGrafo *G, TAlumno n)
{
    int v=-1,c,r;
    for(c=0;c<G->Vertices;c++)
    {
        if(Compara(G->Nodos[c],n))
        {
            v=c;
        }
    }
    printf("\n v:%d \n", v);
    Imprime(n);
    if(v==-1)
    {
        printf("\n error\n");
        return(0);
    }

    for(c=v;c<G->Vertices ;c++)
    {
        G->Nodos[c]=G->Nodos[c+1];
    }

    for(r=v;r<G->Vertices;r++)
    {
        for(c=0;c<G->Vertices;c++)
        {
            G->Adyacencia[r][c]=G->Adyacencia[r+1][c];
        }
    }
        for(r=0;r<G->Vertices;r++)
    {
        for(c=v;c<G->Vertices;c++)
        {
            G->Adyacencia[r][c]=G->Adyacencia[r][c+1];
        }
    }
    G->Vertices--;
}

void InicializaCola(TCola * c, int tam)
{
    tam ++;
     c->tam = tam <= N? tam : N;
     c->inicio = c->fin = 0;
}

int enqueue(TCola * c, int d)
{
     int reg = 0;
     if( ! colaLlena(*c) )
     {

         c->cola[c->fin] = d;
         c->fin = (c->fin + 1) % c->tam;
         reg = 1;
     }
     return(reg);
 }

int colaLlena(TCola c)
{
     int reg;
     reg = (c.fin + 1) % c.tam == c.inicio? 1:0;
     return(reg);
 }

 int dequeue(TCola * c, int *d)
{
     int reg = 0;
     if( ! colaVacia(*c))
     {
         *d = c->cola[c->inicio];
         c->inicio = (c->inicio + 1) % c->tam;
         reg = 1;
     }
     return(reg);
 }

 int colaVacia(TCola c)
{
     int reg;

     reg = c.inicio == c.fin ? 1 : 0;
     return(reg);
}

void ImprimeGrafo(TGrafo G)
{
    int i,j;
    ImprimeNodos(G);
    for(i=0;i<G.Vertices;i++)
    {
        for(j=0;j<G.Vertices;j++)
        {
          printf(" %d",G.Adyacencia[i][j]);
        }
        printf("\n");
    }
}

void ImprimeNodos(TGrafo G)
{
    int i;
    for(i=0;i<G.Vertices;i++)
    {
        printf(" [%d], %s\n",i,G.Nodos[i].nombre);
    }
}

void Imprime(TAlumno aux)
{
    printf(" %s\n",aux.nombre);
}
