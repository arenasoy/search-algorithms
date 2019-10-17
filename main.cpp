#include <bits/stdc++.h>

using namespace std;

pair<int, int> directions[] = {
	make_pair(-1, -1), make_pair(0, -1), make_pair(1, -1),
	make_pair(-1, 0), make_pair(1, 0),
	make_pair(-1, 1), make_pair(0, 1), make_pair(1, 1)};

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

vector<pair<int, int>> dfs_recursive(vector<vector<char>> board, bool **visited, int y, int x) {

	vector<pair<int, int>> v;
	visited[y][x] = true;

	for (int i = 0; i < 8; i++) {
		int new_i = y + directions[i].first;
		int new_j = x + directions[i].second;

		if (in_limits(board.size(), board[0].size(), new_i, new_j)
			&& !visited[new_i][new_j]) {
			if (board[new_i][new_j] == '*') {
				dfs_recursive(board, visited, new_i, new_j);
			} else if (board[new_i][new_j] == '$') {
				cout << "end at: " << new_i << ", " << new_j << endl;
				return v;
			}
		}
	}

	return v;
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

	return dfs_recursive(board, visited, y, x);
}

vector<pair<int, int>> bfs(vector<vector<char>> board, int x, int y) {

	vector<pair<int, int>> v;
	bool visited[board.size()][board[0].size()];
	bool finished = false;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			visited[i][j] = false;
		}
	}

	queue<pair<int, int>> q;

	q.push(make_pair(y, x));

	while (!q.empty() && !finished) {
		pair<int, int> actual = q.front();
		q.pop();

		//think about possibility to do it in other order
		for (int i = 0; i < 8; i++) {
			int new_i = actual.first + directions[i].first;
			int new_j = actual.second + directions[i].second;

			if (in_limits(board.size(), board[0].size(), new_i, new_j)
				&& !visited[new_i][new_j]) {
				if (board[new_i][new_j] == '*') {
					visited[new_i][new_j] = true;
					q.push(make_pair(new_i, new_j));
				} else if (board[new_i][new_j] == '$') {
					cout << "end at: " << new_i << ", " << new_j << endl;
					finished = true;
					break;
				}
			}
		}

	}

	return v;

}


vector<pair<int, int>> best_first(vector<vector<char>> board, int x, int y) {

}

vector<pair<int, int>> a_star(vector<vector<char>> board, int x, int y) {

}

int main(int argc, char const *argv[])
{

	int l, c;
	cin >> l >> c;

	vector<char> v(c);
	vector<vector<char>> board(l, v);
	
	int x = -1, y = -1;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < c; j++) {

			cin >> board[i][j];

			if (board[i][j] == '#') {
				y = i;
				x = j;
			}
		}
	}

	if (x < 0 || y < 0) {
		cout << "Posição inicial não encontrada" << endl;
		return -1;
	}

	cout << "Busca em profundidade" << endl;
	dfs(board, x, y);
	cout << "Busca em largura" << endl;
	bfs(board, x, y);
	// cout << "Busca Best-first Search" << endl;
	// best_first(board, x, y);
	// cout << "Busca A*" << endl;
	// a_star(board, x, y);


	return 0;
}