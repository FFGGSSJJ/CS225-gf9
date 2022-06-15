#include "bptree.cpp"

//give command line argument to load a tree from log
//to create a fresh tree, do not give any command line argument
int main(int argc, char* argv[])
{
	// BPTree bpt;//B+ tree object that carries out all the operations
	// string command;
	// int x;
	// bool close = false;
	// string logBuffer;//used to save into log
	// ifstream fin;
	// ofstream fout;
	// //create tree from log file from command line input
	// if(argc > 1)
	// {
	// 	fin.open(argv[1]);//open file
	// 	if(!fin.is_open())
	// 	{
	// 		cout<<"File not found\n";
	// 		return 0;
	// 	}
	// 	int i = 1;
	// 	getline(fin, logBuffer, '\0');//copy log from file to logBuffer for saving purpose
	// 	fin.close();
	// 	fin.open(argv[1]);//reopening file
	// 	getline(fin,command);
	// 	stringstream max(command);//first line of log contains the max degree
	// 	max>>MAX;
	// 	while(getline(fin,command))//iterating over every line ie command
	// 	{
	// 		if(!command.substr(0,6).compare("insert"))
	// 		{
	// 			stringstream argument(command.substr(7));
	// 			argument>>x;
	// 			bpt.insert(x);
	// 		}
	// 		else if(!command.substr(0,6).compare("delete"))
	// 		{
	// 			stringstream argument(command.substr(7));
	// 			argument>>x;
	// 			bpt.remove(x);
	// 		}
	// 		else
	// 		{
	// 			cout<<"Unknown command: "<<command<<" at line #"<<i<<"\n";
	// 			return 0;
	// 		}
	// 		i++;
	// 	}
	// 	cout<<"Tree loaded successfully from: \""<<argv[1]<<"\"\n";
	// 	fin.close();
	// }
	// else//create fresh tree
	// {
	// 	cout<<"Enter the max degree\n";
	// 	cin>>command;
	// 	stringstream max(command);
	// 	max>>MAX;
	// 	logBuffer.append(command);
	// 	logBuffer.append("\n");
	// 	cin.clear();
	// 	cin.ignore(1);
	// }
	// //command line menu
	// cout<<"Commands:\nsearch <value> to search\n";
	// cout<<"insert <value> to insert\n";
	// cout<<"delete <value> to delete\n";
	// cout<<"display to display\n";
	// cout<<"save to save log\n";
	// cout<<"exit to exit\n";
	// do
	// {
	// 	cout<<"Enter command: ";
	// 	getline(cin,command);
	// 	if(!command.substr(0,6).compare("search"))
	// 	{
	// 		stringstream argument(command.substr(7));
	// 		argument>>x;
	// 		bpt.search(x);
	// 	}
	// 	else if(!command.substr(0,6).compare("insert"))
	// 	{
	// 		stringstream argument(command.substr(7));
	// 		argument>>x;
	// 		bpt.insert(x);
	// 		logBuffer.append(command);
	// 		logBuffer.append("\n");
	// 	}
	// 	else if(!command.substr(0,6).compare("delete"))
	// 	{
	// 		stringstream argument(command.substr(7));
	// 		argument>>x;
	// 		bpt.remove(x);
	// 		logBuffer.append(command);
	// 		logBuffer.append("\n");
	// 	}
	// 	else if(!command.compare("display"))
	// 	{
	// 		bpt.display(bpt.getRoot());
	// 	}
	// 	else if(!command.compare("save"))
	// 	{
	// 		cout<<"Enter file name: ";
	// 		string filename;
	// 		cin>>filename;
	// 		fout.open(filename);
	// 		fout<<logBuffer;
	// 		fout.close();
	// 		cout<<"Saved successfully into file: \""<<filename<<"\"\n";
	// 		cin.clear();
	// 		cin.ignore(1);
	// 	}
	// 	else if(!command.compare("exit"))
	// 	{
	// 		close = true;
	// 	}
	// 	else
	// 	{
	// 		cout<<"Invalid command\n";
	// 	}
	// }while(!close);
	
	BPTree bptree;
	MAX = 5;

	bool loop = true;
	int x;
	int check;
	int key[30] = {5,7,13,4,43,1,17,8,9,10,3,45,6,23,6,54,56,786,543,91,67,35,67,34,5,8,43,910,342,9};
	cout << "\033[031m__________________________________________________________\n";
	cout << "|                                                        |\n";
	cout << "|           Test Cases For Assignment_8 Ex2              |\n";
	cout << "|                                                        |\n";
	cout << "|________________________________________________________|\n";
	cout<<"Using b+ tree to store items, for simplicity and test purpose, the \ninput and output is only the primiary key field of the node, \nother tuples and message can be stored in the node class for other purpose\n";

	while (loop)
	{

		cout << "\033[033m\n0 for add automatically, 1 for insert, 2 for delete, 3 for find min and max, 4 for display, 5 for find predecessor and successor, 6 for exist: \033[0m"<< endl;
		cin >> check;

		switch (check)
		{
		case 0:
			cout << "How many node do you want to insert automatically: (1~30)";
			cin >> x;
			cout << "The Random input is: ";
			for (int i = 0; i<x ; i++)
			{	
				cout << key[i]<<" ";
			}

			for (int i = 0; i<x ; i++)
			{	
				bptree.insert(key[i]);
			}

			break;
		case 1:
			cout << "What number do you want to insert: ";
			cin >> x;
			bptree.insert(x);
			break;
		case 2:
			cout << "What number do you want to delete: ";
			cin >> x;
			bptree.remove(x);
			break;
		case 3:
			cout << "The minimum is: "<<bptree.find_min()<<endl;
			cout << "The maximum is: "<<bptree.find_max()<<endl;
			break;
		case 4:
			cout << "The leaf nodes are: ";
			bptree.display(bptree.getRoot());
			cout<<endl;
			break;
		case 5:
			cout << "For what node do you want to find it's predecessor and successor: ";
			cin >> x ;
			if (bptree.findPrec(x) != -1) cout << "The predecessor is: "<<bptree.findPrec(x)<<endl;
			if (bptree.findSucc(x) != -1) cout << "The successor is: "<<bptree.findSucc(x)<<endl;
			break;
		default:
			loop = false;
			break;
		}	
	}

	return 0;
}
