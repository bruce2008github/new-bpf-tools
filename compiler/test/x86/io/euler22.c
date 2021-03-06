/*
 * Solution to ProjectEuler problem 22
 * (Originally written in real C on June 25, 2012)
 *
 * You need to pipe the input file into it.
 * The input file is available at:
 * http://projecteuler.net/project/names.txt
 */

char** allocnames()
{
	int i;
	char** names;

	if(!(names = malloc(20000 * sizeof(char *))))
		return 0;

	for(i = 0; i < 20000; i++) 
		if(!(names[i] = malloc(64)))
			return 0;
		else
			*names[i] = 0;	/* initialization */

	return names;
}

void freenames(char** names)
{
	int i;
	for(i = 0; i < 20000; i++)
		free(names[i]);
	free(names);
}

int readnames(char** names)
{
	int i = 0, j;
	int c;

	while(1) {
		while((c = getchar()) != '"' && c >= 0)
			;

		/* stop reading on EOF */
		if (c < 0)
			break;

		j = 0;
		while((c = getchar()) != '"' && c >= 0)
			names[i][j++] = c;
		names[i][j] = 0;

		++i;
	}
	return i;
}

void sortnames(char** names, char** sorted)
{
	char dummy[] = "ZZZZZZZZZZZZZZZZZZZ";
	char top[64];
	int key;
	int i = 0, j, k, l = 0;
	while(*names[i++]);
	j = i--;
	while(i) {
		key = -1;
		strcpy(top, dummy);
		for(k = 0; k <= j; k++)
			if(*names[k]) {
				if(strcmp(top, names[k]) > 0)
				{
					key = k;
					strcpy(top, names[k]);
				}
			}
		if(key >= 0) {
			strcpy(sorted[l++], names[key]);
			*names[key] = 0;
			--i;
		}
	}
	*sorted[l] = 0;
}

int main(int argc, char** argv)
{
	char **names, **sorted;
	int total = 0;
	int i, j;
	int score;

	if(!(names = allocnames()) || !(sorted = allocnames())) { 
		printf("malloc failure\n"); 
		return 1; 
	}
	
	if(!readnames(names)) {
		printf("readnames failure\n");
		return 1;
	}

	sortnames(names, sorted);
	for(i = 0; *sorted[i]; i++) {
		for(j = 0, score = 0; sorted[i][j]; j++)
			score += sorted[i][j] - 'A' + 1;
		score *= i+1;
		printf("%s: %d\n", sorted[i], score);
		total += score;
	}

	printf("total: %d\n", total);

	freenames(names);
	freenames(sorted);

	return 0;
}
