char b[20];

char* itoa(int i){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int atoi(char b[])
{
	int res = 0;
	signed char i = 0, minus = 0;
	unsigned int decPower = 1;
	char * c;

	/*detect minus sign, and set begin if numberstring*/
	if(b[0] == '-'){
		minus = 1;
		c = &(b[1]);
	} else {
		c = &(b[0]);
	}
	/*set index to after last char*/
	while((c[i] != '\0' && i< 127)){
		i++;
	}


	/*set index to last char*/
	//i--;

	/*build number*/
	while(i>-1)
	{
		if(((unsigned int)c[i]) >= 0x30 && ((unsigned int)c[i]) <= 0x39 ){ /*decimal numbers*/ /*or minus sign as first entry*/
			res += (((unsigned int) (c[i])) - 0x0030) * decPower;
			decPower = decPower*10;
		}
		i--;
	}

	if(minus) res = -res;
	return res;
}
