/*MATEESCU Cristina - 311CB*/
#include<stdio.h>
#include<string.h>
#include"info.h"
#include<stdlib.h>

 void DistrugeL(TLista* aL)
	{TLista aux;
         while(*aL)
  		{aux = *aL;
    		 *aL = aux->urm;
    		 free(aux);
    		}
	}

 void eliberare(Sala* sala)
	{int nrMese=(*sala)->nrMese,i,k;
	 TLista aux=(*sala)->masa;
	 TLista curent=(*sala)->masa;

	 //1.Parcurg lista de mese
   	 for(i=0;i<nrMese;i++)
		{curent=curent->urm; 
		 int nrCrtJucatori=((Masa)(aux->info))->nrCrtJucatori;
		 TLista santinela=((Masa)(aux->info))->jucatori;
		 TLista curentj=((Masa)(aux->info))->jucatori->urm;
		 TLista auxj=curentj; 

		 //2.Parcurg lista jucatori
		 for ( k=0 ; k<nrCrtJucatori ;k++ )
			{curentj=curentj->urm;
			 free(((Jucator)(auxj->info))->nume);
			 free(auxj->info);
		 	 free(auxj);
		 	 auxj=curentj;}

			 //3.Eliberez santinela
			 free(santinela);
			 //4.Eliberez masa
			 free(((Masa)(aux->info))->numeMasa);
			 free(aux->info);
			 free(aux);
			 aux=curent;}
	free(*sala);
	(*sala)=NULL;}
	

 int InsFinJucator(TLista auxj,char numeMasa[],Sala sala,FILE* outp)
 	{TLista p=sala->masa;
	 //1.Cautare masa
	 while(p!=NULL && strcmp(((Masa)(p->info))->numeMasa,numeMasa)!=0)
	    	p=p->urm;
	  
	 if(p==NULL) 
	    	{fprintf(outp,"Masa nu exista!");
	     	return 0;}

	 //2.Se verifica daca exista locuri la masa
	 if(((Masa)(p->info))->nrCrtJucatori == ((Masa)(p->info))->nrMaxJucatori )
		{fprintf(outp,"Nu exista locuri la masa!");
		 return 0;}

	  //3.Incrementare numar curent jucatori
	  ((Masa)(p->info))->nrCrtJucatori++; 
	  p=((Masa)(p->info))->jucatori;
	  TLista santinela=p;

	  //4.Cautare si inserare dupa ultima celula
	  while(p->urm!=santinela) 
		p=p->urm;
	  p->urm=auxj; 
	  auxj->urm=santinela;
	  return 1;
	  }


 TLista InsLG(void* ae, size_t d)
	{TLista aux=(TLista)malloc(sizeof(Celula));
	 if( !aux ) return NULL;
	 aux->info=ae;
	 aux->urm = NULL;
	 return aux;}
	 

 Jucator alocjucator(char nume[],size_t size,int nrMaini)
	{//1.Alocare structura jucator
	 Jucator jucator=(Jucator)malloc(sizeof(struct jucator));
	  if(!jucator)
		{printf("Alocare jucator nereusita");
		 return NULL;
		}
	  //2.Alocare pentru nume
	  jucator->nume=(char*)malloc(sizeof(char)*(size+1));
	  if(!jucator->nume)	
		{free(jucator);
		 printf("Alocare jucator nereusita");
		 return NULL;
		}
	  //3.Inserare nume, numar maini
	  strcpy(jucator->nume,nume);
	  jucator->nrMaini=nrMaini;
	  return jucator;}


  Masa alocmasa(char nume[],size_t size,int nrMaxJucatori)
	{ //1.Alocare structura masa+verificare alocare
	  Masa masa=(Masa)malloc(sizeof(struct masa));
	  if(!masa)
		{printf("Alocare masa nereusita");
		 return NULL;
		}
	  //2.Alocare nume masa + verificare alocare
	  masa->numeMasa=(char*)malloc(sizeof(char)*(size+1));
	  if(!masa->numeMasa)
		 {free(masa);
		  printf("Alocare masa nereusita");
		  return NULL;
		  }
	  //3.Inserare nume + initializare Masa
	  strcpy(masa->numeMasa,nume);
	  masa->nrCrtJucatori=0;
	  masa->nrMaxJucatori=nrMaxJucatori;
	  masa->jucatori=NULL;
	  return masa;}
	

 Sala citireS(FILE *conf,FILE* outp)
	{ int i,j,k,nrMese;
	  TLista p,aux;
	  
	  //1.Alocare sala + verificare alocare
	  Sala sala=(Sala)malloc(sizeof(struct sala));
	  if(!sala)
		{fprintf(outp,"Alocarea salii nereusita");
		 return NULL;}

	  //2.Initializare valori sala
	  fscanf(conf,"%d",&nrMese);
	  sala->nrMese=nrMese;
	  sala->nrLocCrt=0;
	  sala->nrLocMax=0;
	  sala->masa=NULL;
	 
	  //3.Initializare lista mese
	  //+inserare valori configuratie
	  for( i=0; i<nrMese; i++ )	
		{ char nume[50];
		  int nrCrtJucatori,nrMaxJucatori;
		  fscanf(conf,"%s %d %d",nume,&nrCrtJucatori,&nrMaxJucatori);
		  sala->nrLocCrt+=nrCrtJucatori;
		  sala->nrLocMax+=nrMaxJucatori;
		  
		  //3.1.Alocare masa + verificare alocare
		  Masa masa=alocmasa(nume,strlen(nume),nrMaxJucatori);
		  if(!masa)
		  {eliberare(&sala);
		   fprintf(outp,"Alocarea salii nereusita");
		   return NULL;}

		  //3.2.Inserare info masa in celula aux
		  aux=InsLG(masa,sizeof(struct masa));
		  if(!aux)
			{ free(masa->numeMasa);
			  free(masa);
			  eliberare(&sala);
			  fprintf(outp,"Alocarea salii nereusita");
			  return NULL;}

		  //3.3.Inserare celula in lista mese
		  if(sala->masa==NULL)sala->masa=aux;
		  else p->urm=aux;
		  p=aux;
			
 		  //4.Initializare lista jucatori la masa curenta=aux
		  //+inserare valori
		  //4.1.creare santinela
		  void *info=NULL;
		  TLista auxj=InsLG(info, 0);
		  if(!auxj) {eliberare(&sala);
			     fprintf(outp,"Alocarea salii nereusita");
			     return NULL;}

		  ((Masa)(aux->info))->jucatori=auxj;
		  ((Masa)(aux->info))->jucatori->urm=((Masa)(aux->info))->jucatori;
		  
		  //4.2.Inserare valori
		  for ( k=0 ; k<nrCrtJucatori ;k++ )
			{ char numej[50];
			  int nrMaini;
			  fscanf(conf,"%s %d",numej,&nrMaini);
			  
			  //4.2.1.Alocare jucator, Inserare celula + verificari alocari
			  Jucator jucator=alocjucator(numej,strlen(numej),nrMaini);
			  if(!alocjucator)
 				{eliberare(&sala);
				 printf("Alocarea salii nereusita");
			 	 return NULL;}

			  auxj=InsLG(jucator,sizeof(struct jucator));
			  if(!auxj)
				{ free(jucator->nume);
				  free(jucator);
				  eliberare(&sala);
				  printf("Alocarea salii nereusita");}

			  //4.2.2.Inserare jucator la masa
			  InsFinJucator(auxj,masa->numeMasa,sala,outp);	  
			}
		}	
	return sala;}
	

  int eliminajucator_sau_masa(Sala sala, char masa[], char jucator[],FILE* outp)
	{ TLista p,ant_masa=sala->masa,masa_curenta;

	  //1.Cautare masa	  
	  p=sala->masa;
	  while(p!=NULL && strcmp(((Masa)(p->info))->numeMasa,masa)!=0)
		{ if(p!=sala->masa)ant_masa=ant_masa->urm;
		  p=p->urm;
		}	  	  
         if(p==NULL) {printf("Nu exista masa %s!",masa);
		      return 0;}
	 masa_curenta=p;
	 p=((Masa)(p->info))->jucatori;
	 TLista santinela=p;
	 TLista anterior=p;
         p=p->urm;

	 //2.Cautare jucator	  
	 while (p!=santinela && strcmp(((Jucator)(p->info))->nume,jucator)!=0)
	    {p=p->urm;
	     anterior=anterior->urm;}
	 
	 if ( p == santinela ){printf("Nu exista jucatorul %s!",jucator);
			       return 0;}
	
	 //3.Eliminare jucator in conditiile date	  
	 if( ((Jucator)(p->info))->nrMaini <= 0 )
	    { ((Masa)(masa_curenta->info))->nrCrtJucatori--;
	      sala->nrLocCrt--;
	      anterior->urm=p->urm;
	      free(((Jucator)(p->info))->nume);
	      free(((Jucator)(p->info)));
	      free(p);}

	  //4.Dupa eliminare jucator
	  //Verific daca trebuie eliminata masa
	  if ( santinela == santinela->urm )
	   	{ sala->nrLocMax-=((Masa)(masa_curenta->info))->nrMaxJucatori;
		  sala->nrMese--;
		  if(masa_curenta == ant_masa )
		  sala->masa=ant_masa->urm;	
		  else {
		  	p=ant_masa->urm;
			ant_masa->urm=p->urm;}
		  free(santinela);
		  free( ((Masa)(masa_curenta->info))->numeMasa );
		  free(masa_curenta->info);
		  free (masa_curenta);
		} 
	return 1;}	
		
	
  void print(Sala sala,FILE *outp)
	{ TLista p,santinela,j;
	  
	  //1.Parcurg lista de mese
	  for ( p = sala->masa; p!=NULL; p=p->urm )
	    {  fprintf(outp,"%s:",((Masa)(p->info))->numeMasa);
	       santinela=((Masa)(p->info))->jucatori;

	       //2.{Parcurg lista jucatori masa + afisare
	       for( j = santinela->urm; j!= santinela; j = j->urm )
		  {fprintf(outp," %s - %d",((Jucator)(j->info))->nume,
					((Jucator)(j->info))->nrMaini);

		   if(j->urm!=santinela)fprintf(outp,";");
		   else fprintf(outp,".");}
	       fprintf(outp,"\n"); 
	    } }

	
  int noroc_sau_ghinion ( Sala sala, FILE *outp,char masa[],
				char jucator[],int valoare,char noroc_sau_ghinion[])
	   { TLista p=sala->masa;

	     //1.Cautare masa
	     while (p!=NULL && strcmp(((Masa)(p->info))->numeMasa,masa)!=0  )
	     		p=p->urm;
		 
	     if(p==NULL) { fprintf(outp,"Masa %s nu exista!\n",masa);
		       	   return 0;}
	     p=((Masa)(p->info))->jucatori;
	     TLista santinela=p;
	     p=p->urm;

	     //2.Cautare jucator
	     while(p!=santinela && strcmp( ((Jucator)(p->info))->nume,jucator )!=0 )
		{p=p->urm;}
		  
	     if(p == santinela ) 
		{fprintf(outp,"Jucatorul %s nu exista la masa %s!\n",jucator,masa);
		 return 0;}

	    //3.Incrementare/Decrementare nrMaini cu noroc/ghinion
	    if( strcmp(noroc_sau_ghinion,"noroc")==0 ) 
	        ((Jucator)(p->info))->nrMaini+=valoare;
	    else  ((Jucator)(p->info))->nrMaini-=valoare;
	    return 1;}


  int tura(Sala sala,char masa[],FILE *outp)
	{ TLista p;

	  //1.Cautare masa
	  p=sala->masa;
	      while (p!=NULL && strcmp(((Masa)(p->info))->numeMasa,masa)!=0)
	  	  	 p=p->urm;

	  if(p==NULL) { fprintf(outp,"Masa %s nu exista!\n",masa);
		       	return 0;}
	
	p=((Masa)(p->info))->jucatori;
	//2.Rotatie
	TLista aux=p->urm;
	p->urm=aux->urm;
	TLista santinela=p;
	while(p->urm!=santinela)p=p->urm;
	p->urm=aux;
	aux->urm=santinela;
	
	//3.Decrementez numarul de maini
	//*Parcurgere Lista jucatori
	p=santinela->urm;
	while(p!=santinela)
		{ ((Jucator)(p->info))->nrMaini--;
		  TLista jucator=p;
		  p=p->urm;
		  if(((Jucator)(jucator->info))->nrMaini<=0)
			//Daca trebuie eliminat, se apeleaza functia de eliminare
			eliminajucator_sau_masa(sala,masa,((Jucator)(jucator->info))->nume,outp);
	}       }


  int inchide(Sala sala,char masa[],FILE *outp)
	{TLista p,masa_libera,jucator,ant=sala->masa;

	  //1.Cautare masa
	  p=sala->masa;
	  while (p!=NULL && strcmp(((Masa)(p->info))->numeMasa,masa)!=0)
	        {if(p!=sala->masa)ant=p;
		 p=p->urm;}
	  
	  if(p==NULL) { fprintf(outp,"Masa %s nu exista!\n",masa);
		       	return 0;}

	  //2.Verificare locuri libere
	  int max=(sala->nrLocMax)-(((Masa)(p->info))->nrMaxJucatori);
	  int crt=(sala->nrLocCrt)-(((Masa)(p->info))->nrCrtJucatori);
	  if(max<sala->nrLocCrt)
		{fprintf(outp,"Nu exista suficiente locuri in sala!\n");
		 return 0;}
	 
	  jucator=((Masa)(p->info))->jucatori;
	  TLista santinela=jucator;
	  masa_libera=sala->masa;
	  int nr_jucatori=((Masa)(p->info))->nrCrtJucatori;
	  int i;

	  //3.Parcurg lista de jucatori
	   for(i=0;i<nr_jucatori;i++)
		{ jucator=santinela->urm;
		  
		  //4.Caut masa libera
		  masa_libera=sala->masa;
		  while(masa_libera!=NULL && (
			((Masa)(masa_libera->info))->nrCrtJucatori
				==((Masa)(masa_libera->info))->nrMaxJucatori 
			|| strcmp( ((Masa)(masa_libera->info))->numeMasa,masa)==0  ))
			masa_libera=masa_libera->urm;
		  santinela->urm=jucator->urm;
		  InsFinJucator(jucator,((Masa)(masa_libera->info))->numeMasa,sala,outp);
		  			
		}
		
	   	 //5.Sterg masa
		 sala->nrLocMax-=((Masa)(p->info))->nrMaxJucatori;
		 sala->nrMese--;
		 if(ant==p)
			sala->masa=p->urm;
		else 
 			{
			ant->urm=p->urm;
			}
		free(santinela);
		free(((Masa)(p->info))->numeMasa);
		free(p->info);
		free(p); 
	return 1;}


  int clasament(Sala sala,char masa[],FILE *outp)
	{ TLista p,clasament=NULL,anterior,curent;
	  p=sala->masa;
	  
	  //1.Cautare masa
	  while(p!=NULL &&
	      strcmp(((Masa)(p->info))->numeMasa,masa)!=0)
	      p=p->urm;
	  	  
	  if(p==NULL) { fprintf(outp,"Masa %s nu exista!\n",masa);
		       	return 0;}
	  
	  fprintf(outp,"Clasament %s:\n",masa);
	  TLista santinela=((Masa)(p->info))->jucatori;
	  p=santinela->urm;
	  
	  //2.Parcurgere lista jucatori
	  while(p!=santinela)
		{  //2.1.Alocare structura Jucator
		   Jucator jucator=alocjucator( ((Jucator)(p->info))->nume,
				      strlen(((Jucator)(p->info))->nume),
				      ((Jucator)(p->info))->nrMaini);
		   if(!jucator)
			 {DistrugeL(&clasament);
		  	  return 0;}

		   //2.2.Alocare celula jucator	
		   TLista aux =InsLG(jucator, sizeof(struct jucator));
		   if(!aux) {free(jucator->nume);
			     free(jucator);
			     DistrugeL(&clasament);
			     return 0;}

		   //3.Inserare celula in clasament
		   if(clasament==NULL)
		      {
		       clasament=aux;
		       aux->urm=NULL;}

		  else
		     {int nrMaini=((Jucator)(p->info))->nrMaini;
		      curent=clasament;
		      anterior=clasament;

		      //3.1.Caut prima celula cu nrMaini<nrMaini al celulei de inserat
		      while(curent!=NULL && nrMaini<((Jucator)(curent->info))->nrMaini)
				{anterior=curent;
				 curent=curent->urm;
				}
		      //3.1.*.Daca au acelasi numar de maini, se face lexicografic 
		      while (curent!=NULL && nrMaini==((Jucator)(curent->info))->nrMaini &&
			    strcmp(((Jucator)(curent->info))->nume,((Jucator)(p->info))->nume)>0 )
				{anterior=curent;
				 curent=curent->urm;
				}
		     //4.Inserarea
		     if(anterior!=curent)
		     	{anterior->urm=aux;
		     	 aux->urm=curent;}
		     else 
			{clasament=aux;
			 aux->urm=curent;
			}
		     }
		  p=p->urm;
		}
	 //5.Afisare clasament
	 for(curent=clasament;curent!=NULL;curent=curent->urm)
		fprintf(outp,"%s %d\n",((Jucator)(curent->info))->nume,
			((Jucator)(curent->info))->nrMaini);

	 //6.Eliberare clasament
	 curent=clasament;
	 TLista celula=curent;
	 while(curent!=NULL)
		{celula=curent;
		 curent=curent->urm;
		 free(((Jucator)(celula->info))->nume);
		 free(celula->info);
		 free(celula);
		}
	}

	
	int main(int argc,char *argv[])
	{
	  FILE *conf=fopen(argv[1],"rt");
	  FILE *evenimente=fopen(argv[2],"rt");
	  FILE *outp=fopen(argv[3],"wt");
	  char eveniment[50],masa[50],jucator[50];	
	  int i,valoare;	
	  Sala sala=citireS(conf,outp);
	  while(fscanf(evenimente,"%s",eveniment)==1)
		{ if (strcmp(eveniment,"print")==0)
			print(sala,outp);

		  else if (strcmp(eveniment,"noroc")==0 ||
			   strcmp(eveniment,"ghinion")==0)
			{fscanf(evenimente,"%s %s %d",masa,jucator,&valoare);
			 int ok=noroc_sau_ghinion(sala, outp,masa,jucator,valoare,eveniment);
			 if(ok) eliminajucator_sau_masa(sala,masa,jucator,outp);
			}
		 else if (strcmp(eveniment,"tura")==0)
			{fscanf(evenimente,"%s",masa);
			 tura(sala,masa,outp);
			}
		 else if (strcmp(eveniment,"tura_completa")==0)
			{ TLista p=sala->masa,masa=sala->masa;
			  while (p!=NULL) 
				{masa=p;
				p=p->urm; 
				tura(sala,((Masa)(masa->info))->numeMasa,outp);}
			}
		else if (strcmp(eveniment,"inchide")==0)
			{ fscanf(evenimente,"%s",masa);
			  inchide(sala,masa,outp);
			}
		else if(strcmp(eveniment,"clasament")==0)
			{ fscanf(evenimente,"%s",masa);
			  clasament(sala,masa,outp);
			}
		 if(!sala->masa)
			{fprintf(outp,"Sala este inchisa!\n");break;}	
		}	  
	  eliberare(&sala);
	  fclose(conf);
	  fclose(evenimente);
	  fclose(outp);	
	return 0;
	}
