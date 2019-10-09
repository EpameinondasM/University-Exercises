/* 
Epameinondas Mataragkas
AM: 2022201300090
dit13090@uop.gr




*/





#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int N,M;
int headi,headj;
int snake[13];
char f='1';
int fcount = 1; /*to tablo tha allazi otan afto pai 6*/
int sk = 0;
int zwh = 3;

void printTable(char *table);
void placeSnakeHead(char *table);
void placeFood(char *table);
void movement(char *move,char *table);
int pospow(int dif,char *table);
void skor(int at_food);
int interactions(char *table);
void expand_snake(char *table,int fcount);
void placePowerup(char *table);
void movementPlacement(char *table);





int main(){
	srand (time(NULL));
	int dif = 0; // Diskolia
	int i = 0;
	int j = 0;
	char *table = NULL;
	char move[2];			
	int power; // Arithmos powerups
	
	do{
		printf("Dose diastaseis tablo\n");
		printf("N = ");
		scanf("%d", &N);
		printf("M = ");
		scanf("%d", &M);
		
		if (N*M<=15){
			printf("Poly mikros pinakas. Dwse pali diastaseis\n");
		}
		
	}while(N*M<=15);
	
	
	while (move[0] != 'x' && move[0] != 'X' && zwh>0){
	
		/* epilogi epipedou duskolias */
		printf("EASY : 1 , NORMAL : 2 , HARD : 3 \n");
		do{
			scanf("%d", &dif);
			if(dif==1 || dif==2 || dif==3){
				break;
			}
			printf("Try another number 1,2,3\n");
		}while(dif==0 || dif>4);
		
		/*Desmeusi mnimis pinaka*/
		printf("\n");
		if(table!=NULL)
			free(table);
		table=malloc(sizeof(char)*N*M);
		for(i=0; i<N; i++){
			for(j=0; j<M; j++){
				table[(i*M)+j]='.';
			}
		}
			
		// Arxikopoihsh tou pinaka pou periexei to fidi
		for(i=0; i<13; i++){
			snake[i]=0;
		}
		
		power = pospow(dif,table); /*elegxos gia nea empodia neas pistas kai power-up*/
		placeSnakeHead(table);
		placeFood(table);
		printTable(table);
		printf("Score = %d\n",(sk*50));
		
		
		while (move[0] != 'x' && move[0] != 'X' && zwh>0 && f != '6' ){
			printf("Dose kinisi\n");
			scanf("%s",&move);
			if (move[0] == 'p' || move[0] == 'P'){
				if (power > 0){
					placePowerup(table);
					power--;
				}
				else{
					printf("no more powerups for you please change your move\n");
				}
			}
			movement(move,table);
			printTable(table);
			printf("Score = %d\n",(sk*50));
		}
		if (f=='6'){		
			printf("Congratulations, you passed the level!\n\n Enter new difficulty\n");
			N = N + 2;
			M = M + 2;
			f = '1';
			fcount = 1;
			zwh = 3;
		}
	}	
	return 0;
	
}





int pospow(int dif,char *table){
	int r,pow;
	double pos = 0;
	int h = 0;
		
	/*katwxhrwsh posostou empodiwn kai power-up*/	
	if (dif==1){
		pos = N*M*5/100;
		pow = 2;
	}
	else if (dif==2){
		pos = N*M*10/100;
		pow=1;		
	}
	else if (dif==3){
		pos = N*M*15/100;
	}
	
	if (pos<1){
		pos=1;
	}
	
	/*eisagwgh tyxaiwn empodiwn*/
	srand(time(NULL));
	if (pos == 1){
		r=(rand()% (N*M));
		table[r]='#';
	}
	else{
		while (h<pos){
			do{					
				r=(rand()% (N*M));
			}while (table[r]!='.');
			
			if (h==0){																	/*prwto empodio*/
				table[r]='#';
				h++;
			}			
			else if (r%M==0 && r>0){													/*empodio sthn prwth sthlh*/
				if (table[r-M]=='#'|| table[r+1]=='#' || table[r+M]=='#'){
					table[r]='#';
					h++;				
				} 
			}
			else if ((r+1)%M==0 && r>M){												/*empodio sth teleutaia sthlh*/
				if (table[r-1]=='#' || table[r-M]=='#' || table[r+M]=='#'){
					table[r]='#';
					h++;
				}
			}
			else if (r-M<0){															/*empodio sthn prwth grammh*/
				if (r==0){																/*empodio panw aristera*/
					if (table[r+1]=='#' || table[r+M]=='#' ){
						table[r]='#';
						h++;
					}
				}
				else if (r+1==M){														/*empodio panw deksia*/
					if (table[r-1]=='#' || table[r+M]=='#'){
						table[r]='#';
						h++;	
					}
				}
				else{																	/*empodio panw,oxi sta akra*/
					if (table[r-1]=='#' || table[r+1]=='#' || table[r+M]=='#'){
						table[r]='#';
						h++;
					}
				}
			}
			else if(r+M>N*M ) {															/*empodio sth katw grammh*/
				if(r+1==M*N){															/*empodio katw deksia*/
					if (table[r-1]=='#' || table[r-M]=='#' ){
						table[r]='#';
						h++;				
					}
				}
				else if ((r+M-1)==N*M){													/*empodio katw aristera*/
					if (table[r+1]=='#' || table[r-M]=='#'){
						table[r]='#';
						h++;
					}
				else {																	/*empodio katw,oxi sta akra*/
					if (table[r-1]=='#' || table[r+1]=='#' || table[r-M]=='#'){
						table[r]='#';
						h++;
					}
				}
				}
			}
			else{																					/*allo empodio*/
				if ( table[r-M]=='#' || table[r-1]=='#' || table[r+1]=='#' || table[r+M]=='#' ){
						table[r]='#';
						h++;
					}
			} 
			
		}		
	}
	return pow;
}





