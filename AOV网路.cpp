#include <iostream>
#include <string>
using namespace std;
#define   m   9
void tsort(int quantity, bool(*matrix)[m], string *str)
{
	int dist[m] = { 0 };//标记数组
	int i = 0, j = 0, k = 0;
	for (i = 0; i < quantity; i++)//计算入度
		for (j = 0; j < quantity; j++)
			if (matrix[j][i] == 1)
				dist[j]++;
	for (k = 0; k < quantity; k++)
	{
		for (i = 0; i < quantity; i++)
			if (dist[i] == 0)
			{
				cout << str[i] << endl;
				dist[i]--;
				break;
			}
		for (j = 0; j < quantity; j++)
			if (matrix[j][i] == 1)
				dist[j]--;
	}
}
void modifies(bool(*matrix)[m])
{
	cout << "1.删除一条边\n";
	cout << "2.舔加一条边\n";
	int choose = 0, x = 0, y = 0, i = 0;
	switch (choose)
	{
	case 1:
		cout << "输入两个数，表示学习计划X到学习计划Y的一条有向边删除\n";
		cin >> x >> y;
		matrix[y][x] = 0;
		break;
	case 2:
		cout << "输入两个数，表示学习计划X到学习计划Y的一条有向边舔加\n";
		cin >> x >> y;
		matrix[y][x] = 1;
		break;
	default:
		break;
	}
}
void inputting(int& quantity, bool(*matrix)[m], string* str)
{
	int j = 0;
	cout << "输入学习计划总数\n";
	cin >> quantity;
	cout << "输入学习计划\n";
	for (int i = 0; i < quantity; i++)
		cin >> str[i];
	cout << "---------------------------\n";
	for (int i = 0; i < quantity; i++)
		cout << i << ") " << str[i] << '\n';
	cout << "---------------------------\n";
	for (int i = 0; i < quantity; i++)
	{
		printf("输入一个数，表示学习计划%d到学习计划X的一条有向边(输入99结束)\n", i);
		while (true)
		{
			cout << i << " ---> ";
			cin >> j;
			if (j == 99)break;
			matrix[j][i] = 1;
		}
	}
	cout << "---------------------------\n";
}
void menu()
{
	cout << "1.添加第一学期计划\n";
	cout << "2.添加第二学期计划\n";
	cout << "3.修改第一学期计划\n";
	cout << "4.修改第二学期计划\n";
	cout << "5.第一学期拓扑排序\n";
	cout << "6.第二学期拓扑排序\n";
	cout << "7.退出\n";
}
void test()
{
	/*--------------------------------测试数据--------------------------------*/
	int quantity = 9;
	bool matrix[9][9] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0,
	};
	string str[9] = { "a0","a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", };
	tsort(quantity, matrix, str);
	cout << "---------------------------\n";
	/*------------------------------------------------------------------------*/
}
int main()
{
	int quantity = 0;
	string str[m];
	bool matrix[m][m] = { 0 };
	int quantity1 = 0;
	string str1[m];
	bool matrix1[m][m] = { 0 };
	int choose = 0;
	while (choose != 7)
	{
		menu();
		cout << "输入选项：";
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			inputting(quantity, matrix, str);
			break;
		case 2:
			inputting(quantity1, matrix1, str1);
			break;
		case 3:
			modifies(matrix);
			break;
		case 4:
			modifies(matrix1);
			break;
		case 5:
			tsort(quantity, matrix, str);
			break;
		case 6:
			tsort(quantity1, matrix1, str1);
			break;
		default:
			break;
		}
	}
	return 0;
}