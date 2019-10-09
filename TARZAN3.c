#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0

int N,M;    //oria tablo
int Ti,Tj;  //h thesh tou Tarzan
int tscore=0,rscore;   //synoliko(t) kai ana gyro(r) score

void printTable(char *table);
void hideTableMem(char *table);
int playGame(char *table, char *name);
void placeLions(char *table, int L);
void placeZoulou(char *table, int Z);
void placeTarzan(char *table);
void placeJane(char *table);
char* checkMoves(char* table,char* moves);
void unhideSquare(char* table,int i,int j);
void openRandomSquares(char* table,int i, int j);



int main()
{
int i,j,dif,L,Z,H,X,k,status;
char name[20];
char *table=NULL;
char mov[25]; //arxikopoieitai o arithmos kinhsewn
char start;
printf("\n");
printf("\n");
printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
printf("|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n");
printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
printf("Welcome to the 'Fifty Shades Of Tarzan' Game!!!\n");
printf("_______________________________________________\n");
printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
printf("|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n");
printf("\n");
printf("\n");

/*elegxos diastasewn*/
printf("Give height and length for the table: (BOTH MAXIMUM IN 30)\n");
do{
	scanf("%d %d", &N,&M);
	if(N<=30&&M<=30){
		if(N>=5&&M>=5){
			break;
		}
	}
	printf("Try again!\n");
}while(true);
printf("\n");



/*onoma paikth*/
printf("Give player name: (20 chars.)\n");
do{
	scanf("%s", name);
	if(strlen(name)<=20 && strlen(name)>0){
		break;
	}else{
		printf("Try another name...\n");
	}
}while(true);
printf("\n");



/*zhta to epipedo dyskolias ap'ton paikth*/
printf("Give difficulty level:\n");
printf("EASY:1 , NORMAL:2 , HARD:3 , EXPERT:4\n");
do{
	scanf("%d", &dif);
	if(dif==1 || dif==2 || dif==3 || dif==4){
		break;
	}
	printf("Try another number (1,2,3,4)...\n");
}while(dif==0 || dif>5);

printf("\n");


/*Instuctions*/
printf("You are T as Tarzan, the famous 'Man-Ape' of the jungle...");
printf("Objective: Find J as your beloved Jane, without getting killed\n");
printf("ENEMIES: L as Lions and Z as Zouloues\n");
printf("WARNING: if you get to 1 Lion, the Game is over\n");
printf("         if you get to 2 Zouloues, the Game is over\n");
printf("When you'll get to Jane, you'll procceed to the next level...\n");


printf("Press 'u' or 'U' for going 'Up'\n");
printf("Press 'd' or 'D' for going 'Down'\n");
printf("Press 'l' or 'L' for going 'Left'\n");
printf("Press 'r' or 'R' for going 'Right'\n");
printf("Press 'b' or 'B' to get a 'Bannana' and jump over a square\n");  
printf("REMEMBER: Put it right before one and only one move ----- for example: 'bu or BU')\n");
printf("WARNINIG: You have only 1 bannana available in every round. Use it wisely...\n");
printf("Press 'h' or 'H' to ask help, from the god 'Ugadugu',\n");
printf("and he will reveal two random squares for you to pass or avoid\n");
printf("WARNING: Every time you ask, you'll lose points. Use it wisely...\n");
printf("Press 'x' or 'X' to exit the game\n");



printf("if you wish, look up for instructions...\n");  //an o paikths thelei na dei tis odhgies, na koitaksei panw

while(true){
	rscore=1000;   //pairnoume to score tou gyrou
	//ypologismos liontariwn
	if(dif==1){
		L=N*M*((double)0.02);
	}else if(dif==2){
		L=N*M*((double)0.05);
	}else if(dif==3){
		L=N*M*((double)0.1);
	}else{
		L=N*M*((double)0.2);	
	}

	/*ypologismos zoulou*/
	Z=L*1.5;


	/*arxikopoihsh tablo*/
	if(table!=NULL)
		free(table);
	table=malloc(sizeof(char)*N*M);
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			table[(i*M)+j]='.';
		}
	}


	//topothetoume ta liontaria
	placeLions(table,L);
	//topothetoume tous zoulou 
	placeZoulou(table,Z);
	//topothetoume ton tarzan 	
	placeTarzan(table);
	//topothetoume th tzein 	
	placeJane(table);





	//ektypwnoume fanera to table
	printTable(table);
	printf("Player %s press 's'(for start) when ready...\n", name);
	do{
		scanf("%c", &start);  //frontizoume na arxisei o gyros otan pathsoume 's' h' 'S' gia 'start'
		if(start=='s' || start=='S'){
			break;
		}
	}while(start!='s' || start!='S');
	//twra gyrname ton pinaka anapoda
	hideTableMem(table);
	printTable(table);



	//KAI TWRA PAIZOUME!!
	status=playGame(table,name);   //edw mpainoume sth 'kyria synarthsh' tou paixnidiou
	tscore+=rscore;   //meiwnoume to score kathe fora pou teleiwnei o gyros
	printf("\n ROUND SCORE: %d points...\n", rscore);
	if(status==1 || status==2 || status==4){   //stis periptwseis status pou xanoume h' paraitoumaste...
		break;       //...termatizetai to paixnidi
	}else if(status==3){    //an kerdizoume ston gyro, megalwnetai o pinakas kata 1, eite se ypsos eite se platos, tyxaia th fora
		srand((int)time(NULL));
		double d1=(double)rand()/((double)RAND_MAX +1);
		if(d1<0.5 && N<30){   //ayksanetai to ypsos
			N+=1;
		}else if(M<30){   //ayksanetai to platos
			M+=1;
		}else{    //ftasame sto orio 30x30, opote termatisame
			printf("CONGRATULATIONS!!!!!\n YOU'RE NOW BEYOND JUNGLE!\n THE GAME IS FINISHED!!!\n");
		}
	}else if(status==4){  //otan akyrwnoume to paixnidi
		return 0;
	}
}
printf("\n FINAL SCORE: %d points!!! \n" ,tscore);   //teliko score
free(table);     //kai eleytherwnoume th mnhmh tou tablo
}



