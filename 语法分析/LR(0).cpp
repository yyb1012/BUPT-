#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<stack>
#include<map>
#define rows 17
#define cols 12
using namespace std;
class LR
{
private:
	string input_s;//���룬���������ַ���
	string LR_Table[rows][cols];//������
	vector<string> expression_vec;//�ķ�
	vector<string> s_state;//״̬ջ���ַ�
	vector<string> s_symbol;//symbolջ���ַ�
	stack<string> state_stack;//״̬ջ
	stack<string> symbol_stack;//symbolջ
	map<string, int> states_row;//״̬��Ӧ�к�
	map<string, int> ter_line;//�ս�������ս����Ӧ�к�
public:
	void LR_analy(string& str);
	void show_info(string &c_ch,string &express,int c_ptr);//��������
	void init_stack();//ջ��ʼ��
	void init_set();//�淶�壬�ķ��ȵĳ�ʼ��
};

int main()
{
	LR lr;
	lr.init_set();
	lr.init_stack();
	cout << "������������ַ���" << endl;
	string str;
	cin >> str;
	str += "$";
	lr.LR_analy(str);
	system("pause");
	return 0;
}

void LR::init_stack()//ջ��ʼ��
{
	state_stack.push("0");
	symbol_stack.push("-");
	s_state.push_back("0");
	s_symbol.push_back("-");
}

void LR::init_set()//�淶�壬�ķ��ȵĳ�ʼ��
{
	string states = "states";//�洢����
	LR_Table[0][0] = states, LR_Table[0][1] = "(", LR_Table[0][2] = ")", LR_Table[0][3] = "+",
	LR_Table[0][4] = "-", LR_Table[0][5] = "*", LR_Table[0][6] = "/", LR_Table[0][7] = "num",
	LR_Table[0][8] = "$", LR_Table[0][9] = "E", LR_Table[0][10] = "T", LR_Table[0][11] = "F";
	//�洢���ʽ
	expression_vec.push_back("S->E"), expression_vec.push_back("E->E+T"), expression_vec.push_back("E->E-T");
	expression_vec.push_back("E->T"), expression_vec.push_back("T->T*F"), expression_vec.push_back("T->T/F");
	expression_vec.push_back("T->F"), expression_vec.push_back("F->(E)"), expression_vec.push_back("F->num");
	//�洢״̬
	for (int i = 1; i < rows; i++)
		LR_Table[i][0] = to_string(i-1);
	states_row["0"] = 1, states_row["1"] = 2, states_row["2"] = 3, states_row["3"] = 4;
	states_row["4"] = 5, states_row["5"] = 6, states_row["6"] = 7, states_row["7"] = 8;
	states_row["8"] = 9, states_row["9"] = 10, states_row["10"] = 11, states_row["11"] = 12;
	states_row["12"] = 13, states_row["13"] = 14, states_row["14"] = 15, states_row["15"] = 16;

	ter_line["("] = 1, ter_line[")"] = 2, ter_line["+"] = 3, ter_line["-"] = 4;
	ter_line["*"] = 5, ter_line["/"] = 6, ter_line["num"] = 7, ter_line["$"] = 8;
	ter_line["E"] = 9, ter_line["T"] = 10, ter_line["F"] = 11;

	/*----------�洢������--------*/
	LR_Table[1][1] = "S4", LR_Table[1][7] = "S5", LR_Table[1][9] = "1", LR_Table[1][10] = "2", LR_Table[1][11] = "3";
	LR_Table[2][3] = "S6", LR_Table[2][4] = "S7", LR_Table[2][8] = "acc";
	LR_Table[3][2] = "R3", LR_Table[3][3] = "R3", LR_Table[3][4] = "R3", LR_Table[3][5] = "S8", LR_Table[3][6] = "S9", LR_Table[3][8] = "R3";
	LR_Table[4][2] = "R6", LR_Table[4][3] = "R6", LR_Table[4][4] = "R6", LR_Table[4][5] = "R6", LR_Table[4][6] = "R6", LR_Table[4][8] = "R6";
	LR_Table[5][1] = "S4", LR_Table[5][7] = "S5", LR_Table[5][9] = "10", LR_Table[5][10] = "2", LR_Table[5][11] = "3";
	LR_Table[6][2] = "R8", LR_Table[6][3] = "R8", LR_Table[6][4] = "R8", LR_Table[6][5] = "R8", LR_Table[6][6] = "R8", LR_Table[6][8] = "R8";
	LR_Table[7][1] = "S4", LR_Table[7][7] = "S5", LR_Table[7][10] = "11", LR_Table[7][11] = "3";
	LR_Table[8][1] = "S4", LR_Table[8][7] = "S5", LR_Table[8][10] = "12", LR_Table[8][11] = "3";
	LR_Table[9][1] = "S4", LR_Table[9][7] = "S5", LR_Table[9][11] = "13";
	LR_Table[10][1] = "S4", LR_Table[10][7] = "S5", LR_Table[10][11] = "14";
	LR_Table[11][2] = "S15", LR_Table[11][3] = "S6", LR_Table[11][4] = "S7";
	LR_Table[12][2] = "R1", LR_Table[12][3] = "R1", LR_Table[12][4] = "R1", LR_Table[12][5] = "S8", LR_Table[12][6] = "S9", LR_Table[12][8] = "R1";
	LR_Table[13][2] = "R2", LR_Table[13][3] = "R2", LR_Table[13][4] = "R2", LR_Table[13][5] = "S8", LR_Table[13][6] = "S9", LR_Table[13][8] = "R2";
	LR_Table[14][2] = "R4", LR_Table[14][3] = "R4", LR_Table[14][4] = "R4", LR_Table[14][5] = "R4", LR_Table[14][6] = "R4", LR_Table[14][8] = "R4";
	LR_Table[15][2] = "R5", LR_Table[15][3] = "R5", LR_Table[15][4] = "R5", LR_Table[15][5] = "R5", LR_Table[15][6] = "R5", LR_Table[15][8] = "R5";
	LR_Table[16][2] = "R7", LR_Table[16][3] = "R7", LR_Table[16][4] = "R7", LR_Table[16][5] = "R7", LR_Table[16][6] = "R7", LR_Table[16][8] = "R7";

	cout << "LR����������ɣ�������ʾ��" << endl;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) 
			cout << setw(8) << LR_Table[row][col];
		cout << endl;
	}
	cout << endl;
}
void LR::show_info(string& c_ch, string& express, int c_ptr)//��������
{
	cout << left << "״̬ջ: ";
	for (auto it : s_state)//����
		cout << setw(3) << it;
	cout << endl << left << "����ջ: ";
	for (auto it : s_symbol)//����
		cout << setw(3) << it;

	cout << endl << left << "����:" << setw(c_ch.size() + 15) <<
		c_ch.substr(c_ptr) << "��������:" << setw(25) << express << endl << endl;
}

