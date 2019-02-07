#include <stdio.h>
#include <conio.h>
int pg_size, pg_access, string[20], cache_page_number[20], buffer[20], display_pg[20][20] = { "\0" }, hit[20],cache_full=0,count[20],smallest,replace,next;

void take_input()
{
	int i = 0;
	printf(" Enter the Page Size of Cache: ");
	scanf_s("%d", &pg_size);
	printf(" Enter the number of Page Access: ");
	scanf_s("%d", &pg_access);
	printf(" Enter the Access Array: ");
	while (i < pg_access && scanf_s("%d", &string[i++]) == 1)
	{ }
	for (int j = 0; j < pg_size; j++)
	{
		buffer[j] = "NULL";
	}
}
void cache_controller()
{
	//fill the buffer step by step
	for (int i = 0; i < pg_access; i++)
	{
		
		//Pass the copy to next window
		for (int j = 0; j < pg_size; j++)
			display_pg[j][i] = display_pg[j][i - 1];
		//Find in all pages
		for (int j = 0; j < pg_size; j++)
			if (buffer[j] == string[i])
			{
				hit[i] = 1;
			}
		//Not found anywhere
		if (hit[i] == 0)
		{	//Find the empty page
			next = 0;
			for (int j = 0; j < pg_size; j++)
			{
				if (buffer[j] == "NULL")
				{
					buffer[j] = string[i];
					display_pg[j][i] = buffer[j];
					cache_full++;
					next = 1;
					break;
				}
					
			}
			//Buffer full, use LRU to store new string
			if (cache_full == pg_size && next==0)
			{
				for (int j = 0; j < pg_size; j++)
				{
					for (int t = i-1; t >= 0; t--)
					{
						if (buffer[j] == string[t])
						{
							count[j] = t;
							break;
						}
					} 
				}
				small();
				buffer[replace] = string[i];
				display_pg[replace][i] = buffer[replace];
			}
		}
				
		//compare the buffer with the next string number
		//update the display_pg
	}
	
}int small()
{
	smallest = count[0];
	for (int j = 0; j < pg_size; j++)
	{
		if (count[j] < smallest)
		{
			smallest = count[j];
		}
	}
	for(int j=0;j<pg_size;j++)
	{
		if (count[j] == smallest)
		{
			replace = j;
			break;
		}
	}
		
}
void render_table()
{
	//TOP of table
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 218,196,196,196,196,196,196,196,196,194,196,196,196); //218 for left top, 196 for straight, 194 for center top, 191 for right top
	for (int j = 0; j < pg_access - 1; j++)
		printf("%c%c%c%c%c%c%c", 196,196, 196, 194, 196, 196,196);
	printf("%c%c%c%c",196,196,196,191);
	printf(" \n");
	//Page Access String
	printf("%c        ", 179);
	for (int i = 0; i < pg_access; i++)
	{
		printf("%c   ", 179);// 179 for vertical
		if (string[i] >= 10)
			printf(" %d", string[i]);
		else
			printf("  %d", string[i]);
	}
	printf("%c ", 179);
	printf("\n");
	//Cache Page Numbering and filling
	for (int i = 0; i < pg_size; i++)
	{
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 195,196,196,196,196,196,196, 196, 196, 197, 196, 196,196); //195 for left middle, 197 for center middle, 180 for right middle
		for (int j = 0; j < pg_access - 1; j++)
			printf("%c%c%c%c%c%c%c", 196, 196, 196, 197, 196, 196, 196);
		printf("%c%c%c%c",196, 196, 196, 180);
		printf("\n");
		printf("%c ", 179);// 179 for vertical
		if(i>=10)
			printf("Page %d", i);
		else
			printf("Page %d ", i);
		for (int r = 0; r < pg_access; r++)
		{
			printf("%c    ", 179);
			if (display_pg[i][r] >= 10)
				printf("%d", display_pg[i][r]);
			else
				printf("%d ", display_pg[i][r]);
			
		}
		printf("%c     ", 179);
		printf("\n");
	}
	//Bottom Hit and Miss part
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 196, 196, 196, 197, 196, 196, 196); //195 for left middle, 197 for center middle, 180 for right middle
	for (int j = 0; j < pg_access - 1; j++)
		printf("%c%c%c%c%c%c%c", 196, 196, 196, 197, 196, 196, 196);
	printf("%c%c%c%c", 196, 196, 196, 180);
	printf("\n");
	printf("%c        ", 179);
	for (int i = 0; i < pg_access; i++)
	{
		printf("%c  ", 179);// 179 for vertical
		if (hit[i] > 0)
			printf("Hit ");
		else
			printf("Miss");
	}
	printf("%c ", 179);
	printf("\n");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 193, 196, 196, 196);
	for (int j = 0; j < pg_access - 1; j++)
		printf("%c%c%c%c%c%c%c", 196, 196, 196, 193, 196, 196, 196);
	printf("%c%c%c%c", 196, 196, 196, 217);// 192 for left bottom,193 for center bottom, 217 for right bottom
}
//To make font more stylish
void printfn(char *s)
{
	printf("---%*s%*s---\n", 15 + strlen(s) / 2, s, 15 - strlen(s) / 2, "");
}
int main()
{
	printfn("Cache Replacement Policy");
	printfn("Least Recently Used");
	printf("\n");

	take_input();
	cache_controller();
	render_table();
	/*for (int j = 0; j < pg_size; j++)
		printf("%d\n", buffer[j]);
	printf("\n");
	for (int i = 0; i < pg_access; i++)
		printf("%d\n", hit[i]);
	printf("\n");
	for (int j = 0; j < pg_size; j++)
	{
		for (int i = 0; i < pg_access; i++)
		{
			printf("%d ",display_pg[j][i]);
		}
		printf("\n");
	}
	*/
	printf("\n");
	printfn("Written in Saviour Code. Available on GitHub");
}