void printTable(char *table){
	int j,i;
	printf("\n \n \n ");
	//ektypwsh grammhs platous
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
			if((table[i*M+j]=='j') || (table[i*M+j]=='z') || (table[i*M+j]=='l') || (table[i*M+j]==' '))
				printf(" # ");
			else
				printf(" %c ", table[i*M+j]);
		}
		printf("\n");
	}
	printf("\n");
	
}


//kallyptoume ta squares tou table, kai shmeiwnoume ta stoixeia pou krybontai epishs
void hideTableMem(char *table){
	int i;
	for(i=0; i<N*M; i++){
		if(table[i]=='.')
			table[i]=' ';
		else if(table[i]=='J')
			table[i]='j';
		else if(table[i]=='Z')
			table[i]='z';
		else if(table[i]=='L')
			table[i]='l';
	}
}


int playGame(char *table, char *name){
	char moves[25];
	int i,j,status,zcount=0,k,bcount=1;
	//arxikopoioume me 0 ton pinaka twn kinhsewn
	for(i=0; i<25; i++)
		moves[i]=0;
	while(true){
		printf("Player %s make your move(s):\n", name);
		scanf("%s", moves);     //dinoume thn/is kinhsh/eis
		char *ret=checkMoves(table,moves);
		if(ret!=NULL){
			printf("%s\n", ret);
			continue;
		}
		

		//twra tha kinhsoume ton Tarzan
		k=0;
		while(k<strlen(moves)){ //elegxoume tis kinhseis mia mia..
			int mainTi=Ti,mainTj=Tj;
			if(table[Ti*M+Tj]=='T')
				table[Ti*M+Tj]='.';
			else if(table[Ti*M+Tj]=='@')
				table[Ti*M+Tj]='Z';
			status=0;
			switch(moves[k]){
				case 'U':     //Up
				case 'u':
					Ti=Ti-1;
					break;
				case 'D':     //Down
				case 'd':
					Ti=Ti+1;
					break;
				case 'L':     //Left
				case 'l':
					Tj=Tj-1;
					break;
				case 'R':     //Right
				case 'r':
					Tj=Tj+1;
					break;	
				case 'B':     //Bannana
				case 'b':
					if(bcount==0){    //an thn exeis ksanaxrhsimopoihsei, de mporeis pali s'ayto ton gyro
						Ti=mainTi;
						Tj=mainTj;
						table[Ti*M+Tj]='T';
						printTable(table);	
						printf("You already used your bannana... Next round or next time...\n");
						k++;
						continue;
					}
					bcount=0;
					if(moves[k+1]=='U' || moves[k+1]=='u'){   //h kinhsh meta thn 'b'
						Ti=Ti-1;
					}else if(moves[k+1]=='D' || moves[k+1]=='d'){
						Ti=Ti+1;
					}else if(moves[k+1]=='L' || moves[k+1]=='l'){
						Tj=Tj-1;
					}else if(moves[k+1]=='R' || moves[k+1]=='r'){
						Tj=Tj+1;
					}
					k++;
					continue;
						
					break;
				case 'H':     //Help
				case 'h':
					openRandomSquares(table,Ti,Tj);
					rscore-=30;
					table[Ti*M+Tj]='T';
					printTable(table);
					k++;
					continue;
				case 'X':     //Exit-Quit
				case 'x':
					status=4;
					break;

			}
			if(status==4){   //se periptwsh pou pathsoume to 'X' gia eksodo paixnidiou
				printTable(table);
				printf("QUITING GAME.....GAME OVER!!!\n");
				break;
			}
			//twra elegxoume ti brisketai sto kainourgio tetragwno
			if(table[Ti*M+Tj]=='l'){   //Lion
				table[Ti*M+Tj]='L';
				rscore-=50;
				printTable(table);
				printf("LION GOT YOU!!! THE GAME IS OVER!!!!!\n");
				status=4;
				break;
			}else if(table[Ti*M+Tj]=='z'){  //Zoulou
				zcount++;
				if(zcount==1){
					if(k==strlen(moves)-1)
						table[Ti*M+Tj]='@';
					else
						table[Ti*M+Tj]='Z';
					rscore-=20;
					printTable(table);
					printf("ATTACK FROM ZOULOU! HALF YOUR ENERGY LEFT...\n");
					k++;
				}else if(zcount==2){    //2nd Zoulou
					table[Ti*M+Tj]='Z';
					rscore-=20;
					printTable(table);
					printf("ANOTHER ATTACK FROM ZOULOU! GAME OVER!!!!!!\n");
					status=4;
					break;
				}				
			}else if(table[Ti*M+Tj]=='j'){    //Jane
				table[Ti*M+Tj]='J';
				printTable(table);
				printf("YOU FOUND JANE!!! :) :) NOW PROCEED TO THE NEXT LEVEL:\n");
				status=3;
				break;
			}else if(table[Ti*M+Tj]=='.' || table[Ti*M+Tj]=='Z'){    //prosperasmeno square
				Ti=mainTi;
				Tj=mainTj;
				table[Ti*M+Tj]='T';
				printTable(table);
				printf("You've been before in this resulting place. Try again!...\n");
				break;				
			}else{
			//kenh nea thesh. apla ektypwnoume
				table[Ti*M+Tj]='T';
				printTable(table);				
			}
			k++;
			
		}
		rscore-=5;
		if(rscore<=0){    //to score mhdenisthke
			printf("THE SCORE IS DEPLETED!!! GAME OVER!!! AND NEXT TIME BE CAREFUL ;)\n");
			break;
		}
		if(status>0)  //otan peseis stis periptwseis pou teleiwneis ston gyro h' xaneis sto paixnidi
			break;		
	}
	return status;
	
}



