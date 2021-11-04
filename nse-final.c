#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<string.h>
void level_2(int buyCost,int sellCost){
    printf("\n'LEVEL 2 OF NSE'\n");
    if(buyCost == 0){
        printf("BUYER'S BID: \n");
    }else{
        printf("BUYER'S BID: %d\n",buyCost);
    }
    if(sellCost == INT_MAX){
        printf("SELLER'S BID: \n");
    }else{
        printf("SELLER'S BID: %d\n",sellCost);
    }
}

void level_3(int sales){
	FILE *write=fopen("write_file.csv","a");
	if(write==NULL){
		printf("Error in opening the file");
	}else{
    printf("\n'LEVEL 3 OF NSE'\n");
    printf("SALE = %d\n",sales);
    printf("Time %s %s",__DATE__,__TIME__);
	fprintf(write,"%s,%s,%d\n",__DATE__,__TIME__,sales);
	}
}

void level_1(char typTemp,int idTemp,int quantTemp,int costTemp,int* id,int* buyCost,int* buyQuant,int* sellCost,int* sellQuant,int* copyBp,int* copySp){
    
    if(typTemp == 'b'|| typTemp == 'B'){
        (*copyBp)++;
        int store=-1,i = 0;
        while(costTemp < buyCost[i]){
            i++;
        }
        
        store = i;
        while(buyCost[i] != 0){
             i++;
        }

        while(i != store){
            buyCost[i] = buyCost[i-1];
            buyQuant[i] = buyQuant[i-1];
            i--;
        }
        buyCost[i] = costTemp; 
        buyQuant[i] = quantTemp;
    }

    if(typTemp == 's'|| typTemp == 'S'){
        (*copySp)++;
        int store=-1,i = 0;
        while(costTemp > sellCost[i]){
            i++;
        }

        store = i;
        while(sellCost[i] != INT_MAX){
             i++;
        }

        while(i != store){
            sellCost[i] = sellCost[i-1];
            sellQuant[i] = sellQuant[i-1];
            i--;
        }
        sellCost[i] = costTemp; 
        sellQuant[i] = quantTemp;
    }
}
void printlevel1(char typTemp,int idTemp,int quantTemp,int costTemp,int* id,int* buyCost,int* buyQuant,int* sellCost,int* sellQuant,int* copyBp,int* copySp){
    printf("\n'LEVEL 1 OF NSE'\n");
    printf("\n");
    printf("BUYERS COLUMN\n");
    for(int i=0;i<(*copyBp);i++){
        printf("%d ",buyCost[i]);
    }
    printf("\n");
    for(int i=0;i<(*copyBp);i++){
        printf("%d ",buyQuant[i]);
    }
    printf("\n"); 
    printf("\n");
    printf("SELLERS COLUMN\n");
    for(int i=0;i<(*copySp);i++){
        printf("%d ",sellCost[i]);
    }
    printf("\n");
    for(int i=0;i<(*copySp);i++){
        printf("%d ",sellQuant[i]);
    }
    printf("\n");

}
void updateS(int* sellCost,int* sellQuant,int* copySp){
    
    for(int i=0;i<999;i++){
        sellCost[i] = sellCost[i+1];
        sellQuant[i] = sellQuant[i+1];
    }
    (*copySp) = (*copySp)-1;
    
}
void updateB(int* buyCost,int* buyQuant,int* copyBp){
    
    for(int i=0;i<999;i++){
        buyCost[i] = buyCost[i+1];
        buyQuant[i] = buyQuant[i+1];
    }
    (*copyBp) = (*copyBp)-1;
    
}
void exchageWithSeller(char typTemp,int idTemp,int quantTemp,int costTemp,int* id,int* buyCost,int* buyQuant,int* sellCost,int* sellQuant,int* copyBp,int* copySp){

    while(costTemp >= sellCost[0] && quantTemp >= sellQuant[0]){
        level_3(sellCost[0]);
        quantTemp -= sellQuant[0];
        updateS(sellCost,sellQuant,copySp);
        if(quantTemp==sellQuant[0]){
            level_2(buyCost[0],sellCost[0]);
        }else{
            level_2(costTemp,sellCost[0]);
        }
    }
    if(quantTemp == 0){
        return;
    }
    if(costTemp < sellCost[0]){
        level_1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
        printlevel1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
	    quantTemp=0;
    }
    if(quantTemp == 0){
        return;
    }
    if(quantTemp < sellQuant[0]){
        level_3(sellCost[0]);

        typTemp = 's';
        quantTemp = sellQuant[0] - quantTemp;
        costTemp = sellCost[0];
        updateS(sellCost,sellQuant,copySp);
        level_1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
	    printlevel1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
        level_2(buyCost[0],sellCost[0]);
    }
}
void exchageWithBuyer(char typTemp,int idTemp,int quantTemp,int costTemp,int* id,int* buyCost,int* buyQuant,int* sellCost,int* sellQuant,int* copyBp,int* copySp){

    while(costTemp <= buyCost[0] && quantTemp >= buyQuant[0]){
        level_3(buyCost[0]);
        quantTemp -= buyQuant[0];
        updateB(buyCost,buyQuant,copyBp);
        if(quantTemp==buyQuant[0]){
            level_2(buyCost[0],sellCost[0]);
        }else{
            level_2(buyCost[0],costTemp);
        }
    }
    if(quantTemp == 0){
        return;
    }
    
    if(costTemp > buyCost[0]){
        level_1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
	    printlevel1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
        quantTemp = 0;
    }
     if(quantTemp == 0){
        return;
    }
    if(quantTemp < buyQuant[0]){
        level_3(buyCost[0]);

        typTemp = 'b';
        quantTemp = buyQuant[0] - quantTemp;
        updateB(buyCost,buyQuant,copyBp);
        level_1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
	    printlevel1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
        level_2(buyCost[0],sellCost[0]);
    }
}

