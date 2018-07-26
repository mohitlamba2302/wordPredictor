/* Data Structure Project on implementation of AutoCorrect or Predicting a word the user is willing to
enter using TRIES which is constructed from words in a source file */
#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct node //
{
	int words;
	node*child[26];
};

node* getnode()
{
	node*temp;
	temp = new node;
	temp->words=0;
	for( int i=0; i<26; i++ )
	{
		temp->child[i] = NULL;
	}
	return temp;
}

void join( node* root, string s )
{
	node* temp;
	temp = root;
	int f;
	for( int i=0; i<s.size(); i++ )
	{
		f = s[i] - 'a';
		if( temp->child[f] == NULL )
		{
			temp->child[f] = getnode();
		}
		temp = temp->child[f];

	}
	temp->words++;
}


int totalWords[26];

int DFS( node*root )
{
	int val = root->words;
	for( int i=0; i<26; i++ )
	{
		if( root->child[i]!=NULL )
		{
			val += DFS( root->child[i] );
		}
	}
	return val;
}


//backtracking

void suffixes(node* root, string& q, int& count)
 {
	if(count==3)
	{
		return;
	}
	int poss = 0;
	for(int i=0; i<26; i++)
	 {
		if(root->child[i]!= NULL)
		{
			poss++;
			q+=('a'+i);
			suffixes(root->child[i], q, count);
			q.erase(q.end()-1);
		}
	}

	if(!poss || root->words>0 )
	{
		cout<<q<<endl;
		count++;
	}
}

void predict( node* root, string s)
{
	node* temp;
	temp = root;
	int f;
	string q;

	for( int i=0; i<s.size(); i++ ) //Case when suffix of string is different from words in dictionary
	{
		f = s[i] - 'a';
		if( temp->child[f]==NULL )
		{
			cout<<s<<"a"<<endl;
			cout<<s<<"b"<<endl;
			cout<<s<<"c"<<endl;
			return;
		}
		temp=temp->child[f];
	}


	for(int i=0; i <26; i++)
	{
		if(temp->child[i]!=NULL)
		{
			totalWords[i] = DFS(temp->child[i]);
		}
	}
	vector< pair<int, int> > vec;

	for(int i=0; i<26; i++)
	 {
		node* ch = temp->child[i];
		if(ch!=NULL)
		{
			vec.push_back(make_pair(totalWords[i], i));
			//cout<<totalWords[i]<<" "<<i<<endl;
		}
	}
	sort(vec.rbegin(), vec.rend());

	int count = 0;
	for(int i=0; i<vec.size() && count<3; i++)
	{
		s += (vec[i].second+'a');
		suffixes(temp->child[vec[i].second], s, count);
		s.erase(s.end()-1);
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	fstream f;
	f.open("mohit.txt", ios::in|ios::out|ios::app);
	node* root;
	root = getnode();
	string s;

	while(f>>s)
	{
		join(root, s);
	}

    string d;
		cout<<"\nEnter A Word\n"<<endl;
		cin>>d;
	char ans='y';
	while(ans=='y')

	{
		predict(root,d);
		cout<<"\nDo you want to enter more words (y/n) "<<endl;
		cin>>ans;
		if(ans=='y')
        {
            cout<<"\nEnter A Word\n"<<endl;
            cin>>d;
        }
	}
	f.close();
	return 0;
}
