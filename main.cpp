#include <bits/stdc++.h>

using namespace std;

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

bool dfs_recursive(vector<vector<char>> board, bool **visited, int y, int x, vector<pair<int, int>> &path) {

	visited[y][x] = true;

	for (int i = 0; i < 8; i++) {
		int new_i = y + directions[i].first;
		int new_j = x + directions[i].second;

		if (in_limits(board.size(), board[0].size(), new_i, new_j)
			&& !visited[new_i][new_j]) {
			if (board[new_i][new_j] == '*') {
				path.push_back(make_pair(new_i, new_j));
				if (dfs_recursive(board, visited, new_i, new_j, path)) break;
				path.pop_back();
			} else if (board[new_i][new_j] == '$') {
				path.push_back(make_pair(new_i, new_j));
				return true;
			}
		}
	}

	return true;
}

vector<pair<int, int>> dfs(vector<vector<char>> board, int x, int y) {

	bool **visited = (bool **) malloc(sizeof(bool*) * board.size());
	for (int i = 0; i < board.size(); i++) {
		visited[i] = (bool *) malloc(sizeof(bool) * board[0].size());
		for (int j = 0; j < board[0].size(); j++) {
			visited[i][j] = false;
		}
	}

	bool finished = false;
	vector<pair<int, int>> path;
	path.push_back(make_pair(y, x));
	dfs_recursive(board, visited, y, x, path);
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

	cout << "Busca em profundidade" << endl;
	vector<pair<int, int>> path = dfs(board, x, y);
	vector<vector<char>> result = write_result(board, path);
	print_board(result);

	cout << endl;
	cout << "===================" << endl << endl;
	cout << "Busca em largura" << endl;
	path = bfs(board, x, y);
	result = write_result(board, path);
	print_board(result);

	cout << endl;
	cout << "===================" << endl << endl;
	cout << "Busca Best-first Search" << endl;
	path = best_first(board, x, y);
	result = write_result(board, path);
	print_board(result);
	
	cout << endl;
	cout << "===================" << endl << endl;
	cout << "Busca A*" << endl;
	path = a_star(board, x, y, end_i, end_j);
	result = write_result(board, path);
	print_board(result);

	return 0;
}