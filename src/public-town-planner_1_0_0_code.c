
// Public-Town-Planner version 1.0.0

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int pop,mon,nr,nc,nf,ns,nw,st,adm;
int akt;
int py,px;
int i,j;
char world[28][46],a,aw[28][45],name[31];

void status() {
	if (pop < 10) st = 1;
	if ((pop >= 10) && (pop < 120)) st = 2;
	if ((pop >= 120) && (pop < 500)) st = 3;
	if ((pop >= 500) && (pop < 2000)) st = 4;
	if (pop >= 2000) st = 5;
}

void build() {
	if (a == 'e') {
		if (aw[py][px] == ' ') {
			printf("\n:");
			a = getch();
			if ((a == 'r') && (mon >= 2)) aw[py][px] = '^',nr++,mon-=2;
			if ((a == 'c') && (mon >= 2)) aw[py][px] = 'C',nc++,mon-=2;
			if ((a == 'f') && (mon >= 2)) aw[py][px] = '#',nf++,mon-=2;
			if ((a == 's') && (mon >= 6)) aw[py][px] = '@',ns++,mon-=6;
			if ((a == 'w') && (mon >= 1)) aw[py][px] = '=',nw++,mon-=1;
			if ((a == 'a') && (mon >= 12)) aw[py][px] = '!',adm++,mon-=12;
		}
	}
	if (a == 'x') {
		if (aw[py][px] == '^') nr--,mon++;
		if (aw[py][px] == 'C') nc--,mon++;
		if (aw[py][px] == '#') nf--,mon++;
		if (aw[py][px] == '@') ns--,mon+=2;
		if (aw[py][px] == '=') nw--,mon++;
		if (aw[py][px] == '!') adm--,mon+=5;
		aw[py][px] = ' ';
	}
}

void balance() {
	int o_mon = mon;
	int mnmon = 0;
	if (adm < 1) {
		printf("\nNo administration!");
		mon-=5;
	}
	else if ((ns < nr/10) || (ns < 1)) {
		printf("\nNo energy!");
		if (nr > 1) pop-=3;
	}
	else if (nw < nr-3) {
		printf("\nNo roads!");
	}
	else {
		if (mon < 1) {
			printf("\nNo money!");
			pop-=2;
		}
		else if ((nr < 1) || (nr < pop/14)) {
			printf("\nNo housing!");
		}
		else pop+=2;
		if (pop > 1) mon+=nc*2.5;
	}
	if (mon > pop*6) mon = o_mon;
	if (nf < nr/2) {
		printf("\nNo factories!");
		mnmon = nr/2;
		mnmon -= nf;
		mon-=mnmon,pop--;
	}
	if (pop > 0) mon -= pop/10;
}

void start_world()
{
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 45; j++) {
			aw[i][j] = ' ';
		}
	}
}

void map()
{
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 45; j++) {
			world[i][j] = aw[i][j];
		}
		world[i][45] = '\0';
	}
	if ((py > 27) || (px > 44) || (py < 0) || (px < 0)) py = 15,px = 22;
	world[py][px] = '>';
}

int main()
{
	printf("\nPUBLIC DOMAIN SOFTWARE");
	printf("\nPublic-Town-Planner");
	printf("\nVersion 1.0.0\n");
	printf("\nCity name:");
	scanf("%s",&name);
	name[30] = '\0';
	akt = 1;
	pop = 10,mon = 100;
	px = 22,py = 15;
	nr = 0,nc = 0,nf = 0,ns = 0,nw = 0,adm = 0;
	start_world();
	do
	{
		map();
		status();
		for (i = 0; i < 28; i++) {
			printf("\n%s",world[i]);
		}
		printf("\nName: %s",name);
		balance();
		if (mon < 0) mon = 0;
		if (pop < 0) pop = 0;
		printf("\n$: %d",mon);
		printf("\nPopulation: %d",pop*100);
		printf("\nStatus: ");
		if (st == 1)
			printf("Village");
		if (st == 2)
			printf("Town");
		if (st == 3)
			printf("Medium city");
		if (st == 4)
			printf("Big city");
		if (st == 5)
			printf("Megapolis");
		a = getch();
		printf("\033[H\033[2J\033[3J");
		if (a == 'w') py--;
		if (a == 's') py++;
		if (a == 'd') px++;
		if (a == 'a') px--;
		build();
		if (a == 'q') akt = 0;
	}
	while (akt == 1);
	return 0;
}