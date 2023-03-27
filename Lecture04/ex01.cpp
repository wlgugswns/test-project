#include<iostream>
#include<conio.h>

int main()
{
	while(true)
	{
		
		if(_kbhit()){
		
			if(_getch() == 27){
				break;
			}
		}
		std::cout<<"*";
	}
	return 0;
}
