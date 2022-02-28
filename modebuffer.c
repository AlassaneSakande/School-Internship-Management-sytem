#include <string.h>
#include <stdio.h>

// Fonction to void the buffer
// Used after each float and int

void buffer()
{	
	while(getchar() != '\n');
}


/* Replace enter by the end of line caract .*/
// Used for caracts

void mode(char phrase[])
{
	int i;
	for(i = 0; i < strlen(phrase); i++)
	{
		// Every time we've reached the ENTER key we are at the end of the line
		if(phrase[i] == '\n')
		{
			phrase[i] = '\0';
		}
	}
}


// Unify buffer and mode buffer

void modebuffer(char sentence[], int taille)
{
	fgets(sentence,taille,stdin);
	
	if(strchr(sentence, '\n') == NULL)
		buffer();

	mode(sentence);
}

// Convert strings to lowercase 
const char* miniscule(char phrase[])
{
	int i;
	for(i=0; i<strlen(phrase); i++)
	{
		if(phrase[i] >= 'A' && phrase[i] <= 'Z')
			phrase[i] = phrase[i] + 32;
	}
	return phrase;
}