int main(){
	
	FILE *read=fopen("read_file.csv","r");
	if(read == NULL ){
		printf("Error in opening the file");
	}
	else{
    static int id[1000],buyCost[1000],buyQuant[1000],sellCost[1000],sellQuant[1000];

    for(int i=0;i<1000;i++){
        sellCost[i] =  INT_MAX;
    }
	int idTemp=0,costTemp=0,quantTemp=0;
        char typTemp,tickerTemp='a';
    
    int copyB=0,copyS=0,t;
    int* copyBp = &copyB;
    int* copySp = &copyS;
    //printf("Enter the number of test cases:\n");
    //scanf("%d",&t);
	char tempStr[100];
    while(fgets(tempStr,100,read)!=NULL){
	char *str;
	str=strtok(tempStr,",");
	typTemp=str[0];
	str=strtok(NULL,",");
	costTemp=atoi(str);
	str=strtok(NULL,",");
	quantTemp=atoi(str);

        
        //scanf("%d",&idTemp);
        //scanf("%c",&tickerTemp);
	    
        // printf("Enter the type of your order(B or S):\n");
        // fflush(stdin);
        // scanf("%c",&typTemp);
        // fflush(stdin);
        // printf("Enter the cost of each stock:\n");
        // scanf("%d",&costTemp);
        //printf("Enter the number of stocks you want to buy/sell:\n");
        //scanf("%d",&quantTemp);
        //printf("Ã°Å¸ËœÅ ");
        if((typTemp == 'b'|| typTemp == 'B')&& costTemp >= sellCost[0]){
            exchageWithSeller(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
            continue;
        }
        if((typTemp == 's'|| typTemp == 'S')&& costTemp <= buyCost[0]){
            exchageWithBuyer(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
            continue;
        }
        level_1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
        printlevel1(typTemp,idTemp,quantTemp,costTemp,id,buyCost,buyQuant,sellCost,sellQuant,copyBp,copySp);
        level_2(buyCost[0],sellCost[0]);
    }
	}
}

