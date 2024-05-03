#include <stdio.h>
#include <stdlib.h>

void find_order (int **play_lists, int *lengths, int n_users);
int check_tail (int user, int *pos, int **play_lists, int *lengths, int n_users);

int check_tail (int user, int *pos, int **play_lists, int *lengths, int n_users)
{
	for (int i = 0; i < n_users; i++)
	{
		for (int j = (pos[i] + 1); j < lengths[i]; j++)
		{
			if ((j < lengths[i]) && (play_lists[i][j] == play_lists[user][pos[user]]))
			{
				return 0;
			}
		}
	}
	return 1;
}

void find_order (int **play_lists, int *lengths, int n_users)
{
	int summ = 0, sumpos = 0, error = 0, curr;
	int *pos = (int *)malloc(n_users*sizeof(int));
	for (int i = 0; i < n_users; i++)
	{
		summ = summ + lengths[i];
		pos[i] = 0;
	}
	while (sumpos < summ)
	{
		for (int user = 0; user < n_users; user ++)
		{
			if ((pos[user] != lengths[user]) && (check_tail(user, pos, play_lists, lengths, n_users) == 1))
			{
				error = 0;
				curr = play_lists[user][pos[user]];
				printf("%d ", curr);
				for (int j = 0; j < n_users; j++)
				{
					if ((lengths[j] != pos[j]) && (curr == play_lists[j][pos[j]]))
					{
						pos[j]++;
						sumpos++;
					}
				}
			}
			else 
			{
				error ++;
			}
		}
		if (error > n_users)
		{
			break;
		}
	}
	free(pos);
}


int main (void)
{
	int n_users = 3;
	int lengths[] = {4,3,3};
	int p1[] = {7, 6 , 3, 2};
	int p2[] = {2, 4, 5};
	int p3[] = {1, 2, 8};
	int *play_lists[] = {p1, p2, p3};
	find_order (play_lists, lengths, n_users);
	return 0;
}
