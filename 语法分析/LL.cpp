#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<string>
#include<stack>
#include<map>
#define rows 6
#define cols 9
using namespace std;
class LL
{
private:
	string input_s;//���룬���������ַ���
	string stack_s;//ջ���ַ���
	string ana_table[rows][cols];//Ԥ�������
	stack<string> stack;//ջ
	vector<string> Terminator;//�ս��
	vector<string> nTerminator;//���ս��
	map<string, vector<string>> expression;//�ķ����ʽ
	map<string, vector<string>> first_set;//First����
	map<string, vector<string>> follow_set;//Follow����
	map<string, int> col_nter;//���ս����Ӧ���к�
	map<string, int> row_ter;//�ս����Ӧ���к�
public:
	string init_s;//��ԭʼ�ķ����ַ���
	void init_set();//���ַ��ţ����ϵĳ�ʼ��
	void init_stack();//ջ�ĳ�ʼ��
	void create_anal_table();//���졢���������
	void LL_analysis();//��������Ŵ����з���
};

int main()
{
	LL L_table;
	L_table.init_set();
	L_table.create_anal_table();

	cout << "���������������\n";
	cin >> L_table.init_s;
	L_table.init_s += "$";
	L_table.init_stack();
	L_table.LL_analysis();
	system("pause");
	return 0;
}