//h synarthsh edw elegxei an o xrhsths exei plhktrologisei 'h' h' 'H', xwris alla grammata h' an ayta pou exei plhktrologisei, einai egkyra.
//epistrefei NULL se periptwsh pou nai lathos kai ektypwnei analoga mhnyma sthn othonh 
char* checkMoves(char* table,char* moves){
	if( (strstr(moves,"H") || strstr(moves, "h")) && strlen(moves)>1 ){
		return "Try again without combining 'moves' with 'help'...\n";
	}
	if(strspn(moves, "UDLRBXHudlrbxh") != strlen(moves)){
		return "Try again with the right moves: U,D,L,R,B,H,X,u,d,l,r,b,h,x \n";
	}
	
	int i=Ti,j=Tj,k=0,status=0;
		while(k<=strlen(moves)){  //elegxoume edw mia mia tis kinhseis
			switch(moves[k]){
				case 'U':
				case 'u':
					i=i-1;
					//elegxoume an h kinhsh einai egkyrh
					if(i<0){
						printf("Not valid move. (%d) Please try again\n", i);
						return "Out of bounds...\n";  //elegxei dhladh an einai mes sta synora tou table
					}
					break;
				case 'D':
				case 'd':
					i=i+1;
					//elegxoume an h kinhsh einai egkyrh
					if(i>=N){
						printf("Not valid move. (%d) Please try again\n", i);
						return "Out of bounds...\n";  //elegxei dhladh an einai mes sta synora tou table
					}
					break;
				case 'L':
				case 'l':
					j=j-1;
					//elegxoume an h kinhsh einai egkyrh
					if(j<0){
						printf("Not valid move. (%d) Please try again\n", j);
						return "Out of bounds...\n";  //elegxei dhladh an einai mes sta synora tou table
					}
					break;
				case 'R':
				case 'r':
					j=j+1;
					//elegxoume an h kinhsh einai egkyrh
					if(j>=M){
						printf("Not valid move. (%d) Please try again\n", j);
						return "Out of bounds...\n";  //elegxei dhladh an einai mes sta synora tou table
					}
					break;
				
			}
			k++;
		}
	return NULL;
}