int interactions(char *table){
	//Empodio
	if (table[headi*M+headj] == '#'){
		printf("Too bad you hit an obstacle");
		zwh--;
		return 0;
	}
	//Soma
	else if(table[headi*M+headj] == 'X'){
		printf("You ate yourself");
		zwh = 0;
		return 0;
	}
	//Fagito
	else if(table[headi*M+headj] == f){
		printf("Congrats you reached a food\n");
		f++;
		placeFood(table);
		expand_snake(table,fcount);
		fcount++;
		sk++;
		return 1;
	}
	/*powerup*/
	else if (table[headi*M+headj] == '@'){
		printf("You reached a powerup\n'");
		int x = rand() % 3 + 1;
		if (x == 1 ){
			printf("Your score has increased \n");
			sk++;
		}
		else if (x == 2){
			printf("Snake tail reduces by 2 \n");
			int i;
			for(i = 12; i > 0;i--){
				if (snake[i] != 0 ){
					table[snake[i]] = '.';
					table[snake[i-1]] = '.';
					snake[i] = 0;
					snake[i-1] = 0;
					break;
				}
			}
		}
		else if (x == 3){
			printf("2 obstacles have been removed from the table \n");
			int p = 0;
			int r;
			while (p != 2){
				r=(rand()% (N*M));
				if (table[r] == '#'){
					table[r] = '.';
					p++;
				}
			}
		}
	}
}





void expand_snake(char *table,int fcount){
	int tailcount = 0;
	int temp[13];
	int i,j;
	
	for (i = 0;i <= 12;i++){
		temp[i] = snake[i];
		printf("temp %d = %d \n",i,temp[i]);
	}
	
	table[headi*M+headj] = 'O';
	for (i=0;i<=12;i++){
		if (snake[i+1] == 0){
			table[temp[i]] = '.';
			snake[0] = headi*M+headj;
			break;
		}
		snake[i+1] = temp[i];
		tailcount++;
	}
	for (i = 1; i < tailcount; i++){
		table[snake[i]] = 'X';
	}

	snake[tailcount+1] = temp[tailcount];
	for (i=1; i <= fcount; i++){
	//	snake[tailcount + i] = temp[tailcount] + i - 1;
		table[snake[tailcount + 1]] = 'X';
	}
}





void movementPlacement(char *table){
	int tailcount = 0;
	int temp[13];
	int i,expand;
	
	for (i = 0;i <= 12;i++){
		temp[i] = snake[i];
		printf("temp %d = %d \n",i,temp[i]);
	}
	
	
	expand = interactions(table);
	if (expand == 1)
	{
		return;
	}
	table[headi*M+headj] = 'O';
	for (i=0;i<=12;i++){
		if (snake[i+1] == 0){
			table[temp[i]] = '.';
			snake[0] = headi*M+headj;
			break;
		}
		snake[i+1] = temp[i];
		tailcount++;
	}
	for (i = 1; i < tailcount; i++){
		table[snake[i]] = 'X';
	}
}





