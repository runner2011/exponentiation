/*
PKU ACM 1001

Description

Problems involving the computation of exact values of very large magnitude and precision are common.
For example, the computation of the national debt is a taxing experience for many computer systems. 

This problem requires that you write a program to compute the exact value of Rn where 
R is a real number ( 0.0 < R < 99.999 ) and n is an integer such that 0 < n <= 25. 

Input

The input will consist of a set of pairs of values for R and n. The R value will occupy columns 1 through 6, 
and the n value will be in columns 8 and 9.

Output

The output will consist of one line for each line of input giving the exact value of R^n. 
Leading zeros should be suppressed in the output. Insignificant trailing zeros must not be printed. 
Don't print the decimal point if the result is an integer.

Sample Input

95.123 12
0.4321 20
5.1234 15
6.7592  9
98.999 10
1.0100 12

Sample Output

548815620517731830194541.899025343415715973535967221869852721
.00000005148554641076956121994511276767154838481760200726351203835429763013462401
43992025569.928573701266488041146654993318703707511666295476720493953024
29448126.764121021618164430206909037173276672
90429072743629540498.107596019456651774561044010001
1.126825030131969720661201

Hint

If you don't know how to determine wheather encounted the end of input: 
s is a string and n is an integer 

C++
while(cin>>s>>n)
{
...
}
c
while(scanf("%s%d",s,&n)==2) //to  see if the scanf read in as many items as you want
/*while(scanf(%s%d",s,&n)!=EOF) //this also work
{
...
}
*/

#include "stdio.h"
#include "string.h"
/*pku acm 1001
length,length1为数组实际长度-1
*/
int main()
{
	int circle;
	int i,j,k,n,length,length1,sign,t,temp;//n为小数点后有几位数，sign为结果是否含小数点标志
	int len;
	char str[7],str1[7],c1[255],c2[255];
	while(scanf("%s%d",str,&circle)==2 && strlen(str)<=6 && 0<circle &&circle<=25)
	{
		sign=0;
		t=0;
		strcpy(str1,str);
		len=strlen(str);
		for(i=0;str[i]!='.' && i<len;i++)//t为小数点所在位置的下标
			t++;
		n=len-t-1;
		for(i=t+1;i<len+1;i++)
			str[i-1]=str[i];
		
		len=strlen(str);
		for(i=0;str[i]=='0'&&i<len;i++);//底数为0，输出0
		
		if(i==len)
		{
			printf("0\n");
			continue;
		}
		
		for(i=0;i<(len+1)/2;i++)//反转数组
		{
			temp=str[i];str[i]=str[len-1-i];str[len-1-i]=temp;
		}
		
		for(i=0;i<len;i++)
			str[i]-=48;
		
		for(i=0;i<255;i++)
			c1[i]=0;
		for(i=0;i<255;i++)
			c2[i]=0;
		if(circle>1)
			for(j=0;j<len;j++)
				for(i=0;i<len;i++)
				{
					length=i+j;
					if((c1[i+j]+=str[i]*str[j])>10)
					{
						c1[i+j+1]+=c1[i+j]/10;
						c1[i+j]=c1[i+j]%10;
						length=i+j+1;
					}
				}
		else if(circle==1)goto lab;
		
		length1=length;
				
		for(k=1;k<circle-1;k++)
		{
			for(i=0;i<255;i++)
				c2[i]=c1[i];
			for(i=0;i<255;i++)
				c1[i]=0;
			length=length1;
			for(j=0;j<len;j++)
				for(i=0;i<length+1;i++)
				{
					length1=i+j;
					if((c1[i+j]+=c2[i]*str[j])>=10)
					{
						c1[i+j+1]+=c1[i+j]/10;
						c1[i+j]=c1[i+j]%10;
						length1=i+j+1;
					}
				}
		}
				
		for(i=0;i<=length1;i++)
			c1[i]+=48;
				
		if(n!=0)//底数非整数
		{
			t=n*circle;
			for(i=length1;i>=t;i--)
				c1[i+1]=c1[i];
			c1[t]='.';
			sign=1;
		}
		
		if(c1[length1+sign]=='0')//去掉整数部分的首位0
			length1--;
		for(i=0;c1[i]=='0'||c1[i]=='.';i++)//去掉小数部分无意义的0
		{
			if(c1[i]=='.')
			{
				c1[i]='\0';
				break;
			}
			c1[i]='\0';
		}
		for(i=length1+sign;c1[i]!='\0';i--)
			printf("%c",c1[i]);
			
		printf("\n");
		continue;
		
lab:
		for(i=strlen(str1)-1;str1[i]=='0'||str1[i]=='.'&&i>=0;i--)
		{
			if(str1[i]=='.'){str1[i]='\0';break;}
			str1[i]='\0';
		}
		printf("%s\n",str1);   
	}
	return 0;
	
}
