
/* 	DSA Project 
	BSCS-8-B 
	Phone Directory
	Abdul Rahman Jawad 258729
	Ahmed Rehman Chauhan 247321
	Haider Ahmed 249297	
*/

#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<string>
#include <cstdlib>

using namespace std;
ofstream outf;
ifstream myFileStream;

class contactNode
{
	long long int number;
	char fname[20], lname[20], email[40];
	contactNode *left, *right;
	friend class tree;
};
class tree
{
public:
	contactNode *root;
	tree()
	{
		root = new contactNode();
		root = NULL;
	}

	void create2(contactNode *p){
		contactNode *parent;
		contactNode *tmp = root;
		p->left = NULL;
		p->right = NULL;
		if (root == NULL)
		{
			root = p;
		}
		else
		{
			while (tmp != NULL)
			{
				parent = tmp;
				if (strcmp(p->fname, tmp->fname) < 0)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (strcmp(p->fname, parent->fname) < 0)
				parent->left = p;
			else
				parent->right = p;
		}
	}

	void create()
	{
		int k = 0;
		contactNode *tmp, *p, *parent = NULL;
		tmp = root;
		p = new contactNode();
		cout << "\nFirst Name: ";
		cin >> p->fname;
		cout << "\nLast Name: ";
		cin >> p->lname;
		do{
			cout << "\nPhone number: ";
			cin >> p->number;
			k = numchck(p->number);
		} while (k != 1);
		do{
			cout << "\nEmail-ID: ";
			cin >> p->email;
			k = mailchck(p->email);
		} while (k != 1);
		p->left = NULL;
		p->right = NULL;
		if (root == NULL)
		{
			root = p;
		}
		else
		{
			while (tmp != NULL)
			{
				parent = tmp;
				if (strcmp(p->fname, tmp->fname) < 0)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (strcmp(p->fname, parent->fname) < 0)
				parent->left = p;
			else
				parent->right = p;
		}
	}

	int numchck(long long int d)
	{
		int c = 0;
		while (d>0) { c++; d /= 10; }
		if (c == 10) return 1;
		cout << "Number Invalid";
		return 0;
	}
	int mailchck(char a[])
	{
		int j = 0, i = 0;
		while (a[i] != '\0')
		{
			if (a[i] == '@') j++;
			i++;
		}
		if (j == 1) return 1;
		cout << "Email id Invalid";
		return 0;
	}
	void inorder()
	{
		inordertrav(root);
	}
	void inordertrav(contactNode *t)
	{

		if (t != NULL)
		{

			inordertrav(t->left);
			cout << "\nContact Details:\n";
			cout << "First name: " << t->fname << "\tLast name: " << t->lname << "\nPhone Number: " << t->number << "\tEmail id: " << t->email;
			inordertrav(t->right);
		}
	}
	contactNode * minValueNode(struct contactNode* l)
	{
		contactNode* current = l;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}

	contactNode* deleteNode(struct contactNode* root, char a[20])
	{

		if (root == NULL) return root;

		if (strcmp(a, root->fname)<0)
			root->left = deleteNode(root->left, a);

		else if (strcmp(a, root->fname)>0)
			root->right = deleteNode(root->right, a);

		else
		{

			if (root->left == NULL)
			{
				contactNode *temp = root->right;
				return temp;
			}
			else if (root->right == NULL)
			{
				contactNode *temp = root->left;
				return temp;
			}

			contactNode* temp = minValueNode(root->right);
			root->number = temp->number;
			strcpy(root->lname, temp->lname);
			strcpy(root->fname, temp->fname);
			strcpy(root->email, temp->email);
			root->right = deleteNode(root->right, temp->fname);
		}
		return root;
	}
	contactNode* edit(contactNode* root, char a[])
	{
		if (root == NULL) return root;

		if (strcmp(a, root->fname)<0)
			root->left = edit(root->left, a);

		else if (strcmp(a, root->fname)>0)
			root->right = edit(root->right, a);
		else
		{
			int x;
			cout << "Enter the data choice to edit:\n1.First name\t2.Last name\t3.Phone number\t4.Email id:\n";
			cin >> x;
			cout << "\nEnter the new value:";
			switch (x)
			{
			case 1:cin >> root->fname; break;
			case 2:cin >> root->lname; break;
			case 3:cin >> root->number; break;
			case 4:cin >> root->email; break;
			default: cout << "Value not modifed";
			}
		}
		return root;
	}
	void searc(contactNode* root, char a[])
	{
		if (root)
		{
			if (strcmp(a, root->fname)<0)
				searc(root->left, a);
			else if (strcmp(a, root->fname)>0)
				searc(root->right, a);
			else
			{
				cout << "\nContact Details:\n";
				cout << "First name: " << root->fname << "\tLast name: " << root->lname << "\nPhone Number: " << root->number << "\tEmail id: " << root->email;
			}
		}
	}

	void filee(contactNode* t)
	{
		if (t != NULL)
		{

			filee(t->left);
			outf << t->fname << " " << t->lname << " " << t->number << " " << t->email << "\n";
			filee(t->right);
		}
	}


	void writeExisting(){
		string num, line, fname, lname, email;
		myFileStream.open("Contacts.txt");
		if (!myFileStream.is_open()){
			cout << "File failed to open" << endl;
		}

		contactNode *tmp, *p, *parent = NULL;
		tmp = root;

		while (getline(myFileStream, line)){
			p = new contactNode();
			stringstream ss(line);
			getline(ss, fname, ' ');
			getline(ss, lname, ' ');
			getline(ss, num, ' ');
			p->number = atoll(num.c_str());
			getline(ss, email, ' ');

			strcpy(p->fname, fname.c_str());
			strcpy(p->lname, lname.c_str());
			strcpy(p->email, email.c_str());

			create2(p);

		}
		myFileStream.close();
	}

};
int main()
{
	tree q;
	char c, a[20];
	int x;
	q.writeExisting();
	cout << "\nCreation Successful\n";
	do{
		cout << "Enter the choice :\n1.Insert\n2.Delete\n3.Edit\n4.Search\n5.Print Phone book ?\n";
		cin >> x;
		switch (x)
		{
		case 1:q.create(); cout << "\nContact Insertion successful"; break;
		case 2:
			cout << "\nEnter the First name:";
			cin >> a;
			q.root = q.deleteNode(q.root, a);
			cout << "\n1 Contact deleted successfully";
			break;
		case 3:
			cout << "\nEnter the First name:";
			cin >> a;
			q.root = q.edit(q.root, a);
			cout << "\nChanges updated";
			break;
		case 4:
			cout << "\nEnter the First name:";
			cin >> a;
			q.searc(q.root, a); break;
		case 5:q.inorder(); break;
		default:cout << "\nOption Invalid";
		}
		outf.open("Contacts.txt", ios::trunc);
		q.filee(q.root);
		outf.close();
		cout << endl << "Continue?\n";
		cin >> c;
	} while (c == 'y');

	cout << "\n\nTHANK YOU";
	//outf.close();
	return 0;
}