//topothetoume ta liontaria...
void placeLions(char *table, int L){
	int k=0;
	srand((int)time(NULL));
	while(k<L){
		//pairnoume ena tyxaio i
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		//pairnoume ena tyxaio j
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   //elegxoume an h thesh 'i,j' ,einai kenh
			continue;
		table[i*M+j]='L';
		k++;
	}	
}
//topothetoume tous zoulou
void placeZoulou(char *table, int Z){
	int k=0;
	srand((int)time(NULL));
	while(k<Z){
		//pairnoume ena tyxaio i
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		//pairnoume ena tyxaio j
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   //elegxoume an h thesh 'i,j' ,einai kenh
			continue;
		table[i*M+j]='Z';
		k++;
	}
}
//topothetoume ton Tarzan
void placeTarzan(char *table){
	int k=0;
	srand((int)time(NULL));
	while(true){
		//pairnoume ena tyxaio i
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		//pairnoume ena tyxaio j
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   //elegxoume an h thesh 'i,j' ,einai kenh
			continue;
		table[i*M+j]='T';
		Ti=i;
		Tj=j;
		break;
	}
}
//topothetoume thn Jane
void placeJane(char *table){
	int k=0;
	srand((int)time(NULL));
	while(true){
		//pairnoume ena tyxaio i
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*N;
		int i=(int)d1;
		//pairnoume ena tyxaio j
		double d2=(double)rand()/((double)RAND_MAX +1);
		d2=d2*M;
		int j=(int)d2;
		if(table[i*M+j]!='.')   //elegxoume an h thesh 'i,j' ,einai kenh
			continue;
		table[i*M+j]='J';
		break;
	}
}