void movement(char *move,char *table){
	int i;
	
	if (move[0] == 'U' || move[0] == 'u'){
		for(i = 0; i < (int)move[1] - 48 ; i++ ){
		if (headi == 0){
			headi = N - 1;
		}
		else{
			headi--;
		}
		/*Se oles tis kinhseis einai o idios kodikas ektos tis apopano grammhs h opia kathorizi tin kinisi. Twra o apokato kodikas leitourgi os e3eis. exontas vali 
		to kefali stin epomeni thesi (edo 1 thesi pano) epidi to snake[i] einai o pinakas p einai apothikeumeno to fidi afto p kanis gia na kinhthei to soma einai
		enallagi ton timwn tou pinaka me ton proigoumeno tou dld. apothikevontas ton snake ston temp exoume tin timi p eixe prin to snake[0] tin perni to snake[1] thn timh p 
		eixe to snake[1] perni to snake[2] ktlp */
			movementPlacement(table);
		}
		
		
	}
	else if (move[0] == 'D' || move[0] == 'd' ){
		for(i = 0; i < (int)move[1] - 48 ; i++ ){
		if (headi == N - 1){
			headi = 0;
		}
		else{
			headi++;
		}
		movementPlacement(table);
	}
	}
	else if (move[0] == 'R' || move[0] == 'r'){
		for(i = 0; i < (int)move[1] - 48 ; i++ ){
		if (headj % (M - 1) == 0 && headj !=0){
			headj = headj - M + 1;
		}
		else{
			headj++;
		}
		movementPlacement(table);
	}
		
	}
	else if (move[0] == 'L' || move[0] == 'l'){
		for(i = 0; i < (int)move[1] - 48 ; i++ ){
		if (headj % M == 0){
			headj = headj + M -1;
		}
		else{
			headj--;
		}
		movementPlacement(table);
	}
	}
	
}





void printTable(char *table){
	int j,i;
	/* ektipwsh pinaka */
	printf("\n \n \n ");
	/*ektypwsh grammhs platous*/
	printf("   ");
	for(j=0; j<M; j++){
		printf("%2d ", j+1);
	}
	printf("\n");

	printf("----");
	for(j=0; j<M; j++){
		printf("---");
	}	
	printf("\n");

	for(i=0; i<N; i++){
		printf("%2d| ", i+1);
		for(j=0; j<M; j++){
				printf(" %c ", table[i*M+j]);
		}
		printf("\n");
	}
	printf("\n");
}





void placeSnakeHead(char *table){
	int k=0;
	int x = rand() % 4 + 1;
	while(1){
		/*pairnoume ena tyxaio i*/
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		/*pairnoume ena tyxaio j*/
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   /*elegxoume an h thesh 'i,j' ,einai kenh*/
			continue;
		table[i*M+j]='O';
		snake[0] = i*M+j;
		/*Edw apla epilegei tixea mia apo tis 4ris kateuthinsis (pano,kato,de3ia,aristera) gia na prosthesei to swma*/
		if (x == 1){
			table[i*M+j+1]='X';
			snake[1] = i*M+j+1;
			table[i*M+j+2]='X';
			snake[2] = i*M+j+2;
			headi = i;
			headj = j;
		}
		else if(x == 2 ){
			table[i*M+j-1]='X';
			snake[1] = i*M+j-1;
			table[i*M+j-2]='X';
			snake[2] = i*M+j-2;
			headi = i;
			headj = j;
		}
		else if(x == 3){
			table[(i+1)*M+j]='X';
			snake[1] = (i+1)*M+j;
			table[(i+2)*M+j]='X';
			snake[2] = (i+2)*M+j;
			headi = i;
			headj = j;
		}
		else{
			table[(i-1)*M+j]='X';
			snake[1] = (i-1)*M+j;
			table[(i-2)*M+j]='X';
			snake[2] = (i-2)*M+j;
			headi = i;
			headj = j;
		}
		break;
	}
}





void placeFood(char *table){
	int k=0;
	while(1){
		/*pairnoume ena tyxaio i*/
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		/*pairnoume ena tyxaio j*/
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   /*elegxoume an h thesh 'i,j' ,einai kenh*/
			continue;
		if (f != '6'){
			table[i*M+j]=f;
		}
		break;
	}
}





void placePowerup(char *table){
		while(1){
		/*pairnoume ena tyxaio i*/
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		/*pairnoume ena tyxaio j*/
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   /*elegxoume an h thesh 'i,j' ,einai kenh*/
			continue;
		table[i*M+j]='@';
		break;
	}
}

	

