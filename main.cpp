/*
	Alunos:
	Ana Carolina Fainelo de Oliveira 10284542
	Carolina Arenas Okawa 10258876
	Lui Franco Rocha 10295558
*/

#include <bits/stdc++.h>

using namespace std;

int nodes_dfs, nodes_bfs, nodes_best_first, nodes_a_star;

typedef pair<int, pair<int, int>> triple;

pair<int, int> directions[] = {
	make_pair(-1, -1), make_pair(0, -1), make_pair(1, -1),
	make_pair(1, 0), make_pair(1, 1), make_pair(0, 1), 
	make_pair(-1, 1), make_pair(-1, 0)};

bool in_limits(int n, int m, int i, int j) {
	if (i < 0 || j < 0 || i >= n || j >= m) return false;
	return true;
}

void print_board(vector<vector<char>> board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

vector<vector<char>> write_result(vector<vector<char>> board, vector<pair<int, int>> path) {
	
	for (int i = 0; i < path.size(); i++)
		board[path[i].first][path[i].second] = '@';

	return board;
}

void dfs_recursive(vector<vector<char>> board, bool **visited, int y, int x, vector<pair<int, int>> &path, bool *finished) {

	nodes_dfs++;
	if (*finished) return;
	visited[y][x] = true;

	for (int i = 0; i < 8; i++) {
		int new_i = y + directions[i].first;
		int new_j = x + directions[i].second;

		if (in_limits(board.size(), board[0].size(), new_i, new_j)
			&& !visited[new_i][new_j]) {
			if (board[new_i][new_j] == '*') {
				path.push_back(make_pair(new_i, new_j));
				dfs_recursive(board, visited, new_i, new_j, path, finished);
				if (*finished) return;
				path.pop_back();
			} else if (board[new_i][new_j] == '$') {
				path.push_back(make_pair(new_i, new_j));
				*finished = true;
			}
		}
	}

	return;
}

vector<pair<int, int>> dfs(vector<vector<char>> board, int x, int y) {

	bool **visited = (bool **) malloc(sizeof(bool*) * board.size());
	for (int i = 0; i < board.size(); i++) {
		visited[i] = (bool *) malloc(sizeof(bool) * board[0].size());
		for (int j = 0; j < board[0].size(); j++) {
			visited[i][j] = false;
		}
	}

	vector<pair<int, int>> path;
	path.push_back(make_pair(y, x));
	bool finished = false;
	dfs_recursive(board, visited, y, x, path, &finished);
	return path;
}

vector<pair<int, int>> bfs(vector<vector<char>> board, int x, int y) {

	pair<int, int> path[board.size()][board[0].size()];
	bool visited[board.size()][board[0].size()];
	bool finished = false;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			visited[i][j] = false;
		}
	}

	queue<pair<int, int>> q;

	q.push(make_pair(y, x));

	int new_i = -1, new_j = -1;

	while (!q.empty() && !finished) {
		nodes_bfs++;
		pair<int, int> actual = q.front();
		q.pop();

		//think about possibility to do it in other order
		for (int i = 0; i < 8; i++) {
			new_i = actual.first + directions[i].first;
			new_j = actual.second + directions[i].second;

			if (in_limits(board.size(), board[0].size(), new_i, new_j)
				&& !visited[new_i][new_j]) {
				path[new_i][new_j] = actual;
				if (board[new_i][new_j] == '*') {
					visited[new_i][new_j] = true;
					q.push(make_pair(new_i, new_j));
				} else if (board[new_i][new_j] == '$') {
					finished = true;
					break;
				}
			}
		}

	}

	vector<pair<int, int>> result;
	result.push_back(make_pair(new_i, new_j));

	while (new_i != y || new_j != x) {
		pair<int, int> actual = path[new_i][new_j];
		result.push_back(actual);
		new_i = actual.first;
		new_j = actual.second;
	}

	return result;

}


vector<pair<int, int>> best_first(vector<vector<char>> board, int x, int y) {

	pair<int, int> path[board.size()][board[0].size()];
	bool visited[board.size()][board[0].size()];
	bool finished = false;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			visited[i][j] = false;
		}
	}

	priority_queue<triple, vector<triple>, greater<triple>> q;

	q.push(make_pair(0, make_pair(y, x)));

	int new_i = -1, new_j = -1;

	while (!q.empty() && !finished) {
		nodes_best_first++;
		triple front = q.top();
		pair<int, int> actual = front.second;
		q.pop();

		//think about possibility to do it in other order
		for (int i = 0; i < 8; i++) {
			new_i = actual.first + directions[i].first;
			new_j = actual.second + directions[i].second;
			int weight = sqrt(pow(y - new_i, 2) + pow(x - new_j, 2));

			if (in_limits(board.size(), board[0].size(), new_i, new_j)
				&& !visited[new_i][new_j]) {
				path[new_i][new_j] = actual;
				if (board[new_i][new_j] == '*') {
					visited[new_i][new_j] = true;
					q.push(make_pair(weight, make_pair(new_i, new_j)));
				} else if (board[new_i][new_j] == '$') {
					finished = true;
					break;
				}
			}
		}

	}

	vector<pair<int, int>> result;
	result.push_back(make_pair(new_i, new_j));

	while (new_i != y || new_j != x) {
		pair<int, int> actual = path[new_i][new_j];
		result.push_back(actual);
		new_i = actual.first;
		new_j = actual.second;
	}

	return result;

}

