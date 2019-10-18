from random import randint

print("maze dimensions")

x = int(input())
y = int(input())

start_i = randint(0, y - 1)
start_j = randint(0, x - 1)

end_i = start_i
end_j = start_j

while (end_i == start_i and end_j == start_j):
	end_i = randint(0, y - 1)
	end_j = randint(0, x - 1)

last_direction = 0
maze = [[0 for j in range(x)] for i in range(y)] 

for i in range (0, y):
	for j in range (0, x):
		if (i == start_i and j == start_j):
			maze[i][j] = '#'
		elif (i == end_i and j == end_j):
			maze[i][j] = '$'
		else:
			if ((i - 1) > 0 and maze[i - 1][j] and (j - 1) > 0 and maze[i][j - 1]):
				r = randint(0, 9)
				if r < 7:
					maze[i][j] = '-'
				else:
					maze[i][j] = '*'
			elif (((i - 1) > 0 and maze[i - 1][j]) or ((j - 1) > 0 and maze[i][j - 1])):
				r = randint(0, 9)
				if r < 6:
					maze[i][j] = '-'
				else:
					maze[i][j] = '*'
			else:
				r = randint(0, 9)
				if r < 8:
					maze[i][j] = '*'
				else:
					maze[i][j] = '-'

for i in range(0, y):
	for j in range(0, x):
		print(maze[i][j], end='')
	print()