void LR::LR_analy(string& str)
{
	int c_ptr = 0;//ָ��ǰ�����ַ�
	int row = 0, col = 0;//�кţ��к�
	input_s = str;
	string express = "";
	while (true)
	{
		char current_ch = input_s[c_ptr];//��ǰ�ַ�
		string ch = "";
		ch += current_ch;//��Ϊstring��
		//cout << ch << endl;
		//Ϊ�˶�ȡ��λ���֣���ȡָ���ƶ�����һλ�����ַ���֮ǰ
		if (isdigit(current_ch))
		{
			for (; c_ptr < input_s.size(); c_ptr++) 
			{
				if (input_s[c_ptr] == '+' || input_s[c_ptr] == '-' || input_s[c_ptr] == '*' || input_s[c_ptr] == '/' || input_s[c_ptr] == '(' ||
					input_s[c_ptr] == ')' || input_s[c_ptr] == '$' || input_s[c_ptr] == 'E' || input_s[c_ptr] == 'T' || input_s[c_ptr] == 'F')
				{
					c_ptr--;
					break;
				}
			}
			ch = "num";
		}
		express = "";
		string state_stack_top = state_stack.top();//״̬ջ��
		//��Ӧ���ʽ
		string expression = LR_Table[states_row[state_stack_top]][ter_line[ch]];
		/*cout << states_row[state_stack_top] << " " << ter_line[ch] << endl;
		cout << expression << endl;*/
		if (expression[0] == 'S')//�ƽ�
		{
			c_ptr++;
			expression = expression.substr(1);
			express = "Shift " + expression;
			show_info(input_s, express, c_ptr);
			symbol_stack.push(ch);//������ջ
			state_stack.push(expression);//״̬��ջ
			s_state.push_back(expression);
			s_symbol.push_back(ch);
		}
		else if (expression[0] == 'R')//��Լ
		{
			expression = expression.substr(1);
			int index = stoi(expression);//��Լ���״̬
			express = expression_vec[index];
			string tmp = "reduce by ";
			tmp += express;
			show_info(input_s, tmp, c_ptr);
			//������ʽ��ǰ��������
			string f_string = express.substr(0, express.find_first_of("-"));
			string c_string = express.substr(express.find_first_of(">") + 1);
			int top = c_string.size();//top ��ջ����
			//cout << c_string << " " << top << endl;
			if (c_string == "num")
				top = 1;
			while (top--)
			{//��ջ
				s_state.erase(s_state.end() - 1);
				s_symbol.erase(s_symbol.end() - 1);
				state_stack.pop();
				symbol_stack.pop();
			}
			symbol_stack.push(f_string);
			s_symbol.push_back(f_string);
			//��ȡջ�����ţ�Ϊ����ջ��׼��
			state_stack_top = state_stack.top();
			row = states_row[state_stack_top];
			col = ter_line[f_string];
			state_stack.push(LR_Table[row][col]);
			s_state.push_back(LR_Table[row][col]);
		}
		else if (LR_Table[states_row[state_stack_top]][ter_line[ch]] == "acc") 
		{
			express = "acc";
			show_info(input_s, express, c_ptr);
			cout << "Accepted!�������" << endl;
			return;
		}
		else 
		{
			express = "No acc";
			show_info(input_s, express, c_ptr);
			cout << "Failed��" << endl;
			return;
		}
	}
	return;
}