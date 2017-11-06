// shannon.cpp : Defines the entry point for the console application.
//
#include<stdio.h>
#include<string.h>
struct node
{
	char sym[10];
	float pro;
	int s[20];

}s[20];
typedef struct node node;

int g_level = 0;
void shannon(int start,int end,node s[], char code[20][20],int level)
{
    int i=start;
    int j=end;
    float isum = s[i].pro,jsum = s[j].pro;

    if(level>g_level)
    {
        g_level = level;
    }
    while(i<(j-1))
    {
        while(isum>jsum && i<(j-1))
        {
            j--;
            jsum += s[j].pro;
        }
        while(isum<jsum && i<(j-1))
        {
            i++;
            isum += s[i].pro;
        }
    }

    if(i==start)
    {
        code[start][level]='0';
    }
    else if((i-start)>=1)
    {
        int k;
        for(k=start;k<=i;++k)
            code[k][level] = '0';

        shannon(start,i,s,code,level+1);
    }
    if(j==end)
    {
        code[end][level]='1';
    }
    else if((end-j)>=1)
    {
        int k;
        for(k=j;k<=end;++k)
            code[k][level] = '1';

        shannon(j,end,s,code,level+1);
    }
}

int main(int argc, char* argv[])
{
    float a[20], temp, x, total=0;
    int n,i,j;
    char ch[10];
    printf("Enter the number of symbols :");
    scanf("%d",&n);
    for(i=0;i<n;i++)
	{
		printf("Enter symbol %d ---> ",i+1);
		scanf("%s",ch);
		strcpy(s[i].sym,ch);
	}

    // Take the symbols and sort them as user enters them using insertion sort

    for(i=0; i<n; ++i)
    {
        printf("\n\tEnter probability for %s ---> ",s[i].sym);
        scanf("%f",&x);
        s[i].pro=x;
        total=total+s[i].pro;
		if(total>1)
		{
			printf("\t\tThis probability is not possible.Enter new probability");
			total=total-s[i].pro;
			i--;
		}
    }
    if(total<1)
    {
        return 0;
    }

    for(i=1;i<n;i++)
	{
		temp = s[i].pro;
		j=i-1;
		while(temp>s[j].pro && j>=0)
        {
            s[j+1].pro = s[j].pro;
			--j;
        }
        s[j+1].pro = temp;
    }

    char code[20][20];

    for(i=0; i<n; ++i)
    {
        // Mark row as invalid
        for(j=0;j<n;j++)
        {
            code[i][j] = 'X';
        }
    }


    shannon(0,n-1,s,code,0);




    printf("---------------------------------------------------------------");
printf("\nSymbol\tProbability\tCode\n");
    // Print the data and code
    for(i=0; i<n; ++i)
    {
        printf("%S\t %f\t  :", s[i].sym,s[i].pro);
        for(j=0; j<=g_level; j++)
        {
            if(code[i][j]!='X')
                printf("%c",code[i][j]);
        }
        printf("\n");
    }
    printf("\n---------------------------------------------------------------");

    printf("\n\n");
    return 0;
}




