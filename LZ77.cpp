#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "windows.h"

using namespace std;

struct Node{
	int index;
	string data;
	Node *next;
};

void st_Node(Node *head, int index, string data){
	head->index = index;
	head->data = data;
	head->next = NULL;
}

void insert_Node(Node *head, int index, string data){
	Node *new_Node = new Node;
	new_Node->index = index;
	new_Node->data = data;
	new_Node->next = NULL;

	Node *curr = head;
	while (curr != NULL)
	{
		if (curr->next == NULL)
		{
			curr->next = new_Node;
			return;
		}
		curr = curr->next;
	}
}

Node *search_Node(Node *head, string data)
{
	Node *curr = head;
	while (curr != NULL)
	{
		if (data.compare(curr->data) == 0)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}

Node *search_Node(Node *head, int index)
{
	Node *curr = head;
	while (curr != NULL)
	{
		if (index == curr->index)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}

bool delete_Node(Node *head, Node *to_delete){
	if (to_delete == NULL)
		return false;
	else if (to_delete == head)
	{
		head = to_delete->next;
		delete to_delete;
		return true;
	}
	else{
		Node *curr = head;
		while (curr)
		{
			if (curr->next == to_delete)
			{
				curr->next = to_delete->next;
				delete to_delete;
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
}

vector <string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); 
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

string LZ77(string input, int option);
string LZ78(string input, int option);
string LZW(string input, int option);

int main()
{
	string input, result, method_text;
	int method, option, option2;

	string intro = R"(
	Hi I'm Alpha  ^_^ , Code Expo's assistant, I'm here to help you.
)";
	cout << intro;
main_menu:
	string main_menu = R"(
-------------------------------------------------------------------------------
 This tool generate compression and decompression using LZ-77, LZ-78 and LZW methods :
   1- LZ-77
   2- LZ-78
   3- LZW
 Enter 1, 2 or 3 according to method.
  > )";	cout << main_menu;

	cin >> method;

	if (method == 1)
		method_text = "LZ-77";
	else if (method == 2)
		method_text = "LZ-78";
	else if (method == 3)
		method_text = "LZW";
	else
	{
		system("cls");
		cout << intro;
		goto main_menu;
	}

method_menu:
	system("cls");
	cout << intro;

	string main_menu_2 = R"(
-------------------------------------------------------------------------------
 This tool generate compression and decompression using )" + method_text + R"( method :
   1- Compression
   2- Decompression
   0- Main menu
 Enter 1, 2 or 0 according to method.
  > )";	cout << main_menu_2;

	cin >> option;

	if (option == 1)
	{
		system("cls");
		cout << intro;

		string lz77_Compression = R"(
-------------------------------------------------------------------------------
 )" + method_text + R"( >  Compression :)";
		cout << lz77_Compression << endl;

		cout << "\t Enter your phrases : ";
		cin.ignore();
		getline(cin, input);
		if (method == 1)
			result = LZ77(input, 1);
		else if (method == 2)
			result = LZ78(input, 1);
		else if (method == 3)
			result = LZW(input, 1);
		else
		{
			system("cls");
			cout << intro;
			goto main_menu;
		}

		cout << "\n\t Final result : " << result << endl;

	back_1:
		cout << "\n Enter 0 to back to Main menu or 1 to back to Method menu. \n  > ";
		cin >> option2;

		if (option2 == 0)
		{
			system("cls");
			cout << intro;
			goto main_menu;
		}
		else if (option2 == 1)
			goto method_menu;
		else
			goto back_1;
	}
	else if (option == 2)
	{
		system("cls");
		cout << intro;

		string lz77_Compression = R"(
-------------------------------------------------------------------------------
 LZ-77 >  Decompression :)";
		cout << lz77_Compression << endl;
		cout << "\t Enter your code : ";
		cin.ignore();
		getline(cin, input);
		if (method == 1)
			result = LZ77(input, 2);
		else if (method == 2)
			result = LZ78(input, 2);
		else if (method == 3)
			result = LZW(input, 2);
		else
			main_menu;

		cout << "\n\t Final result : " << result << endl;

	back_2:
		cout << "\n Enter 0 to back to Main menu or 1 to back to Method menu. \n  > ";
		cin >> option2;

		if (option2 == 0)
		{
			system("cls");
			cout << intro;
			goto main_menu;
		}
		else if (option2 == 1)
			goto method_menu;
		else
			goto back_2;

	}
	else if (option == 0)
	{
		system("cls");
		cout << intro;
		goto main_menu;
	}
	else
		goto method_menu;


	cin.get();
	cin.ignore();
	return 0;
}

