#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "windows.h"
#include "list"
using namespace std;

int puntos,pun,pun2,na;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void coloe(int x){

HANDLE hConsoleOutput; 
COORD coord; 
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),x);

}

void gotoxy (int x, int y){
HANDLE hcon;
hcon= GetStdHandle (STD_OUTPUT_HANDLE);
COORD dwPos;
dwPos.X= x;
dwPos.Y= y; 
SetConsoleCursorPosition (hcon, dwPos);
}

void OcultarCursor(){
	HANDLE hcon;
	hcon= GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 100;
	cci.bVisible = false;
	SetConsoleCursorInfo(hcon,&cci);
	
}

void pintar_limites(){
	for(int i = 2; i<78;i++){
		coloe(9);
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,33); printf("%c",205);
	}
	for(int i=4;i<33;i++){
		
		gotoxy(2,i);printf("%c",186);
		gotoxy(77,i);printf("%c",186);
	}
	
	gotoxy(2,3);	printf("%c",201);
	gotoxy(2,33);	printf("%c",200);
	gotoxy(77,3);	printf("%c",187);
	gotoxy(77,33);	printf("%c",188);
	
}

class NAVE{
	int x,y;
	int corazones;
	int vidas;
	public:
		NAVE (int _x,int _y,int _corazones,int _vidas):x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
		int X(){ return x; }
		int Y(){ return y; }
		int VID(){ return vidas; }
		void COR(){corazones--;}
		void COR2(){corazones=-2;}
		void pintar();
		void borrar();
		void mover();
		void pintar_corazones();
		void morir();
		void sumarvid();
		void morivid();
};

void NAVE::pintar(){
	switch(na){
		case 1:
			coloe(8);
			gotoxy(x,y); 	printf("  %c",30);
			gotoxy(x,y+1); 	printf(" %c%c%c",40,207,41);
			gotoxy(x,y+2); 	printf("%c%c %c%c",30,190,190,30);
		break;
		case 2:
			coloe(8);
			gotoxy(x,y); 	printf("  %c",30);
			gotoxy(x,y+1); 	printf(" %c%c%c",40,207,41);
			gotoxy(x,y+2); 	printf("%c%c%c%c%c",91,245,34,245,93);
		break;
		case 3:
			coloe(8);
			gotoxy(x,y); 	printf("  %c",30);
			gotoxy(x,y+1); 	printf(" %c%c%c",91,207,93);
			gotoxy(x,y+2); 	printf("%c%c%c%c%c",47,95,245,95,92);
		break;
		case 4:
			coloe(8);
			gotoxy(x,y); 	printf("  %c",30);
			gotoxy(x,y+1); 	printf(" %c%c%c",47,207,92);
			gotoxy(x,y+2); 	printf("%c%c%c%c%c",30,92,190,47,30);
		break;
		case 5:
			coloe(8);
			gotoxy(x,y); 	printf("  %c",30);
			gotoxy(x,y+1); 	printf(" %c%c%c",47,207,92);
			gotoxy(x,y+2); 	printf("%c%c%c%c%c",91,190,95,190,93);
		break;
	}
}

void NAVE::borrar(){
	gotoxy(x-1,y); 		printf("        ");
	gotoxy(x-1,y+1); 	printf("        ");
	gotoxy(x-1,y+2); 	printf("        ");
}

void NAVE::mover(){
	
	if (kbhit() ){
			char tecla=getch();
			borrar();
			if (tecla==IZQUIERDA && x>4) x--;
			if (tecla==DERECHA && x+6<76) x++;
			if (tecla==ARRIBA && y>6) y--;
			if (tecla==ABAJO && y+3<33) y++;
			
			pintar();
			pintar_corazones();
		}
	
}

