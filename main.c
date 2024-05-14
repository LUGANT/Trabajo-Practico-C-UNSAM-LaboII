#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tools.h"
#define MAX 20 ///MAXIMO DE REGISTROS EN EL ARCHIVO
#define COMISION 0.03 ///CUMPLE DE LA FUNCION DE OBTENER LA COMISION EN EL ARCHIVO

/****************************************
*   programa de Lucas Gabriel Antenni   *
*           Fecha de entrega            *
*               21/11/2021              *
*****************************************/

/**
ERRORES EN EL CODIGO
warning - linea 381 - overflow in conversion from long long unsigned int to long int changes value
warning - linea 396 - mismo warning que la lina 381
EXPLICACIÓN
El problema es que lo que trato de hacer es volver para atras utilizando la funcion fseek, volviendo
el cursor 1 para atras usando como referencia el sizeof de mi struct. el warning es por el tipo de varible,
ya que tendria que hacerle un cast.
El programa funciona con normalidad de igual manera.
**/

/**
documentos utilizados:
    *clientes.dat
    *clientes_actualizado.dat
    *clientes_no.txt
    *categoria.txt
**/
/**
ERRORES CONTROLADOS
    1-OCURRE QUE CUANDO SE CAMBIA EL INGRESO BRUTO Y YA SE HABIA INGRESADO LA COMISION,
    LA COMISION DEL INGRESO BRUTO SE MANTIENE
    2-SE CORROBORA CASOS EN LOS QUE EL CLIENTE YA EXISTA Y SE QUIERAN INGRESAR DATOS
    3-Se CORROBORA CASOS EN LOS QUE NO EXISTA EL CLIENTE EN EL SISTEMA
    4-CORRECION DE VALORES NUMERICOS PARA DEFINIR PARAMETROS DE INGRESO DE VALORES A UN ARCHIVO, CORREJIDOS Y AJUSTADOS AL DEFINE
    5-CUANDO HAY MAS DE UN APELLIDO DEVUELVE EL PRIMERO Y NO TODOS, CORREGIDO PARA QUE MUESTRE TODOS LOS CLIENTES CON EL MISMO APELLIDO
*/



///Referencia del struct utilizado
///El struct se encuentra en la libreria tools.h
/*typedef struct cliente
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
}client;*/

/**
CASOS GENERALES EN EL CODIGO
CUANDO VOY A CREAR UNA VARIABLE DE TIPO FILE, LO LLAMARE POR pA, DE LO CONTRARIO QUEDARA ACLARADO
CUANDO CREE ALGUNA VARIABLE DE TIPO STUCT LO LLAMARE A, Y USARE ESE DURANTE EL PROGRAMA, EN CASO
CONTRARIO SERA COMENTADO EN EL CODIGO
*/