int diagonal_distance(int i, int j, int end_i, int end_j) {

	return max(abs(i - end_i), abs(j - end_j));

}

vector<pair<int, int>> a_star(vector<vector<char>> board, int x, int y, int end_i, int end_j) {

	pair<int, int> path[board.size()][board[0].size()];
	bool visited[board.size()][board[0].size()];
	int cost[board.size()][board[0].size()];
	bool finished = false;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			visited[i][j] = false;
			cost[i][j] = INT_MAX;
		}
	}

	int new_i = -1, new_j = -1;

	priority_queue<triple, vector<triple>, greater<triple>> q;

	q.push(make_pair(0, make_pair(y, x)));

	while (!q.empty() && !finished) {
		nodes_a_star++;
		triple front = q.top();
		pair<int, int> actual = front.second;
		q.pop();

		//think about possibility to do it in other order
		for (int i = 0; i < 8; i++) {
			new_i = actual.first + directions[i].first;
			new_j = actual.second + directions[i].second;
			cost[new_i][new_j] = cost[actual.first][actual.second] 
						+ sqrt(pow(y - new_i, 2) + pow(x - new_j, 2))
						+ diagonal_distance(new_i, new_j, end_i, end_j);

			if (in_limits(board.size(), board[0].size(), new_i, new_j)
				&& !visited[new_i][new_j]) {
				path[new_i][new_j] = actual;
				if (board[new_i][new_j] == '*') {
					visited[new_i][new_j] = true;
					q.push(make_pair(cost[new_i][new_j], make_pair(new_i, new_j)));
				} else if (board[new_i][new_j] == '$') {
					finished = true;
					break;
				}
			}
		}

	}
	
	vector<pair<int, int>> result;
	result.push_back(make_pair(new_i, new_j));

	while (new_i != y || new_j != x) {
		pair<int, int> actual = path[new_i][new_j];
		result.push_back(actual);
		new_i = actual.first;
		new_j = actual.second;
	}

	return result;

}

double calculate_cost(vector<pair<int, int>> path) {

	double cost = 0;

	for (int i = 0; i < path.size() - 1; i++) {
		if (path[i].first == path[i + 1].first || path[i].second == path[i + 1].second) {
			cost += sqrt(2);
		} else {
			cost++;
		}
	}

	return cost;

} 

int main(int argc, char const *argv[])
{

	int l, c;
	cin >> l >> c;

	vector<char> v(c);
	vector<vector<char>> board(l, v);
	
	int x = -1, y = -1, end_i = -1, end_j = -1;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < c; j++) {

			cin >> board[i][j];

			if (board[i][j] == '#') {
				y = i;
				x = j;
			} else if (board[i][j] == '$') {
				end_i = i;
				end_j = j;
			}
		}
	}

	if (x < 0 || y < 0) {
		cout << "Posição inicial não encontrada" << endl;
		return -1;
	}

	clock_t start;
	cout << "Busca em profundidade" << endl;
	start = clock();
	vector<pair<int, int>> path = dfs(board, x, y);
	vector<vector<char>> result = write_result(board, path);
	print_board(result);
	double duration = ( clock() - start ) / (double) (CLOCKS_PER_SEC/1000);
	cout << "cost: " << calculate_cost(path) << endl;
	cout << "visited nodes_dfs: " << nodes_dfs << endl;
	cout << "time " << duration << endl;	

	cout << endl;
	cout << "===================" << endl << endl;
	cout << "Busca em largura" << endl;
	start = clock();
	path = bfs(board, x, y);
	result = write_result(board, path);
	print_board(result);
	duration = ( clock() - start ) / (double) (CLOCKS_PER_SEC/1000);
	cout << "cost: " << calculate_cost(path) << endl;
	cout << "visited nodes: " << nodes_bfs << endl;
	cout << "time " << duration << endl;	

	cout << endl;
	cout << "===================" << endl << endl;
	cout << "Busca Best-first Search" << endl;
	start = clock();
	path = best_first(board, x, y);
	result = write_result(board, path);
	print_board(result);
	duration = ( clock() - start ) / (double) (CLOCKS_PER_SEC/1000);
	cout << "cost: " << calculate_cost(path) << endl;
	cout << "visited nodes: " << nodes_best_first << endl;
	cout << "time " << duration << endl;	
	
	cout << endl;
	cout << "===================" << endl << endl;
	cout << "Busca A*" << endl;
	start = clock();
	path = a_star(board, x, y, end_i, end_j);
	result = write_result(board, path);
	print_board(result);
	duration = ( clock() - start ) / (double) (CLOCKS_PER_SEC/1000);
	cout << "cost: " << calculate_cost(path) << endl;
	cout << "visited nodes: " << nodes_a_star << endl;
	cout << "time " << duration << endl;	

	return 0;
}