void NAVE::pintar_corazones(){
	coloe(15);
	gotoxy(50,2);printf("VIDAS %i",vidas);
	
	gotoxy(64,2); printf("SALUD");
	gotoxy(70,2); printf("      ");
	for (int i=0;i<corazones;i++){
		coloe (4);
		gotoxy(70+i,2); printf("%c",3);
		
	}
	
}

void NAVE::morir(){
	
	if(corazones<=0){
		coloe(4);
		borrar();
		gotoxy(x-1,y);		printf("   **   ");
		gotoxy(x-1,y+1);	printf("  ****  ");
		gotoxy(x-1,y+2);	printf("   **   ");
		Sleep(100);
		borrar();
		gotoxy(x-1,y);		printf("  **** ");
		gotoxy(x-1,y+1);	printf(" *    * ");
		gotoxy(x-1,y+2);	printf("  ****  ");
		Sleep(100);
		borrar();
		gotoxy(x-1,y);		printf(" * ** * ");
		gotoxy(x-1,y+1);	printf("*      *");
		gotoxy(x-1,y+2);	printf(" * ** * ");
		Sleep(100);
		borrar();
		vidas--;
		corazones=3;
		pintar_corazones();
		pintar();
		
	}
	
}

void NAVE::sumarvid(){
	vidas++;
}

void NAVE::morivid(){
	vidas=0;
}

class AST{
	int x,y;
	public:
		AST(int _x,int _y):x(_x),y(_y){}
		int X(){return x;}
		int Y(){return y;}
		void pintar();
		void mover();
		void choque(class NAVE &N);
		
};

void AST::pintar(){
	coloe(7);
	gotoxy(x,y);printf("*");
	
}

void AST::mover(){
	gotoxy(x,y);printf(" ");
	y++;
	if(y>32){
		x = rand()%69+5;
		y = 4;
		Sleep(30);
	}
	pintar();
}

void AST::choque(class NAVE &N){
	
	if( x>=N.X() && x<N.X()+6 && y>=N.Y() && y<=N.Y()+2 ){
		
		N.COR();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x = rand()%71+4;
		y = 4;
		
	}
	
}

class AST2{
	int x,y;
	public:
		AST2(int _x,int _y):x(_x),y(_y){}
		int X2(){return x;}
		int Y2(){return y;}
		void pintar2();
		void mover2();
		void choque2(class NAVE &N);
		
};

void AST2::pintar2(){
	coloe(12);
	gotoxy(x,y);printf("*");
	
}

void AST2::mover2(){
	gotoxy(x,y);printf(" ");
	y++;
	if(y>32){
		x = rand()%69+5;
		y = 4;
		Sleep(30);
	}
	pintar2();
}

void AST2::choque2(class NAVE &N){
	
	if( x>=N.X() && x<N.X()+6 && y>=N.Y() && y<=N.Y()+2 ){
		
		N.COR2();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x = rand()%71+4;
		y = 4;
		
	}
	
}

class BALA{
	int x,y;
	public:
		BALA(int _x,int _y):x(_x),y(_y){}
		int X(){return x;}
		int Y(){return y;}
		void pintar();
		void mover();
		bool fuera();
	
	
};

void BALA::pintar(){
	coloe(5);
	gotoxy(x,y); printf("%c",124);
}

void BALA::mover(){
	
	gotoxy(x,y); printf(" ");
	y--;
	pintar();
}

bool BALA::fuera(){
	
	if(y==4) return true;
	return false;
	
}
class botones{
	int x,y;
	public:
		botones (int _x,int _y):x(_x),y(_y){}
		int X(){ return x; }
		int Y(){ return y; }
		void Jugar();
		void Opciones();
		void Extras();
		void Salir();
		void facil();
		void medio();
		void dificil();
		void regresar();
		void azul();
		void verde();
		void rojo();
		
};

void botones::Jugar(){
	gotoxy(x,y);	printf("Jugar");
}

void botones::Extras(){
	gotoxy(x,y+1);	printf("Extras");
}

