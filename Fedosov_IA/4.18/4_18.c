#include <stdio.h>

int hasVerticalBlackLine(unsigned int icon[32]) {
		
    int counter = 0;
    unsigned int mask = 0;
    for (int i = 1; i < 32; i ++){
    	counter = 0;
    	
    	if ((icon[0] & (1 << i)) != 0 && (icon[0] & (1 << (i - 1))) == 0 && (icon[0] & (1 << (i + 1))) == 0 ) {  //находим индекс бита, равного 1, по бокам которого стоят 0
		mask = (mask | (7 << (i - 1))); //тк 7 это 111 в битовом представлении
		
		for (int row = 1; row < 32; row ++) {
			if((icon[row] & mask) & (1 << i)) {
				counter++;
			}
		}
	if (counter == 31) {
		return 1; //есть вертикальная черная линия
	}
        }
        
    }
    

    return 0; // нет вертикальных черных линий
}


int main() {
    unsigned int icon[32];
    
    for (int i = 0; i < 32; i++){
    	scanf("%u", &icon[i]);
    }

    if (hasVerticalBlackLine(icon)) {
        printf("На иконке есть вертикальные черные линии\n");
    } else {
        printf("На иконке нет вертикальных черных линий\n");
    }

    return 0;
}

