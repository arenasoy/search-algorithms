#include <bits/stdc++.h>

using namespace std;

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

vector<pair<int, int>> dfs(vector<vector<char>> board, int x, int y) {

}

vector<pair<int, int>> bfs(vector<vector<char>> board, int x, int y) {

}


vector<pair<int, int>> best_first(vector<vector<char>> board, int x, int y) {

}

vector<pair<int, int>> a_start(vector<vector<char>> board, int x, int y) {

}

int main(int argc, char const *argv[])
{

	int l, c;
	cin >> l >> c;

	vector<vector<char>> board(l, vector<char>(c));
	
	int x = -1, y = -1;
	int aux;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < c; j++) {

			cin >> board[i][j];

			if (board[i][j] == '$') {
				x = i;
				y = j;
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
	cout << "Busca Best-first Search" << endl;
	best_first(board, x, y);
	cout << "Busca A*" << endl;
	a_start(board, x, y);

	// vector<pair<int, int>> result;
	// result.push_back(make_pair(0, 0));
	// result.push_back(make_pair(1, 1));
	// result.push_back(make_pair(2, 2));
	// result.push_back(make_pair(3, 3));

	// vector<vector<char>> res = write_result(board, result);
	// print_board(res);

	return 0;
}