string LZ77(string input, int option)
{
	string result;
	int length, char_info_selc = 0;

	if (option == 1)
	{
	check_char:	
		length = (int)input.length();	
		if (length <= 2)
		{
			cout << "enter at leaset 3 characters \n";
			getline(cin, input);		
			goto check_char;
		}

		int** result_ary = new int*[3];
		for (int i = 0; i < length; ++i)
			result_ary[i] = new int[length];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < length; j++)
				result_ary[i][j] = 0;
		}

		int** char_info = new int*[3];
		for (int i = 0; i < length; ++i)
			char_info[i] = new int[length];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < length; j++)
				char_info[i][j] = 0;
		}

		result_ary[0][0] = 0;
		result_ary[1][0] = 0;
		result_ary[2][0] = input[0];

		int result_count = 1;
		for (int i = 1; i < length; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (input[i] == input[j])
				{
					char_info[0][char_info_selc] = i - j;
					char_info_selc++;
				}

			}
			for (int j = 0; j < length; j++)
			{
				if (char_info[0][j] != 0)
				{
					int start = i - char_info[0][j];
					int count = 1;
					for (int k = 0; k < length; k++)
					{
						if (input[start + count] == input[i + count])
							count++;	
						else
						{
							char_info[1][j] = count;	
							if (i != (length - 1))
							{
								if (char_info[0][j] + count == length)
									char_info[2][j] = 0;	
								else
									char_info[2][j] = input[char_info[0][j] + count];	
							}
							else
								char_info[2][j] = NULL;		

							break;	
						}
					}
				}
			}
			int large = 0;
			for (int k = 1; k < length; k++)
			{
        if (char_info[1][large] == char_info[1][k])
					large = k;	
				else if (char_info[1][large] < char_info[1][k])
					large = k;	
			}
			if (char_info[1][large] == 0)
				char_info[2][large] = input[i];		
			else
			{
				i += char_info[1][large];	
				char_info[2][large] = input[i];	
			}
			result_ary[0][result_count] = char_info[0][large];
			result_ary[1][result_count] = char_info[1][large];
			result_ary[2][result_count] = char_info[2][large];
			result_count++;
			for (int z = 0; z < 2; z++)
			{
				for (int j = 0; j < length; j++)
					char_info[z][j] = 0;
			}
			char_info_selc = 0;
		}
		for (int j = 0; j < length; j++)
		{
			if (result_ary[0][j] == 0 && result_ary[1][j] == 0)
			{
				if (result_ary[2][j] != NULL || result_ary[2][j] != 0)
				{
					char z = result_ary[2][j];
					result += to_string(result_ary[0][j]) + "," + to_string(result_ary[1][j]) + "," + z + " ";
				}
			}
			else
			{
				result += to_string(result_ary[0][j]) + "," + to_string(result_ary[1][j]) + ",0 ";
			}
		}
		return result;
	}
	else if (option == 2)
	{
		vector<string> s_input = split(input, ' ');

		for (int i = 0; i < s_input.size(); ++i)
		{
			vector<string> ss_input = split(s_input[i], ',');

			int p = stoi(ss_input[0]),
				l = stoi(ss_input[1]);
			string ch;
			if (ss_input[2][0] == '0')
				ch = ' ';
			else
				ch = ss_input[2];

			if (p != 0)
			{
				int result_len = (int)result.length();
				for (int x = 0; x < l; x++)
					result += result[result_len - p + x];
			}

			if (ch[0] != '0' || ch[0] != NULL)
				result += ch;
		}
		return result;
	}
}

