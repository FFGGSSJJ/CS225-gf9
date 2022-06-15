#include "B_tree.cpp"

int main()
{
	Btree t(3);
	// t.insert(1);
	// t.insert(3);
	// t.insert(7);
	// t.insert(10);
	// t.insert(11);
	// t.insert(13);
	// t.insert(14);
	// t.insert(15);
	// t.insert(18);
	// t.insert(16);
	// t.insert(19);
	// t.insert(24);
	// t.insert(25);
	// t.insert(26);
	// t.insert(4);
	// t.insert(5);
	// t.insert(20);
	// t.insert(22);
	// t.insert(2);
	// t.insert(17);
	// t.insert(12);
	// t.insert(6);
    // //write your test here//
	// cout<<t.find_max()<<endl;
	// cout<<t.find_min()<<endl;
	// t.traverse();


	bool loop = true;
	int x;
	int check;
	int key[30] = {5,7,13,4,43,1,17,8,9,10,3,45,6,23,54,56,786,543,91,67,35,67,34,5,8,43,910,342};


	cout<<"==================================================="<<endl;
	cout<<endl;
	cout<<"Use b tree to store items, for simplicity and test purpose, the input and output is only the primiary key field of the node, other tuples and message can be stored in the node class for other purpose\n";

	cout<<"======================START========================"<<endl;
	while (loop)
	{
		cout << "\n0 for add automatically, 1 for insert, 2 for delete, 3 for find min and max, 4 for display, 5 for find predecessor and successor, 6 for exit: "<< endl;
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
				t.insert(key[i]);
			}

			break;
		case 1:
			cout << "What number do you want to insert: ";
			cin >> x;
			t.insert(x);
			break;
		case 2:
			cout << "What number do you want to delete: ";
			cin >> x;
			t.remove(x);
			break;
		case 3:
			cout << "The minimum is: "<<t.find_min()<<endl;
			cout << "The maximum is: "<<t.find_max()<<endl;
			break;
		case 4:
			cout << "The numbers in B-tree are: ";
			t.traverse();
			cout<<endl;
			break;
		case 5:
			cout << "For what node do you want to find it's predecessor and successor: ";
			cin >> x ;
			if (t.findPrec(x) != -1) cout << "The predecessor is: "<<t.findPrec(x)<<endl;
			if (t.findSucc(x) != -1) cout << "The successor is: "<<t.findSucc(x)<<endl;
			break;
		default:
			loop = false;
			break;
		}	
	}

	return 0;

}
