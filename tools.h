//
// Created by lugant on 14/05/24.
//

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

typedef struct cliente
{
        int numero_cuenta;
        char apellido [50];
        char categoria;
        char mes[4];
        // ene, feb, mar, abr, may, jun,
        // jul, ago, sep, oct, nov, dic
        float ingreso_bruto;
        float comision;
        int activo;
        // VERDADERO - 1 - ACTIVO
        // FALSO - 0 - BAJA LOGICA
}client;


void convierte_min(char chain[]){
    int i;
    while (chain[i]!='\0'){
        chain[i]=tolower(chain[i]);
        i++;
    }

}

void convierte_may(char chain[]){
    int i;
    while (chain[i]!='\0'){
        chain[i]=toupper(chain[i]);
        i++;
    }
}

char putcat(int ing_brut){
char aux;
int a=370,b=550,c=770,d=1060,e=1400,f=1750,g=2100,h=2600,i=2910,j=3350,k=3700;

if ((ing_brut<a)||(ing_brut>k)){
    aux='X';
}

else if ((ing_brut>=a)&&(ing_brut<b)){
    aux= 'A';
}
else if ((ing_brut>=b)&&(ing_brut<c)){
    aux = 'B';
}
else if ((ing_brut>=c)&&(ing_brut<d)){
    aux = 'C';
}
else if ((ing_brut>=d)&&(ing_brut<e)){
    aux = 'D';
}
else if ((ing_brut>=e)&&(ing_brut<f)){
    aux = 'E';
}
else if ((ing_brut>=f)&&(ing_brut<g)){
    aux = 'F';
}
else if ((ing_brut>=g)&&(ing_brut<h)){
    aux = 'G';
}
else if ((ing_brut>=h)&&(ing_brut<i)){
    aux = 'H';
}
else if ((ing_brut>=i)&&(ing_brut<j)){
    aux = 'I';
}
else if ((ing_brut>=j)&&(ing_brut<k)){
    aux = 'J';
}
else aux = k;


return aux;}

int Menu(){
    char opcion;
    printf("Elige una opci%cn:\n",162);
    printf("A) Crear el archivo\n");
    printf("B) A%cadir un nuevo cliente\n", 164);
    printf("C) Listar clientes\n");
    printf("D) Buscar cliente\n");
    printf("E) Modificar datos\n");
    printf("F) Actualizar datos con el 3%c de comisi%cn\n",37,162);
    printf("G) Dar de baja l%cgica a un cliente\n",162);
    printf("H) Actualizar archivo eliminando bajas (Baja f%csica)\n", 161);
    printf("I) Salir\n");
    scanf("%c",&opcion);
    fflush(stdin);
    return toupper(opcion); // retorna la letra ingresada en mayúscula
}

void Menu_listaClientes(){

    printf("A) LISTAR TODOS\n");
    printf("B) LISTAR CAMPO ACTIVO\n");
    printf("C) LISTAR POR CATEGORIA\n");
    printf("D) LISTAR POR MES DE INGRESO\n");

}

void Menu_busqueda(){
    printf("A) BUSQUEDA POR CUENTA\n");
    printf("B) BUSQUEDA POR APELLIDO\n");

}

void Curser_search(FILE *pA){
    char option, name[50];
    client A;
    int account;
    Menu_busqueda();
    scanf("%c", &option);
    fflush(stdin);
    option=toupper(option);

    switch(option){
case 'A':{ ///BUSQUEDA POR CUENTA
system("cls");
    printf("Escriba el codigo de cuenta del usuario (Entre 1-%d): ",MAX);
do{
    scanf("%d", &account);
    fflush(stdin);
    if (account<1&&account>MAX){
        printf("EL CODIGO INGRESADO NO ENTRA DENTRO DEL RANDO\nPOR FAVOR INGRESAR DE NUEVO (1-%d): ",MAX);
    }
}while(account<1&&account>MAX);
    //pA=fopen("clientes.dat","rb");
    //if(pA!=NULL){
    fseek(pA,(account-1)*sizeof(struct cliente),SEEK_SET);
    fread(&A,sizeof(struct cliente),1,pA);

    if(A.numero_cuenta!=0){
        printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
        printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
    }
    else {
        system("cls");
        printf("EL USUARIO NO EXISTE EN EL SISTEMA\n");}

    //}
    //else{printf("ERROR");}
    //fclose(pA);


    break;}
case 'B':{ ///BUSQUEDA POR APELLIDO
    gets(name);
    fflush(stdin);
    convierte_may(name);
    //pA=fopen("clientes.dat","rb");
    //if(pA!=NULL){
    fseek(pA,0,SEEK_SET);
        while (!feof(pA)){
            fread(&A,sizeof(struct cliente),1,pA);
            if((strcmp(A.apellido,name))==0){
                printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
                printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
                break;
                //fclose(pA);}
            }}
            //fseek(pA,0,SEEK_END);
            system("cls");
            printf("EL USUARIO NO EXISTE EN EL SISTEMA");
        }
        break;}

    //fclose(pA);
    }

int verify_month(char *chain){
    int i;
    char month[12][4]={"ene","feb","mar","abr","may","jun","jul","ago","sep","oct","nov","dic"};
    for (i=0;i<12;i++){
          if(strcmp(chain,month[i])==0){
            return 1;
          }
    }
return 0;
}

/**
DOCUMENTACION DE LAS FUNCIONES
typedef struct clientes - es el struct que se utiliza en el main para enviar valores a los registros del archivo binario
convierte_min - toma los 3 caracteres que se utilizan para month y los pasa a minuscula con la funcion tolower
convierte_may - toma un array de caracters que convierte a todos en mayusucla con la funcion toupper
putcat - coloca la categoria del usuario segun su ingreso bruto, devuelve caracter, y utiliza condicionales if caso por caso (no es lo mas optimo)
Menu - es un display del menu principal en main, retorna un caracter y lee caracteres. el retorno es en mayuscula
Menu_listaClientes - display de opciones para la funcion de lista de clientes
Menu_busqueda - display del menu para la funcion de busqueda
Curser_serach - devuelve una posicion despues a la posicion de cursor que se esta buscando en un archivo binario
verify_month - verifica si el mes ingresado pertenece al array bidimencional de meses
*/

#endif //TOOLS_H