void LL::init_set()//���ַ��ţ����ϵĳ�ʼ��
{
	/*-----------------��������ݹ��ķ�---------------*/
	expression["E"] = { "TW" };
	expression["W"] = { "+TW","-TW","��" };
	expression["T"] = { "FX" };
	expression["X"] = { "*FX","/FX","��" };
	expression["F"] = { "(E)","num" };
	cout << "LL(1)�ķ�:" << endl;
	for (auto ptr = expression.begin(); ptr != expression.end(); ptr++)
	{
		cout << ptr->first << "->";
		for (auto eptr = ptr->second.begin(); eptr < ptr->second.end(); eptr++)
			if (eptr < ptr->second.end() - 1)
				cout << *eptr << "|";
			else
				cout << *eptr << endl;
	}
	/*-------------------�ս��--------------------*/
	ana_table[0][1] = "+", ana_table[0][2] = "-", ana_table[0][3] = "*", ana_table[0][4] = "/";
	ana_table[0][5] = "(", ana_table[0][6] = ")", ana_table[0][7] = "num", ana_table[0][8] = "$";
	/*-------------------���ս��------------------*/
	ana_table[1][0] = "E", ana_table[2][0] = "W", ana_table[3][0] = "T",
		ana_table[4][0] = "X", ana_table[5][0] = "F";
	/*-------------------FIRST����----------------*/
	first_set["E"] = {"(", "num"};
	first_set["W"] = { "+","-","��" };
	first_set["T"] = { "(","num" };
	first_set["X"] = { "*","/","��" };
	first_set["F"] = { "(","num" };
	/*------------------FOLLOW����----------------*/
	follow_set["E"] = { "$",")" };
	follow_set["W"] = { "$",")" };
	follow_set["T"] = { "$",")","+","-" };
	follow_set["X"] = { "$",")","+","-" };
	follow_set["F"] = { "$","+","-","*","/",")" };
	/*---------�ս���ͷ��ս����Ӧ���кź��к�-------*/
	for (int i = 1; i < rows; i++)
		row_ter[ana_table[i][0]] = i;
	for (int j = 1; j < cols; j++)
		col_nter[ana_table[0][j]] = j;
}
void LL::init_stack()//ջ�ĳ�ʼ��
{
	//����ʼ����E��$��ʼ
	stack.push("$");
	stack.push(ana_table[1][0]);
	stack_s = "$" + ana_table[1][0];
}
void LL::create_anal_table()//���졢���������
{
	ana_table[0][0] = "";
	for (int i = 1; i < rows; i++)
	{
		string n_ter = ana_table[i][0];//ȡ�����ս����first����follow��
		vector<string>first_tmp = first_set[n_ter];
		vector<string>follow_tmp = follow_set[n_ter];
		bool e_empty = false;//exit empty���ж��Ƿ񺬿�
		if (*(first_tmp.end() - 1) == "��")
			e_empty = true;
		for (int j = 1; j < cols; j++)
		{
			string ter = ana_table[0][j];//�ս��
			if (find(first_tmp.begin(), first_tmp.end(), ter) != first_tmp.end())//�ҵ���Ӧ���ս��
			{
				vector<string> sentence = expression[n_ter];
				if (sentence.size() == 1)//��������ʽ
					ana_table[i][j] = n_ter + "->" + sentence[0];
				else//�������ʽ
				{
					for (int k = 0; k < sentence.size(); k++)
					{
						string tmp = sentence[k];
						if (ter.size() == 1)
							tmp = tmp.at(0);
						if (tmp == ter)
						{
							ana_table[i][j] = n_ter + "->" + sentence[k];
							break;
						}
					}
				}
			}
			//���ղ���ʽ���ս����FOLLOW����
			else if (e_empty && find(follow_tmp.begin(), follow_tmp.end(), ter) != follow_tmp.end())
				ana_table[i][j] = n_ter + "->��";
			else if (find(follow_tmp.begin(), follow_tmp.end(), ter) != follow_tmp.end())
				ana_table[i][j] = "synch";
			else
				ana_table[i][j] = "error";
		}
	}
	cout << "���ɵ�Ԥ�������������ʾ:" << endl;
	for (int i = 0; i <rows; i++) 
	{
		for (int j = 0; j < cols; j++)
			cout << setw(10) << left << ana_table[i][j];
		cout << endl;
	}
}
void LL::LL_analysis()//��������Ŵ����з���
{
	input_s = init_s;
	int c_ptr = 0;//ָ�����ڷ������ַ�
	string genrate_s = "";//��������ʽ
	while (!stack.empty())
	{
		cout << "ջ��" << setw(input_s.size() + 10) << stack_s << "����:" << setw(input_s.size() + 10) << init_s.substr(c_ptr) << "ʹ�õ�����ʽ:" << genrate_s << endl;
		string s_flag = "";//�ַ����
		genrate_s = "";//����ʽ
		char ch = input_s.at(c_ptr);//��ǰ�������ַ�
		string s_top = stack.top();//ջ������
		if (s_top == "$")
		{
			cout << "LL(1)�﷨������ɣ�" << endl;
			return;
		}
		if (ch <= '9' && ch >= '0')
			s_flag = "num";
		else
			s_flag = ch;
		//��ǰ�ַ����ź�ջ��������ͬʱ
		if (s_flag == s_top)
		{
			if (stack.top() == "num")
				stack_s.erase(stack_s.end() - 3 - stack_s.begin(), 3);//ɾ�� n u m
			else
				stack_s.erase(stack_s.end() - 1);
			stack.pop();//ջ����ջ
			if (s_flag == "num")
			{
				//Ϊ�˶�ȡ��λ���֣���ָ���ƶ��������ֵĵ�һλ
				for (; c_ptr < input_s.size(); c_ptr++)
				{
					char c_ch = input_s.at(c_ptr);//��ǰ�ַ�
					if (c_ch == '+' || c_ch == '-' || c_ch == '*' ||c_ch == '/' || c_ch == '(' || c_ch == ')' || c_ch == '$')
						break;
				}
			}
			else
				c_ptr++;
		}
		else
		{
			//ջ�����Ŷ�Ӧ���к�
			int row = row_ter[s_top];
			int col = col_nter[s_flag];
			//�ڷ��������ҵ���Ӧ��Ϣ
			genrate_s = ana_table[row][col];
			if (genrate_s == "synch")
			{//��ջ������
				genrate_s = "����M[" + ana_table[row][0] + "," + s_flag + "]" + " = synch,����" + stack.top();
				if (stack.top() == "num")
					stack_s.erase(stack_s.end() - 3 - stack_s.begin(), 3);
				else
					stack_s.erase(stack_s.end() - 1);
				stack.pop();
			}
			else if (genrate_s == "error")
			{
				genrate_s = "����,M[" + ana_table[row][0] + "," + s_flag + "]" + " = error ����ǰ�ƶ���ǰָ��";
				c_ptr++;
			}
			else
			{
				if (stack.top() == "num")
					stack_s.erase(stack_s.end() - 3 - stack_s.begin(), 3);
				else
					stack_s.erase(stack_s.end() - 1);
				stack.pop();
				int pos = genrate_s.find_first_of(">") + 1;
				string tmpstr = genrate_s.substr(pos);
				if (tmpstr == "num")
				{
					stack.push(tmpstr);
					stack_s += tmpstr;
				}
				else if (tmpstr == "��");
				else
				{
					for (int i = tmpstr.size() - 1; i >= 0; i--)
					{//������ջ
						char tmp1 = tmpstr[i];//��ȡ����ʽ�Ҳ�
						string tmp = "";
						tmp += tmp1;
						stack.push(tmp);
						stack_s += tmp;
					}
				}
			}
		}
	}
}