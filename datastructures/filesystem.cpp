#include<iostream>
#include<string>
#include<unordered_map>
#include<map>
#include<sstream>
#include<algorithm>
using namespace std;



unordered_map<string, bool> valid_commands;
vector<string> arr = { "mkdir","mkf","pwd","cd","rmdir","rmf","dir","cd.."};


struct File
{
	string name;
	File(string fname)
	{
		name = fname;
	}

};


struct Node
{
	string name, path;
	Node* parent;
	map<string, Node*>mp;
	map<string, File*>fp;
	Node(string name)
	{
		this->name = name;
		// parent and path need to be set explicitly
		parent = NULL;
		path = "#";
	}
	void create_file(string name)
	{
		fp[name] = new File(name);
	}
};






// creating a root;
Node* root = new Node("root:");
Node* temp_root = root;


// insert the valid commands to hash table(valid commands)
void init()
{
	for (string s : arr)
	{
		valid_commands[s] = 1;
	}
	root->path = root->name;
}



//  function for handling mkdir


void print(Node* curr_node)
{
	cout << "directory of " << curr_node->name <<"\\"<< endl;
	for (auto dir : curr_node->mp)
	{
		cout << "<dir> " << "      " << dir.first << endl;
	}
	for (auto file : curr_node->fp)
	{
		cout << "file " << "      " << file.first << endl;
	}

}

void delimit(vector<string>& arr, string s)
{
		int i = 0;
		string temp;
		while (i < s.size())
		{
			if (s[i] == '/' or s[i] == '\\')
			{
				arr.push_back(temp);
				temp = "";
				i += 1;
			}
			else {
				temp += s[i];
				i++;
			}
		}
		arr.push_back(temp);
} 


bool is_valid(string s)
{
	for (char c : s)
	{
		if (c == '/'  or c == '<' or c == '>' or c == '|' or c == ':')  return false;
	}
	return true;
}


void  delimit_dir(vector<string>& arr, string s)
{
	int i = 0;
	string temp;
	while (i < s.size())
	{
		if (s[i] == '\\')
		{
			arr.push_back(temp);
			temp = "";
			i += 1;
		}
		else {
			temp += s[i];
			i++;
		}
	}
	arr.push_back(temp);
}

bool ispath_dir(string s)
{
	for (char c : s) if (c == '\\') return true;
	return false;
}

bool forward(string s)
{
	for (char c : s) if (c == '/') return false;
	return true;
}



void parse(vector<string>& tokens)
{
	// convert the command to lower case
	//transform(tokens.begin(), tokens.end(), tokens.begin(), ::tolower);
	string command = tokens[0];

	
	if (command == "mkdir")
	{
		for (int i = 1; i < tokens.size(); i++)
		{
			for (int j = 0; j < tokens[i].size(); j++)
			{
				if (tokens[i][j] == '/')
				{
					cout << "The syntax of the command is incorrect." << endl;
					return;
				}
			}
		}
		for(int i = 1; i < tokens.size(); i++) {


			// check current token is invalid
			if (is_valid(tokens[i]) == false)
			{
				cout << "The filename, directory name, or volume label syntax is incorrect.: " << tokens[i] << endl;
				continue;
			}

			// if valid then check if it is nested path
			if (ispath_dir(tokens[i]))
			{
				// create a nested diretory
				vector<string> dir_tokens;
				string nested_dir = tokens[i];

				// parse it into names
				delimit_dir(dir_tokens, nested_dir);

				
				Node* recur_root = temp_root;
				string path = recur_root->path;
				int i = 0, n = dir_tokens.size();
				while (i < n)
				{

					auto map = recur_root->mp;
					if (map.find(dir_tokens[i]) == map.end())
					{
						recur_root->mp[dir_tokens[i]] = new Node(dir_tokens[i]);

					}
					recur_root->mp[dir_tokens[i]]->path = path + "\\" + dir_tokens[i];
					recur_root->mp[dir_tokens[i]]->parent = recur_root;
					path = recur_root->mp[dir_tokens[i]]->path;
					recur_root = recur_root->mp[dir_tokens[i]];
					i++;
				}
			}
			else
			{
				Node* temp = temp_root;
				string path = temp->path;
				auto map = temp->mp;
				if (map.find(tokens[i]) == map.end())
				{
					temp->mp[tokens[i]] = new Node(tokens[i]);
				}
				temp->mp[tokens[i]]->path = path + "\\" + tokens[i];
				temp->mp[tokens[i]]->parent = temp_root;
			}
		}


	}
	else if (command == "mkf")
	{	
		temp_root->create_file(tokens[1]);
	}
	else if (command == "dir")
	{
		print(temp_root);
	}
	else if (command == "pwd")
	{
		cout << temp_root->path << "\\"<<endl;
	}
	else if (command == "cd.." || (tokens.size()==2 and tokens[0]=="cd" and tokens[1]==".."))
	{
		if (temp_root->name == "root:") {}
		else temp_root = temp_root->parent;
	}
	else if (command == "cd")
	{

		
		if (tokens.size() > 2)
		{
			cout << "The system cannot find the path specified.";
		}
		else
		{
			
			string path_to_be_parsed = tokens[1];
			vector<string>  dirs;
			//cout << path_to_be_parsed << endl;
			delimit(dirs, path_to_be_parsed);
			Node* newtemp = temp_root;
			int i = 0, n = dirs.size();
			//cout << i << " " << n << endl;
			while(i<n)
			{
				auto map = newtemp->mp;
				if (map.find(dirs[i]) == map.end()) break;
				newtemp = newtemp->mp[dirs[i]];
				i++;
			}
			if (i == n)
			{
				//cout << "success" << endl;
				temp_root = newtemp;
			}
			else
			{
				cout << "The system cannot find the path specified." << endl;
			}
		}
	}
	else if (command == "rmdir")
	{
		string deldir = tokens[1];
		auto map = temp_root->mp;
		if (map.find(deldir) != map.end())
		{
			Node* rm = temp_root->mp[deldir];
			delete rm;
			temp_root->mp.erase(deldir);
		}
		else
		{
			cout << "The system cannot find the file specified." << endl;
		}
	}
	else if (command == "rmf")
	{
		string deldir = tokens[1];
		auto map = temp_root->fp;
		if (map.find(deldir) != map.end())
		{
			File* rm = temp_root->fp[deldir];
			delete rm;
			temp_root->fp.erase(deldir);
		}
		else
		{
			cout << "The system cannot find the file specified." << endl;
		}

	}
}



int main()
{
	cout << "press exit to exit" << endl;
	init();
	while (true)
	{
		string command;
		if (command == "exit") break;
		cout << temp_root->path << "\\>" << endl;
		getline(cin, command);
		if (command.size() == 0)
		{
			cout << "enter valid command " << endl;
			continue;
		}
		vector<string> tokens;
		istringstream ss(command);

		// split the string
		while(ss)
		{
			string word;
			ss >> word;
			tokens.push_back(word);
			//cout << word << endl;
		} 
		tokens.pop_back();
		//for (auto s : tokens) cout <<"--> "<< s << endl;
		//for (auto s : tokens) cout <<"--> "<< s << endl;


		if (valid_commands[tokens[0]] == 1)
		{
			parse(tokens);
		}
		else
		{
			cout << "'" << tokens[0] << "'" << " is not recognized as an internal or external command" << endl;
		}

	}
	return 0;
}