void botones::Salir(){
	gotoxy(x,y+2);	printf("Salir");
}

void botones::facil(){
	gotoxy(x,y);	printf("facil");
}

void botones::medio(){
	gotoxy(x,y+1);	printf("Medio");
}

void botones::dificil(){
	gotoxy(x,y+2);	printf("Dificil");
}

void botones::regresar(){
	gotoxy(x,y+3);	printf("Regresar");
}

void botones::azul(){
	gotoxy(x,y);	printf("Azul");
}

void botones::verde(){
	gotoxy(x,y+1);	printf("Verde");
}

void botones::rojo(){
	gotoxy(x,y+2);	printf("Rojo");
}

class SELECTOR{
	int x,y;
	char tec=77;
	public:
		SELECTOR (int _x,int _y):x(_x),y(_y){}
		int X(){ return x; }
		int Y(){ return y; }
		char TEC(){ return tec; }
		
		void mover();
		void mover2();
		void mover3();
		void mover4();
		void moverna();
		void pintar();
		void borrar();
		void col(class botones &bot);
		void col2(class botones &bot2);
};

void SELECTOR::pintar(){
	coloe(3);
	gotoxy(x,y); 	printf("%c",219);	
}


void SELECTOR::borrar(){
	
	gotoxy(x,y); 	printf(" ");
}


void SELECTOR::mover(){
	if (kbhit() ){
			tec=getch();
			borrar();
			if (tec==ARRIBA && y>6) y--;
			if (tec==ABAJO && y<8) y++;
			
			pintar();
			
			
		}
}

void SELECTOR::mover2(){
	if (kbhit() ){
			tec=getch();
			borrar();
			if (tec==ARRIBA && y>15) y--;
			if (tec==ABAJO && y<18) y++;
			
			pintar();
			
			
		}
}

void SELECTOR::mover3(){
	if (kbhit() ){
			tec=getch();
			borrar();
			if (tec==ARRIBA && y>16) y--;
			if (tec==ABAJO && y<19) y++;
			
			pintar();
			
			
		}
}

void SELECTOR::mover4(){
	if (kbhit() ){
			tec=getch();
			borrar();
			if (tec==ARRIBA && y>19) y--;
			if (tec==ABAJO && y<19) y++;
			
			pintar();
			
			
		}
}

void SELECTOR::moverna(){
	if (kbhit() ){
			tec=getch();
			borrar();
			if (tec==ARRIBA && y>8) y-=4;
			if (tec==ABAJO && y<=19) y+=4;
			
			pintar();
			
			
		}
}

void SELECTOR::col(class botones &bot){
	if( x>=30 && y>=6){
		pun=1;
		
	}
	if(x<30 &&  y<=7){
		pun=2;
	}
	if(x<30 &&  y<=8){
		pun=3;
	}
}

void SELECTOR::col2(class botones &bot2){
	if( x>=30 && y>=15){
		pun2=1;
	}
	if( x>=30 && y>=16){
		pun2=2;	
	}
	if( x>=30 && y>=17){
		pun2=3;
	}
	if( x>=30 && y>=18){
		pun2=4;
	}
}