//apokalyptoume to krymmeno tetragwno pou epileksame mesw tou 'Help'
void unhideSquare(char* table,int i,int j){
	if(table[i*M+j]==' '){
		table[i*M+j]='.';
	}else if(table[i*M+j]=='j'){
		table[i*M+j]='J';
	}else if(table[i*M+j]=='z'){
		table[i*M+j]='Z';
	}else if(table[i*M+j]=='l'){
		table[i*M+j]='L';
	}
}

//anoigoume ta tyxaia 2 tetragwna, logw ths entolhs 'H' gia bohtheia...
void openRandomSquares(char* table,int i, int j){
	int di[4],dj[4],y=0;  //di kai dj symbolizoun ta krymmena gyrw tetragwna (deksia-aristera-panw-katw),ap'ta opoia tha paroume ta 2 tyxaia
	int z,w,r,k=0;
	srand((int)time(NULL));
	for(z=0; z<4; z++){
		di[z]=-1;
		dj[z]=-1;
	}
	// Elegxoume mia-mia tis 4 geitwnikes theseis kai an einai kenes, tote tis bazoume stin lista gia na epileksoume tis 2 apo aftes
	z=i-1; w=j; // Panw
	if(!(z<0 || z>=N || w<0 || w>=M || (z==i && w==j))) { //elegxoume an oi nees diastaseis einai egkyres. dhladh eimaste entos oriwn tou pinaka kai oxi sto tetragwno tou tarzan
		if(!(table[z*M+w]!=' ' && table[z*M+w]!='j' && table[z*M+w]!='z' && table[z*M+w]!='l')) { //elegxoume an to tetragwno einai krymmeno
			di[y]=z;
			dj[y]=w;
			y++;
		}
	}
	z=i; w=j+1; // Deksia
	if(!(z<0 || z>=N || w<0 || w>=M || (z==i && w==j))) { //elegxoume an oi nees diastaseis einai egkyres. dhladh eimaste entos oriwn tou pinaka kai oxi sto tetragwno tou tarzan
		if(!(table[z*M+w]!=' ' && table[z*M+w]!='j' && table[z*M+w]!='z' && table[z*M+w]!='l')) { //elegxoume an to tetragwno einai krymmeno
			di[y]=z;
			dj[y]=w;
			y++;
		}
	}
	z=i+1; w=j; // Katw
	if(!(z<0 || z>=N || w<0 || w>=M || (z==i && w==j))) { //elegxoume an oi nees diastaseis einai egkyres. dhladh eimaste entos oriwn tou pinaka kai oxi sto tetragwno tou tarzan
		if(!(table[z*M+w]!=' ' && table[z*M+w]!='j' && table[z*M+w]!='z' && table[z*M+w]!='l')) { //elegxoume an to tetragwno einai krymmeno
			di[y]=z;
			dj[y]=w;
			y++;
		}
	}
	z=i; w=j-1; // Aristera
	if(!(z<0 || z>=N || w<0 || w>=M || (z==i && w==j))) { //elegxoume an oi nees diastaseis einai egkyres. dhladh eimaste entos oriwn tou pinaka kai oxi sto tetragwno tou tarzan
		if(!(table[z*M+w]!=' ' && table[z*M+w]!='j' && table[z*M+w]!='z' && table[z*M+w]!='l')) { //elegxoume an to tetragwno einai krymmeno
			di[y]=z;
			dj[y]=w;
			y++;
		}
	}
	// Twra to y periexei ton arithmo twn tetreagwnwn pou mporoume na apokalipsoume
	if (y==0) { // Den yparxoun krymmena tetragwna
		printf("There are no hedden sqares\n");
		return;
	}
	// epilegoume 2 tyxaia tetragwna apo tin lista pou ftiaksame me ta geitwnika tetragwna pou mporoun na apokalyfthoun
	for(r=0; r<2; r++){
		//pairnoume ena tyxaio y
		double d1=(double)rand()/((double)RAND_MAX +1);
		d1=d1*y;
		int d=(int)d1;
		unhideSquare(table,di[d],dj[d]);
	}
}