///A
void create_file() ///Crea los archivos para el programa
{
    FILE *pA;                       ///Variable de tipo FILE, almacena la direccion de
    int i;                          ///los archivos con los que se trabaja
    client A={0,"0",'0',"0",0,0,0};

    //Creo una variable como indice (i) para
    //ir cargando el archivo con 10 resgistros

    ///CREO EL DOCUMENTO CLIENTES.DAT
    pA=fopen("clientes.dat","wb");
    if (pA!=NULL){
        for(i=0;i<MAX;i++){
            fwrite(&A,sizeof(struct cliente),1,pA);}
            system("cls");
            printf("Archivo creado exitosamente\n");
            }
    else { printf("ERROR"); }
    fclose(pA);
    getchar();


    ///CREO EL DOCUMENTO CLIENTES_ACTUALIZADO.DAT
    pA=fopen("clientes_actualizado.dat","wb");
    if (pA!=NULL){
            }
    else { printf("ERROR"); }
    fclose(pA);

    ///CREO EL DOCUMENTO CLIENTES_NO.TXT
    pA=fopen("clientes_no.txt","wt");
    if (pA!=NULL){
            fprintf(pA,"Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
             }
    else { printf("ERROR"); }
    fclose(pA);
    system("cls");
}

///B
void alta_clientes(){
    FILE *pA;
    int fnumber=0,fname=0;
    client A={0,"0",'0',"0",0,0,0},B={0,"0",'0',"0",0,0,0};
    /**
    Creo dos varibales, fnumber (flag number) y fname (flagname).
    la funcion que cumplen es tomarlos de referencia para un ciclo
    indefinido.
    File *pA almacena la direccion del archivo clientes.dat
    client A se usara como struct para colocar o recibir contenido de los archivos
    client B se usa para corroborar la existencia de datos
    */
do{
    //cargo numero de cuenta
    system("cls");
    printf("Escriba el numero de cueta del cliente(1-%d): ",MAX);
    do{
        scanf("%d", &A.numero_cuenta); ///CORROBORO QUE ESTE DENTRO DEL RANGO DE REGISTROS (10)
        fflush(stdin);
        if ((A.numero_cuenta<0)||(A.numero_cuenta>MAX)){
            printf("EL NUMERO DE CUENTA INGRESADO ESTA FUERA DE RANGO\n");
            getchar();
            system("cls");
        }
    }while((A.numero_cuenta<0)||(A.numero_cuenta>MAX));


    //corroboro la existencia de este dato en el .dat
    pA=fopen("clientes.dat","rb");
    if (pA!=NULL){
        fseek(pA,(A.numero_cuenta-1)*sizeof(struct cliente),SEEK_SET);
        fread(&B,sizeof(struct cliente),1,pA);
    }
else {printf("ERROR");}
fclose(pA);

    if(A.numero_cuenta==B.numero_cuenta){                       ///COMPARO EL NUMERO DE CUENTA A Y B
        fnumber=0;                                              ///PARA VERIFICAR Y YA EXISTE EL NUMERO
        printf("ERROR, EL NUMERO DE CUENTA YA EXISTE\n");       ///UTILIZA EL FLAG fnumber PARA CORROBORAR
        getchar();                                              ///SI EXISTE O NO EL NUMERO
        system("cls");
    }
    else{fnumber=1;}
}while(fnumber==0);

    //cargo el apellido
    system("cls");
    printf("Escriba el Apellido del cliente: ");
    gets(A.apellido);
    fflush(stdin);
    convierte_may(A.apellido); ///utilizo la funcion convierte_may para convertir el apellido en mayuscula
    //cargo el mes
    system("cls");
    printf("Escriba el mes de ingreso del cliente(ej: ene-feb-...): ");
    do{
        gets(A.mes);                    ///verify_month LO QUE HACE ES DEVOLVER UN VALOR int EN EL CASO
        fflush(stdin);                  ///DE SER COMPATIBLE CON LAS OPCIONES DE MESES EN LA FUNCION
        convierte_min(A.mes);           ///DE LO CONTRARIO DEVOLVERA 0 Y ENTRARA EN EL CICLO NUEVAMENTE
        fname=verify_month(A.mes);      ///PARA REINGRESAR EL MES
        if(fname==0){
            printf("EL MES INGRESADO ES ERRONEO\nCOLOCAR LOS 3 PRIMEROS CARACTERES DEL MES A INGRESAR\n");
        }
    }while(fname==0);

    //cargo ingreso bruto
    system("cls");

    printf("Escriba el ingreso bruto del cliente: ");   ///NO PONGO UNA VERIFICACION DE DATOS PORQUE
    scanf("%f",&A.ingreso_bruto);                       ///SI LLEGA A ESTAR MAL, "(X<370 ||X>3700)"
    fflush(stdin);                                      ///SE AÑADIRA COMO CATEGORIA 'X', LO CUAL
                                                        ///LO AÑADIRA EN clientes.txt

    //A.comision=A.ingreso_bruto*0.3
    A.categoria=putcat(A.ingreso_bruto);
    A.activo = 1;

    if(A.categoria!='X'){
        pA=fopen("clientes.dat", "rb+");
        if(pA!=NULL){
                fseek(pA,(A.numero_cuenta-1)*sizeof(struct cliente),SEEK_SET);
                fwrite(&A,sizeof(struct cliente),1,pA);
                    }
    else {printf("ERROR");}
    fclose(pA);
    system("cls");}
else {
    system("cls");
    printf("EL VALOR INGRESADO SUPERA/ES INFERIOR A LAS CATEGORIAS REGISTRADAS\nLOS VALORES INGRESADOS SERAN GUARDADOS EN clientes_no.txt.\n");
    pA=fopen("clientes_no.txt","a+");
    if (pA!=NULL){
        fprintf( pA,"%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
    }
    else printf("ERROR");
    fclose(pA);}}


///C
void listarDatos(){                 ///option SE UTILIZA COMO LLAVE PARA ACCEDER A UNA SECCION DEL SWITCH,
FILE *pA;                           ///mes[4] SE UTILIZA PARA ALMACENAR EL/LOS USUARIOS DE ESE MES PARTICULAR
char option, mes[4];                ///i ES UN INDICE, CANTIDAD DE CLIENTES SE UTILIZA COMO REFERENCIA DEL INDICE
client A;                           ///Y FMONTH SE UTILIZA COMO FLAG PARA VERIFICAR QUE EL MES QUE SE INGRESO EXISTA
int i=0, cantclient, fmonth=0;
//10
Menu_listaClientes();       ///IMPRIME UN MENU EL CUAL MUESTRA QUE FUNCIONES CUMPLE LA FUNCION
scanf("%c", &option);       ///ESCANEO LA OPCION Y LUEGO LO CONVIERTO EN MAYUSCULA SI SE DA LA CASUALIDAD
option=toupper(option);     ///DE QUE EL CARACTER SEA MINUSCULA
fflush(stdin);


switch (option){
case 'A':{///IMPRIME TODOS
    pA=fopen("clientes.dat","rb");
    if(pA!=NULL){
        fseek(pA,0,SEEK_END);
        cantclient=ftell(pA)/sizeof(struct cliente);// calculo la cantidad de productos registrados para el ciclo
        printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
        fseek(pA,0,SEEK_SET);
        while( i < cantclient ){
            fseek(pA,i*sizeof(struct cliente),SEEK_SET);
            fread(&A,sizeof(struct cliente),1,pA);
            printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
            i++;}}
    else {printf("ERROR");}
    fclose(pA);
break;}

///CASE A
/**
IMPRIME TODOS LOS REGISTROS DEL ARCHIVO BINARIO
TODOS TOMAN COMO REFERENCIA UN INDICE O UNA VARIBALE QUE LUEGO SE MULTIPLICA POR EL SIZEOF DEL STRUCT
PARA LUEGO ACCEDER CON PRESICION DONDE SE ENCUENTRA EL REGISTRO DEL CUAL QUIER SACAR LOS DATOS
*/


case 'B':{ ///IMPRIME POR CAMPO ACTIVO
    pA=fopen("clientes.dat","rb");
    if (pA!=NULL){
        fseek(pA,0,SEEK_END);
        cantclient=ftell(pA)/sizeof(struct cliente);// calculo la cantidad de productos registrados para el ciclo
        system("cls");
        printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
        fseek(pA,0,SEEK_SET);
    while(i < cantclient ){
        fseek(pA,i*sizeof(struct cliente),SEEK_SET);
        fread(&A,sizeof(struct cliente),1,pA);
        if(A.activo==1){
            printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);}}
    }
    else{printf("ERROR");}
    fclose(pA);
break;}

///CASE B
/**
IMPRIME UNICAMENTE LOS REGISTROS CON CAMPO ACTIVO
BASICAMENTE LEE LOS REGISTROS, Y VERIFICA DENTRO DEL STRUCT SI EL CAMPO ACTIVO ES 1 O 0,
SI ES 0 NO HACE NADA Y SI ES 1 LO IMPRIME
*/

case 'C':{ ///IMPRIME POR CATEGORIA
 do{
        system("cls");
        printf("Escriba la categoria (caracter entre A - K)");
        scanf("%c", &option);
        option=toupper(option);
        fflush(stdin);
        if(option<65||((option>75)&&(option<97||option>107))){
            system("cls");
            printf("EL CARACTER INGRESADO ESTA FUERA DE RANGO\nPOR FAVOR INGRESAR DE NUEVO LOS CARACTERES\n");
        }
    }while(option<65||((option>75)&&(option<97||option>107)));

    pA=fopen("clientes.dat","rb");
    if (pA!=NULL){

    fseek(pA,0,SEEK_END);
    cantclient=ftell(pA)/sizeof(struct cliente);// calculo la cantidad de productos registrados para el ciclo
    system("cls");
    printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
    fseek(pA,0,SEEK_SET);
    while( !feof(pA) ){
        //fseek(pA,i*sizeof(struct cliente),SEEK_SET);
        fread(&A,sizeof(struct cliente),1,pA);
        if(A.categoria==option){
            printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
           }}
    }
    else{printf("ERROR");}
    fclose(pA);
break;
}

///C
/**
IMPRIME LOS CLIENTES RESPECTO A LA CATEGORIA, HACE LO MISMO QUE EL B PERO COMPARA CON LA VARIABLE OPTION
QUE ANTES SE USO PARA EL SWITCH
*/


case 'D':{ ///IMPRIME POR EL MES

do{
    printf("Escriba el mes de ingreso del cliente\n");
    gets(mes);
    convierte_min(mes);
    fflush(stdin);
    fmonth=verify_month(mes);
}while(fmonth==0);

    pA=fopen("clientes.dat","rb");
    if (pA!=NULL){

    fseek(pA,0,SEEK_END);
    cantclient=ftell(pA)/sizeof(struct cliente);// calculo la cantidad de productos registrados para el ciclo
    system("cls");
    printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
    fseek(pA,0,SEEK_SET);
    while( !feof(pA) ){

        //fseek(pA,i*sizeof(struct cliente),SEEK_SET);
        fread(&A,sizeof(struct cliente),1,pA);

        if((strcmp(A.mes,mes))==0){
            printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
            }
        else{
            system("cls");
            printf("NO SE HA ENCONTRADO NINGUN CLIENTE INSCRIPTO EN ESE MES\n");
            }
                        }
    }
    else{printf("ERROR");}
    fclose(pA);

break;}}
}
///D
/**
IMPRIME POR EL MES INDICADO POR EL USUARIO
FUNCIONA A TRAVES DE LA FUNCION FMONTH, EL CUAL REVISA SI EXISTE LA VARIABLE INGRESADA EN
PARA COMPARAR EL MES
(*PARA VERIFICAR COMO FUNCIONA LA FUNCION FMONTH ENTRAR AL ARCHIVO tools.h)
*/


///D
void buscarCliente(){
    FILE *pA;                   ///OPTION CUMPLE LA MISMA FUNCION QUE EN EL ANTERIOR PROBLEMA (C),
    char option, name[50];      ///NAME VA A ALMACENAR EL APELLIDO DEL USUARIO, Y ACCOUNT ALMACENARÁ
    client A;                   ///EL NUMERO DE LA CUENTA DEL USUARIO (1-10)
    int account,contador=0;     ///MENU BUSQUEDA SOLO ES UN DISPLAY DEL MENU
    Menu_busqueda();            ///LA VARIABLE CONTADOR AYUDA A DEFINIR SI EN LA BUSQUEDA DE USUSARIO POR APELLIDO
    scanf("%c", &option);       ///NO SE ENCONTRO NINGUN USUARIO "if(contador==0)"
    fflush(stdin);
    option=toupper(option);

    switch(option){
case 'A':{ ///BUSQUEDA POR CUENTA
    system("cls");
    printf("Escriba el codigo de cuenta del usuario (Entre 1-10): ");
do{
    scanf("%d", &account);
    fflush(stdin);
    if (account<1&&account>MAX){
        printf("EL CODIGO INGRESADO NO ENTRA DENTRO DEL RANDO\nPOR FAVOR INGRESAR DE NUEVO (1-%d): ",MAX);
    }
}while(account<1&&account>MAX);

    pA=fopen("clientes.dat","rb");
    if(pA!=NULL){
    fseek(pA,(account-1)*sizeof(struct cliente),SEEK_SET);
    fread(&A,sizeof(struct cliente),1,pA);

        if(A.numero_cuenta==0){
            system("cls");
            printf("EL CLIENTE NO EXISTE EN EL SISTEMA\n");
            fclose(pA);
            break;
        }

    system("cls");
    printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
    printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
    }
    else{printf("ERROR");}
    fclose(pA);


    break;}
///CASE A
    /**
    BUSCA POR EL CODIGO
    ESTA ES UNA BUSQUEDA DIRECTA, LO QUE HACE ES TOMAR EN CUENTA EL ACCOUNT PARA
    "SALTAR" DIRECTAMENTE A LA SECCION DEL ARCHIVO DONDE SE ENCUENTRA EL REGISTRO QUE
    ALMACENA EL STRUCT CON EL USUARIO
    TAMBIEN VERIFICA QUE EXISTE. UNA VEZ LLEGA A ESA SECCION DEL ARCHIVO, SE CARGA A Y SE
    VERIFICA EL CONTENIDO DEL NUMERO DE CUENTA, SI ES 0 ENTONCES NO EXISTE USUSARIO.
    */

case 'B':{ ///BUSQUEDA POR APELLIDO
    printf("Ingrese el apellido del cliente: ");
    gets(name);
    fflush(stdin);
    convierte_may(name);
    pA=fopen("clientes.dat","rb");
    if(pA!=NULL){
        system("cls");
        printf( "Cuenta\t\tApe\tCat\tMes\tIng-Bruto\tComision\tActivo\n");
        fseek(pA,0,SEEK_SET);
        while (!feof(pA)){
            fread(&A,sizeof(struct cliente),1,pA);
            if((strcmp(A.apellido,name))==0){
                printf( "%6d%13s%8c%8s%14.2f%15.2f%14d\n", A.numero_cuenta, A.apellido, A.categoria, A.mes, A.ingreso_bruto,A.comision,A.activo);
                contador++;
        }}
        if (contador==0){
             printf("EL USUARIO NO FUE ENCONTRADO O NO EXISTE EN EL SISTEMA\n");
        }
        fclose(pA);
        break;

        }
    printf("ERROR");
    fclose(pA);
    break;}
    }


}
///CASE B
    /**
    EMITE EL USUARIO POR APELLIDO
    LO QUE HACE ES TOMAR EL APELLIDO CON EL ARRAY DE CARACTERS Y VA COMPARANDO CON EL NOMBRE ALMACENADO EN EL STRUCT A.
    ESTE AL SER UN CICLO INDEFINIDO SOLAMENTE LEERA EL ARCHIVO E IRA COMPARANDO CASO POR CASO HASTA ENCONTRAR EL USUARIO
    O DEVOLVER UN ERROR
    AMBOS DEVULVEN ERROR EN EL CASO DE NO HABER ENCONTRADO USUARIO.
    */



///E
void modificoLista(){
    FILE *pA;            ///AUX SE UTILIZA PARA ALMACENAR EL VALOR QUE SE
    float aux;           ///EL VALOR QUE SE CAMBIARA EN EL ARCHIVO
    client A;
    //No devolvera nada, pero el cursor estara una posicion adelante
    //de donde esta el registro que yo estoy buscando, por lo tanto
    //esta funcion sirve para mantener la posicion del cursor en el archivo
    // .dat
    pA=fopen("clientes.dat","rb+");
    if(pA!=NULL){

        Curser_search(pA);
        ///ESTA FUNCION CUMPLE EL ROL DE DEVOLVERME LA POSICION DEL CURSOR EN DONDE
        ///SE ENCUENTRABA EL REGISTRO QUE ESTOY BUSCANDO
        ///POR LO QUE NECESITO HACE UN MOVIMIENTO PARA ATRAS USANDO SEEK_CUR TOMANDO
        ///COMO REFERENCIA EL CURSOR
        ///LA FUNCION EN SI ES LA MISMA QUE LA BUSCQUEDA EN EL PUNTO D, PERO
        ///TIENE LA PARTICULARIDAD DE NO CERRAR EL ARCHIVO POR PARA DEVOLVER EL CURSOR

        //fseek(pA,(var-1)*sizeof(struct cliente),SEEK_SET)
        fseek(pA,(-1*sizeof(struct cliente)),SEEK_CUR);
        fread(&A,sizeof(struct cliente),1,pA);
        if(A.numero_cuenta!=0){
            do{
                printf("Ingrese el nuevo ingreso bruto del cliente\n con numero cuenta %d (RANGO 370-3700): ", A.numero_cuenta);
                scanf("%f",&aux);
                fflush(stdin);
                if(aux<370||aux>3700){
                    printf("EL INGRESO BRUTO ESTA FUERA DE RANGO (370-3700)");
                }
            }while(aux<370||aux>3700);

            A.ingreso_bruto=aux;
            A.categoria=putcat(aux);
            A.comision=0;
            fseek(pA,(-1*sizeof(struct cliente)),SEEK_CUR);
            fwrite(&A,sizeof(struct cliente),1,pA);
                                }
    }
    else{printf("ERROR");}
    fclose(pA);

}

/// ESTA FUNCION MODIFICA EL CONTENIDO DEL INGRESO BRUTO DE UN USUARIO, Y EN CONSECUENCIA
/// MODIFICA EL CONTENIDO DE LA CATEGORIA DEL USUARIO
/// TAMBIEN, PARA EVITAR ERRORES, EL VALOR DE COMISION SE DEVUELVE A 0 PORQUE SI NO SE HACE
/// SE MANTIENE LA COMISION DEL INGRESO BRUTO ANTERIOR



///F
void update (){
    FILE *pA;
    client A;
    int i=0;
    pA=fopen("clientes.dat","rb+");
    if (pA!=NULL){
        fseek(pA,0,SEEK_SET);
        for(i=0;i<MAX;i++){

            fseek(pA, i*sizeof(struct cliente),SEEK_SET);
            fread(&A,sizeof(struct cliente),1,pA);
            A.comision=A.ingreso_bruto*COMISION;
            //A.ingreso_bruto+=A.comision;

            fseek(pA,i*sizeof(struct cliente),SEEK_SET);
            fwrite(&A,sizeof(struct cliente),1,pA);
        }

    }
    else{printf("ERROR");}
    fclose(pA);
}

/**
EL OBJETIVO DE LA FUNCION UPDATE ES ACTUALIZAR LOS VALORES DE COMISION MULTIPLICANDO 0.03 DEL INGRESO BRUTO
DEVOLVIENDO ASÌ EL 3% DEL INGRESO BRUTO
*/


///G
void bajaLogica(){          ///NUM_CLIENTE SE UTILIZA PARA HACER UNA BUSQUEDA DIRECTA DE UN VALOR EN EL ARCHIVO
    FILE *pA;               ///OPTION SE UTILIZA PARA CONFIRMAR SI QUIERE REALIZAR O NO LA BAJA LOGICA
    int num_client;
    client A;
    char option;
    printf("Que cliente desea realizar una baja logica? (Activo [1->0])\nEscriba el codigo de cuenta del usuario (Entre 1-10): ");

do{
    scanf("%d", &num_client);
    fflush(stdin);
    if (num_client<1&&num_client>MAX){
        system("cls");
        printf("EL CODIGO INGRESADO NO ENTRA DENTRO DEL RANDO\nPOR FAVOR INGRESAR DE NUEVO (1-%d): ",MAX);}
    }while(num_client<1&&num_client>MAX);

    printf("Esta seguro que desea dar de baja a este usuario? (y/n)");
    scanf("%c", &option);
    fflush(stdin);
    option=tolower(option);
    if(option=='y'){
        pA=fopen("clientes.dat","rb+");
        if (pA!=NULL){
            fseek(pA,(num_client-1)*sizeof(struct cliente),SEEK_SET);
            fread(&A,sizeof(struct cliente),1,pA);
            if(A.activo==1){
                A.activo=0;
                fseek(pA,(num_client-1)*sizeof(struct cliente),SEEK_SET);
                fwrite(&A,sizeof(struct cliente),1,pA);
                printf("CLIENTE DADO DE BAJA CON EXITO");
                }
            else{
                system("cls");
                printf("EL CLIENTE YA ESTA DADO DE BAJA\n");
            }
        }
        else {printf("ERROR");}
        fclose(pA);
        getchar();
}
}

///BAJA LOGICA
/**
LA FUNCION DEL PROGRAMA ES MODIFICAR EL VALOR ACTIVO DE UN REGISTRO PARTICULAR PARA UN CLIENTE.
LA FUNCION VERIFICA SI QUIERE CONFIRMAR EL PROCESO Y CORROBORAR SI YA ESTA O NO DADO DE BAJA
*/


///H
void bajaFisica(){
    FILE *pB, *pA;
    int i;
    client A, B={0,"0",'0',"0",0,0,0};
    pA=fopen("clientes.dat","rb");
    if(pA!=NULL){
        fseek(pA,0,SEEK_SET);
        for(i=0;i<MAX;i++){
            fseek(pA,i*sizeof(struct cliente),SEEK_SET);
            fread(&A,sizeof(struct cliente),1,pA);
            if(A.activo==0){
                A=B;}
            pB=fopen("clientes_actualizado.dat","wb");
            if (pB!=NULL){
                    fseek(pA,i*sizeof(struct cliente),SEEK_SET);
                    fwrite(&A,sizeof(struct cliente),1,pB);
                }
                else printf("ERROR");
                fclose(pB);
        }


    }
    else printf("ERROR");
    fclose(pA);
    printf("ARCHIVO clientes_actualizado.dat HA SIDO ACTUALIZADO\nSE HAN INGRESADO LOS NUEVOS USUARIOS QUE NO ESTAN DE BAJA\n");

}
///BAJA FISICA
/**
    COLOCA NUEVAMENTE LOS REGISTROS EN EL ARCHIVO clientes.dat EN clientes_actualizado.dat PERO SOLAMENTE INGRESA AQUELLOS
    QUE SEAN CLIENTES ACTIVOS, LOS QUE NO SON ACTIVOS, LOS DEVUELVE A 0 Y LOS COLOCA EN EL ARCHIVO clientes_actualizado.dat
*/


int main()
{
    char menu;
    //FILE *pclientes;
    //FILE *pclientes_actualizado;
    //FILE *pclientes_no;
    do{
     menu=Menu();
     switch(menu){
        case 'A': create_file(); printf("\n"); break;
        case 'B': alta_clientes();; printf("\n"); break; ///FALTA REVISAR VALORES NO CONTEMPLADOS, REVISAR PROLIJIDAD
        case 'C': listarDatos(); printf("\n"); break; ///MUESTRA CLIENTES, PERO YA LA ALTA ES UN MENU, REVISAR CONSIGNA
        case 'D': buscarCliente(); printf("\n"); break;
        case 'E': modificoLista(); printf("\n"); break;
        case 'F': update(); printf("\n"); break;
        case 'G': bajaLogica(); printf("\n"); break;
        case 'H': bajaFisica(); printf("\n"); break;
        case 'I': /*end of program*/ break;
        system("cls");
            }}while(menu!='I');

    ///MAIN CUMPLE LA FUNCION DEL ESQUELO DEL MENU, TOMA EL CARACTER DESDE LA FUNCION Menu() Y A PARTIR
    ///DE AHI SE PUEDEN LAS FUNCIONES DEL PROGRAMA


    printf("Hasta pronto");
    return 0;
}
/**
PRE-CONDICION
1. Documentar como comentarios los nombres de archivo que se utilizaron y su extensión.
2. Utilizar librerías propias.
3. Tener en cuenta las funciones que se pueden reutilizar.
4. Validar todos los ingresos de datos y documentarlos.
5. Considerar convertir a mayúsculas los apellidos y a minúsculas con 3 caracteres los meses que se utilicen en el ingreso de datos y así grabarlas en el archivo.
6. Controlar al menos 3 errores y documentarlos.
7. Tener los procesos y funciones debidamente documentados como comentarios: variables, pasaje de parámetros, por qué, que se espera de ese proceso función, etc.
8. El código debe respetar la indentación.
9. Tener nombre y apellido del autor y fecha de entrega.
10. Tener menú de opciones para operarlo.
11. NO se deben utilizar variables globales.
**/