main(){ 
	
	do {   OcultarCursor();
	pun=0;
	system("cls");pintar_limites();
	coloe(11);
	gotoxy(3,32); printf("Perez Flores Gerardo Machariel");
	gotoxy(62,32); printf("2D Programacion");
	botones bot(37,6);
	bot.Jugar();
	
	bot.Extras();
	bot.Salir();
	SELECTOR R(35,6);
	pun=0;
	coloe(3);
	gotoxy(37,5);	printf("MENU");
	R.TEC();
	char tecl;
	while(R.TEC()!=32) {
		R.mover();	
	}
	if(R.Y()==6){
		pun=1;
	}
	if(R.Y()==7){
		pun=2;
	}
	if(R.Y()==8){
		pun=3;
	}
	
	switch(pun) {
		case 1:
			do{	
				pun2=0;int acomu;
				SELECTOR R2(30,15);
				botones bot2(32,15);
				system ("cls");pintar_limites();
				coloe(3);
				gotoxy(32,14);	printf("DIFICULTAD");
				coloe(11);
				bot2.facil();
				bot2.medio();
				bot2.dificil();
				bot2.regresar();
				while(R2.TEC()!=32) {
					R2.mover2();	
				}
				if(R2.Y()==15){
					pun2=1;
				}
				if(R2.Y()==16){
					pun2=2;
				}
				if(R2.Y()==17){
					pun2=3;
				}
				if(R2.Y()==18){
					pun2=4;
				}
				system("cls");
						
						if(pun2!=4){
							SELECTOR nav(30,7);
							coloe(3);
							gotoxy(32,5); printf("Escoger nave.");
							coloe(11);
							gotoxy(32,7); 	printf("  %c",30);
							gotoxy(32,8); 	printf(" %c%c%c",40,207,41);
							gotoxy(32,9); 	printf("%c%c %c%c",30,190,190,30);
		
							gotoxy(32,11); 	printf("  %c",30);
							gotoxy(32,12); 	printf(" %c%c%c ",40,207,41);
							gotoxy(32,13); 	printf("%c%c%c%c%c",91,245,34,245,93);
							
							gotoxy(32,15); 	printf("  %c",30);
							gotoxy(32,16); 	printf(" %c%c%c",91,207,93);
							gotoxy(32,17); 	printf("%c%c%c%c%c",47,95,245,95,92);
							
							gotoxy(32,19); 	printf("  %c",30);
							gotoxy(32,20); 	printf(" %c%c%c",47,207,92);
							gotoxy(32,21); 	printf("%c%c%c%c%c",30,92,190,47,30);
							
							gotoxy(32,23); 	printf("  %c",30);
							gotoxy(32,24); 	printf(" %c%c%c",47,207,92);
							gotoxy(32,25); 	printf("%c%c%c%c%c",91,190,95,190,93);
							
							while(nav.TEC()!=32) {
								nav.moverna();
							}
							if(nav.Y()==7){
								na=1;
							}
							if(nav.Y()==11){
								na=2;
							}
							if(nav.Y()==15){
								na=3;
							}
							if(nav.Y()==19){
								na=4;
							}
							if(nav.Y()==23){
								na=5;
							}
							system("cls");
							}
						
						NAVE N(37,30,3,3);
						
						list<AST*> A;
						list<AST*>::iterator itA;
						
						
						list<AST2*> A2;
						list<AST2*>::iterator itA2;
																		
						list <BALA*> B;
						list <BALA*>::iterator it;
						
						bool game_over;
				switch(pun2) {
					case 1:
						puntos=0;acomu=0;
						OcultarCursor();
						pintar_limites();
						
						N.pintar();
						N.pintar_corazones();
						
						for (int i=0; i<3; i++){
							
						A.push_back(new AST(rand()%75+2,rand()%5+4));
							
						}
						
						for (int i=0; i<3; i++){
							
						A2.push_back(new AST2(rand()%75+2,rand()%5+4));
							
						}
						
						game_over=false;
						
						while(!game_over){
							
							
							
							if (acomu==10){
								N.sumarvid();
								acomu=0;
							}
							coloe(15);
							gotoxy(4,2); printf("Puntos %i  %i",puntos,acomu);
							
							if(puntos<25){
								if(kbhit()){
								
								char tecla=getch();
								if (tecla==32){
									B.push_back(new BALA(N.X()+2,N.Y()-1));
								}
								if (tecla==27){
									N.morivid();
								}
							}
							}
							
							if(puntos>=25){
								if(kbhit()){
			
								char tecla=getch();
								if (tecla==32){
									B.push_back(new BALA(N.X()+4,N.Y()+1));
									B.push_back(new BALA(N.X(),N.Y()+1));
								}
								if (tecla==27){
									N.morivid();
								}
			
							}
							}
		
							if(puntos<25){
								for(it=B.begin(); it!=B.end();it++){
					
									(*it)->mover();
									if((*it)->fuera()){
				
									gotoxy((*it)->X(), (*it)->Y()); printf(" ");
									delete (*it);
									it = B.erase(it);
				
								}
			
							}
						}
		
							if(puntos>=25){
								for(it=B.begin(); it!=B.end();it++){
					
									(*it)->mover();
									if((*it)->fuera()){
										
										gotoxy((*it)->X(), (*it)->Y()); printf(" ");
										delete (*it);
										it = B.erase(it);
				
									}
			
								}
							}
		
							for(itA = A.begin(); itA != A.end(); itA++){
			
								(*itA)->mover();
								(*itA)->choque(N);
			
							}
							
														
		
							for(itA = A.begin(); itA!=A.end(); itA++){
			
								for(it=B.begin(); it!=B.end();it++){
				
									if((*itA)->X()==(*it)->X() && (  (*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y()  )){
					
										gotoxy((*it)->X(),(*it)->Y()); printf(" ");
										delete (*it);
										it = B.erase (it);
					
										A.push_back(new AST(rand()%75+3,rand()%5+4));
										gotoxy((*itA)->X(),(*itA)->Y()); printf(" ");
										delete (*itA);
										itA=A.erase(itA);
					
										puntos+=5;
										acomu+=1;
							
					
									}
					
								}
			
							}
		

		
							if(puntos>=30){
								for(itA2 = A2.begin(); itA2 != A2.end(); itA2++){
			
									(*itA2)->mover2();
									(*itA2)->choque2(N);
								}
								
								for(itA2 = A2.begin(); itA2!=A2.end(); itA2++){
			
									for(it=B.begin(); it!=B.end();it++){
				
										if((*itA2)->X2()==(*it)->X() && (  (*itA2)->Y2()+1 == (*it)->Y() || (*itA2)->Y2() == (*it)->Y()  )){
					
											gotoxy((*it)->X(),(*it)->Y()); printf(" ");
											delete (*it);
											it = B.erase (it);
					
											A2.push_back(new AST2(rand()%75+3,rand()%5+4));
											gotoxy((*itA2)->X2(),(*itA2)->Y2()); printf(" ");
											delete (*itA2);
											itA2=A2.erase(itA2);
					
											puntos+=10;
											acomu+=4;
							
						
										}
					
									}
			
								}	
								
							}
							
							if(N.VID()==0) game_over=true;
		
							N.morir();
							N.mover();
		
							Sleep(30);
						}
						if (N.VID()==0){system("cls");
							pintar_limites();
							coloe(15);
							gotoxy(24,15);printf("Sus puntos acomulados fueron %i",puntos);
							getch();}
						break;
					case 2:
						puntos=0;acomu=0;
						OcultarCursor();
						pintar_limites();
						
						N.pintar();
						N.pintar_corazones();
						
						for (int i=0; i<3; i++){
							
						A.push_back(new AST(rand()%75,rand()%5+4));
							
						}
						
						for (int i=0; i<4; i++){
							
						A2.push_back(new AST2(rand()%75+2,rand()%5+4));
							
						}
						
						game_over=false;
						
						while(!game_over){
							
							
							
							if (acomu==20){
								N.sumarvid();
								acomu=0;
							}
							coloe(15);
							gotoxy(4,2); printf("Puntos %i  %i",puntos,acomu);
							
							if(puntos<45){
								if(kbhit()){
								
								char tecla=getch();
								if (tecla==32){
									B.push_back(new BALA(N.X()+2,N.Y()-1));
								}
								if (tecla==27){
									N.morivid();
								}
			
							}
							}
							
							if(puntos>=45){
								if(kbhit()){
			
								char tecla=getch();
								if (tecla==32){
									B.push_back(new BALA(N.X()+4,N.Y()+1));
									B.push_back(new BALA(N.X(),N.Y()+1));
								}
								if (tecla==27){
									N.morivid();
								}
			
							}
							}
		
							if(puntos<45){
								for(it=B.begin(); it!=B.end();it++){
					
									(*it)->mover();
									if((*it)->fuera()){
				
									gotoxy((*it)->X(), (*it)->Y()); printf(" ");
									delete (*it);
									it = B.erase(it);
				
								}
			
							}
						}
		
							if(puntos>=45){
								for(it=B.begin(); it!=B.end();it++){
					
									(*it)->mover();
									if((*it)->fuera()){
										
										gotoxy((*it)->X(), (*it)->Y()); printf(" ");
										delete (*it);
										it = B.erase(it);
				
									}
			
								}
							}
		
							for(itA = A.begin(); itA != A.end(); itA++){
			
								(*itA)->mover();
								(*itA)->choque(N);
			
							}
		
		
							for(itA = A.begin(); itA!=A.end(); itA++){
			
								for(it=B.begin(); it!=B.end();it++){
				
									if((*itA)->X()==(*it)->X() && (  (*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y()  )){
					
										gotoxy((*it)->X(),(*it)->Y()); printf(" ");
										delete (*it);
										it = B.erase (it);
					
										A.push_back(new AST(rand()%75+3,rand()%5+4));
										gotoxy((*itA)->X(),(*itA)->Y()); printf(" ");
										delete (*itA);
										itA=A.erase(itA);
					
										puntos+=5;
										acomu+=1;
							
					
									}
					
								}
			
							}
		
							if(puntos>=30){
								for(itA2 = A2.begin(); itA2 != A2.end(); itA2++){
			
									(*itA2)->mover2();
									(*itA2)->choque2(N);
								}
								
								for(itA2 = A2.begin(); itA2!=A2.end(); itA2++){
			
									for(it=B.begin(); it!=B.end();it++){
				
										if((*itA2)->X2()==(*it)->X() && (  (*itA2)->Y2()+1 == (*it)->Y() || (*itA2)->Y2() == (*it)->Y()  )){
					
											gotoxy((*it)->X(),(*it)->Y()); printf(" ");
											delete (*it);
											it = B.erase (it);
					
											A2.push_back(new AST2(rand()%75+3,rand()%5+4));
											gotoxy((*itA2)->X2(),(*itA2)->Y2()); printf(" ");
											delete (*itA2);
											itA2=A2.erase(itA2);
					
											puntos+=10;
											acomu+=4;
							
						
										}
					
									}
			
								}	
								
							}
		
		
							if(N.VID()==0) game_over=true;
		
							N.morir();
							N.mover();
		
							Sleep(30);
						}
						if (N.VID()==0){system("cls");
							pintar_limites();
							coloe(15);
							gotoxy(24,15);printf("Sus puntos acomulados fueron %i",puntos);
							getch();}
						break;
					case 3:
						puntos=0;acomu=0;
						OcultarCursor();
						pintar_limites();
						
						N.pintar();
						N.pintar_corazones();
						
						for (int i=0; i<5; i++){
							
						A.push_back(new AST(rand()%75,rand()%5+4));
							
						}
						
						for (int i=0; i<5; i++){
							
						A2.push_back(new AST2(rand()%75+2,rand()%5+4));
							
						}
						
						game_over=false;
						
						while(!game_over){
							
							
							
							if (acomu==30){
								N.sumarvid();
								acomu=0;
							}
							coloe(15);
							gotoxy(4,2); printf("Puntos %i  %i",puntos,acomu);
							
							if(puntos<70){
								if(kbhit()){
								
								char tecla=getch();
								if (tecla==32){
									B.push_back(new BALA(N.X()+2,N.Y()-1));
								}
								if (tecla==27){
									N.morivid();
								}
			
							}
							}
							
							if(puntos>=70){
								if(kbhit()){
			
								char tecla=getch();
								if (tecla==32){
									B.push_back(new BALA(N.X()+4,N.Y()+1));
									B.push_back(new BALA(N.X(),N.Y()+1));
								}
								if (tecla==27){
									N.morivid();
								}
			
							}
							}
		
							if(puntos<70){
								for(it=B.begin(); it!=B.end();it++){
					
									(*it)->mover();
									if((*it)->fuera()){
				
									gotoxy((*it)->X(), (*it)->Y()); printf(" ");
									delete (*it);
									it = B.erase(it);
				
								}
			
							}
						}
		
							if(puntos>=70){
								for(it=B.begin(); it!=B.end();it++){
					
									(*it)->mover();
									if((*it)->fuera()){
										
										gotoxy((*it)->X(), (*it)->Y()); printf(" ");
										delete (*it);
										it = B.erase(it);
				
									}
			
								}
							}
		
							for(itA = A.begin(); itA != A.end(); itA++){
			
								(*itA)->mover();
								(*itA)->choque(N);
			
							}
		
		
							for(itA = A.begin(); itA!=A.end(); itA++){
			
								for(it=B.begin(); it!=B.end();it++){
				
									if((*itA)->X()==(*it)->X() && (  (*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y()  )){
					
										gotoxy((*it)->X(),(*it)->Y()); printf(" ");
										delete (*it);
										it = B.erase (it);
					
										A.push_back(new AST(rand()%75+3,rand()%5+4));
										gotoxy((*itA)->X(),(*itA)->Y()); printf(" ");
										delete (*itA);
										itA=A.erase(itA);
					
										puntos+=5;
										acomu+=1;
							
					
									}
					
								}
			
							}
		
							if(puntos>=30){
								for(itA2 = A2.begin(); itA2 != A2.end(); itA2++){
			
									(*itA2)->mover2();
									(*itA2)->choque2(N);
								}
								
								for(itA2 = A2.begin(); itA2!=A2.end(); itA2++){
			
									for(it=B.begin(); it!=B.end();it++){
				
										if((*itA2)->X2()==(*it)->X() && (  (*itA2)->Y2()+1 == (*it)->Y() || (*itA2)->Y2() == (*it)->Y()  )){
					
											gotoxy((*it)->X(),(*it)->Y()); printf(" ");
											delete (*it);
											it = B.erase (it);
					
											A2.push_back(new AST2(rand()%75+3,rand()%5+4));
											gotoxy((*itA2)->X2(),(*itA2)->Y2()); printf(" ");
											delete (*itA2);
											itA2=A2.erase(itA2);
					
											puntos+=10;
											acomu+=4;
							
						
										}
					
									}
			
								}	
								
							}
		
		
							if(N.VID()==0) game_over=true;
		
							N.morir();
							N.mover();
		
							Sleep(30);
						}
						if (N.VID()==0){system("cls");
							pintar_limites();
							coloe(15);
							gotoxy(24,15);printf("Sus puntos acomulados fueron %i",puntos);
							getch();}
						break;

				}
			}while (pun2!=4);		
	break;
	case 2:
		system ("cls"); pintar_limites();
		SELECTOR R4(28,19);
		coloe(15);
		gotoxy(35,10);	printf("Extras");
		gotoxy(22,13);	printf("Alumno: Perez Flores Gerardo Machariel.");
		gotoxy(22,14);	printf("Grupo: 2D.");
		gotoxy(22,15);	printf("Maestra: Claudia Patricia Paz Robles.");
		gotoxy(22,16);	printf("CBTis #246.");
		gotoxy(35,19);	printf("Regresar");
		while(R4.TEC()!=32) {
			R4.mover4();	
		}
	break;	
	
}


		
} while(pun!=3);

}
