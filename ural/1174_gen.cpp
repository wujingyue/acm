#include <stdio.h>

const char *fileout = "perm.txt";
const int MAXN = 100;

FILE *fout;
int n, i;
int permut[MAXN + 1];
int position[MAXN + 1];
int dir[MAXN + 1];

void PrintPermutation()
{
	for (i = 1; i <= n; i++)
		fprintf(fout, " %d", permut[i]);
	fprintf(fout, "\n");
}

void Switch(int p1, int p2)
{
	int xch = permut[p1];
	permut[p1] = permut[p2];
	permut[p2] = xch;
	position[permut[p1]] = p1;
	position[permut[p2]] = p2;
}

void GeneratePermutation(int nn)
{
	int ii;

	if (nn == n + 1)
		PrintPermutation();
	else
	{
		GeneratePermutation(nn + 1);
		for (ii = 1; ii <= nn - 1; ii++)
		{
			Switch(position[nn],
					position[nn] + dir[nn]);
			GeneratePermutation(nn + 1);
		}
		dir[nn] = -dir[nn];
	}
}

int main()
{
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		permut[i] = i;
		position[i] = i;
		dir[i] = -1;
	}

	fout = fopen(fileout, "wt");

	GeneratePermutation(1);

	fclose(fout);
	return 0;
}