string LZ78(string input, int option)
{
	if (option == 1)
	{
		Node *dictionary = new Node;
		string word, result;
		int length, last_seen, index = 1;

		length = (int)input.length();
		word = input[0];
		st_Node(dictionary, 1, word);
		result += "0," + word;

		for (int i = 1; i < length; i++)
		{
			string data;
			data = input[i];

		re_check:
			Node *search = search_Node(dictionary, data);

			if (search)
			{
				i++;
				data += input[i];
				last_seen = search->index;
				goto re_check;
			}
			else
			{
				char zero;
				if (input[i] == ' ')
					zero = '0';
				else
					zero = input[i];

				if ((int)data.length() < 2)
					result += " " + to_string(0) + "," + zero;
				else
					result += " " + to_string(last_seen) + "," + zero;

				index++;
				if (i != length)
					insert_Node(dictionary, index, data);
			}
		}

		return result;
	}
	if (option == 2)
	{
		Node *dictionary = new Node;
		string result;

		vector <string> s_input = split(input, ' ');
		int zz = 2;
		for (int i = 0; i < s_input.size(); i++)
		{
			vector <string> ss_input = split(s_input[i], ',');

			if (i == 0)
			{
				st_Node(dictionary, 1, ss_input[1]);
				result += ss_input[1];
			}
			else
			{
				Node *serched;
				string get_search = ss_input[1];
				serched = search_Node(dictionary, stoi(ss_input[0]));
				if (serched)
				{
					result += serched->data + get_search;
					get_search = serched->data + split(s_input[i], ',')[1];
					insert_Node(dictionary, zz, get_search);
				}
				else
				{
					if (stoi(ss_input[0]) == 0)
						insert_Node(dictionary, zz, get_search);
					else
						insert_Node(dictionary, zz, get_search);

					result += get_search;
				}
				zz++;
			}
		}

		if (result[(int)result.length() - 1] == '0')
			result = result.substr(0, result.size() - 1);
		
		return result;
	}
}

string LZW(string input, int option)
{
	if (option == 1)
	{
		Node *dictionary = new Node;
		string result;
		int length, last_seen, index = 128;

		st_Node(dictionary, 32, " ");
		for (int i = 33; i < 128; i++)
		{
			string data;
			data = i;
			insert_Node(dictionary, i, data);
		}

		length = (int)input.length();

		for (int i = 0; i < length; i++)
		{
			Node *searched;
			string search;
			search = input[i];

		re_search:
			searched = search_Node(dictionary, search);
			if (searched)
			{
				i++;
				search += input[i];
				last_seen = searched->index;
				if (i != length)
					goto re_search;
				else
					goto print;
			}
			else
			{
				insert_Node(dictionary, index, search);
				index++;
			print:
				result += to_string(last_seen) + " ";
				i--;
			}
		}

		return result;
	}
	if (option == 2)
	{
		Node *dictionary = new Node;
		string result;
		int index = 128;

		st_Node(dictionary, 32, " ");
		for (int i = 33; i < 128; i++)
		{
			string data;
			data = i;
			insert_Node(dictionary, i, data);
		}

		vector <string> s_input = split(input, ' ');
		for (int i = 0; i < s_input.size(); i++)
		{
			Node *searched;
			int search;
			search = stoi(s_input[i]);

			searched = search_Node(dictionary, search);

			string cur, prev, data;
			if (searched)
				cur = search_Node(dictionary, stoi(s_input[i]))->data;
			if (i != 0)
				prev = search_Node(dictionary, stoi(s_input[i - 1]))->data;
			else
				prev = cur;

			int show = 0;
			if (searched)
			{
				result += searched->data;

				if (i != 0)
				{
					data = prev + cur[0];
					if (show != 1)
					{
						insert_Node(dictionary, index, data);
						index++;
					}
				}
				show = 0;
			}
			else
			{
				data = prev + prev[0];
				insert_Node(dictionary, index, data);
				index++;
				show = 1;
				result += data;
			}
		}

		return result;
	}
}
