/*
 * TOPIC : LIBRARY MAANGEMENT

 * MINI PROJECT BY:
		1)ANSARI NOORAS FATIMA - 16CO01
		2)KALADIYA ILAF - 16CO03
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct lib
{
	char book[25];
	char author[25];
	char pub[25];
	int count;
	struct lib *next;
}node; 

typedef struct member
{
	int mid;
	char mname[25];
	int libcard;
	struct member *nextt;
}nod;

FILE *brecord;
FILE *mrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;

void add(node **b,char bk[],char au[],char p[])
{ 
	node *ptr,*temp;
	ptr=(node*)malloc(sizeof(node));
	strcpy(ptr->book,bk);
	strcpy(ptr->author,au);
	strcpy(ptr->pub,p);
	ptr->count=5;
	ptr->next=NULL;
	temp=*b;
	if(temp==NULL)
		*b=ptr;
	else
	{
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=ptr;
	}
	brecord=fopen("brecord.txt","a+");
	fprintf(brecord,"\n%s\t%s\t%s\t%d\n",ptr->book,ptr->author,ptr->pub,ptr->count);
	fclose(brecord);
	printf("\nA NEW BOOK ADDED...\n");
}

void addMemb(nod **m,char name[],int rno)
{
	nod *ptr,*temp;
	ptr=(nod*)malloc(sizeof(nod));
	strcpy(ptr->mname,name);
	ptr->mid=rno;
	ptr->libcard=2;
	ptr->nextt=NULL;
	temp=*m;
	if(temp==NULL)
		*m=ptr;
	else
	{
		while(temp->nextt!=NULL)
			temp=temp->nextt;
		temp->nextt=ptr;
	}
	mrecord=fopen("mrecord.txt","a+");
	fprintf(mrecord,"\n%s\t%d\t%d\n",ptr->mname,ptr->mid,ptr->libcard);
	fclose(mrecord);
	printf("\nA NEW MEMBER ADDED...\n");
}
void dispBook()
{
	node *ptr;
	ptr=(node*)malloc(sizeof(node));
	brecord=fopen("brecord.txt","r");
	printf("\nRECORD OF BOOKS:\n");
	printf("BOOK NAME\tAUTHOR NAME\tPUBLICATION\tNO OF COPIES\n");
	do
	{
		fscanf(brecord,"\n%s\t%s\t%s\t%d\n",ptr->book,ptr->author,ptr->pub,&ptr->count);
		printf("\n%s\t\t%s\t\t%s\t\t%d\n",ptr->book,ptr->author,ptr->pub,ptr->count);
	}while(!feof(brecord));
	fclose(brecord);
}

void dispMem()
{
	nod *ptr;
	ptr=(nod*)malloc(sizeof(nod));
	mrecord=fopen("mrecord.txt","r");
	printf("\nRECORD OF MEMBER:\n");
	printf("MEMBER NAME\tId\tLIBRARY CARD\n");
	do
	{
		fscanf(mrecord,"\n%s\t%d\t%d\n",ptr->mname,&ptr->mid,&ptr->libcard);
		printf("\n%s\t\t%d\t%d\n",ptr->mname,ptr->mid,ptr->libcard);
	}while(!feof(mrecord));
	fclose(mrecord);
}

void search_book()
{
	node *ptr;
	ptr=(node*)malloc(sizeof(node));
	char goal[25];
	int found=0;
	if((brecord=fopen("brecord.txt","r"))==NULL)
	{
		printf("EMPTY FILE!!\n");
	}
	else 
	{
		printf("\nBOOKS BY BOOK NAME : \n");
		printf("\nENTER NAME OF THE BOOK YOU WANT TO SEARCH : \n");
		scanf("%s",goal);
		while(!feof(brecord) && found==0)
		{
			fscanf(brecord,"\n%s\t%s\t%s\t%d\n",ptr->book,ptr->author,ptr->pub,&ptr->count);
			if(strcmp(goal,ptr->book)==0)
				found=1;
		}
		if(found)
			printf("\nNAME OF BOOK : %s\nAUTHOR : %s\nPUBLICATION : %s\nCOPIES : %d\n",ptr->book,ptr->author,ptr->pub,ptr->count);
		else
			printf("\nNO SUCH BOOK IN LIBRARY!!\n");
	}
	fclose(brecord);
}
	
void search_author()
{
	node *ptr;
	ptr=(node*)malloc(sizeof(node));
	char goal[25];
	int found=0;
	if((brecord=fopen("brecord.txt","r"))==NULL)
	{
		printf("EMPTY FILE!!");
	}
	else 
	{
		printf("\nBOOKS BY AUTHOR : \n");
		printf("\nENTER NAME OF THE AUTHOR YOU WANT TO SEARCH : \n");
		scanf("%s",goal);
		
		while(!feof(brecord) && found==0)
		{
			fscanf(brecord,"\n%s\t%s\t%s\t%d\n",ptr->book,ptr->author,ptr->pub,&ptr->count);
			if(strcmp(goal,ptr->author)==0)
			found=1;
		}
		if(found)
			printf("\nNAME OF BOOK : %s\nAUTHOR : %s\nPUBLICATION : %s\nCOPIES : %d\n",ptr->book,ptr->author,ptr->pub,ptr->count);
		else
			printf("\nNO SUCH BOOK OF AUTHOR IN LIBRARY!!\n");
	}
	fclose(brecord);
	
}	

void issue_book()
{
	node *pr;
	pr=(node*)malloc(sizeof(node));
	nod *ptr;
	ptr=(nod*)malloc(sizeof(nod));
	int mbid,f1=0,f2=0;
	char issue_book_name[25];
	printf("\nENTER USER ID OF MEMBER:");
	scanf("%d",&mbid);
	if((mrecord=fopen("mrecord.txt","r"))==NULL)
	{
		printf("\nEMPTY FILE!!\n");
	}
	else
	{
		while(!feof(mrecord) && f1==0)
		{
			fscanf(mrecord,"\n%s\t%d\t%d\n",ptr->mname,&ptr->mid,&ptr->libcard);
			if(mbid==ptr->mid)
				f1=1;
		}
		if(f1)
		{
			if(ptr->libcard < 1)
				printf("\nLIBRARY CARD NOT AVAILABLE...\n");
			else
			{
				printf("\nENTER NAME OF BOOK : ");
				scanf("%s",issue_book_name);
				if((brecord=fopen("brecord.txt","r"))==NULL)
				{
					printf("\nEMPTY FILE!!\n");
				}
				else
				{
					while(!feof(brecord) && f2==0)
					{
						fscanf(brecord,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,&pr->count);
						if(strcmp(issue_book_name,pr->book)==0)
							f2=1;
					}
					if(f2)
					{
						if(pr->count==0)
						{
                            printf("\nBOOK ALREADY ISSUED\n");
						}
						else
						{
							fp2=fopen("fp2.txt","w");
							if((temp2=fopen("mrecord.txt","r"))==NULL)
                                printf("\nEMPTY FILE!!\n");
                            else
                            {
                                while(!feof(temp2))
                                {
									fscanf(temp2,"\n%s\t%d\t%d\n",ptr->mname,&ptr->mid,&ptr->libcard);
									if(mbid==ptr->mid)
									{
										ptr->libcard=ptr->libcard-1;
										fprintf(fp2,"\n%s\t%d\t%d\n",ptr->mname,ptr->mid,ptr->libcard);
									}
									else
									{
										fprintf(fp2,"\n%s\t%d\t%d\n",ptr->mname,ptr->mid,ptr->libcard);
									}
   								}
							}
							fclose(temp2);
							fclose(fp2);
							fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("brecord.txt","r"))==NULL)
                                printf("\nEMPTY FILE\n");
                            else
                            {
								printf("\nBOOK NAME\tAUTHOR NAME\tPUBLICATION\tNO OF COPIES\n");
                                while(!feof(temp1))
                                {	
									
									fscanf(temp1,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,&pr->count);
                                    if(strcmp(issue_book_name,pr->book)!=0)
									{
										
										printf("\n%s\t\t%s\t\t%s\t\t%d\n",pr->book,pr->author,pr->pub,pr->count);
										fprintf(fp1,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,pr->count);
									}
									else
									{
										pr->count=pr->count-1;
										printf("\n%s\t\t%s\t\t%s\t\t%d\n",pr->book,pr->author,pr->pub,pr->count);
										fprintf(fp1,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,pr->count);
									}
								}
							}
							fclose(temp1);
							fclose(fp1);
							fclose(brecord);
							fclose(mrecord);
							remove("brecord.txt");
							rename("fp1.txt","brecord.txt");
							remove("mrecord.txt");
							rename("fp2.txt","mrecord.txt");
							printf("\nBOOK SUCCESSFULLY ISSUED...\n");
						}
					}
					else 
                      printf("\nTHERE IS NO SUCH BOOK!!\n");
				}
			}
		}
		else 
          printf("INVALID USER ID!!\n");
	}
}

void return_book()
{
	node *pr;
	pr=(node*)malloc(sizeof(node));
	nod *ptr;
	ptr=(nod*)malloc(sizeof(nod));
	int mbid,f1=0,f2=0;
	char return_book_name[25];
	printf("\nENTER USER ID OF MEMBER :");
	scanf("%d",&mbid);
	if((mrecord=fopen("mrecord.txt","r"))==NULL)
	{
		printf("\nEMPTY FILE!!");
	}
	else 
	{
		while(!feof(mrecord) && f1==0)
		{
			fscanf(mrecord,"\n%s\t%d\t%d\n",ptr->mname,&ptr->mid,&ptr->libcard);
			if(mbid==ptr->mid)
			{
				f1=1;
			}
		}
		if(f1)
		{
			if(ptr->libcard>=2)
			{
				printf("\nYOU HAVEN'T ISSUED ANY BOOK...\n");
			}
			else
			{
				printf("\nENTER NAME OF THE BOOK : ");
				scanf("%s",return_book_name);
				if((brecord=fopen("brecord.txt","r"))==NULL)
				{
					printf("\nEMPTY FILE!!");
				}
				else
				{
					while(!feof(brecord) && f2==0)
					{
						fscanf(brecord,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,&pr->count);
						if(strcmp(return_book_name,pr->book)==0)
							f2=1;
					}
					if(f2)
					{
						if(pr->count==5)
						{
                            printf("\nBOOK ALREADY PRESENT IN LIBRARY...\n");
						}
						else
						{
							fp2=fopen("fp2.txt","w");
							if((temp2=fopen("mrecord.txt","r"))==NULL)
                                printf("EMPTY FILE!!\n");
                            else
                            {
                                while(!feof(temp2))
                                {
									fscanf(temp2,"\n%s\t%d\t%d\n",ptr->mname,&ptr->mid,&ptr->libcard);
									if(mbid==ptr->mid)
									{
										ptr->libcard=ptr->libcard+1;
										fprintf(fp2,"\n%s\t%d\t%d\n",ptr->mname,ptr->mid,ptr->libcard);
									}
									else
									{
										fprintf(fp2,"\n%s\t%d\t%d\n",ptr->mname,ptr->mid,ptr->libcard);
									}
									if(feof(temp2))
										break;
   								}
							}
							fclose(temp2);
							fclose(fp2);
							fp1=fopen("fp1.txt","w");
							if((temp1=fopen("brecord.txt","r"))==NULL)
								printf("EMPTY FILE!!\n");
							else
							{
								printf("\nBOOK NAME\tAUTHOR NAME\tPUBLICATION\tNO OF COPIES\n");
								while(!feof(temp1))
								{	
									fscanf(temp1,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,&pr->count);
									if(strcmp(return_book_name,pr->book)!=0)
									{
										printf("\n%s\t\t%s\t\t%s\t\t%d\n",pr->book,pr->author,pr->pub,pr->count);
										fprintf(fp1,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,pr->count);
									}
									else
									{
										pr->count=pr->count+1;
										printf("\n%s\t\t%s\t\t%s\t\t%d\n",pr->book,pr->author,pr->pub,pr->count);
										fprintf(fp1,"\n%s\t%s\t%s\t%d\n",pr->book,pr->author,pr->pub,pr->count);
									}
								}
							}
							fclose(temp1);
							fclose(fp1);
							fclose(brecord);
							fclose(mrecord);
							remove("brecord.txt");
							rename("fp1.txt","brecord.txt");
							remove("mrecord.txt");
							rename("fp2.txt","mrecord.txt");
							printf("\nBOOK SUCCESSFULLY RETURNED...\n");
		                }
					}
					else 
                      printf("\nTHERE IS NO SUCH BOOK!!\n");
				}
			}
		}
		else 
          printf("\nINVALID USER ID!!\n");
	}
}



int main()
{
	node *start,*temp;
	nod *first,*tempp;
	int i,n;
	int j,k;
	char bo[25],at[25],pb[25]; 
	char name[25];
	int rno;
	int ch;
	printf("\t\t\t\t\t\t-----INDIAN PIBLIC LIBRARY-----\n");
	printf("\n\t\t\t\t\t\t\t----WELCOME----\n\n");
	do
	{
		
		printf("\n1.ADD BOOK \n2.ADD MEMBER\n3.DISPLAY ALL BOOKS\n4.DISPLAY ALL MEMBERS\n5.SEARCH A BOOK\n6.SEARCH BOOKS OF AN AUTHOR\n7.ISSUE A BOOK\n8.RETURN A BOOK\n9.EXIT\n");
		printf("\nENTER YOUR CHOICE : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nENTER NUMBER OF BOOKS : ");
				scanf("%d",&n);
				printf("\nENTER DETAILS OF BOOK NO. 1: \n");
				start=(node*)malloc(sizeof(node));
				printf("\nENTER NAME OF BOOK: \n");
				scanf("%s",start->book);
				printf("ENTER NAME OF AUTHOR: \n");
				scanf("%s",start->author);
				printf("ENTER NAME OF PUBLICATION: \n");
				scanf("%s",start->pub);
				start->count=5;
				temp=start;
				brecord=fopen("brecord.txt","a+");
				fprintf(brecord,"\n%s\t%s\t%s\t%d\n",start->book,start->author,start->pub,start->count);
				fclose(brecord);
				printf("\nA NEW BOOK ADDED\n");
				for(i=1;i<n;i++)
				{
					printf("\nENTER DETAILS OF BOOK NO. %d: \n",i+1);
					temp->next = NULL;
					printf("\nENTER NAME OF BOOK: \n");
					scanf("%s",bo);
					printf("ENTER NAME OF AUTHOR: \n");
					scanf("%s",at);
					printf("ENTER NAME OF PUBLICATION: \n");
					scanf("%s",pb);
					add(&start,bo,at,pb);
				}
				break;
			case 2:
				printf("\nENTER NUMBER OF MEMBERS : ");
				scanf("%d",&k);
				printf("\nENTER DETAILS OF MEMBER NO. 1: \n");
				first=(nod*)malloc(sizeof(nod));
				printf("\nENTER NAME OF MEMBER: \n");
				scanf("%s",first->mname);
				printf("ENTER ROLLNO OF MEMBER: \n");
				scanf("%d",&first->mid);
				printf("\nA NEW MEMBER ADDED\n");
				first->libcard=2;
				tempp=first;
				mrecord=fopen("mrecord.txt","a+");
				fprintf(mrecord,"\n%s\t%d\t%d\n",first->mname,first->mid,first->libcard);
				fclose(mrecord);
				for(j=1;j<k;j++)
				{
					printf("\nENTER DETAILS OF MEMBER NO. %d: \n",j+1);
					tempp->nextt = NULL;
					printf("\nENTER NAME OF MEMBER: \n");
					scanf("%s",name);
					printf("ENTER ROLL NO OF MEMBER: \n");
					scanf("%d",&rno);
					addMemb(&first,name,rno);
				}
				break;
			case 3:
				dispBook();
				break;
			case 4:
				dispMem();
				break;
			case 5:
				search_book();
				break;
			case 6:
				search_author();
				break;
			case 7:
				issue_book();
				break;
			case 8:
				return_book();
				break;
			case 9:
				exit(0);
				break;
			default:
				printf("\nINVALID CHOICE\n");
		}
	}while(1);
	return 0;
}

